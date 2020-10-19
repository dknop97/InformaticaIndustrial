#ifndef SENSOR_CORRENTE_H
#define SENSOR_CORRENTE_H

#include "sensor.h"
#include <vector>
#include <fstream>
#include "medicao.h"

using namespace std;

// implementando herança
class SensorCorrente : public Sensor
{
private:
    int fRede;
    // ifstream file;
public:
    SensorCorrente(const string &, const vector<string> &);
    ~SensorCorrente();
    bool lerDados();
    void imprimeDados();
    int getFreqRede();
    // bool getDado(const string &, double &);
};

#endif