/**************** Linguagens de Programação - Laboratório 2************/
/*Nome: João Vitor dos Santos Oliveira*/
/*Professor: Miguel Campista*/
/*Data: 04/09/2026*/


/****************Arquivo paralelepipedo.cpp************/

#include "paralelepipedo.h"

Paralelepipedo::Paralelepipedo (double x, double y, double z) {
	setDimX (x); setDimY (y); setDimZ (z);
}

void Paralelepipedo::setDimX (double x) {
	if (x > 0) dimX = x;
	else dimX = 1;
}

void Paralelepipedo::setDimY (double y) {
	if (y > 0) dimY = y;
	else dimY = 1;
}

void Paralelepipedo::setDimZ (double z) {
	if (z > 0) dimZ = z;
	else dimZ = 1;
}

double Paralelepipedo::getVolume () {
	return computeVolume ();
}

double Paralelepipedo::computeVolume () {
	return dimX*dimY*dimZ;
}

