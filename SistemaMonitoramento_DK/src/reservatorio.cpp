#include "reservatorio.h"
#include "sensorVazao.h"
#include <iostream>

double calculaVolume(const string &horario, SensorVazao &SVEntrada, SensorVazao &SVSaida)
{
    // cout << "% Calculando o volume no tanque para o horario " << horario << "h.\n"; // só para debugar no terminal
    int posicao = SVEntrada.getPosicao(horario); // pegando a posição do dado procurado dentro do vetor de dados; ok!
    
    // cout << "SVEntrada = " << SVEntrada.getNome() << endl; // usado só para debugar se o objeto está referenciado corretamente
    // cout << "> Posicao: " << posicao << endl; // ok!
    double volume = 0.0;
    double volumeAux = 0.0;
    for (int i = 0; i < posicao; i++)
    {
        // cout << "> SVEntrada.getDado(i,volumeAux): " << SVEntrada.getDado(i,volumeAux) << endl;
        // cout << "> SVSaida.getDado(i,volumeAux)  : " << SVSaida.getDado(i,volumeAux) << endl << endl;;
        SVEntrada.getDado(i,volumeAux); // obtém a vazão de entrada
        volume += volumeAux; // soma a vazão de entrada
        SVSaida.getDado(i,volumeAux); // obtém a vazão de saída
        volume -= (volumeAux * 1000); // subtrai a vazão de saída
    }
    // o volume até o horario é dado por (VazaoEntrada - VazaoSaida)*(1segundo) do instante inicial até o horario desejado
    return volume; // ok!
}
