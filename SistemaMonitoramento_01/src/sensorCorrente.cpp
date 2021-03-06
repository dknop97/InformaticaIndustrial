#include "sensorCorrente.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;
vector<string> headersCorrente = {"Nome do Sensor", "ID do sensor", "Frequencia da rede", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};

SensorCorrente::SensorCorrente(const string& path) : 
    Sensor::Sensor(path, headersCorrente), fRede(0)
{
    // cout << "CONSTRUTOR SENSOR DE CORRENTE:" << this->file.is_open() << endl;
}

SensorCorrente::~SensorCorrente()
{
    // cout << "\n%% DESTRUTOR DO SENSOR DE CORRENTE\n" << endl;
    this->file.close();
}

bool SensorCorrente::lerDados()
{
    try
    {
        if(this->file.is_open())
        {
            // cout << "O ARQUIVO ESTA ABERTO E O ESTOU LENDO!!\n";
            string d; //string auxiliar par ao processamento do arquivo
            int n = 0; // parâmetro para leitura do cabeçalho
            int idxi; // indíce de determinado elemento
            int idxf; // indíce de determinado elemento

            getline(this->file, d); // o get line sempre pula o cursor para a próxima linha
            idxf = d.find("\n"); //pegando o titulo do arquivo, que também serve para identificar ele na leitura
            vector<string> dadosHeader(this->headers.size());
            this->titulo = d.substr(1, idxf-1);
            cout << "\n $ Lendo dados do " << this->titulo << endl;
            while (n < this->headers.size())
            {                
                getline(this->file, d); // pega a linha e a insere em d
                idxi = d.find(":");
                if(d.substr(1, idxi-1) == this->headers[n]) // 1 para retirar o % do início da linha
                {
                    // pegando o conteúdo após os ':' e indo até o fim da string da linha
                    dadosHeader[n] = d.substr((idxi+2), (d.length() - idxi));
                    n++;
                }
                else
                {
                    return false;                    
                }
            }
            this->nome                  = dadosHeader[0];
            this->id                    = dadosHeader[1];
            this->fRede                 = stoi(dadosHeader[2]); // stoi converte string em int
            this->numAmostrasSegundo    = stoi(dadosHeader[3]);
            this->horarioInicialColeta  = dadosHeader[4].substr(0, dadosHeader[4].length()-2);
            this->numAmostras           = stoi(dadosHeader[5]);
            this->fracSegundo = 1.0 / getNumAmostrasSegundo();

            getline(this->file, d); // lendo a linha do "%DadosInicio"
            // todos os dados estão em uma única linha
            // para os testes, ler apenas os 20 primeiros
            // for (int i = 0; i < 20; i++)
            for (int i = 0; i < this->numAmostras; i++)
            {
                getline(this->file, d, ','); // pega a linha e a insere em d
                double valor = stod(d);
                this->dados.push_back(valor); // faz a alocação dinâmica de m no vector dados
            }
        }
        else
        {
            cout << "O arquivo nao esta aberto!" << endl;
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "\n%% [ERRO] Arquivo corrompido. ID do erro: " << e.what() << '\n';
    }
    return true;
}

int SensorCorrente::getFreqRede()
{
    return this->fRede;
}

bool SensorCorrente::getDado(const int &posicao, double &dadoARetornar)
{    
    if (posicao == -1)
    {
        cout << "\n------------\n# [ERRO] A posicao do dado eh invalida (id do erro: -1).\n------------" << endl;
        return false;
    }
    else
    {
        dadoARetornar = this->dados[posicao];
        return true;  
    }
}

bool SensorCorrente::getCorrente(const string &horario, double &corrente)
{
    if (this->getDado(this->getPosicao(horario), corrente))
    {
        return true;  
    }
    else 
    {
        return false;
    }    
}

double SensorCorrente::getRMS(const string &horario)
{
    int N = numAmostrasSegundo/getFreqRede(); //Numero de amostras por ciclo de onda
    int posicao = getPosicao(horario);	
    
    return calcRMS(N , posicao);
}