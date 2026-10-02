/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/

/*Questão 1)*/

/*Letra c) Esqueleto da classe Carro*/

#include <iostream>
#include <string>

using namespace std;

class Carro {
	public:
		// Construtor
		Carro(string, int);

		// Método para exibir os dados
		void exibir();
	
		// Método sobrecarregado: atualiza ano usando ponteiro
		void atualizarAno(Carro *);
	
		// Método sobrecarregado: atualiza ano usando referência
		void atualizarAno(Carro &);
	
	private:
		string modelo;
		int ano;
};
