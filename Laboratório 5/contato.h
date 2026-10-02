/******************************* Arquivo contato.h ***************************/

/******Laboratório: 5*******/
/******Aluno: João Vitor dos Santos Oliveira*******/

/******Questão 1) a)*******/

#include <iostream>
#include <string>

using namespace std;

class Contato {
        public:
                Contato (string, string, int);

                void setNome (string);
                void setProfissao (string);
                void setIdade (int);

                string getNome ();
                string getProfissao ();
                int getIdade ();

        private:
                string nome, profissao;
                int idade;
};

