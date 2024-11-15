#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int vertice;
    struct no *proximo;
} NO;

typedef NO *PonteiroNO;

typedef struct {
    PonteiroNO *lista;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;


PonteiroGrafo criarGrafo(int numVertices) {
    int indice;
    PonteiroGrafo grafo = malloc(sizeof(Grafo));

    grafo->numVertices = numVertices;
    grafo->lista = malloc(numVertices *sizeof(PonteiroNO));

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
    PonteiroNO novoNo = malloc(sizeof(NO));
    
    novoNo->vertice = vertice;
    novoNo->proximo = lista;

    return novoNo;
}

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    grafo->lista[vertice2] = inserirLista(grafo->lista[vertice2], vertice1);
    grafo->lista[vertice1] = inserirLista(grafo->lista[vertice1], vertice2);
}

PonteiroNO removerLista(PonteiroNO lista, int vertice) {
    PonteiroNO proximo;
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

void removerAresta(PonteiroGrafo grafo, int vertices1, int vertices2) {
    grafo->lista[vertices1] = removerLista(grafo->lista[vertices1], vertices2);
    grafo->lista[vertices2] = removerLista(grafo->lista[vertices2], vertices1);
}

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2) {
    PonteiroNO auxiliar;
    for (auxiliar = grafo->lista[vertice1]; auxiliar != NULL; auxiliar = auxiliar->proximo)
        if (auxiliar->vertice == vertice2)
            return 1;
    
    return 0;
}

void imprimirArestas(PonteiroGrafo grafo) {
    int vertice1;
    PonteiroNO auxiliar;

    for (vertice1 = 0; vertice1 < grafo->numVertices; vertice1++)
        for (auxiliar = grafo->lista[vertice1]; auxiliar != NULL; auxiliar = auxiliar->proximo)
            printf("{%d,%d}\n", vertice1, auxiliar->vertice);
}

int main() {
    int opcao, vertice1, vertice2;
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
                    scanf("%d", &vertice1);
                    printf("Digite o segundo vértice: ");
                    scanf("%d", &vertice2);
                    adicionarAresta(grafo, vertice1, vertice2);
                }
                break;
            case 3:
                if (grafo == NULL) {
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
                if (grafo == NULL) {
                    printf("O grafo não foi criado.\n");
                } else {
                    printf("Digite o primeiro vértice: ");
                    scanf("%d", &vertice1);
                    printf("Digite o segundo vértice: ");
                    scanf("%d", &vertice2);
                    if (existeAresta(grafo, vertice1, vertice2)) {
                        printf("Existe uma aresta entre %d e %d.\n", vertice1, vertice2);
                    } else {
                        printf("Não existe uma aresta entre %d e %d.\n", vertice1, vertice2);
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
