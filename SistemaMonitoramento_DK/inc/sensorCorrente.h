#ifndef SENSOR_CORRENTE_H
#define SENSOR_CORRENTE_H

#include "sensor.h"
#include <vector>
#include <fstream>

using namespace std;

// implementando herança
class SensorCorrente : public Sensor
{
private:
    int fRede;
public:
    SensorCorrente(const string &);
    ~SensorCorrente();
    bool lerDados();
    void imprimeDados();
    int getFreqRede();
    bool getCorrente(const string &, double &); // string com o horário desejado e double com a corrente a ser retornada
    bool getDado(const int &, double &);
};

#endif