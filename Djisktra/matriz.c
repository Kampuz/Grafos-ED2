#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../CodeBase/matriz.h"

typedef struct item {
    int prioridade;
    int vertice;
} Item;

typedef struct heap{
    Item *vertice;
    int *indice;
    int numVertices, tamanho;
} Heap;

typedef Heap *PonteiroHeap;

PonteiroHeap criarHeap(int tamanho) {
    PonteiroHeap heap = (PonteiroHeap)malloc(sizeof(Heap));

    heap->vertice = (Item*)malloc(tamanho * sizeof(Item));
    heap->indice = (int*)malloc(tamanho * sizeof(int));
    heap->numVertices = 0;
    heap->tamanho = tamanho;
    
    return heap;
}

void trocar(PonteiroHeap heap, int i, int j) {
    Item auxiliar = heap->vertice[i];
    heap->vertice[i] = heap->vertice[j];
    heap->vertice[j] = auxiliar;

    heap->indice[heap->vertice[i].vertice] = i;
    heap->indice[heap->vertice[j].vertice] = j;
}

void subir(PonteiroHeap heap, int i) {
    int pai = (i - 1) / 2;
    while ((i > 0) && (heap->vertice[i].prioridade < heap->vertice[pai].prioridade))
    {
        trocar(heap, i, pai);
        i = pai;
        pai = (i - 1) / 2;
    }
}

void descer(PonteiroHeap heap, int i) {
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int menor = i;

    if ((esq < heap->numVertices) && (heap->vertice[esq].prioridade < heap->vertice[menor].prioridade))
        menor = esq;
    if ((dir < heap->numVertices) && (heap->vertice[dir].prioridade < heap->vertice[menor].prioridade))
        menor = dir;
    if (menor != i)
        trocar(heap, i, menor);
        descer(heap, menor);
}

void inserirHeap(PonteiroHeap heap, int vertice, int prioridade) {
    if (heap->numVertices == heap->tamanho)
    {
        printf("ERRO: Heap cheia.\n");
        return;
    }
    
    heap->vertice[heap->numVertices].vertice = vertice;
    heap->vertice[heap->numVertices].prioridade = prioridade;
    heap->indice[vertice] = heap->numVertices;
    heap->numVertices++;
    subir(heap, (heap->numVertices - 1));
}

void diminuirPrioridade(PonteiroHeap heap, int vertice, int prioridade) {
    int i = heap->indice[vertice];
    
    heap->vertice[i].prioridade = prioridade;
    
    subir(heap, i);
}

int extrairMinimo(PonteiroHeap heap) {
    if (heap->numVertices == 0)
    {
        printf("ERRO: Heap vazia.\n");
        return -1;
    }
    
    int verticeMinimo = heap->vertice[0].vertice;
    heap->numVertices--;
    heap->vertice[0] = heap->vertice[heap->numVertices];
    heap->indice[heap->vertice[0].vertice] = 0;
    descer(heap, 0);
    return verticeMinimo;
}

int prioridade(PonteiroHeap heap, int vertice) {
    return heap->vertice[heap->indice[vertice]].prioridade;
}

int heapVazio(PonteiroHeap heap) {
    return heap->numVertices == 0;
}

int *dijkstra(PonteiroGrafo grafo, int verticeInicial) {
    int vertice;
    int *pai = (int*)malloc(grafo->numVertices * sizeof(int));
    int *distancias = (int*)malloc(grafo->numVertices * sizeof(int));

    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        distancias[vertice] = INT_MAX;
        pai[vertice] = -1;
    }

    distancias[verticeInicial] = 0;

    PonteiroHeap heap = criarHeap(grafo->numVertices);
    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        inserirHeap(heap, vertice, distancias[vertice]);
    }
    
    diminuirPrioridade(heap, verticeInicial, 0);

    while (!heapVazio(heap))
    {
        vertice = extrairMinimo(heap);

        if (distancias[vertice] != INT_MAX)
            for (int indice = 0; indice < grafo->numVertices; indice++)
                if ((grafo->matriz[vertice][indice] != INT_MAX) && (distancias[vertice] + grafo->matriz[vertice][indice] < distancias[indice]))
                {
                    distancias[indice] = distancias[vertice] + grafo->matriz[vertice][indice];
                    pai[indice] = vertice;
                    diminuirPrioridade(heap, indice, distancias[indice]);
                }
    }
    free(distancias);
    return pai;
}

void imprimirDjisktra(PonteiroGrafo grafo, int *pais, int verticeInicial) {
    printf("Pais de cada vértice a partir do vértice %d:\n", verticeInicial);
    for (int i = 0; i < grafo->numVertices; i++)
    {
        printf("Vértice %d: Pai = %d\n", i, pais[i]);
    }

    free(pais);
}
/*

int main() {
    int matriz[5][5] = {
        {0, 10, INT_MAX, INT_MAX, INT_MAX},
        {10, 0, 20, INT_MAX, INT_MAX},
        {INT_MAX, 20, 0, 5, INT_MAX},
        {INT_MAX, INT_MAX, 5, 0, 2},
        {INT_MAX, INT_MAX, INT_MAX, 2, 0}
    };

    PonteiroGrafo grafo = inicializarGrafo(5);

    grafo->matriz = matriz;

    int verticeInicial = 0;

    int *pais = dijkstra(grafo, verticeInicial);

    printf("Pais de cada vértice a partir do vértice %d:\n", verticeInicial);
    for (int i = 0; i < grafo->numVertices; i++)
    {
        printf("Vértice %d: Pai = %d\n", i, pais[i]);
    }

    free(pais);
    return 0;
}

*/