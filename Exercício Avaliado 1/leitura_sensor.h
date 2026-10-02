// ============================================================
// Arquivo: leitura_sensor.h
// Descricao: Definicao da classe LeituraSensor, que representa
//            um dado coletado por um sensor de uma estacao.
//            Contem 3 atributos privados: nome da grandeza,
//            valor numerico e instante da coleta.
// ============================================================

#include <string>                // Necessario para usar a classe string.

using namespace std;             // Permite usar string sem o prefixo std::.

class LeituraSensor {            // Declaracao da classe LeituraSensor.
public:
    // Construtor: recebe nome da grandeza, valor e instante.
    // Inicializa os tres atributos privados da classe.
    LeituraSensor(string nomeGrandeza, double valorLeitura, int instanteColeta);

    // Metodos get: retornam o valor de cada atributo privado.
    string getNome();            // Retorna o nome da grandeza (ex: "temperatura").
    double getValor();           // Retorna o valor numerico da leitura.
    int getInstante();           // Retorna o instante da coleta.

    // Metodos set: permitem alterar cada atributo privado.
    void setNome(string n);      // Altera o nome da grandeza.
    void setValor(double v);     // Altera o valor numerico.
    void setInstante(int i);     // Altera o instante.

private:
    string nome;                 // Atributo privado: nome da grandeza medida.
    double valor;                // Atributo privado: valor numerico da leitura.
    int instante;                // Atributo privado: ordem cronologica da coleta.
};