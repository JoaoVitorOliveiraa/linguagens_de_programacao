/******************************* Arquivo cadastro.h ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) b)*******/

#include <iostream>
#include <string>

using namespace std;

class Cadastro {
	public:
		Cadastro (string, string, string);

		string getNome ();
		string getEnd ();
		string getTel ();

	private:
		string nome, end, tel;
};
