#ifndef COMPONENTE_H
#define COMPONENTE_H

#include <iostream>
#include <string>

using namespace std;

struct Componente {
    string codigo;
    string fabricante;
    int quantidade;
    double precoUnitario;
};

// Declarações dos operadores globais para a struct
ostream& operator<<(ostream& os, const Componente& comp);
istream& operator>>(istream& is, Componente& comp);
bool operator==(const Componente& c1, const Componente& c2);
bool operator<(const Componente& c1, const Componente& c2);

#endif