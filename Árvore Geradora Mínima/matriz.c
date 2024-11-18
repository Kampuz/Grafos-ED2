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
        printf("{%d, %d} com peso %d\n", pai[i], i, grafo->matriz[i][pai[i]]);
        pesoTotal += grafo->matriz[i][pai[i]];
    }
    printf("Peso total da MST: %d\n", pesoTotal);

    free(chave);
    free(incluido);
    free(pai);
}

/*

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = criarGrafo(numVertices);

    adicionarAresta(grafo, 0, 1, 2);
    adicionarAresta(grafo, 0, 3, 6);
    adicionarAresta(grafo, 1, 3, 8);
    adicionarAresta(grafo, 1, 2, 3);
    adicionarAresta(grafo, 2, 3, 4);
    adicionarAresta(grafo, 3, 4, 5);

    gerarArvoreMinima(grafo);

    liberarGrafo(grafo);
    return 0;
}

*/