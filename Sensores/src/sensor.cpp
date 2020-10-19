#include "sensor.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string.h>

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
    cout << "%% DESTRUTOR DO SENSOR\n" << endl;
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

// bool Sensor::getDado(const string& horario, double& dado)
// {
//     for (auto it = this->dados.begin(); it != this->dados.end(); it++)
//     {
//         if (it->horario == horario)
//         {
//             dado = it->valor;
//             return true;
//         }
//     }
//     return false;
// }