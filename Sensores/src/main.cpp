#include <iostream>
#include "sensorcorrente.h"
#include "sensorTensao.h"
#include "sensorVazao.h"

#include <vector>

using namespace std;

int main()
{
    // determinação manual dos cabeçalhos esperados para identificação dos dados no arquivo
    vector<string> headersCorrenteTensao = {"Nome do Sensor", "ID do sensor", "Frequencia da rede", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};
    vector<string> headersVazao = {"Nome do Sensor", "ID do sensor", "Unidade das medicoes", "Numero de amostras por segundo", "Horario inicio da coleta", "Total de Amostras"};
    
    // instanciamento do objeto da classe SensorVazao
    
    string pathSensorCorrente1  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorCorrente1.dat";
    string pathSensorCorrente2  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorCorrente2.dat";
    string pathSensorTensao1    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorTensao1.dat";
    string pathSensorTensao2    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorTensao2.dat";
    string pathSensorVazao1     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorVazao1.dat";
    string pathSensorVazao2     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\Testes\\Sensores\\dados\\SensorVazao2.dat";
    

    // SensorCorrente SC1(pathSensorCorrente1, headersCorrenteTensao);
    // SensorCorrente SC2(pathSensorCorrente1, headersCorrenteTensao);

    // SensorTensao ST1(pathSensorTensao1, headersCorrenteTensao);
    // SensorTensao ST2(pathSensorCorrente1, headersCorrenteTensao);

    SensorVazao SV1(pathSensorVazao1, headersVazao);
    // SensorVazao SV2(pathSensorCorrente1, headersVazao);

    SV1.lerDados();
    SV1.imprimeDados();
    return 0;
}