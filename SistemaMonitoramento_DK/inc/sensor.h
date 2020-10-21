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
    string horarioFinalColeta;
    double fracSegundo;
    int numAmostrasSegundo;
    int numAmostras;
    ifstream file;

public:
    Sensor(const string &, const vector<string> &);
    ~Sensor();
    bool abrirArquivo(const string &);
    virtual bool lerDados() = 0;  // classe abstrata
    int getPosicao(const string &); // getPosicao() retorna a posição do dado buscado dentro do vetor de valores, baseado no horário inicial de coleta e no horário buscado pelo usuário
    int getNumAmostrasSegundo();
    int getNumAmostras();
    int horaParaSegundo(const string &);
    string getTitulo();
    string getNome();
    string getId();
    string getHorarioInicialColeta();
    string getHorarioFinalColeta();
    string horaParaString(int &);
    // virtual void imprimeDados() = 0; // classe abstrata
};

#endif