#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <fstream>
#include "medicao.h"

using namespace std;

class Sensor
{
protected:
    vector<Medicao> dados;
    vector<string> headers;
    string titulo;
    string nome;
    string id;
    string horarioInicialColeta;
    int numAmostrasSegundo;
    int numAmostras;
    ifstream file;

public:
    Sensor(const string &, const vector<string> &);
    ~Sensor();
    bool abrirArquivo(const string &);
    virtual bool lerDados() = 0;  // classe abstrata
    virtual void imprimeDados() = 0; // classe abstrata
    string getTitulo();
    string getNome();
    string getId();
    string getHorarioInicialColeta();
    // getPosicao() retorna a posição do dado buscado dentro do vetor de valores, baseado no horário inicial de coleta e no horário buscado pelo usuário
    int getPosicao(const string&); 
    int getNumAmostrasSegundo();
    int getNumAmostras();
    // bool getDado(const string &, double &);
};

#endif