#include "interface.h"
#include "sensor.h"
#include "sensorCorrente.h"
#include <iostream>

using namespace std;

int main()
{
    // string pathSensorCorrente1  = "C:\\Users\\Guilherme\\Documents\\InfoIndustrial\\SistemaMonitoramento\\dados\\SensorCorrente1.dat";
    // SensorCorrente SC1(pathSensorCorrente1);
    // SC1.lerDados();
    // double rms = SC1.calcRMS(10,23099);
    
    // cout <<"Valor RMS" << rms << endl;
    
    // chamada da função de interface, passando os objetos dos sensores para uso posterior
    IHM();
    // string a = "123";
    // string b = "456";
    // string c = a + b;
    // cout << c << endl;
    // a = a[2];
    // int d = stoi(a);
    // cout << d << endl;

    return 0;
}
