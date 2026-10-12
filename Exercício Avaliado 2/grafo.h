// ============================================================
// Arquivo: grafo.h
// Descrição: Definição da classe Grafo, que representa um
//            grafo não direcionado. Armazena um vector de
//            objetos da classe Vertice e um vector de objetos
//            da classe Aresta.
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
    // Construtor padrão: inicializa o grafo vazio.
    Grafo();

    // Lê o arquivo de entrada e monta o grafo.
    void lerArquivo(string nomeArquivo);

    // Busca um vértice pelo rótulo. Retorna o índice ou -1.
    int buscaIndiceVertice(string rotulo);

    // Retorna o grau de um vértice (número de arestas ligadas a ele).
    int getGrau(int indice);

    // ---- Funcionalidades do menu ----
    void imprimirListaAdjacencia();       // Item 1: lista de adjacencia.
    void imprimirGraus();                  // Item 2: graus dos vértices.
    void imprimirComponentesConexas();    // Item 3: componentes conexas (BFS).
    void imprimirArvoreGeradoraMinima();  // Item 4: AGM (Prim).
    void imprimirCentralidade();          // Item 5: centralidade (Dijkstra).

private:
    vector<Vertice> vertices;    // Vector que armazena todos os vértices.
    vector<Aresta>  arestas;     // Vector que armazena todas as arestas.
};

#endif                           // Fim da guarda de inclusão.