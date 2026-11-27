// ============================================================
// Arquivo: dvd.cpp
// Descricao: Implementacao dos metodos da classe DVD.
//            Define multa diaria de R$ 3,00 por dia de atraso.
// ============================================================

#include "dvd.h"                 

// ------------------------------------------------------------
// Construtor: invoca o construtor da base ItemAcervo e
// inicializa duracaoMinutos.
// ------------------------------------------------------------
DVD::DVD(string cod, string tit, int ano, int duracao, int emprestimos)
    : ItemAcervo(cod, tit, ano, emprestimos), duracaoMinutos(duracao) {}

// ------------------------------------------------------------
// Metodos get e set de duracaoMinutos.
// ------------------------------------------------------------
int DVD::getDuracaoMinutos() const { return duracaoMinutos; }
void DVD::setDuracaoMinutos(int duracao) { duracaoMinutos = duracao; }

// ------------------------------------------------------------
// getTipo: identifica este objeto como "DVD".
// ------------------------------------------------------------
string DVD::getTipo() const {
    return "DVD";
}

// ------------------------------------------------------------
// calculaMulta: regra especifica de DVD (R$ 3,00 por dia).
// ------------------------------------------------------------
double DVD::calculaMulta(int diasAtraso) const {
    if (diasAtraso <= 0) return 0.0;         // Sem atraso, multa zero.
    return diasAtraso * 3.00;                // R$ 3,00 multiplicado pelos dias.
}

// ------------------------------------------------------------
// imprimirDetalhes: reutiliza a impressao da classe base e
// concatena a duracao em minutos ao final da linha.
// ------------------------------------------------------------
void DVD::imprimirDetalhes(ostream& out) const {
    ItemAcervo::imprimirDetalhes(out);       // Imprime os atributos comuns.
    out << " | Duracao: " << duracaoMinutos << " min"; // Acrescenta a duracao.
}