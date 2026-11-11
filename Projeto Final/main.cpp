#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

#include "gerenciador_financeiro.h"
#include "perfil_financeiro.h"

using namespace std;

// =====================================================================
// PALETA DE CORES (ANSI)
// =====================================================================
#define RESET       "\033[0m"
#define NEGRITO     "\033[1m"
#define AZUL_TITULO "\033[38;5;39m"   // Azul claro
#define CIANO       "\033[38;5;51m"   // Ciano brilhante
#define VERDE       "\033[38;5;41m"   // Verde
#define VERMELHO    "\033[38;5;203m"  // Vermelho
#define CINZA_TEXTO "\033[38;5;250m"  // Cinza claro

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double lerDouble(string mensagem) {
    double valor;
    while (true) {
        cout << CINZA_TEXTO << "  " << mensagem << RESET;
        if (cin >> valor) {
            cin.ignore(); 
            return valor;
        } else {
            cout << VERMELHO << "  [!] Entrada invalida. Digite um numero.\n" << RESET;
            limparBuffer();
        }
    }
}

int lerInteiro(string mensagem) {
    int valor;
    while (true) {
        cout << CINZA_TEXTO << "  " << mensagem << RESET;
        if (cin >> valor) {
            cin.ignore(); 
            return valor;
        } else {
            cout << VERMELHO << "  [!] Entrada invalida. Digite um inteiro.\n" << RESET;
            limparBuffer();
        }
    }
}

// Função chamada APENAS UMA VEZ no início do programa
void exibirCabecalho() {
    cout << "\n";
    cout << AZUL_TITULO << "  ███████╗██╗███████╗████████╗███████╗███╗   ███╗ █████╗     █████╗ ███╗   ██╗ █████╗ ██╗     ██╗███████╗███████╗    ███████╗██╗███╗   ██╗ █████╗ ███╗   ██╗ ██████╗███████╗██╗██████╗  █████╗ \n";
    cout << AZUL_TITULO << "  ██╔════╝██║██╔════╝╚══██╔══╝██╔════╝████╗ ████║██╔══██╗   ██╔══██╗████╗  ██║██╔══██╗██║     ██║██╔════╝██╔════╝    ██╔════╝██║████╗  ██║██╔══██╗████╗  ██║██╔════╝██╔════╝██║██╔══██╗██╔══██╗\n";
    cout << AZUL_TITULO << "  ███████╗██║███████╗   ██║   █████╗  ██╔████╔██║███████║   ███████║██╔██╗ ██║███████║██║     ██║███████╗█████╗      █████╗  ██║██╔██╗ ██║███████║██╔██╗ ██║██║     █████╗  ██║██████╔╝███████║\n";
    cout << AZUL_TITULO << "  ╚════██║██║╚════██║   ██║   ██╔══╝  ██║╚██╔╝██║██╔══██║   ██╔══██║██║╚██╗██║██╔══██║██║     ██║╚════██║██╔══╝      ██╔══╝  ██║██║╚██╗██║██╔══██║██║╚██╗██║██║     ██╔══╝  ██║██╔══██╗██╔══██║\n";
    cout << AZUL_TITULO << "  ███████║██║███████║   ██║   ███████╗██║ ╚═╝ ██║██║  ██║   ██║  ██║██║ ╚████║██║  ██║███████╗██║███████║███████╗    ██║     ██║██║ ╚████║██║  ██║██║ ╚████║╚██████╗███████╗██║██║  ██║██║  ██║\n";
    cout << AZUL_TITULO << "  ╚══════╝╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝╚══════╝    ╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═══╝ ╚═════╝╚══════╝╚═╝╚═╝  ╚═╝╚═╝  ╚═╝\n\n" << RESET;
}

// Função chamada SEMPRE que o menu precisa ser mostrado novamente
void exibirOpcoes() {
    cout << "\n";
    cout << "  " << CIANO << "❯" << RESET << "  " << CIANO << NEGRITO << "[ 1 ]" << RESET << CIANO << "  Cadastrar Perfil (Simplificado)" << RESET << "\n";
    cout << "  " << CIANO << "❯" << RESET << "  " << CIANO << NEGRITO << "[ 2 ]" << RESET << CIANO << "  Cadastrar Perfil (Detalhado)" << RESET << "\n";
    cout << "  " << CIANO << "❯" << RESET << "  " << CIANO << NEGRITO << "[ 3 ]" << RESET << CIANO << "  Listar Perfis" << RESET << "\n";
    cout << "  " << CIANO << "❯" << RESET << "  " << CIANO << NEGRITO << "[ 4 ]" << RESET << CIANO << "  Excluir Perfil" << RESET << "\n";
    cout << "  " << VERDE << "❯" << RESET << "  " << VERDE << NEGRITO << "[ 5 ]" << RESET << VERDE << "  Previsao de Gastos (IA)" << RESET << "\n";
    cout << "  " << VERMELHO << "❯" << RESET << "  " << VERMELHO << NEGRITO << "[ 0 ]" << RESET << VERMELHO << "  Sair do Sistema" << RESET << "\n\n";
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); 
        _putenv("PYTHONHOME=C:/msys64/ucrt64");
        _putenv("PYTHONPATH=C:/msys64/ucrt64/lib/python3.10;C:/msys64/ucrt64/lib/python3.10/site-packages");
    #endif

    Py_Initialize();

    GerenciadorFinanceiro gerenciador("financas.db");
    int opcao;

    // Exibe o título gigante APENAS UMA VEZ
    exibirCabecalho();

    do {
        // Exibe apenas as opções a cada iteração
        exibirOpcoes();
        
        opcao = lerInteiro("Escolha uma opcao: ");

        if (opcao == 1) {
            PerfilFinanceiro novoPerfil;
            novoPerfil.tipo = "S"; 
            
            cout << "\n  " << CIANO << "--- CADASTRO HISTORICO (SIMPLIFICADO) ---\n" << RESET;
            cout << CINZA_TEXTO << "  Mes/Ano de Referencia (ex: 10/2026): "; getline(cin, novoPerfil.mesAno);
            
            novoPerfil.renda = lerDouble("Renda Mensal (R$): ");
            novoPerfil.gastoTotal = lerDouble("Gasto Total do Mes Passado (R$): ");
            novoPerfil.score = lerDouble("Score de Credito (0 a 1000): ");
            
            cout << CINZA_TEXTO << "  Categoria Principal (ex: Rent): "; getline(cin, novoPerfil.categoriaPrincipal);
            cout << CINZA_TEXTO << "  Estresse Financeiro (Low/Medium/High): "; getline(cin, novoPerfil.nivelEstresse);

            gerenciador.inserirPerfil(novoPerfil);
        } 
        else if (opcao == 2) {
            PerfilFinanceiro novoPerfil;
            novoPerfil.tipo = "D"; 
            
            cout << "\n  " << CIANO << "--- CADASTRO DETALHADO (TODAS AS FEATURES) ---\n" << RESET;
            cout << CINZA_TEXTO << "  Mes/Ano: "; getline(cin, novoPerfil.mesAno);
            
            cout << "\n  " << AZUL_TITULO << "[Bloco 1: Perfil do Cliente]" << RESET << "\n";
            novoPerfil.renda = lerDouble("Renda Mensal (R$): ");
            novoPerfil.score = lerDouble("Score de Credito: ");
            cout << CINZA_TEXTO << "  Tipo de Renda (Salary/Freelance/Mixed): "; getline(cin, novoPerfil.income_type);
            cout << CINZA_TEXTO << "  Nivel de Estresse (Low/Medium/High): "; getline(cin, novoPerfil.nivelEstresse);
            cout << CINZA_TEXTO << "  Categoria Principal: "; getline(cin, novoPerfil.categoriaPrincipal);

            cout << "\n  " << AZUL_TITULO << "[Bloco 2: Dividas e Custos Fixos]" << RESET << "\n";
            novoPerfil.gastoTotal = lerDouble("Gasto Total do Mes Passado (R$): ");
            novoPerfil.debt_to_income_ratio = lerDouble("Taxa de Endividamento (0.0 a 1.0): ");
            novoPerfil.loan_payment = lerDouble("Pagamento de Emprestimo (R$): ");
            novoPerfil.rent_or_mortgage = lerDouble("Aluguel/Financiamento (R$): ");

            cout << "\n  " << AZUL_TITULO << "[Bloco 3: Comportamento Financeiro]" << RESET << "\n";
            novoPerfil.investment_amount = lerDouble("Valor Investido (R$): ");
            novoPerfil.emergency_fund = lerDouble("Fundo de Emergencia (R$): ");
            novoPerfil.subscription_services = lerInteiro("Qtd de Assinaturas: ");
            novoPerfil.transaction_count = lerInteiro("Qtd de Transacoes: ");
            novoPerfil.savings_rate = lerDouble("Taxa de Poupanca (0.1 p/ 10%): ");
            novoPerfil.budget_goal = lerDouble("Meta de Orcamento (R$): ");
            
            cout << CINZA_TEXTO << "  Cenario (normal/inflation/recession): "; getline(cin, novoPerfil.financial_scenario);
            cout << CINZA_TEXTO << "  Fluxo de Caixa (Positive/Negative/Neutral): "; getline(cin, novoPerfil.cash_flow_status);
            
            novoPerfil.financial_advice_score = 50.0;
            novoPerfil.fraud_flag = 0;

            gerenciador.inserirPerfil(novoPerfil);
        }
        else if (opcao == 3) {
            vector<PerfilFinanceiro> perfis = gerenciador.buscarTodosPerfis();
            
            if (perfis.empty()) {
                cout << "\n" << VERMELHO << "  [!] Nenhum perfil cadastrado.\n" << RESET;
            } else {
                cout << "\n  " << CIANO << "--- LISTA DE PERFIS ---\n" << RESET;
                cout << NEGRITO << "  ID  | Mes/Ano  | Tipo | Renda      | Gasto Hist.| Score | Cat    | Estresse\n" << RESET;
                cout << "  --------------------------------------------------------------------------\n";
                
                for (const auto& p : perfis) {
                    cout << "  " << p.getId() << "   | " 
                         << p.getMesAno() << " | " 
                         << p.getTipo() << "    | R$ " 
                         << fixed << setprecision(2) << p.getRenda() << " | R$ " 
                         << fixed << setprecision(2) << p.getGastoTotal() << " | " 
                         << p.getScore() << " | " 
                         << p.getCategoriaPrincipal() << " | " 
                         << p.getNivelEstresse() << "\n";
                }
                cout << "  --------------------------------------------------------------------------\n" << RESET;
            }
        }
        else if (opcao == 4) {
            int id = lerInteiro("ID do perfil para excluir: ");
            gerenciador.excluirPerfil(id);
        }
        else if (opcao == 5) {
            int id = lerInteiro("Digite o ID do perfil para prever: ");
            gerenciador.preverGastosPython(id);
        }
        else if (opcao != 0) {
            cout << "\n" << VERMELHO << "  [!] Opcao invalida! Escolha entre 0 e 5.\n" << RESET;
        }

    } while (opcao != 0);

    Py_Finalize();
    
    cout << "\n  " << CIANO << "Encerrando o sistema...\n\n" << RESET;
    return 0;
}