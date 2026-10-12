// ============================================================
// Arquivo: vertice.cpp
// Descrição: Implementação dos métodos da classe Vertice.
// ============================================================

#include "vertice.h"             // Inclui a definição da classe.

// ------------------------------------------------------------
// Construtor: inicializa o atributo rotulo com o valor recebido.
// ------------------------------------------------------------
Vertice::Vertice(string r) {
    rotulo = r;                  // Atribui o rótulo passado ao atributo.
}

// ------------------------------------------------------------
// Metodo get: retorna o rótulo armazenado.
// ------------------------------------------------------------
string Vertice::getRotulo() {
    return rotulo;               // Devolve o rótulo.
}