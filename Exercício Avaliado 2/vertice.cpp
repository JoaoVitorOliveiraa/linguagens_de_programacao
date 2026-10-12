// ============================================================
// Arquivo: vertice.cpp
// Descricao: Implementacao dos metodos da classe Vertice.
// ============================================================

#include "vertice.h"             // Inclui a definicao da classe.

// ------------------------------------------------------------
// Construtor: inicializa o atributo rotulo com o valor recebido.
// ------------------------------------------------------------
Vertice::Vertice(string r) {
    rotulo = r;                  // Atribui o rotulo passado ao atributo.
}

// ------------------------------------------------------------
// Metodo get: retorna o rotulo armazenado.
// ------------------------------------------------------------
string Vertice::getRotulo() {
    return rotulo;               // Devolve o rotulo.
}