/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/

/*Questão 1)*/

/*Letra c) Declaração da classe Carro2*/

#include "carro2.h"

Carro::Carro(string m, int a, float p) { modelo = m; ano = a; preco = p; }

void Carro::exibir(){
	cout << "Modelo: " << modelo
		<< ", Ano: " << ano
		<< ", Preco: R$ " << preco << endl;
}

void Carro::atualizarPreco(Carro& outro) {
	preco = outro.preco;
}

void Carro::atualizarPreco(Carro* outro) {
	if (outro != NULL) {
		preco = outro->preco;
	}
}

bool Carro::compararAno(Carro& outro) {
	return ano > outro.ano; // true se for mais novo
}

bool Carro::compararAno(Carro* outro) {
	if (outro != NULL) {
		return ano > outro->ano;
	}
	
	return false;
}
