// ============================================================
// Arquivo: main.cpp
// Descricao: Programa principal. Inicializa a Biblioteca com
//            alguns itens de exemplo e exibe um menu interativo
//            com 5 operacoes (inserir, buscar, imprimir,
//            registrar emprestimo e calcular multa media).
//            Trata entradas invalidas do usuario para evitar
//            loop infinito ou encerramento inesperado.
// ============================================================

#include <iostream>              // Para cin, cout e endl.
#include <string>                // Para usar string.
#include "biblioteca.h"          // Inclui a classe gerenciadora Biblioteca.
#include "livro.h"               // Inclui a classe derivada Livro.
#include "periodico.h"           // Inclui a classe derivada Periodico.
#include "dvd.h"                 // Inclui a classe derivada DVD.

using namespace std;             // Permite omitir std::.

// ------------------------------------------------------------
// Funcao auxiliar limparBuffer: limpa o estado de erro do cin
// e descarta caracteres pendentes no buffer ate o Enter.
// ------------------------------------------------------------
void limparBuffer() {
    cin.clear();                 // Reseta as flags de erro do fluxo cin.
    cin.ignore(1000, '\n');      // Descarta ate 1000 caracteres ate a quebra de linha.
}

// ------------------------------------------------------------
// Funcao auxiliar carregarAcervoInicial: insere itens variados
// (Livros, Periodico e DVD) fora de ordem alfabetica para
// demonstrar a insercao ordenada e o polimorfismo logo no inicio.
// ------------------------------------------------------------
void carregarAcervoInicial(Biblioteca& biblioteca) {
    biblioteca.insere(new Livro("LIV-0042", "C++ Como Programar", 2016, 1088, 12));
    biblioteca.insere(new Periodico("PER-0010", "IEEE Transactions on Computers", 2025, 74, 5));
    biblioteca.insere(new DVD("DVD-0005", "Arquitetura de Computadores - Aula", 2024, 120, 8));
    biblioteca.insere(new Livro("LIV-0015", "Algoritmos: Teoria e Pratica", 2012, 928, 20));
}

int main() {
    Biblioteca biblioteca;               // Cria o objeto gerenciador do acervo.
    carregarAcervoInicial(biblioteca);   // Pre-carrega 4 itens de exemplo.

    int opcao;                           // Variavel para armazenar a escolha do menu.

    // Laco do-while: exibe o menu pelo menos uma vez e repete ate opcao == 0.
    do {
        cout << "\n========== MENU BIBLIOTECA ==========" << endl;
        cout << "1 - Inserir novo item no acervo" << endl;
        cout << "2 - Buscar item por codigo" << endl;
        cout << "3 - Imprimir acervo completo" << endl;
        cout << "4 - Registrar/atualizar emprestimos" << endl;
        cout << "5 - Calcular multa media por tipo" << endl;
        cout << "0 - Sair" << endl;
        cout << "\nOpcao: ";

        cin >> opcao;                    // Le a opcao numerica do usuario.

        // Tratamento caso o usuario digite letras em vez de numeros.
        if (cin.fail()) {
            limparBuffer();              // Limpa o erro e o buffer do teclado.
            opcao = -1;                  // Garante que o laco continue.
            cout << "\nOpcao invalida! Digite um numero entre 0 e 5." << endl;
            continue;                    // Retorna ao inicio do menu.
        }
        cin.ignore();                    // Limpa o '\n' deixado pelo cin >> opcao.

        // -----------------------------------------------------
        // Opcao 1: Inserir novo item (Livro, Periodico ou DVD)
        // -----------------------------------------------------
        if (opcao == 1) {
            int tipo;
            cout << "\nTipo de item (1 - Livro | 2 - Periodico | 3 - DVD): ";
            cin >> tipo;

            // Valida se o tipo escolhido esta entre 1 e 3.
            if (cin.fail() || tipo < 1 || tipo > 3) {
                limparBuffer();
                cout << "Tipo invalido! Escolha 1, 2 ou 3." << endl;
                continue;
            }
            cin.ignore();                // Limpa o '\n' antes de usar getline.

            string codigo, titulo;
            int ano, emprestimos;

            cout << "Codigo (ex: LIV-0100): ";
            getline(cin, codigo);        // Le o codigo alfanumerico.
            cout << "Titulo: ";
            getline(cin, titulo);        // Le o titulo completo (com espacos).
            cout << "Ano de publicacao: ";
            cin >> ano;
            cout << "Total de emprestimos iniciais: ";
            cin >> emprestimos;

            // Ponteiro polimorfico da classe base que recebera o objeto derivado.
            ItemAcervo* novoItem = NULL;

            if (tipo == 1) {
                int paginas;
                cout << "Numero de paginas: ";
                cin >> paginas;
                // Instancia um Livro dinamicamente.
                novoItem = new Livro(codigo, titulo, ano, paginas, emprestimos);
            } else if (tipo == 2) {
                int edicao;
                cout << "Numero da edicao: ";
                cin >> edicao;
                // Instancia um Periodico dinamicamente.
                novoItem = new Periodico(codigo, titulo, ano, edicao, emprestimos);
            } else if (tipo == 3) {
                int duracao;
                cout << "Duracao (minutos): ";
                cin >> duracao;
                // Instancia um DVD dinamicamente.
                novoItem = new DVD(codigo, titulo, ano, duracao, emprestimos);
            }

            // Verifica se houve erro na leitura de algum campo numerico.
            if (cin.fail()) {
                limparBuffer();
                delete novoItem;         // Evita vazamento de memoria se ja havia alocado.
                cout << "Erro nos dados numericos informados!" << endl;
                continue;
            }
            cin.ignore();                // Limpa o buffer.

            // Tenta inserir o item na lista ordenada da biblioteca.
            if (biblioteca.insere(novoItem)) {
                cout << "[INFO] Item inserido com sucesso em ordem crescente!" << endl;
            } else {
                // Se o codigo ja existir, a insercao falha e liberamos a memoria.
                delete novoItem;
                cout << "[ERRO] Ja existe um item com o codigo '" << codigo << "'." << endl;
            }
        }

        // -----------------------------------------------------
        // Opcao 2: Buscar item pelo codigo via biblioteca(codigo)
        // -----------------------------------------------------
        else if (opcao == 2) {
            string codigo;
            cout << "\nDigite o codigo do item: ";
            getline(cin, codigo);

            // Usa o operador () sobrecarregado com 1 argumento.
            ItemAcervo* encontrado = biblioteca(codigo);

            if (encontrado != NULL) {
                cout << "\nItem encontrado:" << endl;
                cout << encontrado << endl;  // Usa operator<< para ponteiro ItemAcervo*.
            } else {
                cout << "\nItem com codigo '" << codigo << "' nao encontrado." << endl;
            }
        }

        // -----------------------------------------------------
        // Opcao 3: Imprimir todo o acervo ordenado
        // -----------------------------------------------------
        else if (opcao == 3) {
            biblioteca.imprime();        // Internamente executa "cout << lista;".
        }

        // -----------------------------------------------------
        // Opcao 4: Registrar/atualizar emprestimos via operador ()
        // -----------------------------------------------------
        else if (opcao == 4) {
            string codigo;
            int novoTotal;

            cout << "\nDigite o codigo do item: ";
            getline(cin, codigo);
            cout << "Digite o novo total de emprestimos acumulados: ";
            cin >> novoTotal;

            // Valida se o numero digitado e valido e nao negativo.
            if (cin.fail() || novoTotal < 0) {
                limparBuffer();
                cout << "Valor de emprestimos invalido!" << endl;
                continue;
            }
            cin.ignore();

            // Usa o operador () sobrecarregado com 2 argumentos.
            ItemAcervo* atualizado = biblioteca(codigo, novoTotal);

            if (atualizado != NULL) {
                cout << "\nEmprestimos atualizados com sucesso:" << endl;
                cout << atualizado << endl;
            } else {
                cout << "\nItem com codigo '" << codigo << "' nao encontrado." << endl;
            }
        }

        // -----------------------------------------------------
        // Opcao 5: Calcular multa media agrupada por tipo
        // -----------------------------------------------------
        else if (opcao == 5) {
            int dias;
            cout << "\nInforme a quantidade de dias de atraso para simulacao: ";
            cin >> dias;

            // Valida se a quantidade de dias e um inteiro nao negativo.
            if (cin.fail() || dias < 0) {
                limparBuffer();
                cout << "Numero de dias invalido!" << endl;
                continue;
            }
            cin.ignore();

            // Executa o calculo polimorfico agrupado por Livro, Periodico e DVD.
            biblioteca.calculaMultaMedia(dias);
        }

        // -----------------------------------------------------
        // Qualquer outro numero fora do intervalo [0, 5]
        // -----------------------------------------------------
        else if (opcao != 0) {
            cout << "\nOpcao invalida! Escolha um numero entre 0 e 5." << endl;
        }

    } while (opcao != 0);                // Encerra quando o usuario digitar 0.

    cout << "\nEncerrando o programa.\n" << endl;
    return 0;                            // O destrutor de Biblioteca limpa toda a memoria.
}