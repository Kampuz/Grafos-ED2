#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/matriz.h"

int *buscaEmLargura(PonteiroGrafo grafo, int inicio) {
    int *visitado = (int*)malloc(grafo->numVertices * sizeof(int));
    int *pai = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++)
    {
        visitado[i] = 0;
        pai[i] = -1;
    }
    
    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;
    pai[inicio] = inicio;

    while (frente < tras)
    {
        int verticeAtual = fila[frente++];

        for (int vizinho = 0; vizinho < grafo->numVertices; vizinho++)
            if (grafo->matriz[verticeAtual][vizinho] && !visitado[vizinho])
            {
                fila[tras++] = vizinho;
                visitado[vizinho] = 1;
                pai[vizinho] = verticeAtual;
            }
    }
    
    free(fila);
    free(visitado);
    return pai;
}

/*

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

*/