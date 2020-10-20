#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "sensorCorrente.h"
#include "sensorTensao.h"
#include "sensorVazao.h"

using namespace std;

void monitorarBombas();

void monitorarReservatorio();

// void Interface(SensorCorrente * SC1, SensorCorrente * SC2, SensorTensao * ST1, SensorTensao * ST2, SensorVazao * SV1, SensorVazao * SV2);
// void Interface(SensorCorrente &SC1, SensorCorrente &SC2, SensorTensao &ST1, SensorTensao &ST2, SensorVazao &SV1, SensorVazao &SV2);
// void Interface(SensorCorrente SC1, SensorCorrente SC2, SensorTensao ST1, SensorTensao ST2, SensorVazao SV1, SensorVazao SV2);
void Interface();

#endif