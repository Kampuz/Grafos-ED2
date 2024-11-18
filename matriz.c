#include <stdio.h>
#include <stdlib.h>

#include "CodeBase/matriz.h"

int main() {
    PonteiroGrafo grafo;
    int numVertices;
    int origem, destino, peso;
    int vertice, inicio;
    int opcao, tipoImpressao;
    int *caminho;

    do
    {
        printf("\nOpções:\n");
        printf("1 - Criar Grafo\n");
        printf("2 - Inserir Aresta\n");
        printf("3 - Inserir Aresta com Peso");
        printf("4 - Remover Aresta\n");
        printf("5 - Verificar Aresta\n");
        printf("6 - Imprimir Arestas\n");
        printf("7 - Calcular Grau de um Vértice\n");
        printf("8 - Busca em Profundidade\n");
        printf("9 - Busca em Largura\n");
        printf("10 - Árvore Geradora Mínima\n");
        printf("11 - Djisktra\n");
        printf("0 - Liberar Grafo e Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        printf("\n");

        switch (opcao)
        {
        case 1:
            if (grafo != NULL)
                liberarGrafo(grafo);

            printf("Digite o número de vértices: ");
            scanf("%d", &numVertices);
            
            grafo = inicializarGrafo(numVertices);

            break;

        case 2:
            if (grafo == NULL)
            {
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
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &origem);

                printf("Digite o segundo vértice: ");
                scanf("%d", &destino);

                printf("Digite o peso: ");
                scanf("%d", &peso);

                adicionarArestaComPeso(grafo, origem, destino, peso);
            }
            break;

        case 4:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &origem);

                printf("Digite o segundo vértice: ");
                scanf("%d", &destino);

                removerAresta(grafo, origem, destino);
            }
            break;
        
        case 5:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o primeiro vértice: ");
                scanf("%d", &origem);

                printf("Digite o segundo vértice: ");
                scanf("%d", &destino);

                if (existeAresta(grafo, origem, destino))
                    printf("A aresta (%d, %d) existe.\n", origem, destino);
                else
                    printf("A aresta (%d, %d) não existe.\n", origem, destino);
            }
            break;

        case 6:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Arestas do grafo:\n");

                imprimirArestas(grafo);
            }
            break;

        case 7:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o vértice: ");
                scanf("%d", &vertice);

                printf("Grau do vértice %d: %d\n", vertice, grau(grafo, vertice));
            }
            break;

        case 8:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o vértice de início para busca em profundidade: ");
                scanf("%d", &inicio);

                caminho = buscaEmProfundidade(grafo, inicio);

                printf("Deseja mostrar o caminho normal ou inveros (1. normal | 2. inverso): ");
                scanf("%d", &tipoImpressao);

                if (tipoImpressao == 1)
                    for (int i = 0; i < numVertices; i++)
                        if (caminho[i] != -1)
                        {
                            printf("Caminho até %d: ", i);
                            imprimirCaminho(i, caminho);
                            printf("\n");
                        }
                else
                    for (int i = 0; i < numVertices; i++)
                        if (caminho[i] != -1)
                        {
                            printf("Caminho até %d: ", i);
                            imprimirCaminhoReverso(i, caminho);
                            printf("\n");
                        }
            }
            break;

        case 9:
            if (grafo == NULL)
            {
                printf("O grafo não foi criado.\n");
            } else {
                printf("Digite o vértice de início para busca em largura: ");
                scanf("%d", &inicio);

                caminho = buscaEmLargura(grafo, inicio);

                printf("Deseja mostrar o caminho normal ou inveros (1. normal | 2. inverso): ");
                scanf("%d", &tipoImpressao);

                if (tipoImpressao == 1)
                    for (int i = 0; i < numVertices; i++)
                        if (caminho[i] != -1)
                        {
                            printf("Caminho até %d: ", i);
                            imprimirCaminho(i, caminho);
                            printf("\n");
                        }
                else
                    for (int i = 0; i < numVertices; i++)
                        if (caminho[i] != -1)
                        {
                            printf("Caminho até %d: ", i);
                            imprimirCaminhoReverso(i, caminho);
                            printf("\n");
                        }
            }
            break;

            case 10:
                gerarArvoreMinima(grafo);

                break;

            case 11:
                if (grafo == NULL)
                {
                    printf("O grafo foi criado.\n");
                }  else {
                    printf("Digite o vértice de origem para o algoritmo de Dijkstra: ");
                    scanf("%d", &origem);

                    dijkstra(grafo, origem);
                }
                break;

        case 0:
            if (grafo != NULL)
            {
                liberarGrafo(grafo);
                printf("Grafo liberado. ");
            }

            printf("Saindo...\n");

            return 0;
            break;

        default:
            printf("Opção inválida.\n");

            break;
        }
    } while (opcao != 0);
    
    return 0;
}