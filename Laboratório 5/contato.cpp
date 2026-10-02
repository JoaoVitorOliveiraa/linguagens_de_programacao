/******************************* Arquivo contato.cpp ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) a)*******/

#include "contato.h"

Contato::Contato (string n, string p, int i) {
	setNome (n); setProfissao (p); setIdade (i);
}

void Contato::setNome (string n) {
	nome = n;
}

void Contato::setProfissao (string p) {
	profissao = p;
}

void Contato::setIdade (int i) {
	idade = i;
}

string Contato::getNome () {
	return nome;
}

string Contato::getProfissao () {
	return profissao;
}

int Contato::getIdade () {
	return idade;
}
