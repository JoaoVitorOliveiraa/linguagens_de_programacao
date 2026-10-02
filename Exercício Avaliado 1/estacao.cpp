// ============================================================
// Arquivo: estacao.cpp
// Descricao: Implementacao dos metodos da classe Estacao.
// ============================================================

#include "estacao.h"             // Inclui a definicao da classe.
#include <iostream>              // Necessario para usar cout e endl.

// ------------------------------------------------------------
// Construtor: apenas guarda o nome da estacao.
// ------------------------------------------------------------
Estacao::Estacao(string nomeEstacao) {
    nome = nomeEstacao;          // Atribui o nome recebido ao atributo.
}

// ------------------------------------------------------------
// Metodo get: retorna o nome da estacao.
// ------------------------------------------------------------
string Estacao::getNome() { return nome; }

// ------------------------------------------------------------
// calcularProximoInstante: percorre todas as leituras ja
// armazenadas e descobre o maior instante daquela grandeza.
// Retorna esse maior instante + 1 (o proximo da sequencia).
// O contador e independente para cada grandeza.
// ------------------------------------------------------------
int Estacao::calcularProximoInstante(string grandeza) {
    int maior = 0;               // Comeca em 0 (nenhuma leitura ainda).

    // Percorre todo o vector de leituras.
    for (int i = 0; i < (int)leituras.size(); i++) {

        // Verifica se a leitura atual e da grandeza desejada.
        if (leituras[i].getNome() == grandeza) {

            // Se o instante desta leitura for maior que o maior atual,
            // atualiza a variavel "maior".
            if (leituras[i].getInstante() > maior)
                maior = leituras[i].getInstante();
        }
    }
    return maior + 1;            // Retorna o proximo instante da sequencia.
}

// ------------------------------------------------------------
// inserirLeitura: cria um novo objeto LeituraSensor com o
// instante calculado automaticamente, e adiciona ao vector.
// ------------------------------------------------------------
void Estacao::inserirLeitura(string grandeza, double valor) {
    int inst = calcularProximoInstante(grandeza);    // Calcula o instante.
    LeituraSensor leitura(grandeza, valor, inst);    // Cria o objeto.
    leituras.push_back(leitura);                     // Adiciona ao vector.
}

// ------------------------------------------------------------
// possuiGrandeza: verifica se existe alguma leitura da
// grandeza informada. Retorna true se sim, false caso contrario.
// ------------------------------------------------------------
bool Estacao::possuiGrandeza(string grandeza) {
    for (int i = 0; i < (int)leituras.size(); i++) {
        if (leituras[i].getNome() == grandeza)
            return true;         // Encontrou: retorna true imediatamente.
    }
    return false;                // Nao encontrou: retorna false.
}

// ------------------------------------------------------------
// getLeiturasPorGrandeza: retorna um vector com apenas as
// leituras da grandeza informada, ordenadas por instante.
// ------------------------------------------------------------
vector<LeituraSensor> Estacao::getLeiturasPorGrandeza(string grandeza) {
    vector<LeituraSensor> filtradas;   // Vector que armazenara as leituras filtradas.

    // Filtra as leituras pela grandeza informada.
    for (int i = 0; i < (int)leituras.size(); i++) {
        if (leituras[i].getNome() == grandeza)
            filtradas.push_back(leituras[i]);   // Adiciona ao vector filtrado.
    }

    // Ordenacao por instante (bubble sort - algoritmo simples).
    // Compara pares adjacentes e troca se estiverem fora de ordem.
    for (int i = 0; i < (int)filtradas.size() - 1; i++) {
        for (int j = 0; j < (int)filtradas.size() - 1 - i; j++) {
            if (filtradas[j].getInstante() > filtradas[j+1].getInstante()) {

                // Troca os dois objetos usando uma variavel temporaria.
                LeituraSensor temporaria = filtradas[j];
                filtradas[j] = filtradas[j+1];
                filtradas[j+1] = temporaria;
            }
        }
    }

    return filtradas;            // Retorna o vector filtrado e ordenado.
}

// ------------------------------------------------------------
// exibir: mostra na tela o nome da estacao e todas as suas
// leituras (grandeza, instante e valor).
// ------------------------------------------------------------
void Estacao::exibir() {
    cout << "Estação: " << nome << endl;       // Imprime o nome.

    // Percorre todas as leituras e imprime uma por uma.
    for (int i = 0; i < (int)leituras.size(); i++) {
        cout << "  [" << leituras[i].getNome() << "] "      // Grandeza.
             << "Instante " << leituras[i].getInstante()     // Instante.
             << " -> " << leituras[i].getValor() << endl;    // Valor.
    }
}