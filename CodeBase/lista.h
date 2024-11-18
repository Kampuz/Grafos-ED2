#ifndef LISTA_
#define LISTA_

typedef struct no {
    int vertice;
    struct no *proximo;
} NO;

typedef NO *PonteiroNO;

typedef struct grafo {
    PonteiroNO *lista;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo criarGrafo(int numVertices);

void liberarLista(PonteiroNO lista);

void liberarGrafo(PonteiroGrafo grafo);

PonteiroNO inserirLista(PonteiroNO lista, int vertice);

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

PonteiroNO removerLista(PonteiroNO lista, int vertice);

void removerAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

void imprimirArestas(PonteiroGrafo Grafo);




// BUSCA EM PROFUNDIDADE
int *encontrarCaminhos(PonteiroGrafo grafo, int inicio);
void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int v);
void imprimirCaminhoReverso(int vertice, int *pai);
void imprimirCaminho(int vertice, int *pai);
#endif