#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vertice;
    struct no * proximo;
} NO;

typedef struct {
    struct no **lista;
    int numVertices;
} Grafo;

typedef NO *PonteiroNO;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo criarGrafo(int numVertices) {
    int indice;
    PonteiroGrafo grafo = (PonteiroGrafo)malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->lista = (PonteiroNO*)malloc(numVertices * sizeof(PonteiroNO));

    for (indice = 0; indice < numVertices; indice++)
        grafo->lista[indice] = NULL;

    return grafo;
}

void liberarLista(PonteiroNO lista) {
    if (lista != NULL)
    {
        liberarLista(lista->proximo);
        free(lista);
    }
    return;
}

void liberarGrafo(PonteiroGrafo grafo) {
    int indice;
    for (indice = 0; indice < grafo->numVertices; indice++)
        liberarLista(grafo->lista[indice]);
    
    free(grafo->lista);
    free(grafo);
    return;
}

PonteiroNO inserirLista(PonteiroNO lista, int vertice) {
    PonteiroNO novoNo = (PonteiroNO)malloc(sizeof(NO));

    novoNo->vertice = vertice;
    novoNo->proximo = lista;

    return novoNo;
}

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    grafo->lista[vertice2] = inserirLista(grafo->lista[vertice2], vertice1);
    grafo->lista[vertice1] = inserirLista(grafo->lista[vertice1], vertice2);
}

void buscaemLargura(PonteiroGrafo grafo, int inicio) {
    int *visitado = (int*)malloc(grafo->numVertices * sizeof(int));

    for (int i = 0; i < grafo->numVertices; i++)
        visitado[i] = 0;

    int *fila = (int*)malloc(grafo->numVertices * sizeof(int));
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras)
    {
        int verticeAtual = fila[frente++];
        printf("Visitando %d\n", verticeAtual);

        PonteiroNO atual = grafo->lista[verticeAtual];
        while (atual != NULL)
        {
            if (!visitado[atual->vertice])
            {
                fila[tras++] = atual->vertice;
                visitado[atual->vertice] = 1;
            }
            atual = atual->proximo;
        }
        
    }
    
    free(fila);
    free(visitado);
}

int main() {
    int numVertices = 5;
    PonteiroGrafo grafo = criarGrafo(numVertices);

    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 0, 2);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 2, 4);

    printf("\nBusca em Largura a partir do vértice 0:\n");
    buscaemLargura(grafo, 0);

    liberarGrafo(grafo);
    return 0;
}