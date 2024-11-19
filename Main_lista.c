#include <stdio.h>
#include <stdlib.h>

#include "CodeBase\lista.h"

void menu() {
    printf ("\n\n\nAlgoritmo de Grafos\n\n\n");
    printf ("1. Criar novo Grafo\n");
    printf ("2. Eliminar Grafo\n");
    printf ("3. Inserir Arestas\n");
    printf ("4. Remover Arestas\n");
    printf ("5. Busca em Profundidade\n");
    printf ("6. Busca em Largura\n");
    printf ("7. Dijikstra\n");
    printf ("8. Arvore Geradora Minima\n");
    printf ("0. Sair\n");
}

int main() {
    int opcao = -1, vertices, a, b;
    int* pai;
    PonteiroGrafo grafo = NULL;

    while (opcao != 0) {
        menu();
        printf ("= ");
        scanf ("%d", &opcao);
        switch (opcao) {
        case 1:
            printf ("Numero de Vertices: ");
            scanf ("%d", &vertices);
            grafo = criarGrafo(vertices);
            break;
        case 2:
            printf ("Eliminando Grafo...");
            liberarGrafo(grafo);
            break;
        case 3:
            printf ("A: ");
            scanf("%d", &a);
            printf ("B: ");
            scanf("%d", &b);
            adicionarAresta(grafo, a, b);
            printf ("A:%d <- B:%d", a, b);
            break;     
        case 4:
            printf ("A: ");
            scanf("%d", &a);
            printf ("B: ");
            scanf("%d", &b);
            removerAresta(grafo, a, b);
            printf ("A:%d </- B:%d", a, b);
            break;
        case 5: // busca prof
            printf ("Vertice de Inicio para a Busca em Profundidade: ");
            scanf ("%d", &a);
            pai = encontrarCaminhos(grafo, a);
            printf ("Caminho a partir do vertice %d\n", a);
            for (int i = 0; i < grafo->numVertices; i++) {
                printf("Caminho para %d: ", i);
                imprimirCaminho(i, pai);
                printf("\n");
            }
            free(pai);
            break;
        case 6: // busca larg
            printf ("Vertice de inicio para a Busca em Largura: ");
            scanf("%d", &a);
            buscaEmLargura(grafo, a);
            break;
        case 7: // dijik
            printf("Digite o vertice de origem: ");
            scanf("%d", &a);
            printf("Digite o vertice de destino: ");
            scanf("%d", &b);
            
            // Chamada do algoritmo de Dijkstra
            pai = dijkstra(grafo, a);
            
            printf("Caminho mais curto de %d para %d:\n", a, b);
            if (pai[b] == -1) {
                printf("Nao ha caminho de %d para %d.\n", a, b);
            } else {
                printf("Caminho: ");
                int atual = b;
                while (atual != a) {
                    printf("%d <- ", atual);
                    atual = pai[atual];
                }
                printf("%d\n", a); 
            }
            free(pai); 
            break;
        case 8: // AGM
            printf ("Arvore Geradora Minima:\n");
            gerarArvoreMinima(grafo);
            break;
        case 0:
            printf ("Saindo...");
            break;
        default:
            printf ("Nao existe esssa opcao");
            break;
        }
    }
}