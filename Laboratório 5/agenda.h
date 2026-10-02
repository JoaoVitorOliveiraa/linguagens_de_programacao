/******************************* Arquivo agenda.h ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) a)*******/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "contato.h"

using namespace std;

class Agenda {
	public:
		Agenda (int = 3);

		void insereContato (string, string, int);
		void removeContato (string);

		void editaIdadeContato (string, int);
		void editaProfissaoContato (string, string);
		
		bool existeContato (string);

		void mostraTodos ();

		void lerArquivo ();
		void escreveArquivo ();

	private:
		vector <Contato> v;
		unsigned tamMaxAgenda;
		int tamMaxNome;
		fstream file;
		string nomeArquivo;
		
		string verificaNome (string);
};
