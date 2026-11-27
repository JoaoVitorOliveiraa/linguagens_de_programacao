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

#ifndef BIBLIOTECA_H             // Guarda de inclusao.
#define BIBLIOTECA_H

#include "lista.h"               // Estrutura de dados template Lista<T>.
#include "item_acervo.h"         // Classe base ItemAcervo (ja inclui <string>).

using namespace std;             // Permite omitir std::.

class Biblioteca {               // Declaracao da classe Biblioteca.
public:
    // Construtor e Destrutor.
    Biblioteca();
    ~Biblioteca();

    // Insere um ponteiro de ItemAcervo na lista privada usando "lista = lista + item".
    // Retorna true se inseriu ou false se o codigo ja existia.
    bool insere(ItemAcervo* item);

    // Busca um item pelo codigo utilizando o operador ().
    ItemAcervo* busca(string codigo) const;

    // Sobrecarga do operador () com 1 argumento: busca por codigo.
    ItemAcervo* operator()(string codigo) const;

    // Sobrecarga do operador () com 2 argumentos: atualiza o total de emprestimos.
    ItemAcervo* operator()(string codigo, int novoTotalEmprestimos);

    // Imprime todos os itens do acervo utilizando "cout << lista".
    void imprime() const;

    // Calcula e exibe o valor medio de multa por atraso agrupado por tipo
    // de item derivado de ItemAcervo usando polimorfismo.
    void calculaMultaMedia(int diasAtraso = 1) const;

private:
    Lista<ItemAcervo*> lista;    // Lista encadeada privada de ponteiros polimorficos.
};

#endif                           // Fim da guarda de inclusao.