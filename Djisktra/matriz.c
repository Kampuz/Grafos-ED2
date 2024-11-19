#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
    int v;
    int peso;
    struct no *prox;
} No;

typedef No *PonteiroNo;

typedef struct grafo {
    int n;
    PonteiroNo *adj;
} Grafo;

typedef Grafo *PonteiroGrafo;

typedef struct {
    int prioridade;
    int vertice;
} Item;

typedef struct {
    Item *v;
    int *indice;
    int n, tamanho;
} FP;

typedef FP *PonteiroFP;

int consultarPrioridade(PonteiroFP fila, int vertice);
int filaVazia(PonteiroFP fila);
int extrairMinimo(PonteiroFP fila);
void atualizarPrioridade(PonteiroFP fila, int vertice, int novaPrioridade);
void inserirElemento(PonteiroFP fila, int vertice, int prioridade);
PonteiroFP criarFilaPrioridade(int capacidadeMaxima);


int *dijkstra(PonteiroGrafo g, int s) {
    int v, *pai = (int*)malloc(g->n * sizeof(int));

    PonteiroNo t;
    PonteiroFP h = criarFilaPrioridade(g->n);

    for (v = 0; v < g->n; v++)
    {
        pai[v] = -1;
        inserirElemento(h, v, INT_MAX);
    }

    pai[s] = s;
    atualizarPrioridade(h, s, 0);

    while (!filaVazia(h))
    {
        v = extrairMinimo(h);
        if (consultarPrioridade(h, v) != INT_MAX)
        {
            for (t = g->adj[v]; t != NULL; t = t->prox)
            {
                if (consultarPrioridade(h, v) + t->peso < consultarPrioridade(h, t->v))
                {
                    atualizarPrioridade(h, t->v, consultarPrioridade(h, v) + t->peso);
                    pai[t->v] = v;
                }
            }
        }
    }

    return pai;
}


PonteiroFP criarFilaPrioridade(int capacidadeMaxima) {
    PonteiroFP fila = (PonteiroFP)malloc(sizeof(FP));
    fila->v = (Item*)malloc(capacidadeMaxima * sizeof(Item));
    fila->indice = (int*)malloc(capacidadeMaxima * sizeof(int));
    fila->n = 0;
    fila->tamanho = capacidadeMaxima;

    for (int i = 0; i < capacidadeMaxima; i++)
    {
        fila->indice[i] = -1;
    }
    
    return fila;
}

void inserirElemento(PonteiroFP fila, int vertice, int prioridade) {
    if (fila->n >= fila->tamanho)
    {
        printf("Erro: Fila de prioridade cheia.\n");
        return;
    }

    fila->v[fila->n].vertice = vertice;
    fila->v[fila->n].prioridade = prioridade;
    fila->indice[vertice] = fila->n;
    fila->n++;

    // Refazendo o heap após a inserção
    int posicao = fila->n - 1;
    while (posicao > 0 && fila->v[posicao].prioridade < fila->v[(posicao - 1) / 2].prioridade)
    {
        Item aux = fila->v[posicao];
        fila->v[posicao] = fila->v[(posicao - 1) / 2];
        fila->v[(posicao - 1) / 2] = aux;

        fila->indice[fila->v[posicao].vertice] = posicao;
        fila->indice[fila->v[(posicao - 1) / 2].vertice] = (posicao - 1) / 2;

        posicao = (posicao - 1) / 2;
    }
}

void atualizarPrioridade(PonteiroFP fila, int vertice, int novaPrioridade) {
    int posicao = fila->indice[vertice];
    if (posicao == -1)
    {
        printf("Erro: Vértice não encontrado na fila.\n");
        return;
    }

    fila->v[posicao].prioridade = novaPrioridade;

    // Refazendo o heap após a atualização
    while (posicao > 0 && fila->v[posicao].prioridade < fila->v[(posicao - 1) / 2].prioridade)
    {
        Item aux = fila->v[posicao];
        fila->v[posicao] = fila->v[(posicao - 1) / 2];
        fila->v[(posicao - 1) / 2] = aux;

        fila->indice[fila->v[posicao].vertice] = posicao;
        fila->indice[fila->v[(posicao - 1) / 2].vertice] = (posicao - 1) / 2;

        posicao = (posicao - 1) / 2;
    }
}

int extrairMinimo(PonteiroFP fila) {
    if (fila->n == 0)
    {
        printf("Erro: Fila de prioridade vazia.\n");
        return -1;
    }

    int verticeMinimo = fila->v[0].vertice;

    // Coloca o último elemento no topo e refaz o heap
    fila->n--;
    fila->v[0] = fila->v[fila->n];
    fila->indice[fila->v[0].vertice] = 0;
    fila->indice[verticeMinimo] = -1;

    int posicao = 0;
    while (posicao * 2 + 1 < fila->n)
    {
        int filhoEsquerdo = posicao * 2 + 1;
        int filhoDireito = posicao * 2 + 2;
        int menor = filhoEsquerdo;
    
        if (filhoDireito < fila->n && fila->v[filhoDireito].prioridade < fila->v[filhoEsquerdo].prioridade)
        {
            menor = filhoDireito;
        }

        if (fila->v[posicao].prioridade <= fila->v[menor].prioridade)
        {
            break;
        }
        
        // Troca entre o elemento atual e o filho de menor prioridade
        Item aux = fila->v[posicao];
        fila->v[posicao] = fila->v[menor];
        fila->v[menor] = aux;

        fila->indice[fila->v[posicao].vertice] = posicao;
        fila->indice[fila->v[menor].vertice] = menor;

        posicao = menor;
    }

    return verticeMinimo;
}

int filaVazia(PonteiroFP fila) {
    return fila->n == 0;
}

int consultarPrioridade(PonteiroFP fila, int vertice) {
    int posicao = fila->indice[vertice];
    if (posicao == -1)
    {
        return INT_MAX;
    }
    
    return fila->v[posicao].prioridade;
}

void adicionarAresta(PonteiroGrafo grafo, int origem, int destino, int peso) {
    PonteiroNo novaAdj = (PonteiroNo)malloc(sizeof(No));
    novaAdj->v = destino;
    novaAdj->peso = peso;
    novaAdj->prox = grafo->adj[origem];
    grafo->adj[origem] = novaAdj;
}

/*

int main() {
    int numeroVertices = 5;
    PonteiroGrafo grafo = (PonteiroGrafo)malloc(sizeof(Grafo));
    grafo->n = numeroVertices;
    grafo->adj = (PonteiroNo*)malloc(numeroVertices * sizeof(PonteiroNo));
    if (grafo->adj == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para listasAdj\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numeroVertices; i++)
    {
        grafo->adj[i] = NULL;
    }

    adicionarAresta(grafo, 0, 1, 10);
    adicionarAresta(grafo, 0, 4, 5);
    adicionarAresta(grafo, 1, 2, 1);
    adicionarAresta(grafo, 1, 4, 2);
    adicionarAresta(grafo, 2, 3, 4);
    adicionarAresta(grafo, 3, 0, 7);
    adicionarAresta(grafo, 3, 2, 6);
    adicionarAresta(grafo, 4, 1, 3);
    adicionarAresta(grafo, 4, 2, 9);
    adicionarAresta(grafo, 4, 3, 2);

    int verticeInicial = 0;
    int *caminhos = dijkstra(grafo, verticeInicial);

    printf("Menor caminho a partir do vértice %d:\n", verticeInicial);
    for (int i = 0; i < numeroVertices; i++)
    {
        if (caminhos[i] == -1)
        {
            printf("Vértice %d: Sem caminho.\n", i);
        } else {
            printf("Vértice %d: Pai %d.\n", i, caminhos[i]);
        }
    }

    for (int i = 0; i < numeroVertices; i++)
    {
        PonteiroNo atual = grafo->adj[i];

        while (atual != NULL)
        {
            PonteiroNo auxiliar = atual;
            atual = atual->prox;
            free(auxiliar);
        }
    }

    free(grafo->adj);
    free(grafo);
    free(caminhos);
    return 0;
}

*/