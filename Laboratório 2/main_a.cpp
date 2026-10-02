/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Programa Principal************/

/*Questão 1)*/
/*Letra a) Cálculo do Volume de um Paralelepípedo Reto.*/

#include <iostream>
#include "paralelepipedo.h"

using namespace std;

int main () {
	double dx = 1, dy = 2, dz = 3;
	
	Paralelepipedo paralelepipedo (dx, dy, dz);

	cout << "\n\nO volume é:" << paralelepipedo.getVolume () << endl;

	cout << "\n\nmudando os valores das dimensões..." << endl;

	paralelepipedo.setDimX (-1);
	paralelepipedo.setDimY (3.3);
	paralelepipedo.setDimZ (4.4);

	cout << "O novo volume é: " << paralelepipedo.getVolume () << endl;
	return 0;
}

