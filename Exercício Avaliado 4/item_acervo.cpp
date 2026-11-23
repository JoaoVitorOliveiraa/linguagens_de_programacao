// ============================================================
// Arquivo: item_acervo.cpp
// Descricao: Implementacao dos metodos e operadores da classe
//            base ItemAcervo.
// ============================================================

#include "item_acervo.h"         // Inclui a definicao da classe base.

// ------------------------------------------------------------
// Construtor: usa lista de inicializacao para atribuir os
// valores recebidos aos atributos privados da classe.
// ------------------------------------------------------------
ItemAcervo::ItemAcervo(string cod, string tit, int ano, int emprestimos)
    : codigo(cod), titulo(tit), anoPublicacao(ano), totalEmprestimos(emprestimos) {}

// ------------------------------------------------------------
// Destrutor virtual: corpo vazio, pois nao ha alocacao
// dinamica interna na classe base.
// ------------------------------------------------------------
ItemAcervo::~ItemAcervo() {}

// ------------------------------------------------------------
// Metodos get: retornam os valores dos atributos privados.
// ------------------------------------------------------------
string ItemAcervo::getCodigo() const { return codigo; }
string ItemAcervo::getTitulo() const { return titulo; }
int ItemAcervo::getAnoPublicacao() const { return anoPublicacao; }
int ItemAcervo::getTotalEmprestimos() const { return totalEmprestimos; }

// ------------------------------------------------------------
// Metodos set: modificam os atributos privados com validacao
// basica no total de emprestimos.
// ------------------------------------------------------------
void ItemAcervo::setCodigo(string cod) { codigo = cod; }
void ItemAcervo::setTitulo(string tit) { titulo = tit; }
void ItemAcervo::setAnoPublicacao(int ano) { anoPublicacao = ano; }

void ItemAcervo::setTotalEmprestimos(int emprestimos) {
    if (emprestimos >= 0) {                  // Evita numero negativo de emprestimos.
        totalEmprestimos = emprestimos;      // Atualiza o atributo.
    }
}

// ------------------------------------------------------------
// getTipo: retorna o tipo generico da classe base. Sera
// sobrescrito por Livro, Periodico e DVD.
// ------------------------------------------------------------
string ItemAcervo::getTipo() const {
    return "Item";
}

// ------------------------------------------------------------
// calculaMulta: implementacao padrao na classe base (R$ 1,00
// por dia de atraso). Sera sobrescrita nas classes derivadas.
// ------------------------------------------------------------
double ItemAcervo::calculaMulta(int diasAtraso) const {
    if (diasAtraso <= 0) return 0.0;         // Sem atraso, sem multa.
    return diasAtraso * 1.00;                // Cobranca padrao de R$ 1,00/dia.
}

// ------------------------------------------------------------
// imprimirDetalhes: formata e escreve os atributos comuns
// no fluxo de saida (ostream). As derivadas chamam este metodo
// e acrescentam seus proprios atributos especificos.
// ------------------------------------------------------------
void ItemAcervo::imprimirDetalhes(ostream& out) const {
    out << "[" << getTipo() << "] "          // Chama getTipo() polimorficamente.
        << "Codigo: " << codigo
        << " | Titulo: " << titulo
        << " | Ano: " << anoPublicacao
        << " | Emprestimos: " << totalEmprestimos;
}

// ------------------------------------------------------------
// operator<: compara dois itens em ordem alfabetica pelo
// atributo codigo. Retorna true se este item vier antes.
// ------------------------------------------------------------
bool ItemAcervo::operator<(const ItemAcervo& outro) const {
    return codigo < outro.codigo;
}

// ------------------------------------------------------------
// operator==: verifica se dois itens possuem exatamente o
// mesmo codigo. Retorna true em caso afirmativo.
// ------------------------------------------------------------
bool ItemAcervo::operator==(const ItemAcervo& outro) const {
    return codigo == outro.codigo;
}

// ------------------------------------------------------------
// operator<< (por referencia): permite usar "cout << item".
// Chama imprimirDetalhes, que usa ligacao dinamica (virtual).
// ------------------------------------------------------------
ostream& operator<<(ostream& out, const ItemAcervo& item) {
    item.imprimirDetalhes(out);              // Executa a versao da classe real do objeto.
    return out;                              // Retorna o fluxo para permitir encadeamento.
}

// ------------------------------------------------------------
// operator<< (por ponteiro): permite usar "cout << ptrItem".
// Verifica se o ponteiro nao e nulo antes de desreferenciar.
// ------------------------------------------------------------
ostream& operator<<(ostream& out, const ItemAcervo* item) {
    if (item != NULL) {                      // Protecao contra ponteiro nulo.
        item->imprimirDetalhes(out);         // Chama o metodo virtual via ponteiro.
    }
    return out;
}