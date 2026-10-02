/******************************* Arquivo global.h ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) b)*******/

void formataCadastro (Cadastro &c, void (*formata) (Cadastro &c)){
	(*formata) (c);
}
