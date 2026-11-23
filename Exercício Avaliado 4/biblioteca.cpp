// ============================================================
// Arquivo: biblioteca.cpp
// Descricao: Implementacao dos metodos da classe Biblioteca.
// ============================================================

#include "biblioteca.h"          // Inclui a definicao da classe Biblioteca.

// ------------------------------------------------------------
// Construtor padrao: a lista encadeada ja e iniciada vazia
// automaticamente pelo construtor de Lista<ItemAcervo*>.
// ------------------------------------------------------------
Biblioteca::Biblioteca() {}

// ------------------------------------------------------------
// Destrutor: percorre a lista e libera a memoria de cada
// objeto (Livro, Periodico ou DVD) alocado com "new".
// Graças ao destrutor virtual de ItemAcervo, o destrutor
// correto da classe derivada e executado em cada delete.
// ------------------------------------------------------------
Biblioteca::~Biblioteca() {
    No<ItemAcervo*>* atual = lista.getCabeca();  // Inicia no primeiro no.
    while (atual != NULL) {                      // Percorre todos os nos.
        delete atual->dado;                      // Libera o objeto apontado.
        atual = atual->proximo;                  // Avanca para o proximo no.
    }
}

// ------------------------------------------------------------
// insere: adiciona um item ao acervo mantendo a ordenacao
// crescente por codigo atraves da expressao "lista = lista + item".
// ------------------------------------------------------------
bool Biblioteca::insere(ItemAcervo* item) {
    if (item == NULL) return false;              // Ignora ponteiro nulo.

    // Verifica antes se ja existe um item com o mesmo codigo.
    if (busca(item->getCodigo()) != NULL) {
        return false;                            // Falha: codigo duplicado.
    }

    // Utiliza o operador + sobrecarregado da classe template Lista.
    lista = lista + item;
    return true;                                 // Insercao bem-sucedida.
}

// ------------------------------------------------------------
// busca: procura um item pelo codigo invocando o operador ()
// sobrecarregado da propria classe Biblioteca.
// ------------------------------------------------------------
ItemAcervo* Biblioteca::busca(string codigo) {
    return (*this)(codigo);                      // Chama Biblioteca::operator()(codigo).
}

// ------------------------------------------------------------
// operator()(codigo): permite buscar um item usando a sintaxe
// biblioteca("LIV-0042"). Retorna ponteiro para o item ou NULL.
// ------------------------------------------------------------
ItemAcervo* Biblioteca::operator()(string codigo) {
    // Cria um objeto auxiliar temporario contendo apenas o codigo
    // desejado para que a lista possa comparar usando operator==.
    Livro chave(codigo, "", 0, 0);
    return lista.buscar(&chave);
}

// ------------------------------------------------------------
// operator()(codigo, novoTotalEmprestimos): permite atualizar
// os emprestimos usando biblioteca("LIV-0042", 15).
// Retorna o ponteiro para o item atualizado ou NULL.
// ------------------------------------------------------------
ItemAcervo* Biblioteca::operator()(string codigo, int novoTotalEmprestimos) {
    // Localiza o item utilizando a sobrecarga de 1 argumento do operador ().
    ItemAcervo* encontrado = (*this)(codigo);

    if (encontrado != NULL) {                    // Se o item existe no acervo:
        encontrado->setTotalEmprestimos(novoTotalEmprestimos); // Atualiza o total.
    }
    return encontrado;                           // Retorna o ponteiro (ou NULL).
}

// ------------------------------------------------------------
// imprime: exibe todo o acervo ordenado utilizando o operador <<
// sobrecarregado na classe template Lista ("cout << lista").
// ------------------------------------------------------------
void Biblioteca::imprime() {
    cout << "\n===== ACERVO DA BIBLIOTECA =====" << endl;
    cout << lista;                               // Chama operator<<(ostream&, Lista<T>&).
    cout << "================================" << endl;
}

// ------------------------------------------------------------
// calculaMultaMedia: percorre toda a lista de itens e calcula
// o valor medio de multa por atraso agrupado por tipo
// (Livro, Periodico e DVD).
// Demonstra polimorfismo ao chamar item->calculaMulta(diasAtraso)
// sem precisar saber antecipadamente qual e o tipo concreto.
// ------------------------------------------------------------
void Biblioteca::calculaMultaMedia(int diasAtraso) {
    // Acumuladores de soma das multas e contadores por tipo de item.
    double somaLivro = 0.0, somaPeriodico = 0.0, somaDVD = 0.0;
    int qtdLivro = 0, qtdPeriodico = 0, qtdDVD = 0;

    No<ItemAcervo*>* atual = lista.getCabeca();  // Inicia na cabeca da lista.

    while (atual != NULL) {
        ItemAcervo* item = atual->dado;          // Ponteiro polimorfico da classe base.
        string tipo = item->getTipo();           // Chamada virtual: identifica o tipo real.
        double multa = item->calculaMulta(diasAtraso); // Chamada virtual: aplica regra especifica.

        // Agrupa os valores conforme o tipo retornado.
        if (tipo == "Livro") {
            somaLivro += multa;
            qtdLivro++;
        } else if (tipo == "Periodico") {
            somaPeriodico += multa;
            qtdPeriodico++;
        } else if (tipo == "DVD") {
            somaDVD += multa;
            qtdDVD++;
        }

        atual = atual->proximo;                  // Avanca para o proximo no.
    }

    // Exibe os resultados formatados com duas casas decimais.
    cout << "\n===== MULTA MEDIA POR TIPO (" << diasAtraso << " dia(s) de atraso) =====" << endl;
    cout << fixed << setprecision(2);

    if (qtdLivro > 0)
        cout << "Livro (" << qtdLivro << " itens): R$ " << (somaLivro / qtdLivro) << endl;
    else
        cout << "Livro: Nenhum item cadastrado." << endl;

    if (qtdPeriodico > 0)
        cout << "Periodico (" << qtdPeriodico << " itens): R$ " << (somaPeriodico / qtdPeriodico) << endl;
    else
        cout << "Periodico: Nenhum item cadastrado." << endl;

    if (qtdDVD > 0)
        cout << "DVD (" << qtdDVD << " itens): R$ " << (somaDVD / qtdDVD) << endl;
    else
        cout << "DVD: Nenhum item cadastrado." << endl;
}