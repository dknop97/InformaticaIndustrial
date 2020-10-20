#include "interface.h"
// #include "sensorCorrente.h"
// #include "sensorTensao.h"
// #include "sensorVazao.h"

#include <iostream>
#include <string>

using namespace std;

void monitorarBombas()
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
            // dada uma classe Bomba, que recebe como argumentos os objetos dos sensores relacionados
            // Bomba bomba(SC1, SV1);
            break;
        case 2:
            cout << ">>> Monitorando Bomba 2\n";
            // implementar indicativo para a bomba 2
            // para a bomba 2, tenho SC2, ST2; então, posso fazer algo do tipo:
            // dada uma classe Bomba, que recebe como argumentos os objetos dos sensores relacionados
            // Bomba bomba(SC2, SV2);
            break;
        case 3: // SAIR do menu das bombas
            cout << ">> Retornando ao menu inicial...\n";
            comandosUsuario = 1;
            break;
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while ((comandosUsuario != 1) && (comandosUsuario != 2));
    
    string horaDesejada = "";
    // string horaInicial, horaFinal;
    cout << ">>> Digite a hora desejada (horaI - horaFinal): "; // buscar a hora inicial da coleta e calcular a final aqui de acordo com a bomba em análise 
    cin >> horaDesejada; // a validação da horaDesejada está sendo feita no método de busca
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
            cout << ">>> Digite a hora desejada (horaI - horaFinal): "; // buscar a hora inicial da coleta e calcular a final aqui de acordo com a bomba em análise 
            cin >> horaDesejada; // a validação da horaDesejada está sendo feita no método de busca
            break;
        case 8: // sair do menu
            cout << ">> Retornando ao menu anterior...\n";  
            break;
        default:
            break;
        }

    } while (comandosUsuario != 8);
}

void monitorarReservatorio()
{
    // Assim como para a bomba, implementar uma classe Reservatorio para encapsular os objetos 
    // Reservatorio reservatorio(SV1, SV2);
    int comandosUsuario = 0;
    string horaDesejada = "";
    // string horaInicial, horaFinal;
    cout << ">>> Digite a hora desejada (horaI - horaFinal): "; // buscar a hora inicial da coleta e calcular a final aqui de acordo com a bomba em análise 
    cin >> horaDesejada; // a validação da horaDesejada está sendo feita no método de busca
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
            // double volume = reservatorio.calculaVolume(horaDesejada);
            // cout << ">>> O volume do reservatorio as "<< horaDesejada << "h era de " << volume << "L\n" << endl;
            break;
        case 2:
            // obter vazão de entrada no reservatório na horaDesejada
            // double vazaoEntrada;
            // SV1.getVazao(horaDesejada, vazaoEntrada);
            // cout << ">>> A vazao de entrada as "<< horaDesejada << "h era de " << vazaoEntrada << "L/s.\n" << endl;
            break;
        case 3:
            // obter vazão de saída no reservatório na horaDesejada
            // double vazaoSaida;
            // SV2.getVazao(horaDesejada, vazaoSaida);
            // cout << ">>> A vazao de saida as "<< horaDesejada << "h era de " << vazaoSaida << "L/s.\n" << endl;
            break;
        case 4:
            // alterar a horaDesejada
            cout << ">>> Digite a hora desejada (horaI - horaFinal): "; // buscar a hora inicial da coleta e calcular a final aqui de acordo com a bomba em análise 
            cin >> horaDesejada; // a validação da horaDesejada está sendo feita no método de busca
            break;
        case 5: // sair do menu
            cout << ">> Retornando ao menu anterior...\n";  
            break;
        default:
            break;
        }

    } while (comandosUsuario != 5);
}

void Interface()
{
    cout << "\n\n ===> Sistema de Monitoramento da Planta de Bombeamento <=== \n";
    int entradaDoUsuario = 0;
    do
    {
        cout << "\n> Escolha o equipamento que deseja monitorar (1 - Bombas | 2 - Reservatorio | 3 - Encerrar Programa)\n>> ";
        cin >> entradaDoUsuario;
        switch (entradaDoUsuario)
        {
        case 1: // monitorar bombas
            monitorarBombas();
            break;
        case 2: // monitorar Reservatorio
            monitorarReservatorio();
            break;
        case 3: // SAIR
            cout << ">> Encerrando o Programa.\n";
            return;
        default:
            cout << " # Opcao invalida! Tente novamente...\n";
            break;
        }
    } while(entradaDoUsuario != 3);
    
    return;
}