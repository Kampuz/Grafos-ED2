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
    if (menor == i) { 
        trocar(heap, i, menor);
        descer(heap, menor);
    }
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

    if (!pai || !distancias)
    {
        printf("Erro: Falha ao alocar memória.\n");
        exit(1);
    }
    

    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        distancias[vertice] = INT_MAX;
        pai[vertice] = -1;
    }

    distancias[verticeInicial] = 0;

    PonteiroHeap heap = criarHeap(grafo->numVertices);
    if (!heap)
    {
        printf("Erro: Falha ao criar o heap.\n");
        free(pai);
        free(distancias);
        exit(1);
    }
    

    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        inserirHeap(heap, vertice, distancias[vertice]);
    }
    
    diminuirPrioridade(heap, verticeInicial, 0);

    while (!heapVazio(heap))
    {
        vertice = extrairMinimo(heap);
        if (vertice == -1)
            break;

        if (distancias[vertice] != INT_MAX)
            for (int indice = 0; indice < grafo->numVertices; indice++)
                if ((grafo->matriz[vertice][indice] != INT_MAX) && (distancias[vertice] + grafo->matriz[vertice][indice] < distancias[indice]))
                {
                    distancias[indice] = distancias[vertice] + grafo->matriz[vertice][indice];
                    pai[indice] = vertice;
                    diminuirPrioridade(heap, indice, distancias[indice]);
                }
    }
    free(heap->vertice);
    free(heap->indice);
    free(heap);

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

int main() {
    int numVertices = 6;
    PonteiroGrafo grafo = criarGrafo(numVertices);

    inserirAresta(grafo, 0, 1, 4);
    inserirAresta(grafo, 0, 2, 2);
    inserirAresta(grafo, 1, 2, 5);
    inserirAresta(grafo, 1, 3, 10);
    inserirAresta(grafo, 2, 4, 3);
    inserirAresta(grafo, 4, 3, 4);
    inserirAresta(grafo, 3, 5, 11);

    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            if (grafo->matriz[i][j] != INT_MAX)
                grafo->matriz[j][i] = grafo->matriz[i][j];
    
    printf("Matriz de Adjacência:\n");
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
            if (grafo->matriz[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%3d ", grafo->matriz[i][j]);

        printf("\n");
    }

    int verticeInicial = 0;

    printf("Calculando Dijkstra...\n");
    int *pais = dijkstra(grafo, verticeInicial);
    printf("Dijkstra calculado com sucesso.\n");

    printf("Imprimindo Dijkstra...\n");
    imprimirDjisktra(grafo, pais, verticeInicial);
    printf("Dijkstra imprimido com sucesso.\n");

    for (int i = 0; i < grafo->numVertices; i++)
    {
        free(grafo->matriz[i]);
    }
    
    free(grafo->matriz);
    free(grafo);
    return 0;
}
