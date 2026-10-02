// ============================================================
// Arquivo: main.cpp
// Descricao: Programa principal. Contem o menu interativo
//            que permite ao usuario acessar todas as
//            funcionalidades do sistema meteorologico.
// ============================================================

#include <iostream>                     // Para cin, cout, endl.
#include <string>                       // Para usar string.
#include "sistema_meteorologico.h"      // Inclui a classe principal do sistema.
using namespace std;

int main() {
    SistemaMeteorologico sistema;   // Cria o objeto que gerencia tudo.
    int opcao;                      // Variavel para armazenar a opcao do menu.

    // Laco do-while: executa o menu pelo menos uma vez e repete
    // enquanto a opcao for diferente de 0 (sair).
    do {
        // Exibe o menu na tela.
        cout << "\n========== MENU ==========" << endl;
        cout << "1 - Inserir nova estação" << endl;
        cout << "2 - Inserir nova leitura" << endl;
        cout << "3 - Média móvel por grandeza" << endl;
        cout << "4 - Ordenar por média móvel e detectar variação anormal" << endl;
        cout << "5 - Previsão (regressão linear)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opção: ";
        cin >> opcao;                // Le a opcao do usuario.
        cin.ignore();                // Limpa o '\n' deixado no buffer pelo cin.

        // -----------------------------------------------------
        // Opcao 1: Inserir nova estacao.
        // -----------------------------------------------------
        if (opcao == 1) {
            string nome;
            cout << "Nome da estação: ";
            getline(cin, nome);      // Le o nome completo (com espacos).
            sistema.inserirEstacao(nome);
            cout << "Estação inserida com sucesso!" << endl;
            sistema.exibirRelatorio();  // Exibe o relatorio completo.
        }

        // -----------------------------------------------------
        // Opcao 2: Inserir nova leitura.
        // -----------------------------------------------------
        else if (opcao == 2) {
            string nome, grandeza;
            double valor;

            cout << "Nome da estação: ";
            getline(cin, nome);      // Le o nome da estacao.
            cout << "Grandeza: ";
            getline(cin, grandeza);  // Le a grandeza (ex: temperatura).
            cout << "Valor: ";
            cin >> valor;            // Le o valor numerico.
            cin.ignore();            // Limpa o buffer.

            sistema.inserirLeitura(nome, grandeza, valor);
            sistema.exibirRelatorio();  // Exibe o relatorio atualizado.
        }

        // -----------------------------------------------------
        // Opcao 3: Calcular media movel de uma grandeza.
        // -----------------------------------------------------
        else if (opcao == 3) {
            string grandeza;
            cout << "Grandeza: ";
            getline(cin, grandeza);  // Le a grandeza desejada.
            sistema.calcularMediaMovel(grandeza, 3);  // Chama com janela N=3.
        }

        // -----------------------------------------------------
        // Opcao 4: Ordenar por media movel + detectar variacao.
        // -----------------------------------------------------
        else if (opcao == 4) {
            string grandeza;
            cout << "Grandeza: ";
            getline(cin, grandeza);  // Le a grandeza desejada.
            sistema.ordenarPorMediaMovel(grandeza, 3);  // Chama com N=3.
        }

        // -----------------------------------------------------
        // Opcao 5: Previsao por regressao linear.
        // -----------------------------------------------------
        else if (opcao == 5) {
            string nome, grandeza;
            cout << "Nome da estação: ";
            getline(cin, nome);      // Le o nome da estacao.
            cout << "Grandeza: ";
            getline(cin, grandeza);  // Le a grandeza desejada.
            sistema.preverProximaLeitura(nome, grandeza);  // Chama a previsao.
        }

    } while (opcao != 0);            // Repete enquanto nao for 0.

    return 0;                        // Fim do programa.
}