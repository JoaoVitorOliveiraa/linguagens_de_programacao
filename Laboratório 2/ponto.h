/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Arquivo ponto.h************/

using namespace std;

class Ponto {
	public:
		Ponto (double = 1.0, double = 1.0, double = 1.0);
		
		double getCoordX ();
		double getCoordY ();
		double getCoordZ ();

		void setCoordX (double);
		void setCoordY (double);
		void setCoordZ (double);

	private:
		double coordX, coordY, coordZ;
};
