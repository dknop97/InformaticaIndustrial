""" 
% Grupo composto pelos alunos:
	- David Nery Henriques Knop - 201669038A - Turma A
	- Guilherme de Souza Barbosa Evangelista Coelho - 201765198AI - Turma B
  	- Thiago Duque Saber de Lima - 201665230AI - Turma B
% Data: 27/11/2020
% Enunciado: Trabalho 02 - Sistema de Supervisório em Python
"""
from kivy.app           import App
from mainwidget         import MainWidget
from kivy.lang.builder  import Builder

class MainApp(App):
    """
    Classe com o aplicativo
    """
    def build(self):
        """
        Construir o aplicativo
        """
        # tags e endereços dos dados do MODBUS 
        modbus_addrs = {
            # 'tag'         : [endereço, multiplicador, tabela¹, unidade]
            # ¹tabela: 0 = coil; 1 - holding register
            'estado_mot'    : [800,  None,  0,  None],
            'freq_des'      : [799,  1,  1,  'Hz'],
            't_part'        : [798,  10  ,  1,  's'],
            'auto_control'  : [1000, None,  0,  None],
            'freq_mot'      : [800,  10,    1,  'Hz'],
            'tensao'        : [801,  1,     1,  'V'],
            'rotacao'       : [803,  1,     1,  'RPM'],
            'pot_entrada'   : [804,  10,    1,  'W'],
            'corrente'      : [805,  100,   1,  'A (RMS)'],
            'temp_estator'  : [806,  10,    1,  'ºC'],
            'vz_entrada'    : [807,  100,   1,  'L/s'],
            'nivel'         : [808,  10,    1,  'L'],
            'nivel_h'       : [809,  None,  0,  None],
            'nivel_l'       : [810,  None,  0,  None],
            'solenoide'     : [801,  None,  0,  None]
        }
        db_path = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_2\\DK\\Supervisorio\\db\\scada.db"
        self._widget = MainWidget(scan_time=1000, server_ip='127.0.0.1', server_port=502, modbus_addrs=modbus_addrs, db_path = db_path)
        return self._widget
    
    def on_stop(self):
        """
        Método executado quando a aplicação é fechada
        """
        self._widget.stopRefresh()

if __name__ == '__main__':
    Builder.load_string(open("mainwidget.kv", encoding="utf-8").read(), rulesonly=True)
    Builder.load_string(open("popups.kv",     encoding="utf-8").read(), rulesonly=True)
    MainApp().run()
