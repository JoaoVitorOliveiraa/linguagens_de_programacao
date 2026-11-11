#include "estoque.h"

// ---------------------------------------------------------
// CONSTRUTOR E DESTRUTOR
// ---------------------------------------------------------
EstoqueComponentes::EstoqueComponentes(int capacidadeMax) {
    capacidadeMaxima = capacidadeMax;
    nomeArquivo = "estoque.txt";
    carregarDoArquivo();
}

EstoqueComponentes::~EstoqueComponentes() {
    salvarNoArquivo();
}

// ---------------------------------------------------------
// SOBRECARGA DE OPERADORES DA STRUCT COMPONENTE
// ---------------------------------------------------------
ostream& operator<<(ostream& os, const Componente& comp) {
    os << comp.codigo << " | " << comp.fabricante << " | Qtd: " 
       << comp.quantidade << " | R$ " << comp.precoUnitario;
    return os;
}

istream& operator>>(istream& is, Componente& comp) {
    cout << "Codigo: "; is >> comp.codigo;
    cout << "Fabricante: "; is >> comp.fabricante;
    cout << "Quantidade: "; is >> comp.quantidade;
    cout << "Preco Unitario: "; is >> comp.precoUnitario;
    return is;
}

bool operator==(const Componente& c1, const Componente& c2) {
    return c1.codigo == c2.codigo;
}

bool operator<(const Componente& c1, const Componente& c2) {
    if (c1.fabricante != c2.fabricante) {
        return c1.fabricante < c2.fabricante;
    }
    return c1.codigo < c2.codigo;
}

// ---------------------------------------------------------
// OPERADORES DA CLASSE ESTOQUE
// ---------------------------------------------------------
ostream& operator<<(ostream& os, const EstoqueComponentes& estoque) {
    os << "\n--- ESTOQUE COMPLETO ---" << endl;
    for (unsigned i = 0; i < estoque.componentes.size(); i++) {
        os << estoque.componentes[i] << endl;
    }
    return os;
}

EstoqueComponentes::operator double() const {
    double total = 0.0;
    for (unsigned i = 0; i < componentes.size(); i++) {
        total += componentes[i].quantidade * componentes[i].precoUnitario;
    }
    return total;
}

EstoqueComponentes& EstoqueComponentes::operator+=(const Componente& comp) {
    int idx = buscarIndicePorCodigo(comp.codigo);

    if (idx != -1) {
        componentes[idx].quantidade += comp.quantidade;
        componentes[idx].precoUnitario = comp.precoUnitario;
    } else {
        if (componentes.size() >= (unsigned)capacidadeMaxima) {
            cout << "[ERRO] Estoque cheio! Nao foi possivel adicionar " << comp.codigo << endl;
            return *this;
        }
        
        componentes.push_back(comp);
        // Ordenação manual (Bubble Sort)
        for (int i = 0; i < (int)componentes.size() - 1; i++) {
            for (int j = 0; j < (int)componentes.size() - 1 - i; j++) {
                if (componentes[j + 1] < componentes[j]) {
                    Componente temp = componentes[j];
                    componentes[j] = componentes[j + 1];
                    componentes[j + 1] = temp;
                }
            }
        }
    }
    return *this;
}

EstoqueComponentes& EstoqueComponentes::operator-=(const Componente& comp) {
    int idx = buscarIndicePorCodigo(comp.codigo);

    if (idx == -1) {
        cout << "[ERRO] Componente " << comp.codigo << " nao encontrado." << endl;
        return *this;
    }

    if (componentes[idx].quantidade < comp.quantidade) {
        cout << "[ERRO] Quantidade insuficiente em estoque para " << comp.codigo << endl;
        return *this;
    }

    componentes[idx].quantidade -= comp.quantidade;

    if (componentes[idx].quantidade == 0) {
        componentes.erase(componentes.begin() + idx);
        cout << "[INFO] Componente " << comp.codigo << " removido do estoque." << endl;
    }
    return *this;
}

EstoqueComponentes EstoqueComponentes::operator*(double fator) const {
    // Cria um objeto temporário com a mesma capacidade.
    EstoqueComponentes novoEstoque(capacidadeMaxima);
    
    // Limpa o que foi carregado do arquivo no construtor do temporário
    novoEstoque.componentes.clear(); 

    // Copia os componentes com os preços multiplicados
    for (unsigned i = 0; i < componentes.size(); i++) {
        Componente c = componentes[i];
        c.precoUnitario = c.precoUnitario * fator;
        novoEstoque += c; 
    }
    return novoEstoque;
}

vector<Componente> EstoqueComponentes::operator()(double precoMin, double precoMax) const {
    vector<Componente> resultado;
    for (unsigned i = 0; i < componentes.size(); i++) {
        if (componentes[i].precoUnitario >= precoMin && componentes[i].precoUnitario < precoMax) {
            resultado.push_back(componentes[i]);
        }
    }
    return resultado;
}

// ---------------------------------------------------------
// MÉTODOS AUXILIARES E PERSISTÊNCIA
// ---------------------------------------------------------
int EstoqueComponentes::buscarIndicePorCodigo(string cod) const {
    for (unsigned i = 0; i < componentes.size(); i++) {
        if (componentes[i].codigo == cod) return i;
    }
    return -1;
}

void EstoqueComponentes::carregarDoArquivo() {
    ifstream arquivo(nomeArquivo.c_str());
    if (!arquivo.is_open()) return; // Se não existe, ignora

    string cod, fab;
    int qtd;
    double preco;

    while (arquivo >> cod >> fab >> qtd >> preco) {
        Componente c;
        c.codigo = cod;
        c.fabricante = fab;
        c.quantidade = qtd;
        c.precoUnitario = preco;
        *this += c; 
    }
    arquivo.close();
}

void EstoqueComponentes::salvarNoArquivo() const {
    ofstream arquivo(nomeArquivo.c_str());
    if (!arquivo.is_open()) return;

    for (unsigned i = 0; i < componentes.size(); i++) {
        arquivo << componentes[i].codigo << " " 
                << componentes[i].fabricante << " " 
                << componentes[i].quantidade << " " 
                << componentes[i].precoUnitario << endl;
    }
    arquivo.close();
}