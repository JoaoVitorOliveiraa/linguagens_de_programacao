#ifndef PERFIL_FINANCEIRO_H
#define PERFIL_FINANCEIRO_H

#include <string>
using namespace std;

class PerfilFinanceiro {
public:
    // Atributos
    int id;
    string mesAno;
    string tipo;

    // Bloco 1
    double renda; 
    double score; 
    string income_type;
    string nivelEstresse; 
    string categoriaPrincipal; 

    // Bloco 2
    double gastoTotal; 
    double debt_to_income_ratio;
    double loan_payment;
    double rent_or_mortgage;

    // Bloco 3
    double investment_amount;
    double emergency_fund;
    int subscription_services;
    int transaction_count;
    double savings_rate;
    double budget_goal;
    string financial_scenario;
    string cash_flow_status;

    // Fixos
    double financial_advice_score;
    int fraud_flag;

    // Apenas o construtor padrão
    PerfilFinanceiro();

    // Getters
    int getId() const;
    string getMesAno() const;
    string getTipo() const;
    double getRenda() const;
    double getGastoTotal() const;
    double getScore() const;
    string getCategoriaPrincipal() const;
    string getNivelEstresse() const;
};

#endif