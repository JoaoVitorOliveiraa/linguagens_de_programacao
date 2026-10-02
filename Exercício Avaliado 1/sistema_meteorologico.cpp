// ============================================================
// Arquivo: sistema_meteorologico.cpp
// Descricao: Implementacao dos metodos da classe
//            SistemaMeteorologico.
// ============================================================

#include "sistema_meteorologico.h"   // Inclui a definicao da classe.
#include <iostream>                  // Necessario para cout e endl.

// ------------------------------------------------------------
// Construtor padrao: nao precisa fazer nada, pois o vector
// "estacoes" ja e inicializado automaticamente vazio.
// ------------------------------------------------------------
SistemaMeteorologico::SistemaMeteorologico() {}

// ------------------------------------------------------------
// inserirEstacao: cria um objeto Estacao com o nome dado e
// adiciona ao vector de estacoes.
// ------------------------------------------------------------
void SistemaMeteorologico::inserirEstacao(string nome) {
    Estacao novaEstacao(nome);           // Cria a estacao localmente.
    estacoes.push_back(novaEstacao);     // Adiciona ao vector (faz uma copia).
}

// ------------------------------------------------------------
// buscarEstacao: percorre o vector e retorna um ponteiro para
// a estacao com o nome desejado. Retorna NULL se nao achar.
// Usar ponteiro evita copias desnecessarias.
// ------------------------------------------------------------
Estacao* SistemaMeteorologico::buscarEstacao(string nome) {
    for (int i = 0; i < (int)estacoes.size(); i++) {
        if (estacoes[i].getNome() == nome)
            return &estacoes[i];   // Retorna o endereco do objeto.
    }
    return NULL;                   // Nao encontrou.
}

// ------------------------------------------------------------
// inserirLeitura: localiza a estacao pelo nome e delega a
// insercao da leitura para o metodo da propria Estacao.
// ------------------------------------------------------------
void SistemaMeteorologico::inserirLeitura(string nomeEstacao, string grandeza, double valor) {
    Estacao* estacaoEncontrada = buscarEstacao(nomeEstacao);   // Busca a estacao.

    if (estacaoEncontrada != NULL) {
        estacaoEncontrada->inserirLeitura(grandeza, valor);    // Usa "->" pois e ponteiro.
    } else {
        cout << "Estacao nao encontrada!" << endl;
    }
}

// ------------------------------------------------------------
// exibirRelatorio: mostra todas as estacoes e suas leituras.
// ------------------------------------------------------------
void SistemaMeteorologico::exibirRelatorio() {
    cout << "\n===== RELATORIO DE ESTACOES =====" << endl;

    // Percorre o vector de estacoes e chama exibir() de cada uma.
    for (int i = 0; i < (int)estacoes.size(); i++) {
        estacoes[i].exibir();
    }
    cout << "=================================" << endl;
}

// ------------------------------------------------------------
// calcularMediaMovel (Item 3): para cada estacao que possui a
// grandeza, calcula a media movel com janela N e exibe a evolucao.
// ------------------------------------------------------------
void SistemaMeteorologico::calcularMediaMovel(string grandeza, int tamanhoJanela) {
    cout << "\n===== MEDIA MOVEL (" << grandeza << ", N=" << tamanhoJanela << ") =====" << endl;

    int estacoesProcessadas = 0;   // Conta quantas estacoes possuem a grandeza.

    // Percorre todas as estacoes.
    for (int i = 0; i < (int)estacoes.size(); i++) {

        // Somente processa estacoes que possuem a grandeza.
        if (estacoes[i].possuiGrandeza(grandeza)) {

            // Obtem as leituras filtradas e ordenadas por instante.
            vector<LeituraSensor> leituras = estacoes[i].getLeiturasPorGrandeza(grandeza);

            cout << "\nEstacao: " << estacoes[i].getNome() << endl;
            cout << "Medias moveis: ";

            // Para cada posicao j a partir do indice N-1 (pois precisa
            // de N valores anteriores), calcula a media da janela.
            for (int j = tamanhoJanela - 1; j < (int)leituras.size(); j++) {
                double soma = 0;      // Acumulador da soma.

                // Soma os N valores da janela: de (j-N+1) ate j.
                for (int k = j - tamanhoJanela + 1; k <= j; k++) {
                    soma += leituras[k].getValor();
                }
                double media = soma / tamanhoJanela;   // Divide por N.
                cout << media << "  ";                 // Exibe a media calculada.
            }
            cout << endl;
            estacoesProcessadas++;   // Incrementa o contador.
        }
    }

    // Se nenhuma estacao possui a grandeza, avisa o usuario.
    if (estacoesProcessadas == 0)
        cout << "Nenhuma estacao possui a grandeza informada." << endl;
}

// ------------------------------------------------------------
// Funcao auxiliar (static, visivel apenas neste arquivo):
// Calcula a ultima media movel de uma estacao para uma grandeza.
// Retorna -1 se nao houver leituras suficientes.
// ------------------------------------------------------------
static double calcularUltimaMediaMovel(Estacao& estacao, string grandeza, int tamanhoJanela) {
    vector<LeituraSensor> leituras = estacao.getLeiturasPorGrandeza(grandeza);

    if ((int)leituras.size() < tamanhoJanela) return -1;   // Nao ha leituras suficientes.

    double soma = 0;
    // Soma os N ultimos valores (do fim para tras).
    for (int i = (int)leituras.size() - tamanhoJanela; i < (int)leituras.size(); i++) {
        soma += leituras[i].getValor();
    }
    return soma / tamanhoJanela;   // Retorna a media.
}

// ------------------------------------------------------------
// Funcao auxiliar (static): Calcula a penultima media movel
// (a janela imediatamente anterior a ultima).
//
// Exemplo: se a ultima janela usa os indices 4,5,6 (N=3),
// a penultima deve usar os indices 3,4,5.
//
// Retorna -1 se nao houver leituras suficientes.
// ------------------------------------------------------------
static double calcularPenultimaMediaMovel(Estacao& estacao, string grandeza, int tamanhoJanela) {
    vector<LeituraSensor> leituras = estacao.getLeiturasPorGrandeza(grandeza);

    if ((int)leituras.size() < tamanhoJanela + 1) return -1;   // Precisa de N+1 leituras.

    double soma = 0;

    // A penultima janela termina no indice (tamanho - 2),
    // ou seja, um indice antes do inicio da ultima janela.
    int fim = (int)leituras.size() - 2;

    // Soma os N valores da janela anterior: de (fim-N+1) ate fim.
    for (int i = fim - tamanhoJanela + 1; i <= fim; i++) {
        soma += leituras[i].getValor();
    }
    return soma / tamanhoJanela;   // Retorna a media.
}

// ------------------------------------------------------------
// ordenarPorMediaMovel (Item 4): ordena as estacoes pela
// ultima media movel e detecta variacao anormal (>15%).
// ------------------------------------------------------------
void SistemaMeteorologico::ordenarPorMediaMovel(string grandeza, int tamanhoJanela) {
    cout << "\n===== ORDENACAO POR MEDIA MOVEL (" << grandeza << ", N=" << tamanhoJanela << ") =====" << endl;

    // Vetores paralelos para armazenar nome, ultima media e penultima media.
    vector<string> nomes;
    vector<double> medias;
    vector<double> mediasAnteriores;

    // Percorre todas as estacoes e coleta dados das que possuem a grandeza.
    for (int i = 0; i < (int)estacoes.size(); i++) {
        if (estacoes[i].possuiGrandeza(grandeza)) {
            double media = calcularUltimaMediaMovel(estacoes[i], grandeza, tamanhoJanela);
            double mediaAnterior = calcularPenultimaMediaMovel(estacoes[i], grandeza, tamanhoJanela);

            if (media >= 0) {        // Se conseguiu calcular a media.
                nomes.push_back(estacoes[i].getNome());
                medias.push_back(media);
                mediasAnteriores.push_back(mediaAnterior);
            }
        }
    }

    // Ordenacao decrescente por media movel (bubble sort).
    for (int i = 0; i < (int)medias.size() - 1; i++) {
        for (int j = 0; j < (int)medias.size() - 1 - i; j++) {
            if (medias[j] < medias[j+1]) {

                // Troca as medias.
                double tempMedia = medias[j];
                medias[j] = medias[j+1];
                medias[j+1] = tempMedia;

                // Troca os nomes correspondentes.
                string tempNome = nomes[j];
                nomes[j] = nomes[j+1];
                nomes[j+1] = tempNome;

                // Troca as medias anteriores correspondentes.
                double tempAnterior = mediasAnteriores[j];
                mediasAnteriores[j] = mediasAnteriores[j+1];
                mediasAnteriores[j+1] = tempAnterior;
            }
        }
    }

    // Exibe o resultado ordenado com deteccao de variacao anormal.
    for (int i = 0; i < (int)nomes.size(); i++) {
        cout << nomes[i] << " -> Media: " << medias[i];

        if (mediasAnteriores[i] > 0) {
            // Calcula a variacao percentual entre a ultima e a penultima media.
            double variacao = ((medias[i] - mediasAnteriores[i]) / mediasAnteriores[i]) * 100.0;
            cout << " | Variacao: " << variacao << "%";

            // Se a variacao for maior que +15% ou menor que -15%, marca como ANORMAL.
            if (variacao > 15.0 || variacao < -15.0)
                cout << " [ANORMAL]";
        } else {
            cout << " | Sem media anterior suficiente";
        }
        cout << endl;
    }
}

// ------------------------------------------------------------
// preverProximaLeitura (Item 5): regressao linear simples para
// prever a proxima leitura de uma grandeza em uma estacao.
// Formula: a = (n*Sxy - Sx*Sy) / (n*Sx2 - Sx^2)
//          b = (Sy - a*Sx) / n
//          y_estimado = a * proximo_instante + b
// ------------------------------------------------------------
void SistemaMeteorologico::preverProximaLeitura(string nomeEstacao, string grandeza) {
    Estacao* estacaoEncontrada = buscarEstacao(nomeEstacao);   // Busca a estacao.

    if (estacaoEncontrada == NULL) {
        cout << "Estacao nao encontrada!" << endl;
        return;                  // Encerra o metodo.
    }

    // Verifica se a estacao possui a grandeza.
    if (!estacaoEncontrada->possuiGrandeza(grandeza)) {
        cout << "Estacao nao possui leituras da grandeza informada." << endl;
        return;
    }

    // Obtem as leituras filtradas e ordenadas por instante.
    vector<LeituraSensor> leituras = estacaoEncontrada->getLeiturasPorGrandeza(grandeza);

    int quantidade = (int)leituras.size();   // Numero de leituras.
    if (quantidade < 2) {
        cout << "Leituras insuficientes para regressao." << endl;
        return;
    }

    // Variaveis para os somatorios necessarios na regressao.
    double somaX = 0, somaY = 0, somaXY = 0, somaX2 = 0;

    // Percorre todas as leituras acumulando os somatorios.
    for (int i = 0; i < quantidade; i++) {
        double x = leituras[i].getInstante();   // x = instante.
        double y = leituras[i].getValor();      // y = valor.

        somaX  += x;             // Soma dos x.
        somaY  += y;             // Soma dos y.
        somaXY += x * y;         // Soma dos produtos x*y.
        somaX2 += x * x;         // Soma dos quadrados de x.
    }

    // Denominador comum para o calculo do coeficiente angular.
    // Precisa ser diferente de zero para evitar divisao por zero.
    double denominador = quantidade * somaX2 - somaX * somaX;
    if (denominador == 0) {
        cout << "Nao e possivel calcular a regressao (dados insuficientes ou invalidos)." << endl;
        return;
    }

    // Calculo do coeficiente angular (a).
    double a = (quantidade * somaXY - somaX * somaY) / denominador;

    // Calculo do coeficiente linear (b).
    double b = (somaY - a * somaX) / quantidade;

    // O proximo instante e o ultimo instante + 1.
    int proximoInstante = leituras[quantidade-1].getInstante() + 1;

    // Estima o valor da proxima leitura.
    double estimativa = a * proximoInstante + b;

    // Exibe os resultados.
    cout << "\n===== PREVISAO (" << nomeEstacao << ", " << grandeza << ") =====" << endl;
    cout << "Coeficiente angular (a): " << a << endl;
    cout << "Coeficiente linear (b): " << b << endl;
    cout << "Proximo instante: " << proximoInstante << endl;
    cout << "Valor estimado: " << estimativa << endl;
}