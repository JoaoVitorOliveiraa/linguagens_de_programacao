// ============================================================
// Arquivo: main.cpp
// Descricao: Programa principal. Le o arquivo de entrada e
//            monta o grafo. Depois exibe um menu com 5 opcoes.
// ============================================================

#include <iostream>              // Para cin, cout e endl.
#include "grafo.h"               // Inclui a classe Grafo.
using namespace std;

int main() {
    Grafo grafo;                 // Cria o objeto Grafo.

    // Le o arquivo de entrada e monta o grafo.
    grafo.lerArquivo("grafo.txt");

    int opcao;                   // Variavel para armazenar a opcao do menu.

    // Laco do-while: executa o menu pelo menos uma vez.
    do {
        // Exibe o menu na tela.
        cout << "\n========== MENU ==========" << endl;
        cout << "1 - Lista de adjacencia" << endl;
        cout << "2 - Graus dos vertices (maior, menor e medio)" << endl;
        cout << "3 - Componentes conexas" << endl;
        cout << "4 - Arvore geradora minima (Prim)" << endl;
        cout << "5 - Centralidade de proximidade (Dijkstra)" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";

        cin >> opcao;            // Le a opcao do usuario.
        cin.ignore();            // Limpa o '\n' do buffer do teclado.

        // ---- Chama o metodo correspondente a opcao escolhida ----
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

    } while (opcao != 0);        // Repete enquanto nao for 0.

    return 0;                    // Fim do programa.
}