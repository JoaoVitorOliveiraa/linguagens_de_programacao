// ============================================================
// Arquivo: aresta.cpp
// Descricao: Implementacao dos metodos da classe Aresta.
// ============================================================

#include "aresta.h"              // Inclui a definicao da classe.

// ------------------------------------------------------------
// Construtor: inicializa os ponteiros e o peso da aresta.
// ------------------------------------------------------------
Aresta::Aresta(Vertice *prim, Vertice *seg, double p) {
    primeiroVertice = prim;      // Guarda o ponteiro para o vertice de origem.
    segundoVertice = seg;        // Guarda o ponteiro para o vertice de destino.
    peso = p;                    // Guarda o peso.
}

// ------------------------------------------------------------
// Metodos get: retornam os atributos da aresta.
// ------------------------------------------------------------
Vertice *Aresta::getPrimeiroVertice() {
    return primeiroVertice;      // Devolve o ponteiro de origem.
}

Vertice *Aresta::getSegundoVertice() {
    return segundoVertice;       // Devolve o ponteiro de destino.
}

double Aresta::getPeso() {
    return peso;                 // Devolve o peso da aresta.
}