/**************** Linguagens de Programação - Laboratório 1************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 28/08/2026*/


/****************Programa Principal************/

#include <iostream>

/*Questão 1)*/

/*Letra c) Agenda - Orientação a Objetos*/

using namespace std;

class Agenda {
	public:
		void setNomes () {
			string nome;

			for (int index = 0; index < 3; index++) {
				cout << "Entre com o nome " << (index+1) << ": " << endl;
				getline (cin, nome);
				nomes [index] = checkNome (nome);
			}
		}

		void getNomes () {
			cout << "\nOs nomes na agenda são: " << endl;

			for (int index = 0; index < 3; index++)
				cout << nomes [index] << endl;
		}

	private:
		string nomes [3];

		string checkNome (string nome) {
			if (nome.length () > 10) {
				nome = nome.substr (0, 10);
				cout << "Nome truncado para: " << nome << endl;
			}
			return nome;
		}
};

int main () {
	/*Objeto da Classe Agenda*/
	Agenda agenda;

	agenda.setNomes ();
	agenda.getNomes ();

	return 0;
}
