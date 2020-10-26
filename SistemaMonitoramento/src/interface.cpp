#include "interface.h"
#include "sensorCorrente.h"
#include "sensorTensao.h"
#include "sensorVazao.h"
#include "reservatorio.h"
#include "bomba.h"
#include <iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>

using namespace std;

string setHorarioDesejado(const string &horaInicial, const string &horaFinal)
{
    int aux = 0;
    string horaDesejada = "";
    do
    {
        cout << ">>> Digite a hora desejada (" << horaInicial << " - " << horaFinal << "): ";
        cin >> horaDesejada;
        if (!verificaHorario(horaDesejada)) // se verificaHorario retornar false...
        {
            cout << " # Opcao invalida! Tente novamente...\n"; // notifica o usuário
            aux++;
        }
        else
        {
            return horaDesejada;
        }
    } while (aux != 10); // serão permitidas 10 tentativas de inserção do horário
    cout << "\n # [ERRO] Limite de tentativas de definicao do horario excedida.\n # Retornando ao menu anterior...\n------------" << endl;
    return "-1";
}

bool verificaHorario(const string &horaDesejada)
{
    // modelo desejado para o horario: HH:MM:SS
    // logo, na posição 2 e 5 devem haver ':' e os demais elementos devem ser numeros inteiros
    if (horaDesejada.size() != 8) { return false; }
    for (int i = 0; i < horaDesejada.size(); i++)
    {
        if ((i == 2 ) || (i == 5 ))
        {
            if (horaDesejada[i] == ':') // verifica se o caracter na posição i da string é um ':'
            {
                continue; // passa para próxima iteração do loop
            }
            else 
            {
                return false; // significa que o horário foi digitado fora do padrão esperado
            }
        }
        if( isdigit(horaDesejada[i])) // verifica se o caracter na posição i da string é um dígito decimal
        {
            continue; // passa para próxima iteração do loop
        }
        else 
        {
            return false; // significa que o horário foi digitado fora do padrão esperado
        }
    }
    // se os testes primários deram ok, temos que verificar agora se o intervalo de H, min e s estão de acordo    
    string horas    = ""; // não sei porque, mas não tava aceitando inicialização direta com as strings
    string minutos  = "";
    string segundos = "";
    horas     = horaDesejada[0];
    horas    += horaDesejada[1];
    minutos   = horaDesejada[3];
    minutos  += horaDesejada[4];
    segundos  = horaDesejada[6];
    segundos += horaDesejada[7];
    int horasInt    = stoi(horas);
    int minutosInt  = stoi(minutos);
    int segundosInt = stoi(segundos);
    if( (horasInt > 23)  || (minutosInt > 59) || (segundosInt > 59) )
    { 
        return false;
    }
    else
    {
        return true; // significa que passou pela string inteira e estava tudo como esperado
    }
}

void monitorarBombas(SensorCorrente &SC1, SensorCorrente &SC2, SensorTensao &ST1, SensorTensao &ST2)
{
    //Declarando as bombas
    Bomba bomba;
    int comandosUsuario = 0;
    do
    {
        cout << "\n>> Escolha uma bomba para obter informacoes (1 - Bomba 1 | 2 - Bomba 2 | 3- Sair): ";
        cin >> comandosUsuario;
        switch (comandosUsuario)
        {
        case 1:
            cout << ">>> Monitorando Bomba 1\n";
            // implementar indicativo para a bomba 1
            // para a bomba 1, tenho SC1, ST1; então, posso fazer algo do tipo:
            // dada um aq classe Bomba, que recebe como argumentos os objetos dos sensores relacionados
            bomba.setSensorCorrente(SC1);
            bomba.setSensorTensao(ST1);
            comandosUsuario = -1;
            break;
        case 2:
            cout << ">>> Monitorando Bomba 2\n";
            // implementar indicativo para a bomba 2
            // para a bomba 2, tenho SC2, ST2; então, posso fazer algo do tipo:
            // dada uma classe Bomba, que recebe como argumentos os objetos dos sensores relacionados
            bomba.setSensorCorrente(SC2);
            bomba.setSensorTensao(ST2);
            comandosUsuario = -1;
            break;
        case 3: // SAIR do menu das bombas
            cout << ">> Retornando ao menu inicial...\n";
            return; // return aqui, para não executar o código do menu seguinte para as bombas
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while (comandosUsuario != -1);

    double valorAux;
    string horaAnterior = " ";
    string horaInicial  = SC1.getHorarioInicialColeta();
    string horaFinal    = SC1.getHorarioFinalColeta();
    string horaDesejada = setHorarioDesejado(horaInicial, horaFinal);
    string horaInicialEnergia, horaFinalEnergia;
    // se -1 for retornado pelo setHorarioDesejado, significa que deu erro 
    //      e devemos encerrar essa função, ou seja, retornar ao menu anterior
    if (horaDesejada == "-1") { return;}     
    
    cout << ">>> Escolha a informacao desejada sobre a bomba no horario informado: \n";
    do
    {
        cout << "> 1.  Corrente RMS" << endl;
        cout << "> 2.  Tensao RMS" << endl;
        cout << "> 3.  Potencia ativa" << endl;
        cout << "> 4.  Potencia aparente" << endl;
        cout << "> 5.  Fator de potencia" << endl;
        cout << "> 6.  Energia consumida entre horarios" << endl;
        cout << "> 7.  Obter nome do sensor de corrente" << endl;
        cout << "> 8.  Obter ID do sensor de corrente" << endl;
        cout << "> 9.  Obter nome do sensor de tensao" << endl;
        cout << "> 10. Obter ID do sensor de tensao" << endl;
        cout << "> 11. Escolher novo horario de analise" << endl;
        cout << "> 12. Sair" << endl;
        cout << ">> ";
        cin >> comandosUsuario;

        switch (comandosUsuario)
        {
        case 1:
            // obter corrente rms da bomba X
            cout << fixed;
            cout.precision(2);
            valorAux = bomba.calcularCorrenteRMS(horaDesejada);
            cout <<">>> Valor da Corrente RMS: " << valorAux << " A"<< endl;
            system ("pause");
            break;
        case 2:
            // obter tensão rms da bomba X
            cout << fixed;
            cout.precision(2);
            valorAux = bomba.calcularTensaoRMS(horaDesejada);
            cout <<">>> Valor da Tensao RMS: " << valorAux << " V"<< endl;
            system ("pause");
            break;
        case 3:
            // obter potencia ativa da bomba X na horaDesejada
            valorAux = bomba.getPotAtiva(horaDesejada);
            cout <<">>> Valor da Potencia ativa: " << valorAux << " W"<< endl;
            system ("pause");
            break;
        case 4:
            // obter potencia aparente da bomba X na horaDesejada
            valorAux = bomba.calcularPotenciaAparente(horaDesejada);
            cout <<">>> Valor da Potencia aparente: " << valorAux << " VA"<< endl;
            system ("pause");
            break;
        case 5:
            // obter fator de potencia da bomba X na horaDesejada
            cout << fixed;
            cout.precision(2);
            valorAux = bomba.calculaFP(horaDesejada);
            cout <<">>> Fator de potencia: " << valorAux << endl;
            system ("pause");
            break;
        case 6:
            // obter energia consumida pela bomba X até a horaDesejada
            cout << fixed;
            cout.precision(2);
            horaInicialEnergia  = setHorarioDesejado(horaInicial, horaFinal);
            horaFinalEnergia    = setHorarioDesejado(horaInicial, horaFinal);
            valorAux = bomba.calculaEnergia(horaInicialEnergia, horaFinalEnergia);
            cout <<">>> Energia consumida entre " << horaInicial << "h e " << horaFinalEnergia <<"h: " << valorAux << " kWh"<< endl;
            system ("pause");
            break;
        case 7:
            // Obter nome do sensor de corrente
            cout << ">>> Nome do sensor de corrente: "<< bomba.sensorCorrente->getNome() << endl;
            break;
        case 8:
            // Obter ID do sensor de corrente
            cout << ">>> ID do sensor de corrente: "<< bomba.sensorCorrente->getId() << endl;
            system ("pause");
            break;
        case 9:
            // Obter nome do sensor de tensao
            cout << ">>> Nome do sensor de tensao: "<< bomba.sensorTensao->getNome() << endl;
            system ("pause");
            break;
        case 10:
            // Obter ID do sensor de tensao
            cout << ">>> Nome do sensor de tensao: "<< bomba.sensorTensao->getId() << endl;
            system ("pause");
            break;
        case 11:
            // alterar a horaDesejada
            // se -1 for retornado pelo setHorarioDesejado, significa que deu erro 
            //      e devemos manter o horário previamente definido na variável horaDesejada
            horaAnterior = horaDesejada;
            horaDesejada = setHorarioDesejado(horaInicial, horaFinal);
            if (horaDesejada == "-1")
            {
                cout << ">>> [OBS] O horario definido anteriormente foi mantido." << endl;
                horaDesejada = horaAnterior;
            }
            else
            {
                system ("pause");
            }
            break;
        case 12: // sair do menu
            cout << ">> Retornando ao menu anterior...\n";
            break;
        default:
            break;
        }

    } while (comandosUsuario != 12);
}

void monitorarReservatorio(SensorVazao& SVEntrada, SensorVazao& SVSaida)
{
    // Temos um arquivo de funções para o reservatório.
    // Apesar de só termos 1 cálculo pra fazer, de volume, é bom termos o arquivo de funções
    //      para outras possíveis implementações
    int comandosUsuario = 0;
    double volume = 0.0;
    string horaAnterior = " "; // para backup da horaAnterior durante a troca de horario no item 4 do menu
    string horaInicial  = SVEntrada.getHorarioInicialColeta();
    string horaFinal    = SVEntrada.getHorarioFinalColeta();
    string horaDesejada = setHorarioDesejado(horaInicial, horaFinal);
    // se -1 for retornado pelo setHorarioDesejado, significa que deu erro 
    //      e devemos encerrar essa função, ou seja, retornar ao menu anterior
    if (horaDesejada == "-1") { return;}     

    cout << ">>> Escolha a informacao desejada sobre o reservatorio no horario informado: \n";
    do
    {
        cout << "> 1. Volume do tanque" << endl;
        cout << "> 2. Vazao de entrada" << endl;
        cout << "> 3. Vazao de saida" << endl;
        cout << "> 4. Obter nome do sensor de vazao de entrada" << endl;
        cout << "> 5. Obter ID do sensor de vazao de entrada" << endl;
        cout << "> 6. Obter nome do sensor de vazao de saida" << endl;
        cout << "> 7. Obter ID do sensor de vazao de saida" << endl;
        cout << "> 8. Escolher novo horario de analise" << endl;
        cout << "> 9. Sair" << endl;
        cout << ">> ";
        cin >> comandosUsuario;

        switch (comandosUsuario)
        {
        case 1:
            // obter o volume do reservatório na horaDesejada
            volume = calculaVolume(horaDesejada, SVEntrada, SVSaida);
            cout << fixed;
            cout.precision(2);
            cout << ">>> O volume do reservatorio as "<< horaDesejada << "h era de " << volume << " litros." << endl;
            system ("pause");
            break;
        case 2:
            // obter vazão de entrada no reservatório na horaDesejada
            double vazaoEntrada;
            SVEntrada.getVazao(horaDesejada, vazaoEntrada);
            cout << fixed;
            cout.precision(6);
            cout << ">>> A vazao de entrada as "<< horaDesejada << "h era de " << vazaoEntrada << " " << SVEntrada.getUnidade() << "." << endl;
            system ("pause");
            break;
        case 3:
            // obter vazão de saída no reservatório na horaDesejada
            double vazaoSaida;
            SVSaida.getVazao(horaDesejada, vazaoSaida);
            cout << fixed;
            cout.precision(6);
            cout << ">>> A vazao de saida as "<< horaDesejada << "h era de " << vazaoSaida << " " << SVSaida.getUnidade() << "." << endl;
            system ("pause");
            break;
        case 4:
            cout << ">>> Nome do sensor de vazao de entrada: " << SVEntrada.getNome() << endl;
            break;
        case 5:
            cout << ">>> ID do sensor de vazao de entrada: " << SVEntrada.getId() << endl;
            break;
        case 6:
            cout << ">>> Nome do sensor de vazao de saida: " << SVSaida.getNome() << endl;
            break;
        case 7:
            cout << ">>> ID do sensor de vazao de saida: " << SVSaida.getId() << endl;
            break;
        case 8:
            // alterar a horaDesejada
            // se -1 for retornado pelo setHorarioDesejado, significa que deu erro 
            //      e devemos manter o horário previamente definido na variável horaDesejada
            // string horaAnterior = " ";
            horaAnterior = horaDesejada;
            horaDesejada = setHorarioDesejado(horaInicial, horaFinal);
            if (horaDesejada == "-1")
            {
                cout << ">>> [OBS] O horario definido anteriormente foi mantido." << endl;
                horaDesejada = horaAnterior;
            }
            break;
        case 9: // sair do menu
            cout << ">>> Retornando ao menu anterior...\n";
            break;
        default:
            break;
        }

    } while (comandosUsuario != 9);
}

// void Interface(SensorCorrente &SC1, SensorCorrente *SC2, SensorTensao &ST1, SensorTensao &ST2, SensorVazao &SV1, SensorVazao &SV2)
void IHM()
{
    // declaração dos paths dos arquivos contendo os dados de cada sensor
    string pathSensorCorrente1  = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorCorrente1.dat";
    string pathSensorCorrente2  = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorCorrente2.dat";
    string pathSensorTensao1    = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorTensao1.dat";
    string pathSensorTensao2    = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorTensao2.dat";
    string pathSensorVazao1     = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorVazao1.dat";
    string pathSensorVazao2     = "C:\\Users\\dknop\\Documents\\GitHub\\InformaticaIndustrial\\SistemaMonitoramento\\dados\\SensorVazao2.dat";

    // instanciamento dos objetos das classes
    SensorCorrente  SC1(pathSensorCorrente1);
    SensorCorrente  SC2(pathSensorCorrente2);
    SensorTensao    ST1(pathSensorTensao1);
    SensorTensao    ST2(pathSensorTensao2);
    SensorVazao     SV1(pathSensorVazao1);
    SensorVazao     SV2(pathSensorVazao2);

    // leitura de dados referenets à cada sensor
    SV1.lerDados();
    SV2.lerDados();
    SC1.lerDados();
    SC2.lerDados();
    ST1.lerDados();
    ST2.lerDados();

    cout << "\n\n ===> Sistema de Monitoramento da Planta de Bombeamento <=== \n";
    int entradaDoUsuario = 0;
    do
    {
        cout << "\n> Escolha o equipamento que deseja monitorar (1 - Bombas | 2 - Reservatorio | 3 - Encerrar Programa)\n>> ";
        cin >> entradaDoUsuario;
        switch (entradaDoUsuario)
        {
        case 1: // monitorar bombas
            monitorarBombas(SC1,SC2,ST1,ST2);
            break;
        case 2: // monitorar Reservatorio
            monitorarReservatorio(SV1, SV2);
            break;
        case 3: // SAIR
            cout << ">> Encerrando o Programa.\n";
            system ("pause");
            return;
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while (entradaDoUsuario != 3);

    return;
}