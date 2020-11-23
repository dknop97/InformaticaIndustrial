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
            # self._tags[key] = {'addr': value, 'color': plot_color}
            # value[0] == addr, # value[1] == multiplicador, # value[2] == tabela(coil - 0/holding register - 1)
            self._tags[key] = {'addr': value[0], 'multi': value[1], 'tabela': value[2], 'un':value[3], 'color': plot_color}
        
        for key in kwargs.get('modbus_addrs').keys():
            print(">> self._tags[",key,"]: ", self._tags[key])
        
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
                    self._db.insertData(self._meas)
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
        # self._meas['values']['estado_mot'] = self._modbusClient.read_holding_registers(800, 1)[0]
        for key, value in self._tags.items():
            # value['addr'] == addr, # value['multiplicador'] == multiplicador, # value['tabela'] == 0 (coil) ou 1 (holding register)
            if key == 'freq_des': # tag somente de escrita
                continue # tem que ver como usar essa tag
            elif value['tabela'] == 0: # coils...
                self._meas['values'][key] = self._modbusClient.read_coils(value['addr'], 1)[0]
            else: # holding registers
                self._meas['values'][key] = self._modbusClient.read_holding_registers(value['addr'], 1)[0]

    def updateGUI(self):
        """
        Método para atualização da GUI a partir dos dados lidos
        """
        # Atualização dos labels dos dados da planta
        # self.ids.estado_mot.text = str(self._meas['values']['estado_mot'])
        for key, value in self._tags.items():
            if key == 'freq_des':
                continue
            if value['multi'] is not None:
                self.ids[key].text = key + ": " + str((self._meas['values'][key] * value['multi'])) + value['un']
            else:
                self.ids[key].text = key + ": " + str(self._meas['values'][key])
                
        
        # Atualização do nível do tanque
        self.ids.lb_temp.size = (self.ids.lb_temp.size[0], ((self._meas['values']['nivel']/450)*self.ids.termometro.size[1]))

        # Atualização dos Gráficos em tempo real
        # for key in self._tags.keys():
        # self._graph.ids.graph.updateGraph((self._meas['timestamp'], self._meas['values']['nivel']), 0)

    def stopRefresh(self):
        self._updateWidgets = False
    
    def getDataDB(self):
        """
        Método que coleta as informações da interface fornecedidas pelo usuário
        e requisita a busca no BD
        """
        try:
            init_t = self.parseDTString(self._hgraph.ids.txt_init_time.text) 
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