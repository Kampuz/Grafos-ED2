#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/matriz.h"

int existeCaminho(PonteiroGrafo grafo, int inicio, int fim) {
    int encontrou, i, *visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (i = 0; i < grafo->numVertices; i++)
        visitado[i] = 0;

    encontrou = buscaRec(grafo, visitado, inicio, fim);
    free(visitado);
    return encontrou;
}

int buscaRec(PonteiroGrafo grafo, int *visitado, int chave, int fim) {
    int proximo;
    if(chave == fim)
        return 1;
    
    visitado[chave] = 1;
    for (proximo = 0; proximo < grafo->numVertices; proximo++)
        if (grafo->matriz[chave][proximo] && !visitado[proximo])
            if (buscaRec(grafo, visitado, proximo, fim))
                return 1;

    return 0;
}

int *encontrarCaminhos(PonteiroGrafo grafo, int inicio) {
    int i;
    int *pai = (int*)malloc(grafo->numVertices * sizeof(int));

    for (i = 0; i < grafo->numVertices; i++)
        pai[i] = -1;
    buscaEmProfundidade(grafo, pai, inicio, inicio);
    return pai;
}

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int verticePai, int vertice) {
    int proximo;
    pai[vertice] = verticePai;

    for (proximo = 0; proximo < grafo->numVertices; proximo++)
        if (grafo->matriz[vertice][proximo] && pai[proximo] == -1)
            buscaEmProfundidade(grafo, pai, vertice, proximo);
}

void imprimirCaminhoReverso(int vertice, int *pai) {
    printf("%d", vertice);
    if (pai[vertice] != vertice)
        imprimirCaminhoReverso(pai[vertice], pai);
}

void imprimirCaminho(int vertice, int *pai) {
    if (pai[vertice] != vertice)
        imprimirCaminho(pai[vertice], pai);
    printf("%d", vertice);
}