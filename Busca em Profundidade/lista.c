#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"


int *encontrarCaminhos(PonteiroGrafo grafo, int inicio) {
    int i, *pai = (int*)malloc(grafo->numVertices * sizeof(int));

    for (i = 0; i < grafo->numVertices; i++)
        pai[i] = -1;

    buscaEmProfundidade(grafo, pai, inicio, inicio);

    return pai;
}

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int v) {
    PonteiroNO no;
    pai[v] = p;

    for (no = grafo->lista[v]; no != NULL; no = no->proximo)
        if (pai[no->vertice] == -1)
            buscaEmProfundidade(grafo, pai, v, no->vertice);
}

void imprimirCaminhoReverso(int vertice, int *pai) {
    printf("%d ", vertice);
    if (pai[vertice] != vertice)
        imprimirCaminhoReverso(pai[vertice], pai);
}

void imprimirCaminho(int vertice, int *pai) {
    if (pai[vertice] != vertice)
    imprimirCaminho(pai[vertice], pai);

    printf("%d ", vertice);
}

/*

int main() {
    PonteiroGrafo grafo;
    int numVertices, i, inicio;
    int *pai;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    grafo = criarGrafo(numVertices);

    int origem, destino, opcao;

    printf("Deseja adicionar uma aresta? (1. Sim | 2. Não): ");
    while (scanf("%d", &opcao) && opcao == 1)
    {
        printf("\nDigite a origem e o destino da aresta (ex: 0 1):");
        scanf("%d %d", &origem, &destino);
        adicionarAresta(grafo, origem, destino);
        printf("Deseja adicionar outra aresta? (1. Sim | 2. Não): ");
    }

    printf("Digite o vértice de início para a busca em profundidade: ");
    scanf("%d", &inicio);

    pai = encontrarCaminhos(grafo, inicio);
    
    printf("\nCaminhos a partir do vértice %d:\n", inicio);
    for (i = 0; i < numVertices; i++)
    {
        if (pai[i] != -1)
        {
            printf("Caminho até %d (ordem inversa):", i);
            imprimirCaminhoReverso(i, pai);
            printf("\n");

            printf("Caminho até %d (ordem normal): ", i);
            imprimirCaminho(i, pai);
            printf("\n");
        }
    }

    free(pai);
    liberarGrafo(grafo);
    return 0;
}

*/