/******************************* Programa Principal ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) a)*******/

#include <iostream>

#include "agenda.h"

using namespace std;

int main () {
	Agenda agenda;

	agenda.insereContato("João", "Estudante", 23);
	agenda.insereContato("Jimmy", "Modelo", 22);

	// A agenda estará cheia aqui da primeira vez que o programa for executado
	agenda.insereContato("nao entra", "professor", 30);

	agenda.mostraTodos ();

	// Teste de uma remoção
	agenda.removeContato("miguel");

	// Vou tentar inserir um contato que já exista...
	agenda.insereContato ("aristoteles", "estudante", 21);

	// Vou inserir um contato diferente porque agora tem espaço
	agenda.insereContato("fatima", "jornalista", 50);

	agenda.mostraTodos ();

	// Vou editar a idade do Aristoles e a profissao dele...
	agenda.editaIdadeContato("aristoteles", 1000);
	agenda.editaProfissaoContato("aristoteles", "cientista");

	agenda.mostraTodos ();

	/* Os dados serão escritos no arquivo.
	Por enquanto, este método precisará ser
	invocado explicitamente... */
	agenda.escreveArquivo();

	return 0;
}
