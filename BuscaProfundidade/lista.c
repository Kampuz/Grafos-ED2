#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"


int *encontrarCaminhos(PonteiroGrafo grafo, int inicio) {
    int indice, *pai = (int*)malloc(grafo->numVertices * sizeof(int));

    for (indice = 0; indice < grafo->numVertices; indice++)
        pai[indice] = -1;

    buscaEmProfundidade(grafo, pai, inicio, inicio);

    return pai;
}

void buscaEmProfundidade(PonteiroGrafo grafo, int *pai, int p, int v) {
    PonteiroNo no;
    pai[v] = p;

    for (no = grafo->listaAdjacentes[v]; no != NULL; no = no->proximo)
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
    int numVertices, indice, inicio;
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
    for (indice = 0; indice < numVertices; indice++)
    {
        if (pai[indice] != -1)
        {
            printf("Caminho até %d (ordem inversa):", indice);
            imprimirCaminhoReverso(indice, pai);
            printf("\n");

            printf("Caminho até %d (ordem normal): ", indice);
            imprimirCaminho(indice, pai);
            printf("\n");
        }
    }

    free(pai);
    liberarGrafo(grafo);
    return 0;
}

*/