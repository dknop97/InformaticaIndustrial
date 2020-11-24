import random
from kivy.uix.boxlayout     import BoxLayout
from popups                 import ModbusPopup, ScanPopup, DataGraphPopup, HistGraphPopup
from pyModbusTCP.client     import ModbusClient
from kivy.core.window       import Window
from threading              import Thread
from time                   import sleep
from datetime               import datetime
from timeseriesgraph        import TimeSeriesGraph
from bdhandler              import BDHandler
from kivy_garden.graph      import LinePlot

class MainWidget(BoxLayout):
    """
    Widget principal da aplicação
    """
    _updateThread = None
    _updateWidgets = True
    _tags = {} # referencias para os dados de campo
    _max_points = 20 # número inicial padrão de pontos visualizados no gráfico
    def __init__(self, **kwargs):
        """
        Construtor do widget principal
        """
        super().__init__()  # chamada do construtor da classe mãe, BoxLayout
        # Modbus
        self._scan_time     = kwargs.get('scan_time')
        self._serverIP      = kwargs.get('server_ip')
        self._serverPort    = kwargs.get('server_port')
        # Popups
        self._modbusPopup   = ModbusPopup(self._serverIP, self._serverPort)
        self._scanPopup     = ScanPopup(scantime=self._scan_time)
        # instanciamento do cliente Modbus
        self._modbusClient = ModbusClient(host=self._serverIP, port=self._serverPort)
        # outros atributos
        self._meas = {
            'timestamp': None, 
            'values': {}
        }
        for key, value in kwargs.get('modbus_addrs').items():
            plot_color = (random.random(), random.random(), random.random(), 1)
            # value[0] == addr, # value[1] == multiplicador, # value[2] == tabela(coil - 0/holding register - 1)
            self._tags[key] = {'addr': value[0], 'multi': value[1], 'tabela': value[2], 'un':value[3], 'color': plot_color}
        # para debugar os dados do modbus_addrs
        # for key in kwargs.get('modbus_addrs').keys():
        #     print(">> self._tags[",key,"]: ", self._tags[key])

        # O gráfico em tempo real está sendo apenas do Nível do tanque
        self._graph  = DataGraphPopup(self._max_points, self._tags['nivel']['color']) 
        self._hgraph = HistGraphPopup(tags=self._tags)

        self._db = BDHandler(kwargs.get('db_path'), self._tags)

    def startDataRead(self, ip, port):
        """
        Método utilizado apra a configuração do IP e PORTA do servidor MODBUS e
        inicializar uma thread para a leitura dos dados e atualização da interface gráfica
        """
        self._serverIP          = ip
        self._serverPort        = port
        self._modbusClient.host = self._serverIP
        self._modbusClient.port = self._serverPort

        try:
            Window.set_system_cursor("wait") #cursor de espera, para indicação ao usuário
            self._modbusClient.open() #iniciando conexão
            Window.set_system_cursor("arrow") #cursor normal, para indicação ao usuário
            if self._modbusClient.is_open():
                self._updateThread = Thread(target=self.updater)
                self._updateThread.start()
                self.ids.img_con.source = 'imgs/conectado.png'
                self._modbusPopup.dismiss()
            else:
                self._modbusPopup.setInfo("Falha na conexão com o servidor")
        except Exception as e:
            print("# Erro em startDataRead(): ", e.args)
    
    def updater(self):
        """
        Método que invoca as rotinas de leitura dos dados, atualização da interface e
        inserção dos dados no BD
        """
        try:
            while self._updateWidgets:
                #ler os dados MODBUS
                try:
                    self.readData()
                except Exception as e:
                    print("# Erro em updater readData(): ", e.args)
                #atualizar a interface
                try: 
                    self.updateGUI()
                except Exception as e:
                    print("# Erro em updater updateGUI(): ", e.args)
                #inserir os dados no BD
                try:
                    #passando _meas com os dados e _tags para acesso aos multiplicadores
                    self._db.insertData(self._meas, self._tags)
                except Exception as e:
                    print("# Erro em updater insertData()(): ", e.args)

                sleep(self._scan_time/1000)
        except Exception as e:
            self._modbusClient.close()
            print("# Erro em updater(): ", e.args)
    
    def readData(self):
        """
        Método para leitura dos dados por meio do protocolo MODBUS
        """
        self._meas['timestamp'] = datetime.now()
        for key, value in self._tags.items():
            # value['addr'] == addr, # value['multiplicador'] == multiplicador, # value['tabela'] == 0 (coil) ou 1 (holding register)
            if key == 'freq_des': # tag somente de escrita
                # print("self.ids.txt_freqDes.text: ", self.ids.txt_freqDes.text)
                self._meas['values'][key] = self.ids.txt_freqDes.text
            elif value['multi'] is not None:
                if value['tabela'] == 0: # coils...
                    self._meas['values'][key] = (self._modbusClient.read_coils(value['addr'], 1)[0])/value['multi']
                else: # holding registers
                    self._meas['values'][key] = (self._modbusClient.read_holding_registers(value['addr'], 1)[0])/value['multi']
            else:
                if value['tabela'] == 0: # coils...
                    self._meas['values'][key] = self._modbusClient.read_coils(value['addr'], 1)[0]
                else: # holding registers
                    self._meas['values'][key] = self._modbusClient.read_holding_registers(value['addr'], 1)[0]

    def updateGUI(self):
        """
        Método para atualização da GUI a partir dos dados lidos
        """
        # Atualização dos labels dos dados da planta
        for key, value in self._tags.items():
            if value['multi'] is not None:
                self.ids[key].text = key + ": " + str(self._meas['values'][key]) + value['un']
            else:
                self.ids[key].text = key + ": " + str(self._meas['values'][key])

        # Atualização do nível do tanque
        self.ids.lb_temp.size    = (self.ids.lb_temp.size[0], (self._meas['values']['nivel']*self.ids.termometro.size[1]/1000))
        self.ids['nivel_aux'].text = str(self._meas['values']['nivel']) + ' ' + self._tags['nivel']['un']
        
        # Atualização do Gráfico do Nível do tanque em tempo real
        self._graph.ids.graph.updateGraph((self._meas['timestamp'], self._meas['values']['nivel']), 0)        
        
    def stopRefresh(self):
        self._updateWidgets = False
    
    def getDataDB(self):
        """
        Método que coleta as informações da interface fornecedidas pelo usuário
        e requisita a busca no BD para apresentação no gráfico de dados históricos
        """
        try:
            init_t  = self.parseDTString(self._hgraph.ids.txt_init_time.text) 
            final_t = self.parseDTString(self._hgraph.ids.txt_final_time.text)
            cols = []
            for sensor in self._hgraph.ids.sensores.children:
                if sensor.ids.checkbox.active:
                    cols.append(sensor.id)
            if init_t is None or final_t is None or len(cols)==0:
                return

            cols.append('timestamp')

            dados = self._db.selectData(cols, init_t, final_t)
            if dados is None or len(dados['timestamp']) == 0:
                return

            self._hgraph.ids.graph.clearPlots()
            for key,value in dados.items():
                if key == 'timestamp':
                    continue
                p = LinePlot(line_width=1.5, color=self._tags[key]['color'])
                p.points = [(x, value[x]) for x in range(0, len(value))]
                self._hgraph.ids.graph.add_plot(p)
            self._hgraph.ids.graph.xmax = len(dados[cols[0]])
            self._hgraph.ids.graph.update_x_labels([datetime.strptime(x, "%Y-%m-%d %H:%M:%S.%f") for x in dados['timestamp']])
        except Exception as e:
            print ("# Erro em getDataDB(): ", e.args)

    def parseDTString(self, datetime_str):
        """
        Método que converte a string inserida pelo usuário apra o formato utilizado na 
        busca dos dados no BD
        """
        try:
            d = datetime.strptime(datetime_str, '%d/%m/%Y %H:%M:%S')
            return d.strftime("%Y-%m-%d %H:%M:%S")
        except Exception as e:
            print ("# Erro em parseDTString(): ", e.args)
    
    def habilitaAutoControl(self):
        """
        Método para acionamento do auto controle da planta
        """
        self._meas['values']['auto_control'] = 1
        self._modbusClient.write_single_coil(self._tags['auto_control']['addr'] , self._meas['values']['auto_control'])
    
    def desabilitaAutoControl(self):
        """
        Método para desacionamento do auto controle da planta
        """
        self._meas['values']['auto_control'] = 0
        self._modbusClient.write_single_coil(self._tags['auto_control']['addr'] , self._meas['values']['auto_control'])
    
    def ligarMotor(self):
        """
        Método para acionamento do motor
        """
        self._meas['values']['estado_mot'] = 1
        self._modbusClient.write_single_coil(self._tags['estado_mot']['addr'] , self._meas['values']['estado_mot'])

    def desligarMotor(self):
        """
        Método para desligamento do motor
        """
        self._meas['values']['estado_mot'] = 0
        self._modbusClient.write_single_coil(self._tags['estado_mot']['addr'] , self._meas['values']['estado_mot'])

    def acionaSolenoide(self):
        """
        Método para acionamento da válvula solenóide
        """
        self._meas['values']['solenoide'] = 1
        self._modbusClient.write_single_coil(self._tags['solenoide']['addr'] , self._meas['values']['solenoide'])
    
    def desacionaSolenoide(self):
        """
        Método para desacionamento da válvula solenóide
        """
        self._meas['values']['solenoide'] = 0
        self._modbusClient.write_single_coil(self._tags['solenoide']['addr'] , self._meas['values']['solenoide'])

    def setFreqDes(self, freq):
        """
        Método para configuração da frequência desejada pelo usuário para operação do motor
        """
        if freq: #se a string do campo texto do Text Input não vier vazia, fazemos...
            self._meas['values']['freq_des'] = int(freq)
            self._modbusClient.write_single_register(self._tags['freq_des']['addr'] , self._meas['values']['freq_des'])
        else:
            return
