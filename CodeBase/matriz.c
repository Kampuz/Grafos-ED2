#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "matriz.h"

PonteiroGrafo inicializarGrafo(int numVertices) {
    int linha, coluna;
    PonteiroGrafo grafo = (PonteiroGrafo)malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->matriz = (int**)malloc(numVertices * sizeof(int *));

    for (linha = 0; linha < numVertices; linha++)
        grafo->matriz[linha] = malloc(numVertices * sizeof(int));

    for (linha = 0; linha < numVertices; linha++)
        for (coluna = 0; coluna < numVertices; coluna++)
            grafo->matriz[linha][coluna] = 0;
    
    return grafo;
}

PonteiroGrafo criarGrafo(int numVertices) {
    int linha, coluna;
    PonteiroGrafo grafo = (PonteiroGrafo)malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->matriz = (int**)malloc(numVertices * sizeof(int*));

    for (linha = 0; linha < numVertices; linha++)
        grafo->matriz[linha] = (int*)malloc(numVertices * sizeof(int));

    for (linha = 0; linha < numVertices; linha++)
        for (coluna = 0; coluna < numVertices; coluna++)
            if (linha == coluna)
                grafo->matriz[linha][coluna] = 0;
            else
                grafo->matriz[linha][coluna] = INT_MAX;
    
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

void inserirAresta(PonteiroGrafo grafo, int origem, int destino, int peso) {
    grafo->matriz[origem][destino] = peso;
    grafo->matriz[destino][origem] = peso;
}

void removerAresta(PonteiroGrafo grafo, int origem, int destino) {
    grafo->matriz[origem][destino] = 0;
    grafo->matriz[destino][origem] = 0;
}

int existeAresta(PonteiroGrafo grafo, int origem, int destino) {
    return grafo->matriz[origem][destino];
}

void imprimirArestas(PonteiroGrafo grafo) {
    int vertice1, vertice2;

    for (vertice1 = 0; vertice1 < grafo->numVertices; vertice1++)
        for (vertice2 = vertice1 + 1; vertice2 < grafo->numVertices; vertice2++)
            if (grafo->matriz[vertice1][vertice2])
                printf("{%d,%d}\n", vertice1, vertice2);
}

int grau(PonteiroGrafo grafo, int vertice) {
    int i, grau = 0;

    for (i = 0; i < grafo->numVertices; i++)
        if (grafo->matriz[vertice][i])
            grau++;

    return grau;
}