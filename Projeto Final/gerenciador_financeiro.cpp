#include "gerenciador_financeiro.h"

GerenciadorFinanceiro::GerenciadorFinanceiro(string nomeBanco) {
    nomeArquivoBanco = nomeBanco;
    sqlite3 *db;
    if (sqlite3_open(nomeArquivoBanco.c_str(), &db) == SQLITE_OK) {
        // Tabela atualizada com todas as colunas do dataset
        string sql = "CREATE TABLE IF NOT EXISTS perfis ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                     "mes_ano TEXT, tipo TEXT, renda REAL, score REAL, income_type TEXT, "
                     "nivelEstresse TEXT, categoriaPrincipal TEXT, gastoTotal REAL, "
                     "debt_to_income_ratio REAL, loan_payment REAL, rent_or_mortgage REAL, "
                     "investment_amount REAL, emergency_fund REAL, subscription_services INTEGER, "
                     "transaction_count INTEGER, savings_rate REAL, budget_goal REAL, "
                     "financial_scenario TEXT, cash_flow_status TEXT);";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
    }
    sqlite3_close(db);
}

void GerenciadorFinanceiro::inserirPerfil(PerfilFinanceiro p) {
    sqlite3 *db;
    if (sqlite3_open(nomeArquivoBanco.c_str(), &db) == SQLITE_OK) {
        
        // Query com placeholders (?) para evitar erros de formatação e SQL Injection
        string sql = "INSERT INTO perfis (mes_ano, tipo, renda, score, income_type, "
                     "nivelEstresse, categoriaPrincipal, gastoTotal, debt_to_income_ratio, "
                     "loan_payment, rent_or_mortgage, investment_amount, emergency_fund, "
                     "subscription_services, transaction_count, savings_rate, budget_goal, "
                     "financial_scenario, cash_flow_status) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        
        sqlite3_stmt *stmt;
        
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            // Amarrando (bind) os valores nas posições corretas
            sqlite3_bind_text(stmt, 1, p.mesAno.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, p.tipo.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_double(stmt, 3, p.renda);
            sqlite3_bind_double(stmt, 4, p.score);
            sqlite3_bind_text(stmt, 5, p.income_type.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 6, p.nivelEstresse.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 7, p.categoriaPrincipal.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_double(stmt, 8, p.gastoTotal);
            sqlite3_bind_double(stmt, 9, p.debt_to_income_ratio);
            sqlite3_bind_double(stmt, 10, p.loan_payment);
            sqlite3_bind_double(stmt, 11, p.rent_or_mortgage);
            sqlite3_bind_double(stmt, 12, p.investment_amount);
            sqlite3_bind_double(stmt, 13, p.emergency_fund);
            sqlite3_bind_int(stmt, 14, p.subscription_services);
            sqlite3_bind_int(stmt, 15, p.transaction_count);
            sqlite3_bind_double(stmt, 16, p.savings_rate);
            sqlite3_bind_double(stmt, 17, p.budget_goal);
            sqlite3_bind_text(stmt, 18, p.financial_scenario.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 19, p.cash_flow_status.c_str(), -1, SQLITE_TRANSIENT);

            // Executa a inserção
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                cout << "Perfil cadastrado com sucesso!" << endl;
            } else {
                cout << "Erro ao cadastrar perfil: " << sqlite3_errmsg(db) << endl;
            }
        } else {
            cout << "Erro ao preparar a query: " << sqlite3_errmsg(db) << endl;
        }
        
        sqlite3_finalize(stmt);
    } else {
        cout << "Erro ao abrir o banco de dados." << endl;
    }
    sqlite3_close(db);
}

vector<PerfilFinanceiro> GerenciadorFinanceiro::buscarTodosPerfis() {
    vector<PerfilFinanceiro> lista;
    sqlite3 *db;
    
    if (sqlite3_open(nomeArquivoBanco.c_str(), &db) == SQLITE_OK) {
        string sql = "SELECT id, mes_ano, tipo, renda, gastoTotal, score, categoriaPrincipal, nivelEstresse FROM perfis;";
        sqlite3_stmt *stmt;
        
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                PerfilFinanceiro p; // Cria vazio (construtor padrão)
                
                p.id = sqlite3_column_int(stmt, 0);
                p.mesAno = (const char*)sqlite3_column_text(stmt, 1);
                p.tipo = (const char*)sqlite3_column_text(stmt, 2);
                p.renda = sqlite3_column_double(stmt, 3);
                p.gastoTotal = sqlite3_column_double(stmt, 4);
                p.score = sqlite3_column_double(stmt, 5);
                p.categoriaPrincipal = (const char*)sqlite3_column_text(stmt, 6);
                p.nivelEstresse = (const char*)sqlite3_column_text(stmt, 7);
                
                lista.push_back(p);
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
    return lista;
}

void GerenciadorFinanceiro::excluirPerfil(int id) {
    sqlite3 *db;
    if (sqlite3_open(nomeArquivoBanco.c_str(), &db) == SQLITE_OK) {
        string sql = "DELETE FROM perfis WHERE id = " + to_string(id) + ";";
        sqlite3_exec(db, sql.c_str(), 0, 0, 0);
        cout << "Perfil ID " << id << " excluido!" << endl;
    }
    sqlite3_close(db);
}

// =====================================================================
// Integração Python
// =====================================================================

void GerenciadorFinanceiro::preverGastosPython(int id) {
    string dados = obterDadosParaPrevisao(id);
    if (dados.find("Erro") != string::npos) {
        cout << "\n" << dados << endl;
        return;
    }
    string resultado = chamarPython("processar_e_prever", dados);
    cout << "\n" << resultado << endl;
}

string GerenciadorFinanceiro::chamarPython(string nomeFuncaoPython, string parametro) {
    // Configurando os caminhos do Python
    PyObject* sysPath = PySys_GetObject("path");
    PyList_Append(sysPath, PyUnicode_FromString("."));
    PyList_Append(sysPath, PyUnicode_FromString("C:/msys64/ucrt64/lib/python3.10/site-packages"));

    PyObject* pName = PyUnicode_DecodeFSDefault("motor_preditivo");
    PyObject* pModule = PyImport_Import(pName);
    
    if (pModule == NULL) {
        PyErr_Print(); 
        Py_DECREF(pName);
        return "Erro: Nao foi possivel importar o motor_preditivo.py.";
    }
    
    PyObject* pFunc = PyObject_GetAttrString(pModule, nomeFuncaoPython.c_str());
    
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(parametro.c_str()));
        PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
        
        if (pValue != NULL) {
            string resultado = PyUnicode_AsUTF8(pValue);
            Py_DECREF(pValue);
            Py_DECREF(pArgs);
            Py_DECREF(pFunc);
            Py_DECREF(pModule);
            Py_DECREF(pName);
            return resultado;
        } else {
            PyErr_Print(); 
        }
    }
    
    Py_DECREF(pModule);
    Py_DECREF(pName);
    return "Erro: Falha ao executar a funcao Python.";
}

string GerenciadorFinanceiro::obterDadosParaPrevisao(int id) {
    sqlite3 *db;
    string dados = "Erro: Perfil nao encontrado.";
    
    if (sqlite3_open(nomeArquivoBanco.c_str(), &db) == SQLITE_OK) {
        string sql = "SELECT tipo, renda, gastoTotal, score, categoriaPrincipal, nivelEstresse, "
                     "savings_rate, budget_goal, financial_scenario, debt_to_income_ratio, "
                     "loan_payment, investment_amount, subscription_services, emergency_fund, "
                     "transaction_count, income_type, rent_or_mortgage, cash_flow_status, "
                     "financial_advice_score, fraud_flag FROM perfis WHERE id = " + to_string(id) + ";";
        sqlite3_stmt *stmt;
        
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                string tipo = (const char*)sqlite3_column_text(stmt, 0);
                
                // Se for Simplificado, envia apenas os 5 primeiros dados.
                if (tipo == "S") {
                    double renda = sqlite3_column_double(stmt, 1);
                    double gasto = sqlite3_column_double(stmt, 2);
                    double score = sqlite3_column_double(stmt, 3);
                    string cat = (const char*)sqlite3_column_text(stmt, 4);
                    string est = (const char*)sqlite3_column_text(stmt, 5);
                    
                    dados = to_string(renda) + "," + to_string(gasto) + "," + 
                            to_string(score) + "," + cat + "," + est;
                } 
                // Se for Detalhado, envia os 18 dados na ordem exata que o Python espera.
                else {
                    double renda = sqlite3_column_double(stmt, 1);
                    double gasto = sqlite3_column_double(stmt, 2);
                    double score = sqlite3_column_double(stmt, 3);
                    string cat = (const char*)sqlite3_column_text(stmt, 4);
                    string est = (const char*)sqlite3_column_text(stmt, 5);
                    
                    double savings = sqlite3_column_double(stmt, 6);
                    double budget = sqlite3_column_double(stmt, 7);
                    string scenario = (const char*)sqlite3_column_text(stmt, 8);
                    double dirt = sqlite3_column_double(stmt, 9);
                    double loan = sqlite3_column_double(stmt, 10);
                    double invest = sqlite3_column_double(stmt, 11);
                    int subs = sqlite3_column_int(stmt, 12);
                    double fund = sqlite3_column_double(stmt, 13);
                    int trans = sqlite3_column_int(stmt, 14);
                    string inc_type = (const char*)sqlite3_column_text(stmt, 15);
                    double rent = sqlite3_column_double(stmt, 16);
                    string flow = (const char*)sqlite3_column_text(stmt, 17);
                    double advice = sqlite3_column_double(stmt, 18);
                    int fraud = sqlite3_column_int(stmt, 19);

                    dados = to_string(renda) + "," + to_string(gasto) + "," + to_string(score) + "," +
                            cat + "," + est + "," + to_string(savings) + "," + to_string(budget) + "," +
                            scenario + "," + to_string(dirt) + "," + to_string(loan) + "," +
                            to_string(invest) + "," + to_string(subs) + "," + to_string(fund) + "," +
                            to_string(trans) + "," + inc_type + "," + to_string(rent) + "," +
                            flow + "," + to_string(advice) + "," + to_string(fraud);
                }
            }
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
    return dados;
}