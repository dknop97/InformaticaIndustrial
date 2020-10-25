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
    double calcularPotenciaAparente(const string& HoraDesejada);
    double calculaFP(const string& horaDesejada);
    double calculaEnergia(const string& horaDesejada);
    double getPotAtiva(const string& HoraDesejada);
};


#endif