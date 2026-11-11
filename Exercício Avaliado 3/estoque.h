// ============================================================
// Arquivo: estoque.h
// Descrição: Definição da classe EstoqueComponentes, que gerencia
//            o vector de componentes, a capacidade máxima e a
//            persistência em arquivo.
//            Declara todos os operadores sobrecarregados
//            (<<, +=, -=, *, (), double).
// ============================================================

#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "componente.h"

using namespace std;

class EstoqueComponentes {
    // Permite que o cout acesse os dados privados do estoque para imprimir
    friend ostream& operator<<(ostream& os, const EstoqueComponentes& estoque);

public:
    // Construtor que define a capacidade máxima e carrega o arquivo
    EstoqueComponentes(int capacidadeMax);
    ~EstoqueComponentes(); // Destrutor para salvar os dados no arquivo

    // Operador de conversão explícita para double (Valor total do estoque)
    explicit operator double() const;

    // Operador de consulta por faixa de preço
    vector<Componente> operator()(double precoMin, double precoMax) const;

    // Entrada e saída de componentes
    EstoqueComponentes& operator+=(const Componente& comp);
    EstoqueComponentes& operator-=(const Componente& comp);

    // Reajuste de preços (retorna um novo objeto temporário)
    EstoqueComponentes operator*(double fator) const;

    // Método para salvar os dados no arquivo
    void salvarNoArquivo() const;

private:
    vector<Componente> componentes;
    int capacidadeMaxima;
    string nomeArquivo;

    void carregarDoArquivo();
    int buscarIndicePorCodigo(string cod) const;
};

#endif