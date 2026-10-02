/******************************* Programa Principal ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) b)*******/

#include <iostream>
#include <locale>
#include <string>

#include "cadastro.h"
#include "global.h"

using namespace std;

void formataMaiusculas (Cadastro &c) {
	for (unsigned i = 0; i < c.getNome().length(); i++)
		cout << static_cast<char>(toupper(c.getNome()[i]));
	cout << endl;

	for (unsigned i = 0; i < c.getEnd().length(); i++)
		cout << static_cast<char>(toupper(c.getEnd()[i]));

	cout << endl;
	
	for (unsigned i = 0; i < c.getTel().length(); i++)
		cout << static_cast<char>(toupper(c.getTel()[i]));

	cout << endl;
}

void formataCSV (Cadastro &c) {
	cout << c.getNome() << ',' << c.getEnd() << ',' << c.getTel() << endl;
}

int main() {
	Cadastro cadastro ("Aluno", "Av. Brigadeiro Trompowski", "2122223333");

	formataCadastro (cadastro, formataMaiusculas);

	cout << endl;

	formataCadastro (cadastro, formataCSV);

	return 0;
}
