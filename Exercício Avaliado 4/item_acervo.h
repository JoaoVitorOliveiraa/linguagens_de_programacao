// ============================================================
// Arquivo: item_acervo.h
// Descricao: Definicao da classe base ItemAcervo, que representa
//            um item generico do acervo da biblioteca.
//            Contem os atributos privados comuns (codigo, titulo,
//            anoPublicacao e totalEmprestimos), metodos get/set,
//            sobrecarga dos operadores (<, ==, <<) e metodos
//            virtuais para comportamento polimorfico nas classes
//            derivadas (Livro, Periodico e DVD).
// ============================================================

#ifndef ITEM_ACERVO_H            // Guarda de inclusao: evita que o arquivo
#define ITEM_ACERVO_H            // seja incluido mais de uma vez na compilacao.

#include <iostream>              // Para usar cout, ostream e endl.
#include <iomanip>               // Para formatacao de saida.
#include <string>                // Para usar a classe string.

using namespace std;             // Permite omitir o prefixo std::.

class ItemAcervo {               // Declaracao da classe base ItemAcervo.
    // Funcoes globais amigas (friend) para permitir imprimir tanto
    // um objeto (cout << item) quanto um ponteiro (cout << ptrItem).
    friend ostream& operator<<(ostream& out, const ItemAcervo& item);
    friend ostream& operator<<(ostream& out, const ItemAcervo* item);

public:
    // Construtor: inicializa os atributos comuns do item.
    // O parametro emprestimos tem valor padrao igual a 0.
    ItemAcervo(string cod, string tit, int ano, int emprestimos = 0);

    // Destrutor virtual: essencial em classes base polimorficas para
    // garantir que o destrutor da classe derivada seja chamado quando
    // um objeto derivado for deletado atraves de um ponteiro ItemAcervo*.
    virtual ~ItemAcervo();

    // Metodos get (constantes, pois nao alteram os atributos do objeto).
    string getCodigo() const;          // Retorna o codigo do item (ex: "LIV-0042").
    string getTitulo() const;          // Retorna o titulo do item.
    int getAnoPublicacao() const;      // Retorna o ano de publicacao.
    int getTotalEmprestimos() const;   // Retorna o total de emprestimos acumulados.

    // Metodos set: permitem atualizar os atributos privados.
    void setCodigo(string cod);              // Atualiza o codigo.
    void setTitulo(string tit);              // Atualiza o titulo.
    void setAnoPublicacao(int ano);          // Atualiza o ano de publicacao.
    void setTotalEmprestimos(int emprestimos); // Atualiza o total de emprestimos.

    // Metodos virtuais: podem ser sobrescritos pelas classes derivadas
    // para que cada tipo de item tenha seu proprio comportamento.
    virtual string getTipo() const;                       // Retorna o nome do tipo do item.
    virtual double calculaMulta(int diasAtraso) const;    // Calcula a multa por atraso.
    virtual void imprimirDetalhes(ostream& out) const;    // Imprime os dados na tela.

    // Sobrecarga dos operadores de comparacao utilizando o codigo do item.
    bool operator<(const ItemAcervo& outro) const;        // Usado na ordenacao da lista.
    bool operator==(const ItemAcervo& outro) const;       // Usado na busca e duplicatas.

private:
    string codigo;               // Codigo alfanumerico identificador (ex: "LIV-0042").
    string titulo;               // Titulo da obra ou midia.
    int anoPublicacao;           // Ano em que o item foi publicado.
    int totalEmprestimos;        // Quantidade acumulada de vezes que foi emprestado.
};

#endif                           // Fim da guarda de inclusao.