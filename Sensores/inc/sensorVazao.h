#ifndef SENSOR_VAZAO_H
#define SENSOR_VAZAO_H

#include "sensor.h"
#include <vector>
#include <fstream>
#include "medicao.h"
#include <string.h>

using namespace std;

// implementando herança
class SensorVazao : public Sensor
{
private:
    string unidade;
public:
    SensorVazao(const string &, const vector<string> &);
    ~SensorVazao();
    bool lerDados();
    void imprimeDados();
    string getUnidade();
};

#endif