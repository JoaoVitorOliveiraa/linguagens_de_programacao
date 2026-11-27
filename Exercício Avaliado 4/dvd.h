// ============================================================
// Arquivo: dvd.h
// Descricao: Definicao da classe derivada DVD, que herda
//            publicamente de ItemAcervo e acrescenta o
//            atributo privado duracaoMinutos.
// ============================================================

#ifndef DVD_H                    
#define DVD_H

#include "item_acervo.h"         

class DVD : public ItemAcervo {  // Heranca publica de ItemAcervo.
public:
    // Construtor: recebe os atributos da base e a duracao em minutos.
    DVD(string cod, string tit, int ano, int duracao, int emprestimos = 0);

    // Metodos get e set para o atributo especifico duracaoMinutos.
    int getDuracaoMinutos() const;
    void setDuracaoMinutos(int duracao);

    // Sobrescrita dos metodos virtuais da classe base.
    virtual string getTipo() const;
    virtual double calculaMulta(int diasAtraso) const;
    virtual void imprimirDetalhes(ostream& out) const;

private:
    int duracaoMinutos;          
};

#endif                           