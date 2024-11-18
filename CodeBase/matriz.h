#ifndef MATRIZ_
#define MATRIZ_

typedef struct {
    int **matriz;
    int numVertices;
} Grafo;

typedef Grafo *PonteiroGrafo;

PonteiroGrafo inicializarGrafo(int numVertices);

void liberarGrafo(PonteiroGrafo grafo);

void adicionarAresta(PonteiroGrafo grafo, int vertice1, int vertice2);
void adicionarArestaComPeso(PonteiroGrafo grafo, int vertice1, int vertice2, int peso);

void removerAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

int existeAresta(PonteiroGrafo grafo, int vertice1, int vertice2);

PonteiroGrafo criarGrafo();

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
typedef struct {
    int origem, destino, peso;
} Aresta;

void gerarArvoreMinima(PonteiroGrafo grafo);

// DIJKSTRA
void dijkstra(PonteiroGrafo grafo, int origem);

#endif