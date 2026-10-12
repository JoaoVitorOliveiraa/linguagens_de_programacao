// ============================================================
// Arquivo: grafo.cpp
// Descrição: Implementação dos métodos da classe Grafo.
// ============================================================

#include "grafo.h"               // Inclui a definição da classe.

// ------------------------------------------------------------
// Construtor padrão: não precisa fazer nada, pois os vectors
// "vertices" e "arestas" são inicializados vazios automaticamente.
// ------------------------------------------------------------
Grafo::Grafo() {}

// ------------------------------------------------------------
// lerArquivo: lê o arquivo linha por linha. Cada linha tem
// o formato "Origem Destino Peso". Para cada linha, cria (se
// ainda nao existir) os dois vértices e depois cria a aresta.
// ------------------------------------------------------------
void Grafo::lerArquivo(string nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());   // Abre o arquivo para leitura.

    // Verifica se o arquivo abriu corretamente.
    if (!arquivo.is_open()) {
        cout << "Arquivo nao encontrado: " << nomeArquivo << endl;
        return;                              // Encerra o método.
    }

    string origem, destino;   // Rotulos dos dois vértices.
    double peso;              // Peso da aresta.

    // Le tres valores por linha: origem, destino e peso.
    while (arquivo >> origem >> destino >> peso) {

        // ---- Verifica o vértice de origem ----
        int idxOrigem = buscaIndiceVertice(origem);
        if (idxOrigem == -1) {               // Se ainda não existe:
            Vertice novo(origem);            // Cria o vértice.
            vertices.push_back(novo);        // Adiciona ao vector.
            idxOrigem = (int)vertices.size() - 1;  // Guarda o índice.
        }

        // ---- Verifica o vértice de destino ----
        int idxDestino = buscaIndiceVertice(destino);
        if (idxDestino == -1) {              // Se ainda não existe:
            Vertice novo(destino);           // Cria o vértice.
            vertices.push_back(novo);        // Adiciona ao vector.
            idxDestino = (int)vertices.size() - 1;  // Guarda o índice.
        }

        // ---- Cria a aresta e adiciona ao vector ----
        // Passa os endereços dos vértices dentro do vector.
        Aresta nova(&vertices[idxOrigem], &vertices[idxDestino], peso);
        arestas.push_back(nova);             // Adiciona a aresta.
    }

    arquivo.close();                          // Fecha o arquivo.

    // Exibe quantos vértices e arestas foram carregados.
    cout << "Grafo carregado: " << vertices.size() << " vertices e "
         << arestas.size() << " arestas." << endl;
}

// ------------------------------------------------------------
// buscaIndiceVertice: procura um vértice pelo rotulo.
// Retorna o índice no vector ou -1 se nao encontrar.
// ------------------------------------------------------------
int Grafo::buscaIndiceVertice(string rotulo) {
    for (unsigned i = 0; i < vertices.size(); i++) {
        if (vertices[i].getRotulo() == rotulo)
            return (int)i;                   // Encontrou: retorna o índice.
    }
    return -1;                               // Não encontrou.
}

// ------------------------------------------------------------
// getGrau: conta quantas arestas tem como extremo o vértice
// indicado pelo índice. Compara por PONTEIRO (não por rótulo),
// garantindo que apenas o vértice exato seja contado.
// ------------------------------------------------------------
int Grafo::getGrau(int indice) {
    int grau = 0;                            // Contador de grau.

    // Ponteiro para o vértice alvo (dentro do vector).
    Vertice *alvo = &vertices[indice];

    // Percorre todas as arestas.
    for (unsigned i = 0; i < arestas.size(); i++) {

        // Se a aresta tiver o vértice alvo em qualquer extremo,
        // incrementa o grau.
        if (arestas[i].getPrimeiroVertice() == alvo ||
            arestas[i].getSegundoVertice() == alvo)
            grau++;
    }
    return grau;                             // Retorna o grau.
}

// ------------------------------------------------------------
// imprimirListaAdjacencia (Item 1): para cada vértice,
// mostra os vizinhos diretos e o peso da aresta.
// ------------------------------------------------------------
void Grafo::imprimirListaAdjacencia() {
    cout << "\n===== LISTA DE ADJACENCIA =====" << endl;

    // Percorre todos os vértices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        string rotuloAtual = vertices[i].getRotulo();
        cout << rotuloAtual << ":";          // Imprime o rotulo atual.

        // Procura todas as arestas que possuem este vértice.
        for (unsigned k = 0; k < arestas.size(); k++) {

            // Pega os rotulos dos dois vértices da aresta.
            string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
            string rot2 = arestas[k].getSegundoVertice()->getRotulo();

            // Se o rotulo atual for a origem, imprime o destino.
            if (rot1 == rotuloAtual) {
                cout << " (" << rot2 << ", " << arestas[k].getPeso() << ")";
            }
            // Se for o destino, imprime a origem (grafo não direcionado).
            else if (rot2 == rotuloAtual) {
                cout << " (" << rot1 << ", " << arestas[k].getPeso() << ")";
            }
        }
        cout << endl;                        // Quebra de linha por vértice.
    }
}

// ------------------------------------------------------------
// imprimirGraus (Item 2): mostra o vértice de maior grau, o
// de menor grau e o grau médio do grafo.
// ------------------------------------------------------------
void Grafo::imprimirGraus() {
    cout << "\n===== GRAUS DOS VERTICES =====" << endl;

    // Se o grafo estiver vazio, avisa e encerra.
    if (vertices.empty()) {
        cout << "Grafo vazio." << endl;
        return;
    }

    int maiorGrau = -1;               // Maior grau encontrado.
    int menorGrau = -1;               // Menor grau encontrado.
    string nomeMaior = "";            // Rotulo do vértice de maior grau.
    string nomeMenor = "";            // Rotulo do vértice de menor grau.
    int somaGraus = 0;                // Soma dos graus (para a média).

    // Percorre todos os vértices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        int grau = getGrau(i);        // Calcula o grau do vértice atual.
        somaGraus += grau;            // Acumula para a média.

        // Atualiza o maior grau se necessário.
        if (maiorGrau == -1 || grau > maiorGrau) {
            maiorGrau = grau;
            nomeMaior = vertices[i].getRotulo();
        }
        // Atualiza o menor grau se necessário.
        if (menorGrau == -1 || grau < menorGrau) {
            menorGrau = grau;
            nomeMenor = vertices[i].getRotulo();
        }
    }

    // Grau médio = soma dos graus / número de vértices.
    double grauMedio = (double)somaGraus / vertices.size();

    // Exibe os resultados.
    cout << "Vertice de maior grau: " << nomeMaior << " (" << maiorGrau << ")" << endl;
    cout << "Vertice de menor grau: " << nomeMenor << " (" << menorGrau << ")" << endl;
    cout << "Grau medio: " << fixed << setprecision(1) << grauMedio << endl;
}

// ------------------------------------------------------------
// imprimirComponentesConexas (Item 3): usa BFS com fila
// simulada por vector. Cada busca inicia em um vértice não
// visitado e marca todos os alcançáveis.
// ------------------------------------------------------------
void Grafo::imprimirComponentesConexas() {
    cout << "\n===== COMPONENTES CONEXAS =====" << endl;

    int n = vertices.size();
    if (n == 0) {
        cout << "Grafo vazio." << endl;
        return;
    }

    // Vector de visitados (0 = nao visitado, 1 = visitado).
    vector<int> visitado(n, 0);

    int numComponentes = 0;              // Contador de componentes conexas.

    // Percorre todos os vértices.
    for (int inicio = 0; inicio < n; inicio++) {
        if (visitado[inicio] == 1) continue;   // Já visitado: pula.

        numComponentes++;                     // Nova componente conexa.

        // Fila simulada: usamos um vector e um índice de leitura.
        vector<int> fila;
        fila.push_back(inicio);               // Começa pelo vértice atual.
        visitado[inicio] = 1;                 // Marca como visitado.

        cout << "Componente " << numComponentes << ": { ";

        unsigned pos = 0;                     // Índice de leitura da fila.
        while (pos < fila.size()) {           // Enquanto houver elementos na fila:
            int atual = fila[pos];            // Pega o elemento atual.
            pos++;                            // Avanca o índice.

            cout << vertices[atual].getRotulo() << " ";   // Imprime o rótulo.

            // Procura os vizinhos do vértice atual.
            string rotAtual = vertices[atual].getRotulo();

            for (unsigned k = 0; k < arestas.size(); k++) {
                string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
                string rot2 = arestas[k].getSegundoVertice()->getRotulo();

                // Descobre quem é o vizinho.
                string vizinho = "";
                if (rot1 == rotAtual) vizinho = rot2;
                else if (rot2 == rotAtual) vizinho = rot1;
                else continue;               // Esta aresta não toca o vértice atual.

                // Acha o índice do vizinho.
                int idxViz = buscaIndiceVertice(vizinho);

                // Se o vizinho ainda não foi visitado, adiciona na fila.
                if (idxViz >= 0 && visitado[idxViz] == 0) {
                    visitado[idxViz] = 1;
                    fila.push_back(idxViz);
                }
            }
        }

        cout << "}" << endl;
    }

    cout << "Total de componentes: " << numComponentes << endl;
}

// ------------------------------------------------------------
// imprimirArvoreGeradoraMinima (Item 4): usa o algoritmo de
// Prim. Começa de um vértice qualquer e, a cada passo, escolhe
// a aresta de menor peso que liga um vértice ja incluido a um
// vértice ainda não incluido.
// ------------------------------------------------------------
void Grafo::imprimirArvoreGeradoraMinima() {
    cout << "\n===== ARVORE GERADORA MINIMA (Prim) =====" << endl;

    int n = vertices.size();
    if (n == 0) {
        cout << "Grafo vazio." << endl;
        return;
    }

    // Vetor de incluidos na árvore (0 = fora, 1 = dentro).
    vector<int> incluido(n, 0);

    // Começa pelo vértice 0.
    incluido[0] = 1;
    int incluidos = 1;
    double custoTotal = 0;

    // Enquanto nem todos os vértices estiverem incluidos:
    while (incluidos < n) {
        bool achou = false;              // Flag: encontrou aresta valida?
        double menorPeso = 0;            // Menor peso encontrado (inicializacao).
        int melhorIncluido = -1;         // Vértice já dentro da árvore.
        int melhorNovo = -1;             // Vértice que sera adicionado.

        // Para cada aresta, verifica se ela liga um vértice
        // incluido a um não incluido.
        for (unsigned k = 0; k < arestas.size(); k++) {
            string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
            string rot2 = arestas[k].getSegundoVertice()->getRotulo();

            int i1 = buscaIndiceVertice(rot1);
            int i2 = buscaIndiceVertice(rot2);

            // Verifica se uma ponta está dentro e a outra fora.
            if ((incluido[i1] == 1 && incluido[i2] == 0) ||
                (incluido[i2] == 1 && incluido[i1] == 0)) {

                // Se e o primeiro candidato ou tem peso menor que o atual.
                if (!achou || arestas[k].getPeso() < menorPeso) {
                    achou = true;
                    menorPeso = arestas[k].getPeso();

                    // Guarda quem está dentro e quem sera incluido.
                    if (incluido[i1] == 1) {
                        melhorIncluido = i1;
                        melhorNovo = i2;
                    } else {
                        melhorIncluido = i2;
                        melhorNovo = i1;
                    }
                }
            }
        }

        // Se nenhuma aresta válida foi encontrada, o grafo e desconexo.
        if (!achou) {
            cout << "Grafo desconexo: nao foi possivel completar a AGM." << endl;
            return;
        }

        // Inclui o novo vértice e soma o peso.
        incluido[melhorNovo] = 1;
        incluidos++;
        custoTotal += menorPeso;

        // Exibe sempre na ordem "incluido -> novo".
        cout << "Aresta: " << vertices[melhorIncluido].getRotulo()
             << " - " << vertices[melhorNovo].getRotulo()
             << " (peso " << menorPeso << ")" << endl;
    }

    cout << "Custo total da AGM: " << custoTotal << endl;
}

// ------------------------------------------------------------
// imprimirCentralidade (Item 5): usa o algorítmo de Dijkstra
// para calcular a distância mínima de cada vértice a todos os
// demais. Depois, calcula 1 / soma das distâncias (centralidade
// de proximidade) e ordena em ordem decrescente.
// ------------------------------------------------------------
void Grafo::imprimirCentralidade() {
    cout << "\n===== CENTRALIDADE DE PROXIMIDADE =====" << endl;

    int n = vertices.size();
    if (n == 0) {
        cout << "Grafo vazio." << endl;
        return;
    }

    // Vetores paralelos para armazenar rótulo e centralidade.
    vector<string> nomes;
    vector<double> centralidades;

    // Para cada vértice de origem, roda Dijkstra.
    for (int origem = 0; origem < n; origem++) {

        // dist[i] = menor distância conhecida de origem até i.
        // -1 significa "infinito" (ainda não alcançado).
        vector<double> dist(n, -1);
        vector<int> visitado(n, 0);

        dist[origem] = 0;                // Distância de origem a ela mesma = 0.

        // Executa no máximo n iterações do Dijkstra.
        for (int iter = 0; iter < n; iter++) {

            // Escolhe o vértice não visitado de menor distância.
            int atual = -1;
            for (int i = 0; i < n; i++) {
                if (visitado[i] == 0 && dist[i] != -1) {
                    if (atual == -1 || dist[i] < dist[atual])
                        atual = i;
                }
            }

            if (atual == -1) break;      // Não há mais alcançáveis.

            visitado[atual] = 1;         // Marca o atual como visitado.

            // Relaxa as arestas que saem do vértice atual.
            string rotAtual = vertices[atual].getRotulo();

            for (unsigned k = 0; k < arestas.size(); k++) {
                string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
                string rot2 = arestas[k].getSegundoVertice()->getRotulo();

                // Descobre quem é o vizinho.
                string vizinho = "";
                if (rot1 == rotAtual) vizinho = rot2;
                else if (rot2 == rotAtual) vizinho = rot1;
                else continue;

                int idxViz = buscaIndiceVertice(vizinho);

                // Calcula a nova distância passando pelo vértice atual.
                double novaDist = dist[atual] + arestas[k].getPeso();

                // Se melhora a distância, atualiza.
                if (dist[idxViz] == -1 || novaDist < dist[idxViz])
                    dist[idxViz] = novaDist;
            }
        }

        // Soma das distâncias mínimas a todos os alcançáveis.
        double somaDistancias = 0;
        for (int i = 0; i < n; i++) {
            if (i != origem && dist[i] != -1)
                somaDistancias += dist[i];
        }

        // Calcula a centralidade (com proteção contra divisão por zero).
        double centralidade = 0;
        if (somaDistancias > 0)
            centralidade = 1.0 / somaDistancias;

        nomes.push_back(vertices[origem].getRotulo());
        centralidades.push_back(centralidade);
    }

    // Ordena em ordem decrescente de centralidade (bubble sort).
    for (int i = 0; i < (int)centralidades.size() - 1; i++) {
        for (int j = 0; j < (int)centralidades.size() - 1 - i; j++) {
            if (centralidades[j] < centralidades[j+1]) {

                // Troca as centralidades.
                double tempC = centralidades[j];
                centralidades[j] = centralidades[j+1];
                centralidades[j+1] = tempC;

                // Troca os nomes correspondentes.
                string tempN = nomes[j];
                nomes[j] = nomes[j+1];
                nomes[j+1] = tempN;
            }
        }
    }

    // Exibe o resultado ordenado.
    for (unsigned i = 0; i < nomes.size(); i++) {
        cout << nomes[i] << " -> " << centralidades[i] << endl;
    }
}