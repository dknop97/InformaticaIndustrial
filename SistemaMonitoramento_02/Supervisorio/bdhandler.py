import sqlite3
from   threading import Lock

class BDHandler():
    """
    Classe apra a manipulação do BD
    """
    def __init__(self, dbpath, tags, tablename='datatable'):
        """
        Construtor
        """
        self._dbpath = dbpath
        self._tablename = tablename
        self._con = sqlite3.connect(self._dbpath, check_same_thread=False)
        self._cursor = self._con.cursor()
        self._col_names = tags.keys()
        self._lock = Lock()
        self.createTable()

    def __del__(self):
        """
        Destrutor
        """
        self._con.close()

    def createTable(self):
        """
        Método que cria a tabela para armazenamento dos dados, caso ela não exista
        """
        try:
            # SQL QUERY
            sql_str = f"""
            CREATE TABLE IF NOT EXISTS {self._tablename} (
                id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                timestamp TEXT NOT NULL,
            """
            # Aribuição de REAL à cada item
            for n in self._col_names:
                sql_str += f'{n} REAL,'
            # Retirando a última vírgula concatenada pelo for
            sql_str = sql_str[:-1]
            # fechando a SQL QUERY
            sql_str += ');'
            # Protegendo a sessão crítica de operação com o Lock
            self._lock.acquire()
            # Preparando a query
            self._cursor.execute(sql_str)
            # Implementado a SQL QUERY no BD
            self._con.commit()
            # Liberando a zona de operação com o Lock
            self._lock.release()
        except Exception as e:
            print("# Erro em createTable(): ", e.args)
    
    def insertData(self, data, tags):
        """
        Método para inserção do dados no BD
        :param data = meas
        """
        try:
            # Protegendo a sessão crítica de operação com o Lock
            self._lock.acquire()
            timestamp   = str(data['timestamp'])
            str_cols    = 'timestamp,' + ','.join(data['values'].keys())
            # print(data['values'].keys())
            # print(">> str_cols: ", str_cols)
            str_values = f"'{timestamp}'"
            for key in data['values'].keys():
                # print("> tags[", key, "]['multi']: ", tags[key]['multi'])
                if tags[key]['multi'] is not None:
                    # >Na escrita deve-se multiplicar o valor a ser escrito pelo multiplicador
                    # antes de realizar o envio para o CLP.
                    str_values  += ',' + (str(data['values'][key]*tags[key]['multi']))
                else:
                    str_values  += ',' + str(data['values'][key])
            # str_values  = f"'{timestamp}'," + ','.join([str(data['values'][k]) for k in data['values'].keys()])
            # print("> str_values: ", str_values)
            sql_str = f'INSERT INTO {self._tablename} ({str_cols}) VALUES ({str_values});'
            # Preparando a query
            self._cursor.execute(sql_str)
            # Implementado a SQL QUERY no BD
            # self._con.commit()
        except Exception as e:
            print("# Erro em insertData(): ", e.args)
        finally:
            # Liberando a zona de operação com o Lock
            self._lock.release()
    
    def selectData(self, cols, init_t, final_t):
        """
        Método que realiza da busca no BD entre 2 horários especificados
        """
        try:
            # Protegendo a sessão crítica de operação com o Lock
            self._lock.acquire()
            sql_str = f"SELECT {','.join(cols)} FROM {self._tablename} WHERE timestamp BETWEEN '{init_t}' AND '{final_t}'"
            # Preparando a query
            self._cursor.execute(sql_str)
            # dict para armazenar os dados obtidos na consulta do BD
            dados = dict((sensor, []) for sensor in cols)
            # atribuição de valores ao dicionário de dados da consulta
            for linha in self._cursor.fetchall():
                for d in range(0, len(linha)):
                    dados[cols[d]].append(linha[d])
            return dados
        except Exception as e:
            print("# Erro em insertData(): ", e.args)
        finally:
            # Liberando a zona de operação com o Lock
            self._lock.release()