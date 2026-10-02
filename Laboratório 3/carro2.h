/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/


/*Questão 1)*/

/*Letra c) Esqueleto da classe Carro2*/

#include <iostream>
#include <string>

using namespace std;

class Carro {

	public:
		// Construtor
		Carro (string, int, float);
		
		// Exibir informações
		void exibir();
		
		// Atualizar preço - por referência
		void atualizarPreco (Carro&);
		
		// Atualizar preço - por ponteiro
		void atualizarPreco (Carro*);
		
		// Comparar ano - por referência
		bool compararAno (Carro&);
		
		// Comparar ano - por ponteiro
		bool compararAno(Carro*);

	private:
		string modelo;
		int ano;
		float preco;
};
