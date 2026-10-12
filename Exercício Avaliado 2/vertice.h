// ============================================================
// Arquivo: vertice.h
// Descricao: Definicao da classe Vertice, que representa um
//            vertice (no) de um grafo nao direcionado.
//            Possui apenas um atributo privado do tipo string
//            para armazenar o rotulo do vertice.
// ============================================================

#include <iostream>              // Para usar cout e endl (em alguns casos).
#include <string>                // Para usar a classe string.
using namespace std;             // Permite omitir o prefixo std::.

#ifndef VERTICE_H                // Guarda de inclusao: evita que o arquivo
#define VERTICE_H                // seja incluido mais de uma vez na compilacao.

class Vertice {                  // Declaracao da classe Vertice.
public:
    // Construtor: recebe o rotulo do vertice e inicializa o atributo.
    Vertice(string r);

    // Metodo get: retorna o rotulo do vertice.
    string getRotulo();

private:
    string rotulo;               // Atributo privado: rotulo do vertice.
};

#endif                           // Fim da guarda de inclusao.