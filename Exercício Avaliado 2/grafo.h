// ============================================================
// Arquivo: grafo.h
// Descricao: Definicao da classe Grafo, que representa um
//            grafo nao direcionado. Armazena um vector de
//            objetos da classe Vertice e um vector de objetos
//            da classe Aresta.
// ============================================================

#include <iostream>              // Para usar cout e endl.
#include <iomanip>               // Para usar setprecision na saida formatada.
#include <string>                // Para usar a classe string.
#include <vector>                // Para armazenar vertices e arestas.
#include <fstream>               // Para ler o arquivo de entrada.
#include "vertice.h"             // Necessario para armazenar vertices.
#include "aresta.h"              // Necessario para armazenar arestas.
using namespace std;

#ifndef GRAFO_H                  // Guarda de inclusao.
#define GRAFO_H

class Grafo {                    // Declaracao da classe Grafo.
public:
    // Construtor padrao: inicializa o grafo vazio.
    Grafo();

    // Le o arquivo de entrada e monta o grafo.
    void lerArquivo(string nomeArquivo);

    // Busca um vertice pelo rotulo. Retorna o indice ou -1.
    int buscaIndiceVertice(string rotulo);

    // Retorna o grau de um vertice (numero de arestas ligadas a ele).
    int getGrau(int indice);

    // ---- Funcionalidades do menu ----
    void imprimirListaAdjacencia();       // Item 1: lista de adjacencia.
    void imprimirGraus();                  // Item 2: graus dos vertices.
    void imprimirComponentesConexas();    // Item 3: componentes conexas (BFS).
    void imprimirArvoreGeradoraMinima();  // Item 4: AGM (Prim).
    void imprimirCentralidade();          // Item 5: centralidade (Dijkstra).

private:
    vector<Vertice> vertices;    // Vector que armazena todos os vertices.
    vector<Aresta>  arestas;     // Vector que armazena todas as arestas.
};

#endif                           // Fim da guarda de inclusao.