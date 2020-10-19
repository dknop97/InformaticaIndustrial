#ifndef SENSOR_VAZAO_H
#define SENSOR_VAZAO_H

#include "sensor.h"
#include <vector>
#include <fstream>
#include <string.h>

using namespace std;

// implementando herança
class SensorVazao : public Sensor
{
private:
    string unidade;
public:
    SensorVazao(const string &);
    ~SensorVazao();
    bool lerDados();
    bool getDado(const int &, double &); //int da posicao à ser buscada dentro do vector de dados e double para o valor à ser preenchido com o valor referente presente na posição do vector
    bool getVazao(const string &, double &); // string com o horário que se deseja saber a vazão e um double com a vazão retornada
    void imprimeDados();
    string getUnidade();
};

#endif