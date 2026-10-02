/**************** Linguagens de Programação - Laboratório 1************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 28/08/2026*/


/****************Programa Principal************/

#include <iostream>

/*Questão 1)*/

/*Letra a) Fibonacci - Procedural*/

using namespace std;

int calcularFibonacci (int index) {
	
	/*Tratando dos índices não positivos*/
	if (index == 0)
		return 0;
	else if (index == 1)
		return 1;
	else
		return calcularFibonacci (index-1) + calcularFibonacci (index-2);
}

int main () {
	
	/*Declaração da variável de índices*/
	int index;

	cout << "Entre com o índice da série de Fibonacci: ";
	cin >> index;

	cout << "\n\nO número é: " << calcularFibonacci (index) << endl;

	return 0;
}
