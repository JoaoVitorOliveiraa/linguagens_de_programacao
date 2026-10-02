/**************** Linguagens de Programação - Laboratório 1************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 28/08/2026*/


/****************Programa Principal************/

#include <iostream>

/*Questão 1)*/

/*Letra b) Fibonacci - Orientação a Objetos*/

using namespace std;

/*Definindo a classe*/
class Fibonacci {
	public:
		void setFibonacci (int index) {
			resultado_fibonacci = calcularFibonacci (index);
		}

		int getFibonacci () { return resultado_fibonacci; }

	private:
		int calcularFibonacci (int index) {
		
			/*Tratando os índices não positivos*/
			if (index == 0)
				return 0;
			else if (index == 1)
				return 1;
			else
				return calcularFibonacci (index-1) + calcularFibonacci (index-2);
		}
		
		/*Declaração da variável que armazena o resultado*/
		int resultado_fibonacci;
};


int main () {

	/*Objeto da classe Fibonacci*/
	Fibonacci fibonacci;
	int index;

	cout << "Entre com o índice da série de Fibonacci: ";
	cin >> index;

	fibonacci.setFibonacci (index);

	cout << "\n\nO número é: " << fibonacci.getFibonacci () << endl;

	return 0;
}
