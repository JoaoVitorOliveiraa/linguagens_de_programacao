// ============================================================
// Arquivo: periodico.cpp
// Descricao: Implementacao dos metodos da classe Periodico.
//            Define multa diaria de R$ 1,00 com teto maximo
//            de R$ 15,00 por atraso.
// ============================================================

#include "periodico.h"          

// ------------------------------------------------------------
// Construtor: invoca o construtor da base ItemAcervo e
// inicializa numEdicao.
// ------------------------------------------------------------
Periodico::Periodico(string cod, string tit, int ano, int edicao, int emprestimos)
    : ItemAcervo(cod, tit, ano, emprestimos), numEdicao(edicao) {}

// ------------------------------------------------------------
// Metodos get e set de numEdicao.
// ------------------------------------------------------------
int Periodico::getNumEdicao() const { return numEdicao; }
void Periodico::setNumEdicao(int edicao) { numEdicao = edicao; }

// ------------------------------------------------------------
// getTipo: identifica este objeto como "Periodico".
// ------------------------------------------------------------
string Periodico::getTipo() const {
    return "Periodico";
}

// ------------------------------------------------------------
// calculaMulta: regra especifica de Periodico (R$ 1,00/dia,
// limitado ao valor maximo de R$ 15,00).
// ------------------------------------------------------------
double Periodico::calculaMulta(int diasAtraso) const {
    if (diasAtraso <= 0) return 0.0;         // Sem atraso, multa zero.
    double multa = diasAtraso * 1.00;        // Calcula R$ 1,00 por dia.
    if (multa > 15.00) {                     // Aplica o teto maximo de R$ 15,00.
        multa = 15.00;
    }
    return multa;
}

// ------------------------------------------------------------
// imprimirDetalhes: reutiliza a impressao da classe base e
// concatena o numero da edicao ao final da linha.
// ------------------------------------------------------------
void Periodico::imprimirDetalhes(ostream& out) const {
    ItemAcervo::imprimirDetalhes(out);       // Imprime os atributos comuns.
    out << " | Edicao: " << numEdicao;       // Acrescenta o numero da edicao.
}