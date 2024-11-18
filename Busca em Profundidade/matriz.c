#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/matriz.h"

PonteiroPilha criarPilha(int capacidade) {
    PonteiroPilha pilha = (PonteiroPilha)malloc(sizeof(Pilha));
    
    pilha->capacidade = capacidade;
    pilha->topo = -1;
    pilha->dados = (int*)malloc(capacidade * sizeof(int));
    
    return pilha;
}

int pilhaVazia(PonteiroPilha pilha) {
    return pilha->topo == -1;
}

void empilhar(PonteiroPilha pilha, int valor) {
    if (pilha->topo < pilha->capacidade - 1)
        pilha->dados[++(pilha->topo)] = valor;
}

int desempilhar(PonteiroPilha pilha) {
    if (!pilhaVazia(pilha))
    {
        return pilha->dados[(pilha->topo)--];
    }
    return -1;
}

void destruirPilha(PonteiroPilha pilha) {
    free(pilha->dados);
    free(pilha);
}


int *buscaEmProfundidade(PonteiroGrafo grafo, int verticeInicial) {
    int vizinho, vertice;
    int *pais = (int*)malloc(grafo->numVertices * sizeof(int));
    int *visitados = (int*)malloc(grafo->numVertices * sizeof(int));
    PonteiroPilha pilha = criarPilha(grafo->numVertices);

    for (vertice = 0; vertice < grafo->numVertices; vertice++)
    {
        pais[vertice] = -1;
        visitados[vertice] = 0;
    }

    empilhar(pilha, verticeInicial);
    pais[verticeInicial] = verticeInicial;

    while (!pilhaVazia(pilha))
    {
        vertice = desempilhar(pilha);
        visitados[vertice] = 1;
        for (vizinho = 0; vizinho < grafo->numVertices; vizinho++)
            if (grafo->matriz[vertice][vizinho] && !visitados[vizinho])
            {
                pais[vizinho] = vertice;
                empilhar(pilha, vizinho);
            }
    }
    
    destruirPilha(pilha);
    free(visitados);
    return pais;
}

void imprimirCaminhoReverso(int vertice, int *pais) {
    printf("%d ", vertice);
    if (pais[vertice] != vertice)
        imprimirCaminhoReverso(pais[vertice], pais);
}

void imprimirCaminho(int vertice, int *pais) {
    if (pais[vertice] != vertice)
        imprimirCaminho(pais[vertice], pais);
    printf("%d ", vertice);
}

/*

int main() {

    PonteiroGrafo grafo;
    int numVertices, origem, destino, inicio, opcao;
    int *pais;

    printf("Digite o número de vértices do grafo: ");
    scanf("%d", &numVertices);

    grafo = inicializarGrafo(numVertices);

    printf("Deseja adicionar uma aresta? (1. Sim | 2. Não): ");

    while (scanf("%d", &opcao) && opcao == 1)
    {
        printf("\nDigite a origem e o destino da aresta (ex: 0 1): ");
        scanf("%d %d", &origem, &destino);
        
        adicionarAresta(grafo, origem, destino);

        printf("Deseja adicionar outra aresta? (1. Sim | 2. Não): ");
    }

    printf("Digite o vértice de início para busca em profundidade: ");
    scanf("%d", &inicio);

    pais = buscaEmProfundidade(grafo, inicio);

    printf("\nCaminhos a partir do vértice %d:\n", inicio);

    for (int i = 0; i < numVertices; i++)
    {
        if (pais[i] != -1)
        {
            printf("Caminho até %d (ordem reversa): ", i);
            imprimirCaminhoReverso(i, pais);
            printf("\n");

            printf("Caminho até %d (ordem normal): ", i);
            imprimirCaminho(i, pais);
            printf("\n");
        }
        
    }
    
    free(pais);
    liberarGrafo(grafo);
}

*/