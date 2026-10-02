// ============================================================
// Arquivo: sistema_meteorologico.h
// Descricao: Definicao da classe SistemaMeteorologico, que
//            gerencia todas as estacoes cadastradas.
// ============================================================

#include <vector>                // Para usar vector de estacoes.
#include <string>                // Para usar string.
#include "estacao.h"             // Para armazenar objetos Estacao.

using namespace std;

class SistemaMeteorologico {     // Declaracao da classe.
public:
    // Construtor padrao (nao faz nada especial).
    SistemaMeteorologico();

    // Insere uma nova estacao no sistema (a partir do nome).
    void inserirEstacao(string nome);

    // Insere uma nova leitura em uma estacao existente.
    void inserirLeitura(string nomeEstacao, string grandeza, double valor);

    // Busca uma estacao pelo nome. Retorna um ponteiro para ela,
    // ou NULL se nao encontrada (usado para evitar copias).
    Estacao* buscarEstacao(string nome);

    // Exibe o relatorio completo de todas as estacoes.
    void exibirRelatorio();

    // Item 3: calcula e exibe a evolucao da media movel
    // de uma grandeza, com janela N, para todas as estacoes.
    void calcularMediaMovel(string grandeza, int tamanhoJanela);

    // Item 4: ordena as estacoes pela ultima media movel e
    // detecta variacoes anormais (superiores a +/-15%).
    void ordenarPorMediaMovel(string grandeza, int tamanhoJanela);

    // Item 5: preve a proxima leitura via regressao linear.
    void preverProximaLeitura(string nomeEstacao, string grandeza);

private:
    vector<Estacao> estacoes;    // Vector que armazena todas as estacoes.
};