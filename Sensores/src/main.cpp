#include <iostream>
#include "sensorcorrente.h"
#include "sensorTensao.h"
#include "sensorVazao.h"
#include <vector>

using namespace std;

int main()
{
    string pathSensorCorrente1  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorCorrente1.dat";
    string pathSensorCorrente2  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorCorrente2.dat";
    string pathSensorTensao1    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorTensao1.dat";
    string pathSensorTensao2    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorTensao2.dat";
    string pathSensorVazao1     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorVazao1.dat";
    string pathSensorVazao2     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorVazao2.dat";
    
    // instanciamento dos objetos das classes
    SensorCorrente SC1(pathSensorCorrente1);
    // SensorCorrente SC2(pathSensorCorrente1);
    // SensorTensao ST1(pathSensorTensao1);
    // SensorTensao ST2(pathSensorTensao2);
    // SensorVazao SV1(pathSensorVazao1);
    // SensorVazao SV2(pathSensorVazao2);
    
    SC1.lerDados();
    SC1.getPosicao("18:09:55");
    // SV1.imprimeDados();
    return 0;
}