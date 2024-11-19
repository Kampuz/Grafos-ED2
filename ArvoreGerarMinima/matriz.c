#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../CodeBase/matriz.h"

void gerarArvoreMinima(PonteiroGrafo grafo) {
    int numVertices = grafo->numVertices;
    int *chave = (int*)malloc(numVertices * sizeof(int));
    int *incluido = (int*)malloc(numVertices * sizeof(int));
    int *pai = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++)
    {
        chave[i] = INT_MAX;
        incluido[i] = 0;
        pai[i] = -1;
    }

    chave[0] = 0;

    for (int i = 0; i < numVertices - 1; i++)
    {
        int u = -1, minChave = INT_MAX;
        for (int v = 0; v < numVertices; v++)
            if (!incluido[v] && chave[v] < minChave)
            {
                minChave = chave[v];
                u = v;
            }
        incluido[u] = 1;

        for (int v = 0; v < numVertices; v++)
            if (grafo->matriz[u][v] != INT_MAX && !incluido[v] && grafo->matriz[u][v] < chave[v])
            {
                chave[v] = grafo->matriz[u][v];
                pai[v] = u;
            }
    }

    printf("Arestas da Árvore Geradora Mínima (MST):\n");
    int pesoTotal = 0;
    for (int i = 1; i < numVertices; i++)
    {
        if (grafo->matriz[i][pai[i]] != INT_MAX)
        {
            printf("{%d, %d} com peso %d\n", pai[i], i, grafo->matriz[i][pai[i]]);
            pesoTotal += grafo->matriz[i][pai[i]];
        }
    }
    printf("Peso total da MST: %d\n", pesoTotal);

    free(chave);
    free(incluido);
    free(pai);
}

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = criarGrafo(numVertices);
    
    inserirAresta(grafo, 0, 1, 2);
    inserirAresta(grafo, 0, 3, 6);
    inserirAresta(grafo, 1, 2, 3);
    inserirAresta(grafo, 1, 3, 8);
    inserirAresta(grafo, 1, 4, 5);
    inserirAresta(grafo, 2, 4, 7);
    inserirAresta(grafo, 3, 4, 9);

    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (grafo->matriz[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%d ", grafo->matriz[i][j]);
            printf("\n");

    gerarArvoreMinima(grafo);

    liberarGrafo(grafo);
    return 0;
}