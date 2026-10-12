// ============================================================
// Arquivo: aresta.h
// Descricao: Definicao da classe Aresta, que representa uma
//            aresta de um grafo nao direcionado. Possui dois
//            ponteiros para objetos da classe Vertice (origem
//            e destino) e um peso do tipo double.
// ============================================================

#include <iostream>              // Para usar cout e endl em alguns casos.
#include "vertice.h"             // Necessario para usar ponteiros para Vertice.
using namespace std;

#ifndef ARESTA_H                 // Guarda de inclusao.
#define ARESTA_H

class Aresta {                   // Declaracao da classe Aresta.
public:
    // Construtor: recebe dois ponteiros para Vertice (origem e
    // destino) e o peso. O peso tem valor padrao 1.0.
    Aresta(Vertice *prim, Vertice *seg, double p = 1.0);

    // Metodos get: retornam os atributos da aresta.
    Vertice *getPrimeiroVertice();   // Retorna o ponteiro para o vertice de origem.
    Vertice *getSegundoVertice();    // Retorna o ponteiro para o vertice de destino.
    double getPeso();                // Retorna o peso da aresta.

private:
    Vertice *primeiroVertice;    // Ponteiro para o vertice de origem.
    Vertice *segundoVertice;     // Ponteiro para o vertice de destino.
    double peso;                 // Peso da aresta (double).
};

#endif                           // Fim da guarda de inclusao.