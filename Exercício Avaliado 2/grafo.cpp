// ============================================================
// Arquivo: grafo.cpp
// Descricao: Implementacao dos metodos da classe Grafo.
// ============================================================

#include "grafo.h"               // Inclui a definicao da classe.

// ------------------------------------------------------------
// Construtor padrao: nao precisa fazer nada, pois os vectors
// "vertices" e "arestas" sao inicializados vazios automaticamente.
// ------------------------------------------------------------
Grafo::Grafo() {}

// ------------------------------------------------------------
// lerArquivo: le o arquivo linha por linha. Cada linha tem
// o formato "Origem Destino Peso". Para cada linha, cria (se
// ainda nao existir) os dois vertices e depois cria a aresta.
// ------------------------------------------------------------
void Grafo::lerArquivo(string nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());   // Abre o arquivo para leitura.

    // Verifica se o arquivo abriu corretamente.
    if (!arquivo.is_open()) {
        cout << "Arquivo nao encontrado: " << nomeArquivo << endl;
        return;                              // Encerra o metodo.
    }

    string origem, destino;   // Rotulos dos dois vertices.
    double peso;              // Peso da aresta.

    // Le tres valores por linha: origem, destino e peso.
    while (arquivo >> origem >> destino >> peso) {

        // ---- Verifica o vertice de origem ----
        int idxOrigem = buscaIndiceVertice(origem);
        if (idxOrigem == -1) {               // Se ainda nao existe:
            Vertice novo(origem);            // Cria o vertice.
            vertices.push_back(novo);        // Adiciona ao vector.
            idxOrigem = (int)vertices.size() - 1;  // Guarda o indice.
        }

        // ---- Verifica o vertice de destino ----
        int idxDestino = buscaIndiceVertice(destino);
        if (idxDestino == -1) {              // Se ainda nao existe:
            Vertice novo(destino);           // Cria o vertice.
            vertices.push_back(novo);        // Adiciona ao vector.
            idxDestino = (int)vertices.size() - 1;  // Guarda o indice.
        }

        // ---- Cria a aresta e adiciona ao vector ----
        // Passa os enderecos dos vertices dentro do vector.
        Aresta nova(&vertices[idxOrigem], &vertices[idxDestino], peso);
        arestas.push_back(nova);             // Adiciona a aresta.
    }

    arquivo.close();                          // Fecha o arquivo.

    // Exibe quantos vertices e arestas foram carregados.
    cout << "Grafo carregado: " << vertices.size() << " vertices e "
         << arestas.size() << " arestas." << endl;
}

// ------------------------------------------------------------
// buscaIndiceVertice: procura um vertice pelo rotulo.
// Retorna o indice no vector ou -1 se nao encontrar.
// ------------------------------------------------------------
int Grafo::buscaIndiceVertice(string rotulo) {
    for (unsigned i = 0; i < vertices.size(); i++) {
        if (vertices[i].getRotulo() == rotulo)
            return (int)i;                   // Encontrou: retorna o indice.
    }
    return -1;                               // Nao encontrou.
}

// ------------------------------------------------------------
// getGrau: conta quantas arestas tem como extremo o vertice
// indicado pelo indice. Compara por PONTEIRO (nao por rotulo),
// garantindo que apenas o vertice exato seja contado.
// ------------------------------------------------------------
int Grafo::getGrau(int indice) {
    int grau = 0;                            // Contador de grau.

    // Ponteiro para o vertice alvo (dentro do vector).
    Vertice *alvo = &vertices[indice];

    // Percorre todas as arestas.
    for (unsigned i = 0; i < arestas.size(); i++) {

        // Se a aresta tiver o vertice alvo em qualquer extremo,
        // incrementa o grau.
        if (arestas[i].getPrimeiroVertice() == alvo ||
            arestas[i].getSegundoVertice() == alvo)
            grau++;
    }
    return grau;                             // Retorna o grau.
}

// ------------------------------------------------------------
// imprimirListaAdjacencia (Item 1): para cada vertice,
// mostra os vizinhos diretos e o peso da aresta.
// ------------------------------------------------------------
void Grafo::imprimirListaAdjacencia() {
    cout << "\n===== LISTA DE ADJACENCIA =====" << endl;

    // Percorre todos os vertices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        string rotuloAtual = vertices[i].getRotulo();
        cout << rotuloAtual << ":";          // Imprime o rotulo atual.

        // Procura todas as arestas que possuem este vertice.
        for (unsigned k = 0; k < arestas.size(); k++) {

            // Pega os rotulos dos dois vertices da aresta.
            string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
            string rot2 = arestas[k].getSegundoVertice()->getRotulo();

            // Se o rotulo atual for a origem, imprime o destino.
            if (rot1 == rotuloAtual) {
                cout << " (" << rot2 << ", " << arestas[k].getPeso() << ")";
            }
            // Se for o destino, imprime a origem (grafo nao direcionado).
            else if (rot2 == rotuloAtual) {
                cout << " (" << rot1 << ", " << arestas[k].getPeso() << ")";
            }
        }
        cout << endl;                        // Quebra de linha por vertice.
    }
}

// ------------------------------------------------------------
// imprimirGraus (Item 2): mostra o vertice de maior grau, o
// de menor grau e o grau medio do grafo.
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
    string nomeMaior = "";            // Rotulo do vertice de maior grau.
    string nomeMenor = "";            // Rotulo do vertice de menor grau.
    int somaGraus = 0;                // Soma dos graus (para a media).

    // Percorre todos os vertices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        int grau = getGrau(i);        // Calcula o grau do vertice atual.
        somaGraus += grau;            // Acumula para a media.

        // Atualiza o maior grau se necessario.
        if (maiorGrau == -1 || grau > maiorGrau) {
            maiorGrau = grau;
            nomeMaior = vertices[i].getRotulo();
        }
        // Atualiza o menor grau se necessario.
        if (menorGrau == -1 || grau < menorGrau) {
            menorGrau = grau;
            nomeMenor = vertices[i].getRotulo();
        }
    }

    // Grau medio = soma dos graus / numero de vertices.
    double grauMedio = (double)somaGraus / vertices.size();

    // Exibe os resultados.
    cout << "Vertice de maior grau: " << nomeMaior << " (" << maiorGrau << ")" << endl;
    cout << "Vertice de menor grau: " << nomeMenor << " (" << menorGrau << ")" << endl;
    cout << "Grau medio: " << fixed << setprecision(1) << grauMedio << endl;
}

// ------------------------------------------------------------
// imprimirComponentesConexas (Item 3): usa BFS com fila
// simulada por vector. Cada busca inicia em um vertice nao
// visitado e marca todos os alcancaveis.
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

    // Percorre todos os vertices.
    for (int inicio = 0; inicio < n; inicio++) {
        if (visitado[inicio] == 1) continue;   // Ja visitado: pula.

        numComponentes++;                     // Nova componente conexa.

        // Fila simulada: usamos um vector e um indice de leitura.
        vector<int> fila;
        fila.push_back(inicio);               // Comeca pelo vertice atual.
        visitado[inicio] = 1;                 // Marca como visitado.

        cout << "Componente " << numComponentes << ": { ";

        unsigned pos = 0;                     // Indice de leitura da fila.
        while (pos < fila.size()) {           // Enquanto houver elementos na fila:
            int atual = fila[pos];            // Pega o elemento atual.
            pos++;                            // Avanca o indice.

            cout << vertices[atual].getRotulo() << " ";   // Imprime o rotulo.

            // Procura os vizinhos do vertice atual.
            string rotAtual = vertices[atual].getRotulo();

            for (unsigned k = 0; k < arestas.size(); k++) {
                string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
                string rot2 = arestas[k].getSegundoVertice()->getRotulo();

                // Descobre quem e o vizinho.
                string vizinho = "";
                if (rot1 == rotAtual) vizinho = rot2;
                else if (rot2 == rotAtual) vizinho = rot1;
                else continue;               // Esta aresta nao toca o vertice atual.

                // Acha o indice do vizinho.
                int idxViz = buscaIndiceVertice(vizinho);

                // Se o vizinho ainda nao foi visitado, adiciona na fila.
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
// Prim. Comeca de um vertice qualquer e, a cada passo, escolhe
// a aresta de menor peso que liga um vertice ja incluido a um
// vertice ainda nao incluido.
// ------------------------------------------------------------
void Grafo::imprimirArvoreGeradoraMinima() {
    cout << "\n===== ARVORE GERADORA MINIMA (Prim) =====" << endl;

    int n = vertices.size();
    if (n == 0) {
        cout << "Grafo vazio." << endl;
        return;
    }

    // Vetor de incluidos na arvore (0 = fora, 1 = dentro).
    vector<int> incluido(n, 0);

    // Comeca pelo vertice 0.
    incluido[0] = 1;
    int incluidos = 1;
    double custoTotal = 0;

    // Enquanto nem todos os vertices estiverem incluidos:
    while (incluidos < n) {
        bool achou = false;              // Flag: encontrou aresta valida?
        double menorPeso = 0;            // Menor peso encontrado (inicializacao).
        int melhorIncluido = -1;         // Vertice ja dentro da arvore.
        int melhorNovo = -1;             // Vertice que sera adicionado.

        // Para cada aresta, verifica se ela liga um vertice
        // incluido a um nao incluido.
        for (unsigned k = 0; k < arestas.size(); k++) {
            string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
            string rot2 = arestas[k].getSegundoVertice()->getRotulo();

            int i1 = buscaIndiceVertice(rot1);
            int i2 = buscaIndiceVertice(rot2);

            // Verifica se uma ponta esta dentro e a outra fora.
            if ((incluido[i1] == 1 && incluido[i2] == 0) ||
                (incluido[i2] == 1 && incluido[i1] == 0)) {

                // Se e o primeiro candidato ou tem peso menor que o atual.
                if (!achou || arestas[k].getPeso() < menorPeso) {
                    achou = true;
                    menorPeso = arestas[k].getPeso();

                    // Guarda quem esta dentro e quem sera incluido.
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

        // Se nenhuma aresta valida foi encontrada, o grafo e desconexo.
        if (!achou) {
            cout << "Grafo desconexo: nao foi possivel completar a AGM." << endl;
            return;
        }

        // Inclui o novo vertice e soma o peso.
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
// imprimirCentralidade (Item 5): usa o algoritmo de Dijkstra
// para calcular a distancia minima de cada vertice a todos os
// demais. Depois, calcula 1 / soma das distancias (centralidade
// de proximidade) e ordena em ordem decrescente.
// ------------------------------------------------------------
void Grafo::imprimirCentralidade() {
    cout << "\n===== CENTRALIDADE DE PROXIMIDADE =====" << endl;

    int n = vertices.size();
    if (n == 0) {
        cout << "Grafo vazio." << endl;
        return;
    }

    // Vetores paralelos para armazenar rotulo e centralidade.
    vector<string> nomes;
    vector<double> centralidades;

    // Para cada vertice de origem, roda Dijkstra.
    for (int origem = 0; origem < n; origem++) {

        // dist[i] = menor distancia conhecida de origem ate i.
        // -1 significa "infinito" (ainda nao alcancado).
        vector<double> dist(n, -1);
        vector<int> visitado(n, 0);

        dist[origem] = 0;                // Distancia de origem a ela mesma = 0.

        // Executa no maximo n iteracoes do Dijkstra.
        for (int iter = 0; iter < n; iter++) {

            // Escolhe o vertice nao visitado de menor distancia.
            int atual = -1;
            for (int i = 0; i < n; i++) {
                if (visitado[i] == 0 && dist[i] != -1) {
                    if (atual == -1 || dist[i] < dist[atual])
                        atual = i;
                }
            }

            if (atual == -1) break;      // Nao ha mais alcancaveis.

            visitado[atual] = 1;         // Marca o atual como visitado.

            // Relaxa as arestas que saem do vertice atual.
            string rotAtual = vertices[atual].getRotulo();

            for (unsigned k = 0; k < arestas.size(); k++) {
                string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
                string rot2 = arestas[k].getSegundoVertice()->getRotulo();

                // Descobre quem e o vizinho.
                string vizinho = "";
                if (rot1 == rotAtual) vizinho = rot2;
                else if (rot2 == rotAtual) vizinho = rot1;
                else continue;

                int idxViz = buscaIndiceVertice(vizinho);

                // Calcula a nova distancia passando pelo vertice atual.
                double novaDist = dist[atual] + arestas[k].getPeso();

                // Se melhora a distancia, atualiza.
                if (dist[idxViz] == -1 || novaDist < dist[idxViz])
                    dist[idxViz] = novaDist;
            }
        }

        // Soma das distancias minimas a todos os alcancaveis.
        double somaDistancias = 0;
        for (int i = 0; i < n; i++) {
            if (i != origem && dist[i] != -1)
                somaDistancias += dist[i];
        }

        // Calcula a centralidade (com protecao contra divisao por zero).
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