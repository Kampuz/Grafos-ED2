#include <stdio.h>
#include <stdlib.h>

#include "../CodeBase/lista.h"

void buscaEmProfundidade(PonteiroGrafo grafo, int inicio) {
    int i, *visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (i = 0; i < grafo->numVertices; i++)
        visitado[i] = 0;
    
    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras)
    {
        int verticeAtual = fila[frente++];
        printf("Visitando %d\n", verticeAtual);

        ponteiroNO no = grafo->lista[verticeAtual];

        while (no != NULL) {
            int vizinho = no->vertice;
            if (!visitado[vizinho])
            {
                fila[tras++] = vizinho;
                visitado[vizinho] = 1;
            }
            
            no = no->proximo;
        }
    }
    free(fila);
    free(visitado);
}