#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"

typedef struct {
    int origem, destino, peso;
} Aresta;

typedef struct {
    int *parente, *rank, numVertices;
} UnionFind;

PonteiroGrafo criarGrafo(int numVertices) {
    int indice;
    
    PonteiroGrafo grafo = malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->listaAdjacentes = malloc(numVertices * sizeof(PonteiroNo));

    for (indice = 0; indice < numVertices; indice++)
        grafo->listaAdjacentes[indice] = NULL;

    return grafo;
}

PonteiroNo inserirListaComPeso(PonteiroNo lista, int vertice, int peso) {
    PonteiroNo novoNo = malloc(sizeof(No));
    
    novoNo->vertice = vertice;
    novoNo->peso = peso;
    novoNo->proximo = lista;

    return novoNo;
}

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino, int peso) {
    grafo->listaAdjacentes[origem] = inserirListaComPeso(grafo->listaAdjacentes[origem], destino, peso);
    grafo->listaAdjacentes[destino] = inserirListaComPeso(grafo->listaAdjacentes[destino], origem, peso);
}

UnionFind* criarUnionFind(int numVertices) {
    UnionFind* uf = malloc(sizeof(UnionFind));
    uf->parente = malloc(numVertices * sizeof(int));
    uf->rank = malloc(numVertices * sizeof(int));
    uf->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        uf->parente[i] = i;
        uf->rank[i] = 0;
    }

    return uf;
}

int find(UnionFind* uf, int i) {
    if (uf->parente[i] != i)
        uf->parente[i] = find(uf, uf->parente[i]);

    return uf->parente[i];
}

void unionSets(UnionFind* uf, int x, int y) {
    int raizX = find(uf, x);
    int raizY = find(uf, y);
    
    if (raizX != raizY) {
        if (uf->rank[raizX] > uf->rank[raizY])
            uf->parente[raizY] = raizX;
        else if (uf->rank[raizX] < uf->rank[raizY])
            uf->parente[raizX] = raizY;
        else {
            uf->parente[raizY] = raizX;
            uf->rank[raizX]++;
        }
    }
}

int compararArestas(const void* a, const void* b) {
    return ((Aresta*)a)->peso - ((Aresta*)b)->peso;
}

void gerarArvoreMinima(PonteiroGrafo grafo) {
    Aresta* arestas = malloc(grafo->numVertices * grafo->numVertices * sizeof(Aresta));
    int numArestas = 0;
    int pesoTotal = 0;

    for (int i = 0; i < grafo->numVertices; i++) {
        PonteiroNo auxiliar = grafo->listaAdjacentes[i];
        while (auxiliar != NULL) {
            if (i < auxiliar->vertice) {
                arestas[numArestas].origem = i;
                arestas[numArestas].destino = auxiliar->vertice;
                arestas[numArestas].peso = auxiliar->peso;
                numArestas++;
            }
            auxiliar = auxiliar->proximo;
        }
    }

    qsort(arestas, numArestas, sizeof(Aresta), compararArestas);

    UnionFind* uf = criarUnionFind(grafo->numVertices);

    printf("Arestas da Árvore Geradora Mínima (MST):\n");
    for (int i = 0; i < numArestas; i++) {
        int u = arestas[i].origem;
        int v = arestas[i].destino;
        int peso = arestas[i].peso;

        if (find(uf, u) != find(uf, v)) {
            printf("{%d, %d} com peso %d\n", u, v, peso);
            pesoTotal += peso;
            unionSets(uf, u, v);
        }
    }

    printf("Peso total da MST: %d\n", pesoTotal);

    free(arestas);
    free(uf->parente);
    free(uf->rank);
    free(uf);
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