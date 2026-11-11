// ============================================================
// Arquivo: componente.h
// Descrição: Definição da struct Componente, que representa um
//            item do estoque. Contém o código, fabricante,
//            quantidade e preço unitário.
//            Também declara as assinaturas dos operadores
//            globais de comparação e entrada/saída de dados.
// ============================================================

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