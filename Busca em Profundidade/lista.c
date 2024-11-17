#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"

int *encontraComponentes(PonteiroGrafo grafo) {
    int s, c = 0, *componentes = (int*)malloc(grafo->numVertices * sizeof(int));

    for (s = 0; s < grafo->numVertices; s++)
        componentes[s] = -1;
    for (s = 0; s < grafo->numVertices; s++)
        if (componentes[s] == -1) {
            visitaRec(grafo, componentes, c, s);
            c++;
        }
    return componentes;
}

void visitaRec(PonteiroGrafo grafo, int *componentes, int componente, int vertice) {
    PonteiroNO no;
    componentes[vertice] = componente;
    for (no = grafo->lista[vertice]; no != NULL; no->proximo)
        if (componentes[no->vertice] == -1)
            visitaRec(grafo, componentes, componente, no->vertice);
}

int *encontraCaminhos(PonteiroGrafo grafo, int s) {
    int i, *pai = (int*)malloc(grafo->numVertices * sizeof(int));
    for (i = 0; i < grafo->numVertices; i++)
        pai[i] = -1;
    buscaEmProfundidade(grafo, pai, s, s);
    return pai;
}

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int vertice) {
    PonteiroNO no;
    pai[vertice] = p;
    for (no = grafo->lista[vertice]; no != NULL; no->proximo)
        if (pai[no->vertice] == -1)
            buscaEmProfundidade(grafo, pai, vertice, no->vertice);
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