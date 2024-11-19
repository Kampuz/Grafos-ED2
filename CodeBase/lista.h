#ifndef LISTA_
#define LISTA_

/**
 * @brief Estrutura do Nó das Listas de Adjacências
 * 
 */
typedef struct no {
    int vertice;
    struct no *proximo;
    int peso;
} No;

/**
 * @brief Ponteiro para No da Lista de Adjacência
 * 
 */
typedef No *PonteiroNo;

/**
 * @brief Estrutura do Grafo de Lista de Adjacência
 * 
 */
typedef struct {
    // Uma lista de ponteiros, que cada posição representa o vértice
    PonteiroNo *listaAdjacentes;
    // Quantidade de vértices que tem no grafo
    int numVertices;
} Grafo;

/**
 * @brief Ponteiro para o Grafo.
 * 
 */
typedef Grafo *PonteiroGrafo;

/**
 * @brief Funçao para criar o grafo com n vertices
 * 
 * @param numVertices quantidade de vertices que o grafo possui
 * @return PonteiroGrafo o ponteiro para o grafo
 */
PonteiroGrafo criarGrafo(int numVertices);

typedef struct {
    int origem, destino, peso;
} Aresta;

void liberarLista(PonteiroNo lista);

void liberarGrafo(PonteiroGrafo grafo);

PonteiroNo inserirLista(PonteiroNo lista, int vertice);

PonteiroNo inserirListaComPeso(PonteiroNo lista, int vertice, int peso);

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino);

void adicionarArestaComPeso(PonteiroGrafo grafo, int origem, int destino, int peso);

PonteiroNo removerLista(PonteiroNo lista, int vertice);

void removerAresta(PonteiroGrafo grafo, int origem, int destino);

int existeAresta(PonteiroGrafo grafo, int origem, int destino);

void imprimirArestas(PonteiroGrafo Grafo);

int compararPesoArestas(const void* a, const void* b);

// BUSCA EM PROFUNDIDADE

int *encontrarCaminhos(PonteiroGrafo grafo, int inicio);

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int v);

void imprimirCaminhoReverso(int vertice, int *pai);

void imprimirCaminho(int vertice, int *pai);

// BUSCA EM LARGURA

void buscaEmLargura(PonteiroGrafo grafo, int inicio);

// DIJIKSTRA

int* dijkstra (PonteiroGrafo grafo, int incio);

// ARVORE GERADORA MÍNIMA

void gerarArvoreMinima(PonteiroGrafo grafo);

#endif

/** TODO:
 * (Implementados em Matriz, mas não lista) (EXTRA)
 * GRAU, POPULARIDADE, RECOMENDAÇÕES
 * 
 * (Não Implementados, talvez não obrigatório) (EXTRA)
 * ENCONTRAR COMPONENTES (componentes conexos)
 * ORDENAÇÃO TOPOLÓGICA
 */