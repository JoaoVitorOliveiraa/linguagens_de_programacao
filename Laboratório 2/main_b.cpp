/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/
/*Letra b) Cálculo do Comprimento de Linhas Usando Composição entre Classes.*/

#include <iostream>
#include "linha.h"

using namespace std;

void printCoordenadas (Ponto p) {
	cout << "Coordenadas de p (" << p.getCoordX ()
	       << ", " << p.getCoordY ()
       		<< ", " << p.getCoordZ ()
 		<< ")" << endl;		
}

int main () {
	Ponto p1 (2, 2, 1);
	Ponto p2; // Construtor da classe Ponto com argumentos padrão (1.0, 1.0, 1.0)
	Linha linha (p1, p2);
	
	printCoordenadas (p1);
	printCoordenadas (p2);
	
	cout << "== O comprimento da linha eh: " << linha.getComprimento () << endl;
	
	cout << "\nNovas coordenadas para p2...\n" << endl;
	p2.setCoordX(2); // Método setCoordX atualiza a coordenada X do ponto p2
	printCoordenadas (p2);
	
	linha.setP2 (p2); // Método setP2 atualiza o ponto p2 da linha
	
	cout << "== O NOVO comprimento da linha eh: " << linha.getComprimento () << endl;
	return 0;
}

