#include "sensorVazao.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string.h>
#include <iomanip>

using namespace std;

vector<string> headersVazao = {"Nome do Sensor", "ID do sensor", "Unidade das medicoes", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};

SensorVazao::SensorVazao(const string& path) : 
    Sensor::Sensor(path, headersVazao), unidade("desconhecida")
{
    // cout << "CONSTRUTOR SENSOR DE VAZAO:" << this->file.is_open() << endl;
}

SensorVazao::~SensorVazao()
{
    // cout << "\n%% DESTRUTOR DO SENSOR DE VAZAO\n" << endl;
    this->file.close();
}

bool SensorVazao::lerDados()
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
            // cout << "LINHA SENDO ANALISADA: \n" << d << endl;
            this->titulo = d.substr(1, idxf-1);
            cout << "\n $ Lendo dados do " << this->titulo << endl;
            while (n < this->headers.size())
            {                
                getline(this->file, d); // pega a linha e a insere em d
                // cout << "LINHA SENDO ANALISADA: \n" << d << endl;
                idxi = d.find(":");
                // dados os cabeçalhos esperados por algum outro meio, podemos compará-los aos do arquivo
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
            this->unidade               = dadosHeader[2]; 
            this->numAmostrasSegundo    = stoi(dadosHeader[3]); // stoi converte string em int
            this->horarioInicialColeta  = dadosHeader[4].substr(0, dadosHeader[4].length()-2);
            this->numAmostras           = stoi(dadosHeader[5]);
            this->fracSegundo = 1.0 / getNumAmostrasSegundo();

            getline(this->file, d); // lendo a linha do "%DadosInicio"
            // todos os dados estão em uma única linha
            for (int i = 0; i < this->numAmostras; i++)
            {
                getline(this->file, d, ','); // pega a linha e a insere em d
                double valor = stod(d);
                this->dados.push_back(valor); // faz a alocação dinâmica de m no vector dados
            }
        }
        else
        {
            cout << "O arquivo Nao esta aberto!" << endl;
            return false;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "\n%% [ERRO] Arquivo corrompido. ID do erro: " << e.what() << '\n';
    }
    return true;
}

string SensorVazao::getUnidade()
{
    return this->unidade;
}

bool SensorVazao::getDado(const int &posicao, double &dadoARetornar)
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

bool SensorVazao::getVazao(const string &horario, double &vazao)
{
    if (this->getDado(this->getPosicao(horario), vazao))
    {
        return true;  
    }
    else 
    {
        return false;
    }     
}