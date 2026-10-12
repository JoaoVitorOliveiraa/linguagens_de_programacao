// ============================================================
// Arquivo: grafo.h
// Descrição: Definição da classe Grafo, que representa um
//            grafo não direcionado. Os vértices e as arestas
//            são armazenados como objetos dentro de vectors. 
//            Para evitar que os endereços dos vértices mudem 
//            durante o preenchimento do vector, o construtor
//            reserva espaço com reserve().
// ============================================================

#include <iostream>              // Para usar cout e endl.
#include <iomanip>               // Para usar setprecision na saída formatada.
#include <string>                // Para usar a classe string.
#include <vector>                // Para armazenar vértices e arestas.
#include <fstream>               // Para ler o arquivo de entrada.
#include "vertice.h"             // Necessário para armazenar vértices.
#include "aresta.h"              // Necessário para armazenar arestas.
using namespace std;

#ifndef GRAFO_H                  // Guarda de inclusão.
#define GRAFO_H

class Grafo {                    // Declaração da classe Grafo.
public:
    // Construtor padrão: reserva espaço nos vectors para que
    // os endereços dos vértices não mudem durante o push_back.
    Grafo();

    // Lê o arquivo de entrada e monta o grafo.
    void lerArquivo(string nomeArquivo);

    // Busca um vértice pelo rótulo. Retorna um PONTEIRO ou NULL.
    Vertice *buscaVertice(string rotulo);

    // Retorna o grau de um vértice (número de arestas ligadas a ele).
    int getGrau(Vertice *v);

    // ---- Funcionalidades do menu ----
    void imprimirListaAdjacencia();       // Item 1: lista de adjacência.
    void imprimirGraus();                  // Item 2: graus dos vértices.
    void imprimirComponentesConexas();    // Item 3: componentes conexas (BFS).
    void imprimirArvoreGeradoraMinima();  // Item 4: AGM (Prim).
    void imprimirCentralidade();          // Item 5: centralidade (Dijkstra).

private:
    vector<Vertice> vertices;    // Vector de objetos Vertice.
    vector<Aresta>  arestas;     // Vector de objetos Aresta.
};

#endif                           // Fim da guarda de inclusão.