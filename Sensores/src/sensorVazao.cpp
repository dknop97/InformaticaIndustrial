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
            // cout << this->titulo << endl;
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

            Medicao m;
            getline(this->file, d); // lendo a linha do "%DadosInicio"
            // todos os dados estão em uma única linha
            idxi = 0;
            // for (int i = 0; i < this->numAmostras; i++)
            // para os testes, ler apenas os 20 primeiros
            for (int i = 0; i < 20; i++)
            {
                getline(this->file, d, ','); // pega a linha e a insere em d
                m.valor = stod(d);
                this->dados.push_back(m); // faz a alocação dinâmica de m no vector dados
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

void SensorVazao::imprimeDados()
{
    cout << "> "<< this->getTitulo() << endl;
    cout << " >> Nome: " << this->getNome()<<endl;
    cout << " >> ID: " << this->getId()<<endl;
    cout << " >> Unidade das medicoes: " << this->getUnidade() <<endl;
    cout << " >> Numero de amostras por segundo: " << this->getNumAmostrasSegundo()<<endl;
    cout << " >> Horario inicio da coleta: " << this->getHorarioInicialColeta() << " h"<< endl;
    cout << " >> Total de amostras: " << this->getNumAmostras() << endl;
    
    // // para os testes, imprimir apenas os 20 primeiros
    // for (int count = 0; count < 20; count++)
    // {
    //     cout << "Valor " << count << ": " << this->dados[count].valor << endl;
    // }
    cout << " >> Valores: " << endl;
    // identificar a unidade conforme o tipo de dado
    for (auto it = this->dados.begin(); it != this->dados.end(); it++)
    {
        cout << "  >>> " << it->valor << " " << getUnidade() << endl;
    }
}

string SensorVazao::getUnidade()
{
    return this->unidade;
}