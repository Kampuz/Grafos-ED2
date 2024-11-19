#ifndef MATRIZ_
#define MATRIZ_

typedef struct {
    int **matriz;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo inicializarGrafo(int numVertices);

void liberarGrafo(PonteiroGrafo grafo);

void inserirAresta(PonteiroGrafo grafo, int origem, int destino, int peso);

void removerAresta(PonteiroGrafo grafo, int origem, int destino);

int existeAresta(PonteiroGrafo grafo, int origem, int destino);

void imprimirArestas(PonteiroGrafo Grafo);

int grau(PonteiroGrafo grafo, int vertice);

//BUSCA EM LARGURA
int *buscaEmLargura(PonteiroGrafo grafo, int inicio);

//BUSCA EM PROFUNDIDADE
typedef struct pilha
{
    int *dados;
    int topo;
    int capacidade;
} Pilha;

typedef Pilha *PonteiroPilha;


int *buscaEmProfundidade(PonteiroGrafo grafo, int inicio);
void imprimirCaminho(int vertice, int *pais);
void imprimirCaminhoReverso(int vertice, int *pais);

PonteiroPilha criarPilha(int capacidade);
int pilhaVazia(PonteiroPilha pilha);
void empilhar(PonteiroPilha pilha, int valor);
int desempilhar(PonteiroPilha pilha);
void destruirPilha(PonteiroPilha pilha);

// ÁRVORE GERADORA MÍNIMA
PonteiroGrafo criarGrafo(int numVertices);
void gerarArvoreMinima(PonteiroGrafo grafo);

// DIJKSTRA

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

PonteiroFP criarFilaPrioridade(int capacidadeMaxima);
#endif