// ============================================================
// Arquivo: grafo.cpp
// Descrição: Implementação dos métodos da classe Grafo.
//            Os vértices e arestas são armazenados como
//            objetos dentro de vectors. O construtor
//            reserva espaço suficiente para evitar que os
//            endereços dos vértices mudem durante o preenchimento.
// ============================================================

#include "grafo.h"               // Inclui a definição da classe.

// ------------------------------------------------------------
// Construtor padrão.
// ------------------------------------------------------------
Grafo::Grafo() {}

// ------------------------------------------------------------
// buscaVertice: procura um vértice pelo rótulo.
// Retorna o PONTEIRO para o vértice ou NULL se não encontrar.
// Como "vertices" guarda objetos (não ponteiros), usamos "&"
// para devolver o endereço do elemento no vector.
// ------------------------------------------------------------
Vertice *Grafo::buscaVertice(string rotulo) {
    for (unsigned i = 0; i < vertices.size(); i++) {
        if (vertices[i].getRotulo() == rotulo)
            return &vertices[i];      // Endereço do objeto dentro do vector.
    }
    return NULL;                      // Não encontrou.
}

// ------------------------------------------------------------
// lerArquivo: lê o arquivo linha por linha. Para cada linha,
// verifica se os dois vértices já existem no vector. Se não,
// cria um novo vértice e o adiciona. Depois cria a aresta
// passando os ENDEREÇOS dos vértices (que são estáveis por
// causa do reserve no construtor).
// ------------------------------------------------------------
void Grafo::lerArquivo(string nomeArquivo) {
    ifstream arquivo(nomeArquivo.c_str());   // Abre o arquivo para leitura.

    // Verifica se o arquivo abriu corretamente.
    if (!arquivo.is_open()) {
        cout << "Arquivo nao encontrado: " << nomeArquivo << endl;
        return;
    }

    string origem, destino;         // Rótulos dos dois vértices.
    double peso;                    // Peso da aresta.

    int qtdArestas = 0;             // Contador de arestas.
    vector<string> nomesVertices;   // Vetor que armazena os nomes dos vértices.

    // Contando quantos vértices e arestas existem no arquivo.
    while (arquivo >> origem >> destino >> peso) {
        qtdArestas++;
        
        bool achouOrigem = false;
        for (unsigned i = 0; i < nomesVertices.size(); i++) {
            if (nomesVertices[i] == origem) { achouOrigem = true; break; }
        }
        if (!achouOrigem) nomesVertices.push_back(origem);

        bool achouDestino = false;
        for (unsigned i = 0; i < nomesVertices.size(); i++) {
            if (nomesVertices[i] == destino) { achouDestino = true; break; }
        }
        if (!achouDestino) nomesVertices.push_back(destino);
    }
    
    // Fecha o arquivo para reabrir depois.
    arquivo.close(); 

    // Reserva o espaço exato para não invalidar os ponteiros.
    vertices.reserve(nomesVertices.size());
    arestas.reserve(qtdArestas);

    // Reabre o arquivo para ler novamente e montar o grafo.
    arquivo.open(nomeArquivo.c_str()); 
    
    // Lê três valores por linha: origem, destino e peso.
    while (arquivo >> origem >> destino >> peso) {

        // ---- Verifica o vértice de origem ----
        Vertice *vOrigem = buscaVertice(origem);
        if (vOrigem == NULL) {                   // Se ainda não existe:
            Vertice novo(origem);                // Cria o objeto local.
            vertices.push_back(novo);            // Adiciona uma cópia ao vector.
            vOrigem = &vertices[vertices.size() - 1];   // Pega o endereço.
        }

        // ---- Verifica o vértice de destino ----
        Vertice *vDestino = buscaVertice(destino);
        if (vDestino == NULL) {                  // Se ainda não existe:
            Vertice novo(destino);
            vertices.push_back(novo);
            vDestino = &vertices[vertices.size() - 1];
        }

        // ---- Cria a aresta e adiciona ao vector ----
        // Passa os ENDEREÇOS dos vértices. Como reservamos espaço,
        // eles são estáveis durante toda a execução.
        Aresta nova(vOrigem, vDestino, peso);
        arestas.push_back(nova);
    }

    arquivo.close();                          // Fecha o arquivo.

    // Exibe quantos vértices e arestas foram carregados.
    cout << "\nGrafo carregado: " << vertices.size() << " vertices e "
         << arestas.size() << " arestas." << endl;
}

// ------------------------------------------------------------
// getGrau: conta quantas arestas têm o vértice v como extremo.
// Compara por PONTEIRO (não por rótulo).
// ------------------------------------------------------------
int Grafo::getGrau(Vertice *v) {
    int grau = 0;

    // Percorre todas as arestas.
    for (unsigned i = 0; i < arestas.size(); i++) {
        if (arestas[i].getPrimeiroVertice() == v ||
            arestas[i].getSegundoVertice() == v)
            grau++;
    }
    return grau;
}

// ------------------------------------------------------------
// imprimirListaAdjacencia: para cada vértice,
// mostra os vizinhos diretos e o peso da aresta.
// ------------------------------------------------------------
void Grafo::imprimirListaAdjacencia() {
    cout << "\n===== LISTA DE ADJACENCIA =====" << endl;

    // Percorre todos os vértices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        string rotuloAtual = vertices[i].getRotulo();
        cout << rotuloAtual << ":";          // Imprime o rótulo atual.

        // Procura todas as arestas que possuem este vértice.
        for (unsigned k = 0; k < arestas.size(); k++) {

            // Pega os rótulos dos dois vértices da aresta.
            string rot1 = arestas[k].getPrimeiroVertice()->getRotulo();
            string rot2 = arestas[k].getSegundoVertice()->getRotulo();

            // Se o rótulo atual for a origem, imprime o destino.
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
// imprimirGraus: mostra o vértice de maior grau, o
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
    string nomeMaior = "";            // Rótulo do vértice de maior grau.
    string nomeMenor = "";            // Rótulo do vértice de menor grau.
    int somaGraus = 0;                // Soma dos graus (para a média).

    // Percorre todos os vértices.
    for (unsigned i = 0; i < vertices.size(); i++) {
        int grau = getGrau(&vertices[i]);   // Calcula o grau (passa endereço).
        somaGraus += grau;

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
// imprimirComponentesConexas: usa BFS com fila
// simulada por vector de ÍNDICES. Cada busca inicia em um
// vértice não visitado e marca todos os alcançáveis.
// ------------------------------------------------------------
void Grafo::imprimirComponentesConexas() {
    cout << "\n===== COMPONENTES CONEXAS =====" << endl;

    int n = vertices.size();
    if (n == 0) { cout << "Grafo vazio." << endl; return; }

    // Vector de visitados (0 = não visitado, 1 = visitado).
    vector<int> visitado(n, 0);

    int numComponentes = 0;

    // Percorre todos os vértices.
    for (int inicio = 0; inicio < n; inicio++) {
        if (visitado[inicio] == 1) continue;

        numComponentes++;

        // Fila simulada por vector de índices.
        vector<int> fila;
        fila.push_back(inicio);
        visitado[inicio] = 1;

        cout << "Componente " << numComponentes << ": { ";

        unsigned pos = 0;
        while (pos < fila.size()) {
            int atual = fila[pos];
            pos++;

            cout << vertices[atual].getRotulo() << " ";

            // Procura os vizinhos do vértice atual.
            Vertice *vAtual = &vertices[atual];

            for (unsigned k = 0; k < arestas.size(); k++) {
                Vertice *v1 = arestas[k].getPrimeiroVertice();
                Vertice *v2 = arestas[k].getSegundoVertice();

                // Descobre qual é o vizinho.
                Vertice *vizinho = NULL;
                if (v1 == vAtual) vizinho = v2;
                else if (v2 == vAtual) vizinho = v1;
                else continue;

                // Acha o índice do vizinho.
                int idxViz = -1;
                for (unsigned m = 0; m < vertices.size(); m++) {
                    if (&vertices[m] == vizinho) { idxViz = m; break; }
                }

                // Se ainda não foi visitado, adiciona na fila.
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
// imprimirArvoreGeradoraMinima: usa o algoritmo de
// Prim. Começa de um vértice qualquer e, a cada passo, escolhe
// a aresta de menor peso que liga um vértice já incluído a um
// vértice ainda não incluído.
// ------------------------------------------------------------
void Grafo::imprimirArvoreGeradoraMinima() {
    cout << "\n===== ARVORE GERADORA MINIMA (Prim) =====" << endl;

    int n = vertices.size();
    if (n == 0) { cout << "Grafo vazio." << endl; return; }

    // Vector de incluídos na árvore (0 = fora, 1 = dentro).
    vector<int> incluido(n, 0);

    // Começa pelo vértice 0.
    incluido[0] = 1;
    int incluidos = 1;
    double custoTotal = 0;

    // Enquanto nem todos os vértices estiverem incluídos:
    while (incluidos < n) {
        bool achou = false;
        double menorPeso = 0;
        int melhorIncluido = -1;
        int melhorNovo = -1;

        // Para cada aresta, verifica se liga um incluído a um não incluído.
        for (unsigned k = 0; k < arestas.size(); k++) {
            Vertice *v1 = arestas[k].getPrimeiroVertice();
            Vertice *v2 = arestas[k].getSegundoVertice();

            int i1 = -1, i2 = -1;
            for (unsigned m = 0; m < vertices.size(); m++) {
                if (&vertices[m] == v1) i1 = m;
                if (&vertices[m] == v2) i2 = m;
            }

            // Uma ponta dentro e outra fora?
            if ((incluido[i1] == 1 && incluido[i2] == 0) ||
                (incluido[i2] == 1 && incluido[i1] == 0)) {

                if (!achou || arestas[k].getPeso() < menorPeso) {
                    achou = true;
                    menorPeso = arestas[k].getPeso();
                    if (incluido[i1] == 1) { melhorIncluido = i1; melhorNovo = i2; }
                    else { melhorIncluido = i2; melhorNovo = i1; }
                }
            }
        }

        if (!achou) {
            cout << "Grafo desconexo: nao foi possivel completar a AGM." << endl;
            return;
        }

        // Inclui o novo vértice e soma o peso.
        incluido[melhorNovo] = 1;
        incluidos++;
        custoTotal += menorPeso;

        // Exibe sempre na ordem "incluído -> novo".
        cout << "Aresta: " << vertices[melhorIncluido].getRotulo()
             << " - " << vertices[melhorNovo].getRotulo()
             << " (peso " << menorPeso << ")" << endl;
    }

    cout << "Custo total da AGM: " << custoTotal << endl;
}

// ------------------------------------------------------------
// imprimirCentralidade: usa o algoritmo de Dijkstra
// para calcular a distância mínima de cada vértice a todos os
// demais. Depois, calcula 1 / soma das distâncias (centralidade
// de proximidade) e ordena em ordem decrescente.
// ------------------------------------------------------------
void Grafo::imprimirCentralidade() {
    cout << "\n===== CENTRALIDADE DE PROXIMIDADE =====" << endl;

    int n = vertices.size();
    if (n == 0) { cout << "Grafo vazio." << endl; return; }

    // Vetores paralelos para armazenar rótulo e centralidade.
    vector<string> nomes;
    vector<double> centralidades;

    // Para cada vértice de origem, roda Dijkstra.
    for (int origem = 0; origem < n; origem++) {

        // dist[i] = menor distância conhecida de origem até i.
        // -1 significa "infinito" (ainda não alcançado).
        vector<double> dist(n, -1);
        vector<int> visitado(n, 0);

        dist[origem] = 0;

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

            if (atual == -1) break;

            visitado[atual] = 1;

            // Relaxa as arestas que saem do vértice atual.
            Vertice *vAtual = &vertices[atual];

            for (unsigned k = 0; k < arestas.size(); k++) {
                Vertice *v1 = arestas[k].getPrimeiroVertice();
                Vertice *v2 = arestas[k].getSegundoVertice();

                // Descobre quem é o vizinho.
                Vertice *vizinho = NULL;
                if (v1 == vAtual) vizinho = v2;
                else if (v2 == vAtual) vizinho = v1;
                else continue;

                // Acha o índice do vizinho no vector.
                int idxViz = -1;
                for (unsigned m = 0; m < vertices.size(); m++) {
                    if (&vertices[m] == vizinho) { idxViz = m; break; }
                }

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

    // Exibe o resultado ordenado com 4 casas decimais
    // (evita empates falsos na exibição).
    cout << fixed << setprecision(4);
    for (unsigned i = 0; i < nomes.size(); i++) {
        cout << nomes[i] << " -> " << centralidades[i] << endl;
    }
}