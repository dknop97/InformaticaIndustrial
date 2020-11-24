from kivy.uix.popup     import Popup
from kivy.uix.label     import Label
from kivy_garden.graph  import LinePlot
from kivy.uix.boxlayout import BoxLayout

class ModbusPopup(Popup):
    """
    Popup da configuração do protocolo MODBUS
    """
    _info_lb = None
    def __init__(self, server_ip, server_port, **kwargs): #kwargs: keywords arguments: permite receber mais argumentos sem tê-los definidos
        """
        Construtor da classe ModbusPopup
        """
        super().__init__(**kwargs)
        self.ids.txt_ip.text    = str(server_ip)
        self.ids.txt_port.text  = str(server_port)
    
    def setInfo(self, message):
        """
        Método para criação de um Label na janela do popups para informar algo ao usuário
        """
        self._info_lb = Label(text=message)
        self.ids.layout.add_widget(self._info_lb)
    
    def clearInfo(self):
        """
        Método para remoção do Label informativo para o usuário, criado pela setInfo
        """
        if self._info_lb is not None:
            self.ids.layout.remove_widget(self._info_lb)

class ScanPopup(Popup):
    """
    Popup da configuração do tempo de varredura
    """
    def __init__(self, scantime, **kwargs): #kwargs: keywords arguments: permite receber mais argumentos sem tê-los definidos
        """
        Construtor da classe ScanPopup
        """
        super().__init__(**kwargs)
        self.ids.txt_st.text = str(scantime)

class DataGraphPopup(Popup):
    def __init__(self, xmax, plot_color, **kwargs):
        super().__init__(**kwargs)
        self.plot = LinePlot(line_width=1.5, color=plot_color)
        self.ids.graph.add_plot(self.plot)
        self.ids.graph.xmax = xmax

class LabeledCheckBoxDataGraph(BoxLayout):
    pass

class HistGraphPopup(Popup):
    """
    Gráfico com dados históricos
    """
    def __init__(self, **kwargs):
        """
        Construtor
        """
        super().__init__()
        for key,value in kwargs.get('tags').items():
            if key == 'freq_des':
                continue
            cb = LabeledCheckBoxHistGraph()
            cb.ids.label.text = key
            cb.ids.label.color = value['color']
            cb.id = key
            cb.orientation = 'vertical'
            self.ids.sensores.add_widget(cb)

class LabeledCheckBoxHistGraph(BoxLayout):
    pass