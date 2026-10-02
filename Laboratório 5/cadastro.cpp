/******************************* Arquivo cadastro.cpp ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) b)*******/

#include "cadastro.h"

Cadastro::Cadastro (string n, string e, string t) {
	nome = n; end = e; tel = t;
}

string Cadastro::getNome () {
	return nome;
}

string Cadastro::getEnd () {
	return end;
}

string Cadastro::getTel () {
	return tel;
}
