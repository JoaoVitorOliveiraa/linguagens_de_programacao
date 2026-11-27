// ============================================================
// Arquivo: livro.h
// Descricao: Definicao da classe derivada Livro, que herda
//            publicamente de ItemAcervo e acrescenta o
//            atributo privado numPaginas.
// ============================================================

#ifndef LIVRO_H                  
#define LIVRO_H

#include "item_acervo.h"

class Livro : public ItemAcervo { // Heranca publica de ItemAcervo.
public:
    // Construtor: recebe os atributos da base e o numero de paginas.
    Livro(string cod, string tit, int ano, int paginas, int emprestimos = 0);

    // Metodos get e set para o atributo especifico numPaginas.
    int getNumPaginas() const;
    void setNumPaginas(int paginas);

    // Sobrescrita dos metodos virtuais da classe base.
    virtual string getTipo() const;
    virtual double calculaMulta(int diasAtraso) const;
    virtual void imprimirDetalhes(ostream& out) const;

private:
    int numPaginas;            
};

#endif                         