/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Arquivo linha.cpp************/

#include "linha.h"

Linha::Linha (Ponto p1_, Ponto p2_) {
	p1 = p1_; p2 = p2_;
}

void Linha::setP1 (Ponto p) {
	p1 = p;
}

void Linha::setP2 (Ponto p) {
	p2 = p;
}

double Linha::getComprimento () {
	return sqrt (pow (p1.getCoordX() - p2.getCoordX(), 2) + 
			pow (p1.getCoordY() - p2.getCoordY(), 2) +
			pow (p1.getCoordZ() - p2.getCoordZ(), 2));
}

