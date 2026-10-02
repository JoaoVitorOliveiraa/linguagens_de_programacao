/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/

/****************Arquivo paralelepipedo.h************/

#include <iostream>

using namespace std;

class Paralelepipedo {
	public:
		Paralelepipedo (double, double, double);

		void setDimX (double);
		void setDimY (double);
		void setDimZ (double);

		double getVolume ();

	private:
		double dimX, dimY, dimZ;

		double computeVolume ();
};

