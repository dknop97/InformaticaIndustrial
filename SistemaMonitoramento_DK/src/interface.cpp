#include "interface.h"
#include "sensorCorrente.h"
#include "sensorTensao.h"
#include "sensorVazao.h"
#include "reservatorio.h"
#include "bomba.h"

#include <iostream>
#include <string>

using namespace std;

void monitorarBombas(SensorCorrente &SC1, SensorCorrente &SC2, SensorTensao &ST1, SensorTensao &ST2)
{
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
            // Bomba bomba(SC1, SV1);
            comandosUsuario = 3;
            break;
        case 2:
            cout << ">>> Monitorando Bomba 2\n";
            // implementar indicativo para a bomba 2
            // para a bomba 2, tenho SC2, ST2; então, posso fazer algo do tipo:
            // dada uma classe Bomba, que recebe como argumentos os objetos dos sensores relacionados
            // Bomba bomba(SC2, SV2);
            comandosUsuario = 3;
            break;
        case 3: // SAIR do menu das bombas
            cout << ">> Retornando ao menu inicial...\n";
            // break;
            return; // return aqui, para não executar o código do menu seguinte para as bombas
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while (comandosUsuario != 3);

    string horaDesejada = "";
    string horaInicial  = SC1.getHorarioInicialColeta();
    string horaFinal    = SC1.getHorarioFinalColeta();
    // implementar cálculo do horário final das amostras
    cout << ">>> Digite a hora desejada (" << horaInicial << " - " << horaFinal << "): ";
    cin >> horaDesejada;                                        // a validação da horaDesejada está sendo feita no método de busca
    cout << ">>> Escolha a informacao desejada sobre a bomba no horario informado: \n";
    do
    {
        cout << "\n> 1. Corrente RMS" << endl;
        cout << "> 2. Tensao RMS" << endl;
        cout << "> 3. Potencia ativa" << endl;
        cout << "> 4. Potencia aparente" << endl;
        cout << "> 5. Fator de potencia" << endl;
        cout << "> 6. Energia consumida ate o horario informado" << endl;
        cout << "> 7. Escolher novo horario de analise" << endl;
        cout << "> 8. Sair" << endl;
        cout << ">> ";
        cin >> comandosUsuario;

        switch (comandosUsuario)
        {
        case 1:
            // obter corrente rms da bomba X
            // bomba.calcularCorrenteRMS();
            break;
        case 2:
            // obter tensão rms da bomba X
            // bomba.calcularTensaoRMS();
            break;
        case 3:
            // obter potencia ativa da bomba X na horaDesejada
            // bomba.calcularPotenciaAtiva(horaDesejada);
            break;
        case 4:
            // obter potencia aparente da bomba X na horaDesejada
            // bomba.calcularPotenciaAparente(horaDesejada);
            break;
        case 5:
            // obter fator de potencia da bomba X na horaDesejada
            // bomba.calculaFP(horaDesejada);
            break;
        case 6:
            // obter energia consumida pela bomba X até a horaDesejada
            // bomba.calculaEnergia(horaDesejada);
            break;
        case 7:
            // alterar a horaDesejada
            cout << ">>> Digite a hora desejada (" << horaInicial << " - " << horaFinal << "): ";
            cin >> horaDesejada;                                        // a validação da horaDesejada está sendo feita no método de busca
            break;
        case 8: // sair do menu
            cout << ">> Retornando ao menu anterior...\n";
            break;
        default:
            break;
        }

    } while (comandosUsuario != 8);
}

void monitorarReservatorio(SensorVazao& SVEntrada, SensorVazao& SVSaida)
{
    // Temos um arquivo de funções para o reservatório.
    // Apesar de só termos 1 cálculo pra fazer, de volume, é bom termos o arquivo de funções
    //      para outras possíveis implementações
    int comandosUsuario = 0;
    double volume = 0.0;
    string horaDesejada = "";
    string horaInicial  = SVEntrada.getHorarioInicialColeta(); // qualquer objeto, visto que o horário final ´eo mesmo, assim como inicial
    string horaFinal    = SVEntrada.getHorarioFinalColeta();
    // implemtnar cálculo do horário final das amostras
    cout << ">>> Digite a hora desejada (" << horaInicial << " - " << horaFinal << "): ";
    cin >> horaDesejada;                                        // a validação da horaDesejada está sendo feita no método de busca
    cout << ">>> Escolha a informacao desejada sobre o reservatorio no horario informado: \n";
    do
    {
        cout << "\n> 1. Volume do tanque" << endl;
        cout << "> 2. Vazao de entrada" << endl;
        cout << "> 3. Vazao de saida" << endl;
        cout << "> 4. Escolher novo horario de analise" << endl;
        cout << "> 5. Sair" << endl;
        cout << ">> ";
        cin >> comandosUsuario;

        switch (comandosUsuario)
        {
        case 1:
            // obter o volume do reservatório na horaDesejada
            volume = calculaVolume(horaDesejada, SVEntrada, SVSaida);
            cout << ">>> O volume do reservatorio as "<< horaDesejada << "h era de " << volume << " litros.\n" << endl;
            break;
        case 2:
            // obter vazão de entrada no reservatório na horaDesejada
            double vazaoEntrada;
            SVEntrada.getVazao(horaDesejada, vazaoEntrada);
            cout << ">>> A vazao de entrada as "<< horaDesejada << "h era de " << vazaoEntrada << " " << SVEntrada.getUnidade() << ".\n" << endl;
            break;
        case 3:
            // obter vazão de saída no reservatório na horaDesejada
            double vazaoSaida;
            SVSaida.getVazao(horaDesejada, vazaoSaida);
            cout << ">>> A vazao de saida as "<< horaDesejada << "h era de " << vazaoSaida << " " << SVSaida.getUnidade() << ".\n" << endl;
            break;
        case 4:
            // alterar a horaDesejada
            cout << ">>> Digite a hora desejada (" << horaInicial << " - " << horaFinal << "): ";cout << ">>> Digite a hora desejada (" << horaInicial << " - horaFinal): "; // buscar a hora inicial da coleta e calcular a final aqui de acordo com a bomba em análise
            cin >> horaDesejada;                                        // a validação da horaDesejada está sendo feita no método de busca
            break;
        case 5: // sair do menu
            cout << ">>> Retornando ao menu anterior...\n";
            break;
        default:
            break;
        }

    } while (comandosUsuario != 5);
}

// void Interface(SensorCorrente &SC1, SensorCorrente *SC2, SensorTensao &ST1, SensorTensao &ST2, SensorVazao &SV1, SensorVazao &SV2)
void Interface()
{
    // declaração dos paths dos arquivos contendo os dados de cada sensor
    string pathSensorCorrente1  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorCorrente1.dat";
    string pathSensorCorrente2  = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorCorrente2.dat";
    string pathSensorTensao1    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorTensao1.dat";
    string pathSensorTensao2    = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorTensao2.dat";
    string pathSensorVazao1     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorVazao1.dat";
    string pathSensorVazao2     = "G:\\Meu Drive\\UFJF\\Engenharia Eletrica\\2020-1\\04 - Informatica Industrial\\ERE\\Trabalhos\\Trabalho_1\\DK\\SistemaMonitoramento_DK\\dados\\SensorVazao2.dat";

    // instanciamento dos objetos das classes
    SensorCorrente SC1(pathSensorCorrente1);
    SensorCorrente SC2(pathSensorCorrente2);
    SensorTensao ST1(pathSensorTensao1);
    SensorTensao ST2(pathSensorTensao2);
    SensorVazao SV1(pathSensorVazao1);
    SensorVazao SV2(pathSensorVazao2);

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
            monitorarBombas(SC1, SC2, ST1, ST2);
            break;
        case 2: // monitorar Reservatorio
            monitorarReservatorio(SV1, SV2);
            break;
        case 3: // SAIR
            cout << ">> Encerrando o Programa.\n";
            return;
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while (entradaDoUsuario != 3);

    return;
}