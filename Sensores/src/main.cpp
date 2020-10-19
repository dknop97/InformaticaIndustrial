#include <iostream>
#include "sensorCorrente.h"
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
    SensorTensao ST1(pathSensorTensao1);
    // SensorTensao ST2(pathSensorTensao2);
    SensorVazao SV1(pathSensorVazao1);
    // SensorVazao SV2(pathSensorVazao2);
    
    // SV1.lerDados();
    SC1.lerDados();
    // ST1.lerDados();
    double dadoRetornado;
    // SV1.getVazao("18:19:01", dadoRetornado);
    // ST1.getTensao("18:09:00", dadoRetornado);
    SC1.getCorrente("18:09:01", dadoRetornado);
    cout << ">> Dado retornado: " << dadoRetornado << endl;
    // int posicao = SV1.getPosicao("18:09:00");
    // if (posicao != -1)
    // {
    //     double dadoRetornado;
    //     SV1.getDado(posicao, dadoRetornado);
    //     cout << ">> Dado retornado: " << dadoRetornado << endl;
    // }
    // else
    // {
    //     cout << "# Houve um erro na obtencao da posicao do dado.\n" << endl;
    // }
    // SV1.imprimeDados();
    return 0;
}