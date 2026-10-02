/**************** Linguagens de Programação - Laboratório 3************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 11/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/

/*Letra a) Diferença entre Ponteiros e Referências Usando Variáveis Inteiras*/

#include <iostream>

using namespace std;

int main() {

	/*Declaração das duas variáveis inteiras, com valores distintos*/
	int x = 100;
	int y = 200;

	/*Ponteiro para x*/
	int* ponteiro = &x;

	/*Referência para x*/
	int& referencia = x;

	cout << "\nValores iniciais:" << endl;
	cout << "x = " << x << ", y = " << y << endl;

	/*Alterando x através do ponteiro*/
	*ponteiro = 300;
	cout << "\nDepois de alterar via referencia (*ponteiro = 300):" << endl;
	cout << "x = " << x << ", y = " << y << endl;
	cout << "*ponteiro = " << *ponteiro << ", referencia = " << referencia << endl;

	/*Alterando x através da referência*/
	referencia = 400;
	cout << "\nDepois de alterar via referência (referencia = 400):" << endl;
 	cout << "x = " << x << ", y = " << y << endl;
	cout << "*ponteiro = " << *ponteiro << ", referencia = " << referencia << endl;

	/*Agora, o ponteiro aponta para y*/
	ponteiro = &y;

	/*Atribuiução via referência (não muda para onde "referencia" aponta, apenas copia o valor de y para x)*/
	referencia = y;

	cout << "\nDepois de mudar o ponteiro para y e fazer (referencia = y):" << endl;
 	cout << "x = " << x << ", y = " << y << endl;
	cout << "*ponteiro = " << *ponteiro << ", referencia = " << referencia << "\n" << endl;

	return 0;
}
