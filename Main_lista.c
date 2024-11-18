#include <stdio.h>

#include "lista.h"

void menu() {
    printf ("Algoritmo de Grafos\n\n\n");
    printf ("1. Criar novo Grafo\n");
    printf ("2. Inserir Arestas\n");
    printf ("3. Eliminar Grafo\n");
    printf ("4. Busca em Profundidade\n");
    printf ("5. Busca em Largura\n");
    printf ("6. Dijikstra\n");
    printf ("7. Arvore Geradora Minima\n");
    printf ("0. Sair\n");
}

int main() {
    int opcao, vertices, a, b;
    PonteiroGrafo grafo;

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
            printf ("");
            break;
        case 6: // busca larg
            printf ("");
            break;
        case 7: // dijik
            printf ("");
            break;
        case 8: // AGM
            printf ("");
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