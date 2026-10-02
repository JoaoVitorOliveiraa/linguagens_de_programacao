/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/

/*Letra c) Criando dois objetos da classo Carro e exibindo seus atributos*/

#include <iostream>
#include <string>
#include "carro.h"

using namespace std;

int main() {
	/*Definindo os objetos*/
	Carro carro1("Fusca", 1980);
	Carro carro2("Civic", 2020);
	
	cout << "\n=== Antes das atualizações ===" << endl;
	cout << "Carro1: "; carro1.exibir();
	cout << "Carro2: "; carro2.exibir();
	
	/*Atualizando carro1 a partir de carro2 via ponteiro*/
	carro1.atualizarAno(&carro2);
	
	// Atualizando carro2 a partir de carro1 via referencia
	carro2.atualizarAno(carro1);
	
	cout << "\n=== Depois das atualizações ===" << endl;
	cout << "Carro1: "; carro1.exibir();
	cout << "Carro2: "; carro2.exibir();
	
	return 0;
}
