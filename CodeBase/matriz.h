#ifndef MATRIZ_
#define MATRIZ_

typedef struct {
    int **matriz;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo inicializarGrafo(int numVertices);

void liberarGrafo(PonteiroGrafo grafo);

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

void removerAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

PonteiroGrafo criarGrafo();

void imprimirArestas(PonteiroGrafo Grafo);

int grau(PonteiroGrafo grafo, int vertice);

#endif