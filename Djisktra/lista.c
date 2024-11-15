#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
    int vertice;
    int peso;
    struct no *proximo;
} NO;

typedef NO *PonteiroNO;

typedef struct {
    PonteiroNO *lista;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

typedef struct item
{
    int prioridade;
    int vertice;
} ITEM;

typedef struct heap
{
    ITEM *itens;
    int *indice;
    int tamanhoMaximo, tamanho;
} HEAP;

typedef HEAP *PonteiroHeap;

PonteiroGrafo criarGrafo(int numVertices) {
    PonteiroGrafo grafo = (PonteiroGrafo)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->lista = (PonteiroNO *)malloc(numVertices * sizeof(PonteiroNO));
    for (int i = 0; i < numVertices; i++)
    {
        grafo->lista[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino, int peso) {
    PonteiroNO  novoNo = (PonteiroNO)malloc(sizeof(NO));
    novoNo->vertice = destino;
    novoNo->peso = peso;
    novoNo->proximo = grafo->lista[origem];
    grafo->lista[origem] = novoNo;
}

void liberarGrafo(PonteiroGrafo grafo) {
    for (int i = 0; i < grafo->numVertices; i++)
    {
        PonteiroNO noAtual = grafo->lista[i];
        while (noAtual != NULL)
        {
            PonteiroNO aux = noAtual;
            noAtual = noAtual->proximo;
            free(aux);
        }
    }

    free(grafo->lista);
    free(grafo);
}

PonteiroHeap criarHeap(int tamanhoMaximo) {
    PonteiroHeap heap = (PonteiroHeap)malloc(sizeof(HEAP));
    heap->itens = (ITEM *)malloc(tamanhoMaximo * sizeof(ITEM));
    heap->indice = (int *)malloc(tamanhoMaximo * sizeof(int));
    heap->tamanho = 0;
    heap->tamanhoMaximo = tamanhoMaximo;

    for (int i = 0; i < tamanhoMaximo; i++)
        heap->indice[i] = -1;
    
    return heap;
} 

void heapify(PonteiroHeap heap, int algo) {
    int menor = algo;
    int esq = 2 * algo + 1;
    int dir = 2 * algo + 2;

    if (esq < heap->tamanho && heap->itens[esq].prioridade < heap->itens[menor].prioridade)
        menor = esq;

    if (dir < heap->tamanho && heap->itens[dir].prioridade < heap->itens[menor].prioridade)
        menor = dir;
    
    if (menor != algo)
    {
        ITEM aux = heap->itens[algo];
        heap->itens[algo] = heap->itens[menor];
        heap->itens[menor] = aux;

        heap->indice[heap->itens[algo].vertice] = algo;
        heap->indice[heap->itens[menor].vertice] = menor;

        heapify(heap, menor);
    }
}


void insere(PonteiroHeap heap, int vertice, int prioridade) {
    int i = heap->tamanho++;
    heap->itens[i].vertice = vertice;
    heap->itens[i].prioridade = prioridade;
    heap->indice[vertice] = i;

    while (i > 0 && heap->itens[(i - 1) / 2].prioridade > heap->itens[i].prioridade)
    {
        ITEM aux = heap->itens[i];
        heap->itens[i] = heap->itens[(i - 1) / 2];
        heap->itens[(i - 1) / 2] = aux;

        heap->indice[heap->itens[i].vertice] = i;
        heap->indice[heap->itens[(i - 1) / 2].vertice] = (i - 1) / 2;
        i = (i - 1) / 2;
    }
}

int vazia(PonteiroHeap heap) {
    return (heap->tamanho == 0);
}

int minimo(PonteiroHeap heap) {
    int verticeMinimo = heap->itens[0].vertice;
    heap->itens[0] = heap->itens[--heap->tamanho];
    heap->indice[heap->itens[0].vertice] = 0;

    heapify(heap, 0);
    return verticeMinimo;
}

int prioridade(PonteiroHeap heap, int vertice) {
    int i = heap->indice[vertice];
    return ((i != -1) ? heap->itens[i].prioridade : __INT_MAX__);
}

void diminuirPrioridade(PonteiroHeap heap, int vertice, int novaPrioridade) {
    int i = heap->indice[vertice];
    heap->itens[i].prioridade = novaPrioridade;

    while (i > 0 && heap->itens[(i - 1) / 2].prioridade > heap->itens[i].prioridade)
    {
        ITEM aux = heap->itens[i];
        heap->itens[i] = heap->itens[(i - 1) / 2];
        heap->itens[(i - 1) / 2] = aux;

        heap->indice[heap->itens[i].vertice] = i;
        heap->indice[heap->itens[(i - 1) / 2].vertice] = (i - 1) / 2;
        i = (i - 1) / 2;
    }
    
}

int *dijkstra(PonteiroGrafo grafo, int inicio) {
    int vertice, *pai = (int*)malloc(grafo->numVertices * sizeof(int));
    PonteiroNO no;
    PonteiroHeap heap = criarHeap(grafo->numVertices);
    
    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        pai[vertice] = -1;
        insere(heap, vertice, INT_MAX);
    }

    pai[inicio] = inicio;
    diminuirPrioridade(heap, inicio, 0);

    while (!vazia(heap))
    {
        vertice = minimo(heap);

        if (prioridade(heap, vertice) != INT_MAX)
            for (no = grafo->lista[vertice]; no != NULL; no = no->proximo)
                if (prioridade(heap, vertice) + no->peso < prioridade(heap, no->vertice))
                {
                    diminuirPrioridade(heap, no->vertice, prioridade(heap, vertice) + no->peso);
                    pai[no->vertice] = vertice;
                }
    }
    
    return pai;
}

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = criarGrafo(numVertices);


    adicionarAresta(grafo, 0, 1, 10);
    adicionarAresta(grafo, 0, 2, 3);
    adicionarAresta(grafo, 1, 2, 1);
    adicionarAresta(grafo, 1, 3, 2);
    adicionarAresta(grafo, 2, 1, 4);
    adicionarAresta(grafo, 2, 3, 8);
    adicionarAresta(grafo, 2, 4, 2);
    adicionarAresta(grafo, 3, 4, 7);
    adicionarAresta(grafo, 4, 3, 9);

    int inicio = 0;
    int *pai = dijkstra(grafo, inicio);

    printf("Caminho mínimo a partir do vértice %d:\n", inicio);
    for (int i = 0; i < numVertices; i++)
        printf("Vértice %d: predecessor = %d\n", i, pai[i]);
    
    free(pai);
    liberarGrafo(grafo);
    return 0;
}