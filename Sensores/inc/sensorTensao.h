#ifndef SENSOR_TENSAO_H
#define SENSOR_TENSAO_H

#include "sensor.h"
#include <vector>
#include <fstream>
#include "medicao.h"

using namespace std;

// implementando herança
class SensorTensao : public Sensor
{
private:
    int fRede;
public:
    SensorTensao(const string &, const vector<string> &);
    ~SensorTensao();
    bool lerDados();
    void imprimeDados();
    int getFreqRede();
    // bool getDado(const string &, double &);
};

#endif