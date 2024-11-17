#ifndef LISTA_
#define LISTA_

typedef struct {
    int vertice;
    struct no *proximo;
} NO;

typedef struct {
    PonteiroNO *lista;
    int numVertices;
} Grafo;

typedef NO *PonteiroNO;

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

#endif