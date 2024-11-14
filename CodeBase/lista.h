#ifndef LISTA_
#define LISTA_

typedef struct {
    int vertice;
    struct no *proximo;
} NO;

typedef struct {
    ponteiroNO *lista;
    int numVertices;
} Grafo;

typedef NO *ponteiroNO;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo criarGrafo(int numVertices);

void liberarLista(ponteiroNO lista);

void liberarGrafo(PonteiroGrafo grafo);

ponteiroNO inserirLista(ponteiroNO lista, int vertice);

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

ponteiroNO removerLista(ponteiroNO lista, int vertice);

void removerAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

void imprimirArestas(PonteiroGrafo Grafo);

#endif