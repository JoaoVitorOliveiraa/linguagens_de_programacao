#include "perfil_financeiro.h"

PerfilFinanceiro::PerfilFinanceiro() {
    id = -1;
    tipo = "";
    
    // Inicializando valores numéricos com 0
    renda = 0.0;
    score = 0.0;
    gastoTotal = 0.0;
    debt_to_income_ratio = 0.0;
    loan_payment = 0.0;
    rent_or_mortgage = 0.0;
    investment_amount = 0.0;
    emergency_fund = 0.0;
    subscription_services = 0;
    transaction_count = 0;
    savings_rate = 0.0;
    budget_goal = 0.0;
    financial_advice_score = 50.0;
    fraud_flag = 0;
    
    income_type = "Salary";
    nivelEstresse = "Low";
    categoriaPrincipal = "Rent";
    financial_scenario = "normal";
    cash_flow_status = "Positive";
}

// =====================================================================
// Métodos Getters
// =====================================================================

int PerfilFinanceiro::getId() const {
    return id;
}

string PerfilFinanceiro::getMesAno() const {
    return mesAno;
}

string PerfilFinanceiro::getTipo() const {
    return tipo;
}

double PerfilFinanceiro::getRenda() const {
    return renda;
}

double PerfilFinanceiro::getGastoTotal() const {
    return gastoTotal;
}

double PerfilFinanceiro::getScore() const {
    return score;
}

string PerfilFinanceiro::getCategoriaPrincipal() const {
    return categoriaPrincipal;
}

string PerfilFinanceiro::getNivelEstresse() const {
    return nivelEstresse;
}