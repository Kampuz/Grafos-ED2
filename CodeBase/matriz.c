#include <stdio.h>
#include <stdlib.h>

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

void liberarGrafo(PonteiroGrafo grafo) {
    int linha;
    for (linha = 0; linha < grafo->numVertices; linha++)
        free(grafo->matriz[linha]);

    free(grafo->matriz);
    free(grafo);
    return;
}

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    grafo->matriz[vertice1][vertice2] = 1;
    grafo->matriz[vertice2][vertice1] = 1;
}

void removerAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    grafo->matriz[vertice1][vertice2] = 0;
    grafo->matriz[vertice2][vertice1] = 0;
}

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    return grafo->matriz[vertice1][vertice2];
}

PonteiroGrafo criarGrafo() {
    int numArestas, numVertices, i, vertice1, vertice2;
    PonteiroGrafo grafo;

    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);
    printf("Digite o número de arestas: ");
    scanf("%d", &numArestas);

    grafo = inicializarGrafo(numVertices);
    for (i = 0; i < numArestas; i++)
    {
        printf("Digite o vértice 1: ");
        scanf("%d", &vertice1);
        printf("Digite o vértice 2: ");
        scanf("%d", &vertice2);

        adicionarAresta(grafo, vertice1, vertice2);
    }

    return grafo;
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

/*

int main() {
    int opcao, vertice1, vertice2, vertice;
    PonteiroGrafo grafo = NULL;

    while(1) {
        printf("\nOpções:\n");
        printf("1 - Criar Grafo\n");
        printf("2 - Inserir Aresta\n");
        printf("3 - Remover Aresta\n");
        printf("4 - Verificar Aresta\n");
        printf("5 - Imprimir Arestas\n");
        printf("6 - Calcular Grau de um Vértice\n");
        printf("7 - Liberar Grafo e Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (grafo != NULL)
                libearGrafo(grafo);

            grafo = criarGrafo();
            break;
        
        case 2:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &vertice1);
                printf("Digite o segundo vértice: ");
                scanf("%d", &vertice2);

                adicionarAresta(grafo, vertice1, vertice2);
            }
            break;

        case 3:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &vertice1);
                printf("Digite o segundo vértice: ");
                scanf("%d", &vertice2);

                removerAresta(grafo, vertice1, vertice2);
            }
            
            break;

        case 4:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &vertice1);
                printf("Digite o segundo vértice: ");
                scanf("%d", &vertice2);

                if (existeAresta(grafo, vertice1, vertice2))
                    printf("Existe aresta (%d, %d).\n", vertice1, vertice2);
                else
                    printf("Não existe aresta (%d, %d).\n", vertice1, vertice2);
            }

            break;

        case 5:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Arestas do grafo:\n");

                imprimirArestas(grafo);
            }

            break;

        case 6:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o vértice: ");
                scanf("%d", &vertice);

                printf("Grau do vértice %d: %d\n", vertice, grau(grafo, vertice));
            }

            break;

        case 7:
            if (grafo != NULL)
                libearGrafo(grafo);
            
            printf("Grafo liberado. Saindo...\n");
            
            return 0;
        
        default:
            printf("Opção inválida.\n");
        }
    }

    return 0;
}

*/