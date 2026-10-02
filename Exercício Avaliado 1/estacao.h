// ============================================================
// Arquivo: estacao.h
// Descricao: Definicao da classe Estacao, que representa uma
//            estacao meteorologica. Armazena um nome e um
//            vector de objetos LeituraSensor.
// ============================================================

#include <string>                // Para usar string.
#include <vector>                // Para usar vector 
#include "leitura_sensor.h"      // Para poder armazenar LeituraSensor.

using namespace std;

class Estacao {                  // Declaracao da classe Estacao.
public:
    // Construtor: recebe o nome da estacao e inicializa o atributo.
    Estacao(string nomeEstacao);

    // Metodo get: retorna o nome da estacao.
    string getNome();

    // Insere uma nova leitura na estacao, com grandeza e valor.
    // O instante e calculado automaticamente pela propria classe.
    void inserirLeitura(string grandeza, double valor);

    // Retorna todas as leituras de uma grandeza especifica,
    // ordenadas pelo instante (crescente).
    vector<LeituraSensor> getLeiturasPorGrandeza(string grandeza);

    // Verifica se a estacao possui ao menos uma leitura
    // da grandeza informada. Retorna true ou false.
    bool possuiGrandeza(string grandeza);

    // Exibe na tela todos os dados da estacao (nome e leituras).
    void exibir();

private:
    string nome;                             // Nome da estacao (ex: "EST-CENTRO").
    vector<LeituraSensor> leituras;          // Vector que armazena todas as leituras.

    // Metodo auxiliar privado: calcula o proximo instante
    // para uma grandeza especifica (contador independente por grandeza).
    int calcularProximoInstante(string grandeza);
};