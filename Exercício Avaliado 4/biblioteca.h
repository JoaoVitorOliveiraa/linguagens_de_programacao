// ============================================================
// Arquivo: biblioteca.h
// Descricao: Definicao da classe Biblioteca, que gerencia o
//            acervo universitario usando uma lista encadeada
//            generica de ponteiros para a classe base
//            (Lista<ItemAcervo *>).
//            Oferece insercao ordenada, busca e atualizacao
//            via operador (), impressao e calculo polimorfico
//            de multa media por tipo.
// ============================================================

#ifndef BIBLIOTECA_H             
#define BIBLIOTECA_H

#include "lista.h"               
#include "item_acervo.h"         

using namespace std;             

class Biblioteca {               // Declaracao da classe Biblioteca.
public:
    // Construtor e Destrutor.
    Biblioteca();
    ~Biblioteca();

    // Insere um ponteiro de ItemAcervo na lista privada usando "lista = lista + item".
    // Retorna true se inseriu ou false se o codigo ja existia.
    bool insere(ItemAcervo* item);

    // Busca um item pelo codigo utilizando o operador ().
    ItemAcervo* busca(string codigo);

    // Sobrecarga do operador () com 1 argumento: busca por codigo.
    ItemAcervo* operator()(string codigo);

    // Sobrecarga do operador () com 2 argumentos: atualiza o total de emprestimos.
    ItemAcervo* operator()(string codigo, int novoTotalEmprestimos);

    // Imprime todos os itens do acervo utilizando "cout << lista".
    void imprime();

    // Calcula e exibe o valor medio de multa por atraso agrupado por tipo
    // de item derivado de ItemAcervo usando polimorfismo.
    void calculaMultaMedia(int diasAtraso = 1);

private:
    Lista<ItemAcervo*> lista;    // Lista encadeada privada de ponteiros polimorficos.
};

#endif                           