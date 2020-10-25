#include <iostream>
#include <string>

#include "bomba.h"
#include "sensorCorrente.h"
#include "sensorTensao.h"
#include <math.h>
Bomba :: Bomba()
{

}
Bomba :: ~Bomba()
{
    // cout << "\n%% DESTRUTOR DA BOMBA\n" << endl;
}
void Bomba::setSensorCorrente(SensorCorrente &SC)
{
    this->sensorCorrente = &SC;
}

void Bomba::setSensorTensao(SensorTensao &ST)
{
    this-> sensorTensao = &ST;
}

double Bomba::calcularCorrenteRMS(const string& horaDesejada)
{
    return sensorCorrente->getRMS(horaDesejada);
}

double Bomba::calcularTensaoRMS(const string& horaDesejada)
{
    return sensorTensao->getRMS(horaDesejada);
}
double Bomba::calcularPotenciaAparente(const string& horaDesejada)
{
    double correnteRMS, tensaoRMS, potAparente;
    correnteRMS = sensorCorrente->getRMS(horaDesejada);
    correnteRMS = correnteRMS*1000;
    correnteRMS = ceil(correnteRMS);
    correnteRMS = correnteRMS/1000;
    tensaoRMS = sensorTensao->getRMS(horaDesejada);
    tensaoRMS = tensaoRMS*1000;
    tensaoRMS = ceil(tensaoRMS);
    tensaoRMS = tensaoRMS/1000;
    potAparente = correnteRMS*tensaoRMS;
    return potAparente;
}

double Bomba::calcularPotenciaAtiva(int N, int posicaoAmostra)
{
    double PotAtiva=0,x2=0;									// Vari?veis que armazenam o valor da Potencia Ativa 
	double xo, dadoC, dadoT; 
    //double *ptr_bufferCalculoC, *ptr_bufferCalculoT; 		
	double *const bufferCalculoPot = new double [N];	// Vetor que ir? armazenar os dados de 1 ciclo da onda (Aloca��o din�mica)
	double *ptr_bufferCalculoPot = bufferCalculoPot;	// ponteiro que ser? utilizado para varrer os dados
	memset(bufferCalculoPot, 0 , N*sizeof(double));		// Limpa os valores do vetor
	
	for (int i = 0; i <= posicaoAmostra;++i)
	{
		xo = *ptr_bufferCalculoPot;                     //Ao inserir uma nova amostra no vetor, retira a amostra mais antiga e armazena-a em xo
        sensorCorrente->getDado(i,dadoC);
        sensorTensao->getDado(i,dadoT);
        *ptr_bufferCalculoPot = dadoC*dadoT;			//Armazena o novo valor no vetor (x�)
		x2 += (*ptr_bufferCalculoPot - xo)/N;			//Soma a contribui??o
		

		if(ptr_bufferCalculoPot < (bufferCalculoPot+N-1))    //Enquanto o ponteiro apontar para um endere�o que esteja contido no bloco de mem?ria apontado por bufferCalculo
		{
			ptr_bufferCalculoPot++;					        //Incremente o ponteiro do buffer;									   
		
		}
		else
		{
			ptr_bufferCalculoPot = bufferCalculoPot;		  // caso contrario, atribua para ptr_bufferCalculo o endere�o do inicial do bloco de mem?ria apontado por bufferCalculo	
		}
	}

	delete[] bufferCalculoPot;							  //Desalocando bloco de mem?ria alocado									  
	return PotAtiva = x2;
 
    cout<<"pot "<< PotAtiva<<endl;

}

double Bomba::getPotAtiva(const string& HoraDesejada)
{
    int NumAmostrasSegundo = sensorCorrente->getNumAmostrasSegundo();
    int FreqRede = sensorTensao->getFreqRede();
    int N = NumAmostrasSegundo/FreqRede; //Numero de amostras por ciclo de onda
    int posicao = sensorCorrente->getPosicao(HoraDesejada);
    return calcularPotenciaAtiva(N,posicao);
}

double Bomba::calculaFP(const string& horaDesejada)
{
    double potAtv, potApa, FP;
    potAtv = getPotAtiva(horaDesejada);
    potApa = calcularPotenciaAparente(horaDesejada);
    FP = potAtv/potApa;
    
    return FP;
}

double Bomba::calculaEnergia(const string& horaDesejada)
{
    double energia,potAtiva = getPotAtiva(horaDesejada);
    //cout<<"pot: "<< potAtiva<<endl;
    double min, seg, segHoras, absSH;
    int idx = 2;
    //Calcula segundos para minuto;
    segHoras = ((seg=stod(horaDesejada.substr(idx + 4, idx + 5))-(55)) / 60);
    absSH = fabs(segHoras);
    //cout<<"abs1: "<< absSH<<endl;
    //Calcula minutos para h;
    absSH += (((stod(horaDesejada.substr(idx + 1, idx + 2)) - 8)+ absSH));
    segHoras = absSH/60;
    //min = stod(horaDesejada.substr(idx + 1, idx + 2));
    //cout<< "minuto: "<< min <<endl;
    //cout<<"abs2: "<< segHoras<<endl;
    //Calcula energia
    energia = segHoras*potAtiva/1000;

    return energia;
}