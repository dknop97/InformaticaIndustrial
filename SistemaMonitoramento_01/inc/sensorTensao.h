#ifndef SENSOR_TENSAO_H
#define SENSOR_TENSAO_H

#include "sensor.h"
#include <vector>
#include <fstream>

using namespace std;

// implementando herança
class SensorTensao : public Sensor
{
private:
    int fRede; 
public:
    SensorTensao(const string &);
    ~SensorTensao();
    bool lerDados();
    int getFreqRede();
    double getTensao(const string &, double &); // string com o horário desejado e double com a tensão a ser retornada
    bool getDado(const int &, double &);
    double getRMS(const string &);//  chama o calcula RMS para o horario especifico
};

#endif