// ============================================================
// Arquivo: periodico.h
// Descricao: Definicao da classe derivada Periodico, que herda
//            publicamente de ItemAcervo e acrescenta o
//            atributo privado numEdicao.
// ============================================================

#ifndef PERIODICO_H             
#define PERIODICO_H

#include "item_acervo.h"         // Inclui a definicao da classe base.

class Periodico : public ItemAcervo { // Heranca publica de ItemAcervo.
public:
    // Construtor: recebe os atributos da base e o numero da edicao.
    Periodico(string cod, string tit, int ano, int edicao, int emprestimos = 0);

    // Metodos get e set para o atributo especifico numEdicao.
    int getNumEdicao() const;
    void setNumEdicao(int edicao);

    // Sobrescrita dos metodos virtuais da classe base.
    virtual string getTipo() const;
    virtual double calculaMulta(int diasAtraso) const;
    virtual void imprimirDetalhes(ostream& out) const;

private:
    int numEdicao;               // Atributo especifico da classe Periodico.
};

#endif                           