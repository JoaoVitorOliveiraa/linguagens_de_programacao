// ============================================================
// Arquivo: main.cpp
// Descrição: Programa principal. Lê o arquivo de entrada e
//            monta o grafo. Depois exibe um menu com 5 opções.
//            Trata entradas inválidas do usuário no menu para
//            evitar loop infinito ou quebra do programa.
// ============================================================

#include <iostream>              // Para cin, cout e endl.
#include "grafo.h"               // Inclui a classe Grafo.
using namespace std;

int main() {
    Grafo grafo;                 // Cria o objeto Grafo.

    // Lê o arquivo de entrada e monta o grafo.
    grafo.lerArquivo("grafo.txt");

    int opcao;                   // Variável para armazenar a opção do menu.

    // Laço do-while: executa o menu pelo menos uma vez.
    do {
        // Exibe o menu na tela.
        cout << "\n========== MENU ==========" << endl;
        cout << "1 - Lista de adjacencia" << endl;
        cout << "2 - Graus dos vertices (maior, menor e medio)" << endl;
        cout << "3 - Componentes conexas" << endl;
        cout << "4 - Arvore geradora minima (Prim)" << endl;
        cout << "5 - Centralidade de proximidade (Dijkstra)" << endl;
        cout << "0 - Sair" << endl;
        cout << "\nOpcao: ";

        cin >> opcao;                   // Lê a entrada.
        
        cin.ignore();                   // Limpa o '\n' do buffer do teclado.

        // ---- TRATAMENTO DE ENTRADA INVÁLIDA ----
        // Se o usuário digitou letras, o cin falha.
        if (cin.fail()) {
            cin.clear();                // Limpa o estado de erro do cin.
            opcao = -1;                 // Limpa o valor anterior da variável para garantir que o menu continue.

            cin.ignore(1000, '\n');     // Descarta até 1000 caracteres digitados até o Enter.
            
            cout << "Opcao invalida! Por favor, digite um dos numeros abaixo:" << endl;
            continue;                   // Pula para o topo do do-while.
        }

        // ---- Chama o método correspondente a opção escolhida ----
        if (opcao == 1) {
            grafo.imprimirListaAdjacencia();
        }
        else if (opcao == 2) {
            grafo.imprimirGraus();
        }
        else if (opcao == 3) {
            grafo.imprimirComponentesConexas();
        }
        else if (opcao == 4) {
            grafo.imprimirArvoreGeradoraMinima();
        }
        else if (opcao == 5) {
            grafo.imprimirCentralidade();
        }
        else if (opcao != 0) {
            // Se o usuário digitou um número, mas não está entre 0 e 5.
            cout << "Opcao invalida! Escolha um numero entre 0 e 5." << endl;
        }

    } while (opcao != 0);        // Repete enquanto não for 0.

    cout << "Encerrando o programa.\n" << endl;
    return 0;                    // Fim do programa.
}