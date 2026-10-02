/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/

/*Questão 1)*/

/*Letra c) Declaração da classe Carro*/

#include "carro.h"

Carro::Carro(string m, int a) { modelo = m; ano = a; }

void Carro::exibir() {
	cout << "Modelo: " << modelo << ", Ano: " << ano << endl;
}

void Carro::atualizarAno(Carro* outro) {
	if (outro != NULL) {
		ano = (*outro).ano;
	}
}

void Carro::atualizarAno(Carro& outro) {
	ano = outro.ano;
}
