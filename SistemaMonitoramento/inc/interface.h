#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>

using namespace std;

void IHM();
void monitorarBombas();
void monitorarReservatorio();
bool verificaHorario(const string &);
string setHorarioDesejado(const string &, const string &);

#endif