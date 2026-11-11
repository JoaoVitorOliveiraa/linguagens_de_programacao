// ============================================================
// Arquivo: main.cpp
// Descrição: Programa principal. Carrega o estoque do arquivo
//            e exibe um menu com 6 opções. Trata entradas
//            inválidas do usuário no menu para evitar loop
//            infinito ou quebra do programa.
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include "estoque.h"             // Inclui a classe EstoqueComponentes.
#include "componente.h"          // Inclui a struct Componente.
using namespace std;

// Define a capacidade máxima do estoque de forma explícita e fácil de alterar.
// Escolhido 15 como valor didático, já que o enunciado não especifica um número fixo.
const int CAPACIDADE_MAXIMA = 15;

// Função auxiliar para limpar o buffer do teclado de forma segura.
void limparBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

int main() {
    // O construtor já carrega automaticamente o arquivo estoque.txt.
    // Passamos a constante em vez do número "solto".
    EstoqueComponentes estoque(CAPACIDADE_MAXIMA); 
    
    int opcao;                   // Variável para armazenar a opção do menu.

    // Laço do-while: executa o menu pelo menos uma vez.
    do {
        // Exibe o menu na tela.
        cout << "\n========== MENU ESTOQUE ==========" << endl;
        cout << "1 - Imprimir estoque completo" << endl;
        cout << "2 - Adicionar componente (+=)" << endl;
        cout << "3 - Retirar componente (-=)" << endl;
        cout << "4 - Consultar por faixa de preco ()" << endl;
        cout << "5 - Reajustar precos (*)" << endl;
        cout << "6 - Ver valor total do estoque (double)" << endl;
        cout << "0 - Sair" << endl;
        cout << "\nOpcao: ";

        cin >> opcao;                   // Lê a entrada.
        
        // ---- TRATAMENTO DE ENTRADA INVÁLIDA ----
        // Se o usuário digitou letras, o cin falha.
        if (cin.fail()) {
            limparBuffer();             // Limpa o estado de erro e o buffer.
            opcao = -1;                 // Força uma opção inválida.
            
            cout << "\nOpcao invalida! Por favor, digite um dos numeros do menu." << endl;
            continue;                   // Pula para o topo do do-while.
        }
        
        // Limpa o '\n' que sobrou no buffer após o cin >> opcao.
        cin.ignore();                   

        // ---- Chama o método correspondente a opção escolhida ----
        if (opcao == 1) {
            cout << estoque;            // Usa o operador << sobrecarregado.
        }
        else if (opcao == 2) {
            Componente c;
            cout << "\n--- Cadastrar Novo Componente ---" << endl;
            cin >> c;                   // Usa o operador >> sobrecarregado.
            cin.ignore();               // Limpa o Enter após a leitura do preço.
            
            estoque += c;               // Usa o operador += sobrecarregado.
            cout << "[INFO] Operacao de entrada realizada." << endl;
        }
        else if (opcao == 3) {
            Componente c;
            cout << "\n--- Retirar Componente ---" << endl;
            cout << "Digite o codigo do componente: ";
            cin >> c.codigo;
            cout << "Digite a quantidade a retirar: ";
            cin >> c.quantidade;
            cin.ignore();               // Limpa o Enter.

            estoque -= c;               // Usa o operador -= sobrecarregado.
        }
        else if (opcao == 4) {
            double precoMin, precoMax;
            cout << "\n--- Consulta por Faixa de Preco ---" << endl;
            cout << "Preco minimo: R$ ";
            cin >> precoMin;
            cout << "Preco maximo: R$ ";
            cin >> precoMax;
            cin.ignore();               // Limpa o Enter.

            // Usa o operador () sobrecarregado.
            vector<Componente> encontrados = estoque(precoMin, precoMax);
            
            cout << "\n--- RESULTADO DA CONSULTA ---" << endl;
            if (encontrados.empty()) {
                cout << "Nenhum componente encontrado nesta faixa de preco." << endl;
            } else {
                for (unsigned i = 0; i < encontrados.size(); i++) {
                    cout << encontrados[i] << endl;
                }
            }
        }
        else if (opcao == 5) {
            double fator;
            cout << "\n--- Reajuste de Precos ---" << endl;
            cout << "Digite o fator de reajuste (ex: 1.10 para +10%): ";
            cin >> fator;
            cin.ignore();               // Limpa o Enter.

            // Usa o operador * sobrecarregado.
            EstoqueComponentes novoEstoque = estoque * fator;
            
            cout << "\n--- ESTOQUE COM PRECOS REAJUSTADOS (NAO SALVO) ---" << endl;
            cout << novoEstoque;
            cout << "\n[AVISO] O estoque original nao foi alterado." << endl;
        }
        else if (opcao == 6) {
            // Usa a conversão explícita para double.
            double total = static_cast<double>(estoque);
            cout << "\nValor total do estoque: R$ " << total << endl;
        }
        else if (opcao != 0) {
            // Se o usuário digitou um número, mas não está entre 0 e 6.
            cout << "\nOpcao invalida! Escolha um numero entre 0 e 6." << endl;
        }

    } while (opcao != 0);        // Repete enquanto não for 0.

    cout << "\nEncerrando o programa e salvando dados no arquivo...\n" << endl;
    
    return 0;                    // O destrutor do 'estoque' é chamado aqui e salva o arquivo.
}