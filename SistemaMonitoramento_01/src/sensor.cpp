#include "sensor.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <math.h>
#include <string.h>
#include <iomanip>

using namespace std;

Sensor::Sensor(const string& path, const vector<string>& h) : 
    nome("desconhecido"), id("desconhecido"),horarioInicialColeta("desconhecido"), numAmostrasSegundo(0) , numAmostras(0)
{
    // cout << "%% CONSTRUTOR DO SENSOR\n" << endl;
    this->headers.assign(h.begin(), h.end());
    this->abrirArquivo(path);
    // cout << "CONSTRUTOR SENSOR:" << this->file.is_open() << endl;
}

Sensor::~Sensor()
{
    // cout << "%% DESTRUTOR DO SENSOR\n" << endl;
    this->file.close();
}

bool Sensor::abrirArquivo(const string& path)   
{
    try
    {
        // cout << "ABRIR ARQUIVO - SENSOR" << endl;
        this->file.open(path); // abrindo no modo padrão, leitura
        // cout << "abrirArquivo SENSOR:" << this->file.is_open() << endl;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    return false;    
}

string Sensor::getTitulo()
{
    return this->titulo;
}


string Sensor::getNome()
{
    return this->nome;
}

string Sensor::getId()
{
    return this->id;
}

string Sensor::getHorarioInicialColeta()
{
    return this->horarioInicialColeta;
}

string Sensor::getHorarioFinalColeta()
{
    this->fracSegundo = 1.0 / getNumAmostrasSegundo();
    string horarioInicial = getHorarioInicialColeta();
    int horarioInicialSegundos = this->horaParaSegundo(horarioInicial);
    int horarioFinalSegundos =  horarioInicialSegundos + (this->fracSegundo * this->numAmostras);
    this->horarioFinalColeta = horaParaString(horarioFinalSegundos);
    return this->horarioFinalColeta;
}

int Sensor::getNumAmostrasSegundo()
{
    return this->numAmostrasSegundo;
}

int Sensor::getNumAmostras()
{
    return this->numAmostras;
}

int Sensor::horaParaSegundo(const string& horarioDoUsuario)
{
    // cout << "Horario passado pelo usuario: " << horarioDoUsuario << endl;
    int idx = horarioDoUsuario.find(':'); // retorna idx = 2
    // transformando hora em segundos
    int horarioEmSegundos = (stod(horarioDoUsuario.substr(0, idx)) * 3600);
    // transformando minuto em segundos
    horarioEmSegundos += (stod(horarioDoUsuario.substr(idx + 1, idx + 2)) * 60);
    horarioEmSegundos += (stod(horarioDoUsuario.substr(idx + 4, idx + 5)));
    // cout << setprecision(4) << fixed;  // para exibição com casas decimais
    // cout << setprecision(4) << "hora em segundos: " << horarioEmSegundos << fixed << endl;
    return horarioEmSegundos;  
}

string Sensor::horaParaString(int &horarioEmSegundos)
{
    // cout << ">>> horaParaString <<<" << endl;
    int horas = horarioEmSegundos / 3600; // retirando a parcela das horas do total de segundos
    horarioEmSegundos -= horas * 3600; // restaram agora minutos e segundos
    int minutos = horarioEmSegundos / 60; // retirando a parcela dos minutos do total de segundos
    horarioEmSegundos -= minutos * 60; // restaram agora só os segundos 
    // cout << "> horas: " << horas << endl;
    // cout << "> minutos: " << minutos << endl;
    // cout << "> horas: " << horarioEmSegundos << endl;
    string horario = to_string(horas) + ":" + to_string(minutos) + ":" + to_string(horarioEmSegundos);
    
    return horario;
}

int Sensor::getPosicao(const string& horarioDoUsuario)
{
    // dado o horário desejado pelo usuário, procurar o índice referente nos dados para
    //      acionar o loop até esse índice, baseado no numero de amostras pro segundo
    // cout << "> Horario passado pelo usuario: " << horarioDoUsuario << endl;
    double horarioUsuarioEmSegundos = horaParaSegundo(horarioDoUsuario);
    // cout << setprecision(4) << "> Horario passado pelo usuario em segundos: " << horarioUsuarioEmSegundos << fixed << endl;
    // obter fração de segundo referente à cada amostra= 1s / numAmostrasSegundo    
    // cout << setprecision(6);  // para exibição com casas decimais
    // cout << "> Num amostras por segundo: " << this->getNumAmostrasSegundo() << endl;
    // cout << "> Fracao de segundos entre amostras: " << fracSegundo << endl;
    // cout << "> Horario inicio da coleta: " << this->getHorarioInicialColeta() << endl;
    double horarioInicialEmSegundos = horaParaSegundo(this->getHorarioInicialColeta());
    // cout << "> Horario inicio da coleta em segundos: " << horarioInicialEmSegundos << endl;
    // calcular agora o indice, posicao, do valor referente ao horário passado pelo usuario
    int posicao = (horarioUsuarioEmSegundos - horarioInicialEmSegundos) / this->fracSegundo;
    // cout << "> Posicao: " << posicao << endl;

    if (horarioUsuarioEmSegundos < horarioInicialEmSegundos)
    {
        cout << "\n------------\n# [ERRO] O horario especificado eh invalido: anterior ao inicio da coleta de dados.\n------------" << endl;
    }
    else if (posicao > this->numAmostras)
    {
        cout << "\n------------\n# [ERRO] O horario especificado eh invalido: posterior ao fim da coleta de dados.\n------------" << endl;
    }
    else 
    {
        return posicao;
    }
    // o erro de identificação do dado tem que ser feito aqui e não em outras etapas, como na aquisição do dado em si
    return -1; // código de erro da busca; especificar na documentação depois
}

double Sensor::calcRMS(int N, int posicaoAmostra)			
{
	double RMS=0,x2=0;									// Vari?vel que armazena o valor RMS e que armazena o valor RMS� (x2 = RMS�)
	double xo;											// Vari?vel que armazena a amostra a ser descartada
	double *const bufferCalculo = new double [N];		// Vetor que ir? armazenar os dados de 1 ciclo da onda (Aloca��o din�mica)
	double *ptr_bufferCalculo = bufferCalculo;			// ponteiro que ser? utilizado para varrer os dados
	memset(bufferCalculo, 0 , N*sizeof(double));		// Limpa os valores do vetor
	
	for (int i = 0; i <= posicaoAmostra;++i)
	{
		xo = *ptr_bufferCalculo;						//Ao inserir uma nova amostra no vetor, retira a amostra mais antiga e armazena-a em xo
		*ptr_bufferCalculo = this->dados[i]*dados[i];					//Armazena o novo valor no vetor (x�)
		x2 += (*ptr_bufferCalculo - xo)/N;				//Soma a contribui??o
		

		if(ptr_bufferCalculo < (bufferCalculo+N-1))    //Enquanto o ponteiro apontar para um endere�o que esteja contido no bloco de mem?ria apontado por bufferCalculo
		{
			ptr_bufferCalculo++;					   //Incremente o ponteiro do buffer;									   //Incremente o ponteiro que aponta para os dados	
		}
		else
		{
			ptr_bufferCalculo = bufferCalculo;		  // caso contrario, atribua para ptr_bufferCalculo o endere�o do inicial do bloco de mem?ria apontado por bufferCalculo
		}
	}

	delete[] bufferCalculo;							  //Desalocando bloco de mem?ria alocado
	RMS = sqrt(x2);									  // Calcula a raiz quadrada de RMS� = RMS
	return RMS;
}