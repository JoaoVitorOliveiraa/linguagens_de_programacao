/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/

/*Letra b) Concatenar uma Palavra Extra ao Final de uma string*/

#include <iostream>
#include <string>

using namespace std;

/*Função que concatena usando ponteiro*/
void adicionarComPonteiro(string* texto, string sufixo) {
	/*Acessa e altera o conteúdo via ponteiro*/
	*texto += sufixo; 
}

/*Função que concatena usando referencia*/
void adicionarComReferencia(string& texto, string sufixo) {
	/*Acessa e altera o conteúdo diretamente*/
	texto += sufixo; 
}

int main() {
	string mensagem = "Jimmy, ";

	cout << "\nUsando ponteiro:" << endl;
	cout << "Antes: " << mensagem << endl;
	adicionarComPonteiro(&mensagem, "o chinês loiro de olhos azuis");
	cout << "Depois: " << mensagem << endl;

	/*Redefinindo para novo teste*/
	mensagem = "Ian ";

	cout << "\nUsando referência:" << endl;
	cout << "Antes: " << mensagem << endl;
	adicionarComReferencia(mensagem, "do bumbum guloso");
	cout << "Depois: " << mensagem << "\n" << endl;

	return 0;
}

