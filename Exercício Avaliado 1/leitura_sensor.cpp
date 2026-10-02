// ============================================================
// Arquivo: leitura_sensor.cpp
// Descricao: Implementacao dos metodos da classe LeituraSensor.
// ============================================================

#include "leitura_sensor.h"      // Inclui a definicao da classe.

// ------------------------------------------------------------
// Construtor: inicializa os tres atributos com os valores
// recebidos como parametro.
// ------------------------------------------------------------
LeituraSensor::LeituraSensor(string nomeGrandeza, double valorLeitura, int instanteColeta) {
    nome = nomeGrandeza;         // Atribui o nome da grandeza.
    valor = valorLeitura;        // Atribui o valor numerico.
    instante = instanteColeta;   // Atribui o instante da coleta.
}

// ------------------------------------------------------------
// Metodos get: apenas retornam o valor do atributo.
// ------------------------------------------------------------
string LeituraSensor::getNome() { return nome; }        // Retorna o nome.
double LeituraSensor::getValor() { return valor; }      // Retorna o valor.
int LeituraSensor::getInstante() { return instante; }   // Retorna o instante.

// ------------------------------------------------------------
// Metodos set: atribuem um novo valor ao atributo.
// ------------------------------------------------------------
void LeituraSensor::setNome(string n) { nome = n; }        // Atualiza o nome.
void LeituraSensor::setValor(double v) { valor = v; }      // Atualiza o valor.
void LeituraSensor::setInstante(int i) { instante = i; }   // Atualiza o instante.