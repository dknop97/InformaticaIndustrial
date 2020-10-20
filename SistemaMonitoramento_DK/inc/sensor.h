#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <fstream>

using namespace std;

class Sensor
{
protected:
    vector<double> dados;
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
    int getPosicao(const string &); // getPosicao() retorna a posição do dado buscado dentro do vetor de valores, baseado no horário inicial de coleta e no horário buscado pelo usuário
    int getNumAmostrasSegundo();
    int getNumAmostras();
    double horaParaSegundo(const string &);
};

#endif