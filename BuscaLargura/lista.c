#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"

void buscaEmLargura(PonteiroGrafo grafo, int inicio) {
    int *visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++)
        visitado[i] = 0;

    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras) {
        int verticeAtual = fila[frente++];
        printf("Visitando %d\n", verticeAtual);

        PonteiroNo atual = grafo->listaAdjacentes[verticeAtual];
        while (atual != NULL) {
            if (!visitado[atual->vertice]) {
                fila[tras++] = atual->vertice;
                visitado[atual->vertice] = 1;
            }
            atual = atual->proximo;
        }
        
    }
    
    free(fila);
    free(visitado);
}

/*

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = criarGrafo(numVertices);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 2, 4);

    printf("\nBusca em Largura a partir do vértice 0:\n");
    buscaemLargura(grafo, 0);

    liberarGrafo(grafo);
    return 0;
}

*/