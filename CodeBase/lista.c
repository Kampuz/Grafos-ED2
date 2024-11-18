#include <stdio.h>
#include <stdlib.h>

#include "lista.h"


PonteiroGrafo criarGrafo(int numVertices) {
    int indice;
    PonteiroGrafo grafo = malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->listaAdjacentes = malloc(numVertices * sizeof(PonteiroNo));

    for (indice = 0; indice < numVertices; indice++)
        grafo->listaAdjacentes[indice] = NULL;

    return grafo;
}

void liberarLista(PonteiroNo lista) {
    if (lista != NULL) {
        liberarLista(lista->proximo);
        free(lista);
    }
}

void liberarGrafo(PonteiroGrafo grafo) {
    int indice;
    for (indice = 0; indice < grafo->numVertices; indice++)
        liberarLista(grafo->listaAdjacentes[indice]);
    free(grafo->listaAdjacentes);
    free(grafo);
    return;
}

PonteiroNo inserirLista(PonteiroNo lista, int vertice) {
    PonteiroNo novoNo = malloc(sizeof(No));
    
    novoNo->vertice = vertice;
    novoNo->proximo = lista;

    return novoNo;
}

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino) {
    grafo->listaAdjacentes[destino] = inserirLista(grafo->listaAdjacentes[destino], origem);
}

PonteiroNo removerLista(PonteiroNo lista, int vertice) {
    PonteiroNo proximo;
    if (lista == NULL)
        return NULL;
    else if (lista->vertice == vertice) {
        proximo = lista->proximo;
        free(lista);
        return proximo;
    } else {
        lista->proximo = removerLista(lista->proximo, vertice);
        return lista;
    }
}

void removerAresta(PonteiroGrafo grafo, int origem, int destino) {
    grafo->listaAdjacentes[origem] = removerLista(grafo->listaAdjacentes[origem], destino);
}

int existeAresta(PonteiroGrafo grafo, int origem, int destino) {
    PonteiroNo auxiliar;
    for (auxiliar = grafo->listaAdjacentes[origem]; auxiliar != NULL; auxiliar = auxiliar->proximo)
        if (auxiliar->vertice == destino)
            return 1;
    
    return 0;
}

void imprimirArestas(PonteiroGrafo grafo) {
    int origem;
    PonteiroNo auxiliar;

    for (origem = 0; origem < grafo->numVertices; origem++)
        for (auxiliar = grafo->listaAdjacentes[origem]; auxiliar != NULL; auxiliar = auxiliar->proximo)
            printf("{%d,%d}\n", origem, auxiliar->vertice);
}

/** TODO:
 * (Implementados em Matriz, mas não lista)
 * GRAU, POPULARIDADE, RECOMENDAÇÕES
 * 
 * (Não Implementados, talvez não obrigatório)
 * ENCONTRAR COMPONENTES (componentes conexos)
 * ENCONTRAR CAMINHO
 * IMPRIMIR CAMINHO e CAMINHO REVERSO
 * ORDENAÇÃO TOPOLÓGICA
 * 
 * (Não Implementados, obrigatório)
 * BUSCA EM PROFUNDIDADE
 * BUSCA EM LARGURA
 * DIJIKSTRA
 * ÁRVORE GERADORA MÍNIMA
 */

/*
int main() {
    int opcao, origem, destino;
    PonteiroGrafo grafo = NULL;

    while (1) {
        printf("\nOpções:\n");
        printf("1 - Criar Grafo\n");
        printf("2 - Adicionar Aresta\n");
        printf("3 - Remover Aresta\n");
        printf("4 - Verificar Aresta\n");
        printf("5 - Imprimir Arestas\n");
        printf("6 - Liberar Grafo e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (grafo != NULL) {
                    liberarGrafo(grafo);
                }
                int numVertices;
                printf("Digite o número de vértices: ");
                scanf("%d", &numVertices);
                grafo = criarGrafo(numVertices);
                break;
            case 2:
                if (grafo == NULL) {
                    printf("O grafo não foi criado.\n");
                } else {
                    printf("Digite o primeiro vértice: ");
                    scanf("%d", &origem);
                    printf("Digite o segundo vértice: ");
                    scanf("%d", &destino);
                    adicionarAresta(grafo, origem, destino);
                }
                break;
            case 3:
                if (grafo == NULL) {
                    printf("O grafo não foi criado.\n");
                } else {
                    printf("Digite o primeiro vértice: ");
                    scanf("%d", &origem);
                    printf("Digite o segundo vértice: ");
                    scanf("%d", &destino);
                    removerAresta(grafo, origem, destino);
                }
                break;
            case 4:
                if (grafo == NULL) {
                    printf("O grafo não foi criado.\n");
                } else {
                    printf("Digite o primeiro vértice: ");
                    scanf("%d", &origem);
                    printf("Digite o segundo vértice: ");
                    scanf("%d", &destino);
                    if (existeAresta(grafo, origem, destino)) {
                        printf("Existe uma aresta entre %d e %d.\n", origem, destino);
                    } else {
                        printf("Não existe uma aresta entre %d e %d.\n", origem, destino);
                    }
                }
                break;
            case 5:
                if (grafo == NULL) {
                    printf("O grafo não foi criado.\n");
                } else {
                    printf("Arestas do grafo:\n");
                    imprimirArestas(grafo);
                }
                break;
            case 6:
                if (grafo != NULL) {
                    liberarGrafo(grafo);
                }
                printf("Grafo liberado. Saindo...\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}

*/