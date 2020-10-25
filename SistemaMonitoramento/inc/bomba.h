#ifndef BOMBA_H
#define BOMBA_H

#include "sensor.h"
#include "sensorVazao.h"
#include "sensorTensao.h"  	
#include "sensorCorrente.h"  	

class Bomba
{
public:
    Bomba();
    ~Bomba();
    SensorTensao* sensorTensao;
    SensorCorrente* sensorCorrente;
    void setSensorTensao(SensorTensao&);
    void setSensorCorrente(SensorCorrente&);
    double calcularCorrenteRMS(const string&);
    double calcularTensaoRMS(const string&);
    double calcularPotenciaAtiva(int, int);
    double calcularPotenciaAparente(const string&);
    double calculaFP(const string&);
    double calculaEnergia(const string&, const string&);
    double getPotAtiva(const string&);
};


#endif