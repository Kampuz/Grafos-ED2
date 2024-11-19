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
typedef struct grafo {
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

PonteiroGrafo criarGrafo(int numVertices);

void liberarLista(PonteiroNo lista);

void liberarGrafo(PonteiroGrafo grafo);

PonteiroNo inserirLista(PonteiroNo lista, int vertice);

PonteiroNo inserirListaComPeso(PonteiroNo lista, int vertice, int peso);

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino);

PonteiroNo removerLista(PonteiroNo lista, int vertice);

void removerAresta(PonteiroGrafo grafo, int origem, int destino);

int existeAresta(PonteiroGrafo grafo, int origem, int destino);

void imprimirArestas(PonteiroGrafo Grafo);

// BUSCA EM PROFUNDIDADE

int *encontrarCaminhos(PonteiroGrafo grafo, int inicio);

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int v);

void imprimirCaminhoReverso(int vertice, int *pai);

void imprimirCaminho(int vertice, int *pai);

// BUSCA EM LARGURA

// DIJIKSTRA

// ARVORE GERADORA MÍNIMA


#endif