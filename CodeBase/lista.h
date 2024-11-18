#ifndef LISTA_
#define LISTA_

typedef struct no {
    int vertice;
    struct no *proximo;
    int peso;
} No;

typedef No *PonteiroNo;

typedef struct grafo {
    // Vetor de vértices
    PonteiroNo *listaAdjacentes;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo criarGrafo(int numVertices);

void liberarLista(PonteiroNo lista);

void liberarGrafo(PonteiroGrafo grafo);

PonteiroNo inserirLista(PonteiroNo lista, int vertice);

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