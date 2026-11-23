// ============================================================
// Arquivo: lista.h
// Descricao: Definicao e implementacao da classe template
//            Lista<T>, que implementa uma lista simplesmente
//            encadeada ordenada de forma crescente.
//            Como se trata de um template, toda a implementacao
//            permanece no arquivo .h para que o compilador possa
//            gerar o codigo no momento da instanciacao.
// ============================================================

#ifndef LISTA_H                  // Guarda de inclusao.
#define LISTA_H

#include <iostream>              // Para usar cout, ostream e endl.

using namespace std;             // Permite omitir std::.

// ------------------------------------------------------------
// Funcoes auxiliares template sobrecarregadas:
// Permitem que a Lista<T> compare e imprima corretamente tanto
// valores diretos (T) quanto ponteiros (T*), desreferenciando-os
// automaticamente quando T for um tipo ponteiro (ex: ItemAcervo*).
// ------------------------------------------------------------
template <class T>
bool menorQue(const T& a, const T& b) {
    return a < b;                // Comparacao direta entre objetos.
}

template <class T>
bool menorQue(T* const& a, T* const& b) {
    return (*a) < (*b);          // Compara o conteudo apontado (usa ItemAcervo::operator<).
}

template <class T>
bool igualA(const T& a, const T& b) {
    return a == b;               // Igualdade direta entre objetos.
}

template <class T>
bool igualA(T* const& a, T* const& b) {
    return (*a) == (*b);         // Compara o conteudo apontado (usa ItemAcervo::operator==).
}

template <class T>
void imprimirElemento(ostream& out, const T& a) {
    out << a;                    // Imprime objeto diretamente.
}

template <class T>
void imprimirElemento(ostream& out, T* const& a) {
    out << (*a);                 // Imprime o objeto apontado (usa ItemAcervo::operator<<).
}

// ------------------------------------------------------------
// Struct No<T>: representa cada celula (no) da lista
// simplesmente encadeada. Guarda o dado generico e o ponteiro
// para o proximo no da sequencia.
// ------------------------------------------------------------
template <class T>
struct No {
    T dado;                      // Informacao armazenada no no.
    No<T>* proximo;              // Ponteiro para o proximo no (ou NULL se for o ultimo).

    // Construtor do no: guarda o dado e inicializa proximo com NULL.
    No(T d) : dado(d), proximo(NULL) {}
};

// ------------------------------------------------------------
// Classe template Lista<T>: gerencia a lista encadeada a
// partir do ponteiro privado "cabeca".
// ------------------------------------------------------------
template <class T>
class Lista {
    // Sobrecarga global amiga do operador << para imprimir toda a lista
    // atraves da expressao "cout << lista;".
    friend ostream& operator<<(ostream& out, const Lista<T>& lista) {
        if (lista.cabeca == NULL) {              // Se a lista nao tem elementos:
            out << "Acervo vazio." << endl;
            return out;
        }

        No<T>* atual = lista.cabeca;             // Comeca pela cabeca (primeiro no).
        while (atual != NULL) {                  // Percorre ate o fim da lista.
            imprimirElemento(out, atual->dado);  // Imprime o elemento do no atual.
            out << endl;
            atual = atual->proximo;              // Avanca para o proximo no.
        }
        return out;                              // Retorna o fluxo de saida.
    }

public:
    // Construtor padrao: inicia a lista vazia (cabeca apontando para NULL).
    Lista() : cabeca(NULL) {}

    // Construtor de copia: cria uma copia profunda dos nos da lista.
    // Necessario porque o operador + retorna uma nova Lista por valor,
    // evitando que dois objetos Lista compartilhem os mesmos nos na memoria.
    Lista(const Lista<T>& outra) : cabeca(NULL) {
        copiarDe(outra);
    }

    // Destrutor: libera toda a memoria alocada para os nos da lista.
    ~Lista() {
        limpar();
    }

    // Sobrecarga do operador = (atribuicao): permite executar a instrucao
    // "lista = lista + item;" sem vazamento de memoria.
    Lista<T>& operator=(const Lista<T>& outra) {
        if (this != &outra) {        // Protecao contra auto-atribuicao (lista = lista).
            limpar();                // Libera os nos antigos desta lista.
            copiarDe(outra);         // Copia os nos da lista recebida.
        }
        return *this;                // Retorna referencia para o proprio objeto.
    }

    // --------------------------------------------------------
    // Sobrecarga do operador +: insere um elemento mantendo a
    // lista ordenada em ordem crescente.
    // Se ja existir um elemento igual (mesmo codigo), retorna
    // uma copia da lista original sem alteracoes.
    // --------------------------------------------------------
    Lista<T> operator+(T item) const {
        // Cria uma copia da lista atual para preservar a original em caso de falha.
        Lista<T> resultado(*this);

        // 1) Percorre a lista verificando se o item ja existe (evita duplicatas).
        No<T>* verifica = resultado.cabeca;
        while (verifica != NULL) {
            if (igualA(item, verifica->dado)) {
                return resultado;    // Falha: codigo duplicado, retorna sem alterar.
            }
            verifica = verifica->proximo;
        }

        // Aloca dinamicamente o novo no que sera inserido.
        No<T>* novoNo = new No<T>(item);

        // 2) Caso a lista esteja vazia OU o novo item seja menor que o primeiro no:
        // insere o novo no exatamente no inicio (nova cabeca).
        if (resultado.cabeca == NULL || menorQue(item, resultado.cabeca->dado)) {
            novoNo->proximo = resultado.cabeca;
            resultado.cabeca = novoNo;
            return resultado;
        }

        // 3) Caso geral: percorre a partir da cabeca ate encontrar o primeiro
        // no cujo elemento seja maior que o novo item (ou chegar ao fim).
        No<T>* anterior = resultado.cabeca;
        No<T>* atual = resultado.cabeca->proximo;

        while (atual != NULL && !menorQue(item, atual->dado)) {
            anterior = atual;        // Guarda o no anterior.
            atual = atual->proximo;  // Avanca para o proximo no.
        }

        // Encadeia o novo no entre "anterior" e "atual".
        novoNo->proximo = atual;
        anterior->proximo = novoNo;

        return resultado;            // Retorna a nova lista ordenada.
    }

    // --------------------------------------------------------
    // buscar: percorre a lista procurando um elemento igual a
    // "chave". Retorna o dado encontrado ou NULL caso nao ache.
    // --------------------------------------------------------
    T buscar(T chave) const {
        No<T>* atual = cabeca;
        while (atual != NULL) {
            if (igualA(chave, atual->dado)) {
                return atual->dado;  // Encontrou: retorna o elemento armazenado.
            }
            atual = atual->proximo;
        }
        return NULL;                 // Nao encontrou: retorna NULL.
    }

    // --------------------------------------------------------
    // getCabeca: retorna o ponteiro para o primeiro no da lista,
    // permitindo que a classe Biblioteca percorra os elementos.
    // --------------------------------------------------------
    No<T>* getCabeca() const {
        return cabeca;
    }

private:
    No<T>* cabeca;               // Ponteiro para o primeiro no da lista encadeada.

    // Metodo auxiliar privado: desaloca todos os nos da lista.
    void limpar() {
        No<T>* atual = cabeca;
        while (atual != NULL) {
            No<T>* temp = atual;     // Salva o ponteiro do no atual antes de avancar.
            atual = atual->proximo;  // Avanca para o proximo no.
            delete temp;             // Libera a memoria do no salvo.
        }
        cabeca = NULL;               // Garante que a lista fique marcada como vazia.
    }

    // Metodo auxiliar privado: duplica encadeadamente os nos de "outra".
    void copiarDe(const Lista<T>& outra) {
        if (outra.cabeca == NULL) {
            cabeca = NULL;
            return;
        }

        // Copia o primeiro no (cabeca).
        cabeca = new No<T>(outra.cabeca->dado);
        No<T>* destino = cabeca;
        No<T>* origem = outra.cabeca->proximo;

        // Copia cada no subsequente mantendo a mesma ordem.
        while (origem != NULL) {
            destino->proximo = new No<T>(origem->dado);
            destino = destino->proximo;
            origem = origem->proximo;
        }
    }
};

#endif                           // Fim da guarda de inclusao.