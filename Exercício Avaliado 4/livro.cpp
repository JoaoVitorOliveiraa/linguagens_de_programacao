// ============================================================
// Arquivo: livro.cpp
// Descricao: Implementacao dos metodos da classe Livro.
//            Define multa diaria de R$ 1,50 por dia de atraso.
// ============================================================

#include "livro.h"             

// ------------------------------------------------------------
// Construtor: repassa os parametros comuns ao construtor da
// classe base ItemAcervo e inicializa numPaginas.
// ------------------------------------------------------------
Livro::Livro(string cod, string tit, int ano, int paginas, int emprestimos)
    : ItemAcervo(cod, tit, ano, emprestimos), numPaginas(paginas) {}

// ------------------------------------------------------------
// Metodos get e set de numPaginas.
// ------------------------------------------------------------
int Livro::getNumPaginas() const { return numPaginas; }
void Livro::setNumPaginas(int paginas) { numPaginas = paginas; }

// ------------------------------------------------------------
// getTipo: identifica este objeto como "Livro".
// ------------------------------------------------------------
string Livro::getTipo() const {
    return "Livro";
}

// ------------------------------------------------------------
// calculaMulta: regra especifica de Livro (R$ 1,50 por dia).
// ------------------------------------------------------------
double Livro::calculaMulta(int diasAtraso) const {
    if (diasAtraso <= 0) return 0.0;         // Sem atraso, multa zero.
    return diasAtraso * 1.50;                // R$ 1,50 multiplicado pelos dias.
}

// ------------------------------------------------------------
// imprimirDetalhes: reutiliza a impressao da classe base e
// concatena o numero de paginas ao final da linha.
// ------------------------------------------------------------
void Livro::imprimirDetalhes(ostream& out) const {
    ItemAcervo::imprimirDetalhes(out);       // Imprime codigo, titulo, ano e emprestimos.
    out << " | Paginas: " << numPaginas;     // Acrescenta o dado especifico de Livro.
}