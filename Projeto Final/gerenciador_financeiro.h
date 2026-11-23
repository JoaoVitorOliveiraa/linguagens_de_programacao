#ifndef GERENCIADOR_FINANCEIRO_H
#define GERENCIADOR_FINANCEIRO_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <Python.h>
#include "perfil_financeiro.h"

using namespace std;

class GerenciadorFinanceiro {
public:
    GerenciadorFinanceiro(string nomeBanco);

    // CRUD
    void inserirPerfil(PerfilFinanceiro perfil);
    vector<PerfilFinanceiro> buscarTodosPerfis();
    void excluirPerfil(int id);

    // Integração Python
    void preverGastosPython(int id);

private:
    string nomeArquivoBanco;
    
    // Auxiliares
    string obterDadosParaPrevisao(int id);
    string chamarPython(string nomeFuncaoPython, string parametro);
};

#endif