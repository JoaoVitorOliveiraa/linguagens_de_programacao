/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Arquivo linha.h************/

#include <cmath>
#include "ponto.h"

using namespace std;

class Linha {
	public:
		Linha (Ponto, Ponto);

		void setP1 (Ponto);
		void setP2 (Ponto);

		double getComprimento ();
	
	private:
		Ponto p1, p2;
};
