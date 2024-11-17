#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numVertices;
    int **matriz;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo inicializarGrafo(int numVertices) {
    int linha, coluna;
    PonteiroGrafo grafo = malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->matriz = malloc(numVertices * sizeof(int *));

    for (linha = 0; linha < numVertices; linha++)
        grafo->matriz[linha] = malloc(numVertices * sizeof(int));

    for (linha = 0; linha < numVertices; linha++)
        for (coluna = 0; coluna < numVertices; coluna++)
            grafo->matriz[linha][coluna] = 0;
    
    return grafo;
}

void liberarGrafo(PonteiroGrafo grafo) {
    int linha;
    for (linha = 0; linha < grafo->numVertices; linha++)
        free(grafo->matriz[linha]);

    free(grafo->matriz);
    free(grafo);
    return;
}

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    grafo->matriz[vertice1][vertice2] = 1;
    grafo->matriz[vertice2][vertice1] = 1;
}


void  buscaEmLargura(PonteiroGrafo grafo, int inicio) {
    int *visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++)
        visitado[i] = 0;
    
    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras)
    {
        int verticeAtual = fila[frente++];
        printf("Visitando %d\n", verticeAtual);

        for (int vizinho = 0; vizinho < grafo->numVertices; vizinho++)
            if (grafo->matriz[verticeAtual][vizinho] && !visitado[vizinho])
            {
                fila[tras++] = vizinho;
                visitado[vizinho] = 1;
            }
    }
    
    free(fila);
    free(visitado);
}

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = inicializarGrafo(numVertices);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 2, 4);

    printf("Busca em Largura a partir do vértice 0:\n");
    buscaEmLargura(grafo, 0);

    liberarGrafo(grafo);
    return 0;
}