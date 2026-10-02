/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/

/*Letra d) Implementando a classe Carro adicionando o atributo privado float*/

#include <iostream>
#include <string>
#include "carro2.h"

using namespace std;

int main() {
	Carro fusca("Fusca", 1980, 15000.0);
	Carro civic("Civic", 2020, 90000.0);
	Carro corolla("Corolla", 2018, 80000.0);

	cout << "=== Antes das atualizacoes ===" << endl;
	fusca.exibir();
	civic.exibir();
	corolla.exibir();

	// Atualizando preços
	fusca.atualizarPreco(&civic); // via ponteiro
	corolla.atualizarPreco(fusca); // via referência

	cout << "\n=== Depois das atualizações ===" << endl;
	fusca.exibir();
	civic.exibir();
	corolla.exibir();

	// Comparações de ano
	cout << "\n=== Comparações de Ano ===" << endl;
	cout << "Civic mais novo que Corolla (ref)? "
	<< (civic.compararAno(corolla) ? "Sim" : "Nao") << endl;
	cout << "Civic mais novo que Corolla (ptr)? "
	<< (civic.compararAno(&corolla) ? "Sim" : "Nao") << endl;

	return 0;
}
