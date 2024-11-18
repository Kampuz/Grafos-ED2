#include <stdio.h>
#include <limits.h>

#include "../CodeBase/matriz.h"

void adicionarArestaComPeso(PonteiroGrafo grafo, int vertice1, int vertice2, int peso) {
    grafo->matriz[vertice1][vertice2] = peso;
    grafo->matriz[vertice1][vertice2] = peso;
}

void dijkstra(PonteiroGrafo grafo, int origem) {
    int numVertices = grafo->numVertices;
    int distancias[numVertices];
    int visitados[numVertices];
    int caminho[numVertices];
    int i, j;

    for (i = 0; i < numVertices; i++)
    {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
        caminho[i] = -1;
    }

    distancias[origem] = 0;

    for (i = 0; i < (numVertices - 1); i++)
    {
        int distanciaMinima = INT_MAX;
        int u = -1;

        for (j = 0; j < numVertices; j++)
            if (!visitados[j] && distancias[j] < distanciaMinima)
            {
                distanciaMinima = distancias[j];
                u = j;
            }

        visitados[u] = 1;

        for (j = 0; j < numVertices; j++)
            if ((grafo->matriz[u][j] != 0) && (!visitados[j]) && (distancias[u] != INT_MAX) && ((distancias[u] + grafo->matriz[u][j]) < distancias[j]))
                distancias[j] = distancias[u] + grafo->matriz[u][j];
                caminho[j] = u;
    }

    printf("Distâncias mínimas a partir do vértice %d:\n", origem);
    for (i = 0; i < numVertices; i++)
        if (distancias[i] == INT_MAX)
            printf("Vértice %d: Inacessível\n", i);
        else
            printf("Vértice %d: %d\n", i, distancias[i]);

    printf("Caminhos mais curtos:\n");
    for (i = 0; i < numVertices; i++)
    {
        if (i != origem)
        {
            printf("Caminho de %d para %d: ", origem, i);
            int j = i;
            while (caminho[j] != -1)
            {
                printf("%d <- ", j);
                j = caminho[j];
            }
            printf("%d\n", origem);
        }
        
    }
    
    
}

/*

int main() {
    int numVertices, numArestas, i, origem, peso, vertice1, vertice2;
    PonteiroGrafo grafo;
    int *distancia, *caminho;


    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);

    grafo = inicializarGrafo(numVertices);

    printf("Digite o número de arestas: ");
    scanf("%d", &numArestas);

    for (i = 0; i < numArestas; i++)
    {
        printf("Digite o vertice 1, vertice 2 e o peso da aresta");
        scanf("%d %d %d", &vertice1, &vertice2, &peso);
        adicionarArestaComPeso(grafo, vertice1, vertice2, peso);
    }

    printf("Digite o vértice de origem para Dijkstra: ");
    scanf("%d", &origem);

    dijkstra(grafo, origem, distancia, caminho);

    liberarGrafo(grafo);
    return 0;
}
*/