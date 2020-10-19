#include "sensor.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <math.h>
#include <string.h>
#include <iomanip>

using namespace std;

Sensor::Sensor(const string& path, const vector<string>& h) : 
    nome("desconhecido"), id("desconhecido"),horarioInicialColeta("desconhecido"), numAmostrasSegundo(0) , numAmostras(0)
{
    // cout << "%% CONSTRUTOR DO SENSOR\n" << endl;
    this->headers.assign(h.begin(), h.end());
    this->abrirArquivo(path);
    // cout << "CONSTRUTOR SENSOR:" << this->file.is_open() << endl;
}

Sensor::~Sensor()
{
    // cout << "%% DESTRUTOR DO SENSOR\n" << endl;
    this->file.close();
}

bool Sensor::abrirArquivo(const string& path)   
{
    try
    {
        // cout << "ABRIR ARQUIVO - SENSOR" << endl;
        this->file.open(path); // abrindo no modo padrão, leitura
        // cout << "abrirArquivo SENSOR:" << this->file.is_open() << endl;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return false;    
}

string Sensor::getTitulo()
{
    return this->titulo;
}


string Sensor::getNome()
{
    return this->nome;
}

string Sensor::getId()
{
    return this->id;
}

string Sensor::getHorarioInicialColeta()
{
    return this->horarioInicialColeta;
}

int Sensor::getNumAmostrasSegundo()
{
    return this->numAmostrasSegundo;
}

int Sensor::getNumAmostras()
{
    return this->numAmostras;
}

double horaParaSegundo(const string& horarioDoUsuario)
{
    // cout << "Horario passado pelo usuario: " << horarioDoUsuario << endl;
    // 01234567
    // 19:55:44
    int idx = horarioDoUsuario.find(':'); // retorna idx = 2
    // transformando hora em segundos
    double horarioEmSegundos = (stof(horarioDoUsuario.substr(0, idx)) * 3600);
    // transformando minuto em segundos
    horarioEmSegundos += (stof(horarioDoUsuario.substr(idx + 1, idx + 2)) * 60);
    horarioEmSegundos += (stof(horarioDoUsuario.substr(idx + 4, idx + 5)));
    // cout << setprecision(4) << fixed;  // para exibição com casas decimais
    // cout << setprecision(4) << "hora em segundos: " << horarioEmSegundos << fixed << endl;
    return horarioEmSegundos;  
}

int Sensor::getPosicao(const string& horarioDoUsuario)
{
    // dado o horário desejado pelo usuário, procurar o índice referente nos dados para
    //      acionar o loop até esse índice, baseado no numero de amostras pro segundo
    cout << "> Horario passado pelo usuario: " << horarioDoUsuario << endl;
    double horarioUsuarioEmSegundos = horaParaSegundo(horarioDoUsuario);
    cout << setprecision(4) << "> Horario passado pelo usuario em segundos: " << horarioUsuarioEmSegundos << fixed << endl;

    // obter fração de segundo referente à cada amostra= 1s / numAmostrasSegundo
    double fracSegundo = 1.0 / getNumAmostrasSegundo();
    cout << setprecision(6);  // para exibição com casas decimais
    cout << "> Num amostras por segundo: " << this->getNumAmostrasSegundo() << endl;
    cout << "> Fracao de segundos entre amostras: " << fracSegundo << endl;
    cout << "> Horario inicio da coleta: " << this->getHorarioInicialColeta() << endl;
    double horarioInicialEmSegundos = horaParaSegundo(this->getHorarioInicialColeta());
    cout << "> Horario inicio da coleta em segundos: " << horarioInicialEmSegundos << endl;
    // calcular agora o indice, posicao, do valor referente ao horário passado pelo usuario
    int posicao = (horarioUsuarioEmSegundos - horarioInicialEmSegundos) / fracSegundo;
    cout << "> Posicao: " << posicao << endl;
    

    if (horarioUsuarioEmSegundos < horarioInicialEmSegundos)
    {
        cout << "\n------------# [ERRO] O horario especificado eh invalido: anterior ao inicio da coleta de dados.\n------------" << endl;
    }
    else if (posicao > this->numAmostras)
    {
        cout << "\n------------# [ERRO] O horario especificado eh invalido: posterior ao fim da coleta de dados.\n------------" << endl;
    }
    else 
    {
        return posicao;
    }
    return -1; // código de erro da busca; especificar na documentação depois
}