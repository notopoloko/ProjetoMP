#ifndef TIPO_GRAFO
#define TIPO_GRAFO

//Estrutura do tipo Vertices com um inteiro representando o nome da aresta, e dois inteiros que representam o vertice de origem e o vertice de destino.
//Apresenta tambem um ponteiro(Tipo Arestas) que aponta para proxima aresta.
typedef struct Arestas{ 
  int nomeAresta;                //Um inteiro que representa o nome da aresta.
  struct Vertices *VerticeDest;                 //ponteiro que aponta para o vertice destino.
  struct Vertices * VerticeOrig;                  //ponteiro que aponta para o vertice origem.

  struct Arestas *proxAresta;       //Ponteiro para uma lista de arestas que aponta para proxima aresta.
  struct Arestas *antAresta;       //Ponteiro para uma lista de arestas que aponta para aresta anterior.
                                 // Apesar de existir um ponteiro para a aresta anterior, o Grafo é direcionado. Esse ponteiro só é usado
                                // para melhorar o desempenho do programa.
}Arestas;

//Estrutura do tipo Vertices com dois inteiros representando o nome do vertice e o numero de arestas para cada vertice.
//Apresenta tambem um ponteiro(Tipo Vertices) que aponta para proxima Vertice e um ponteira para uma estrutura do tipo Arestas.
typedef struct Vertices{
  int nomeVertice;               //Inteiro que representa o nome do vertice.
  int N_ArestasdoVertice;        //Inteiro que representa o numero de arestas da vertice.

  struct Arestas *pontArestaInicio;     //Ponteiro para uma lista de arestas que aponta para o inicio da lista.
  struct Arestas *pontArestaFim;     //Ponteiro para uma lista de arestas que aponta para o fim da lista.
  struct Vertices *proxVertice;   //Ponteiro para uma lista de vertices que aponta para o proximo vertice.
  struct Vertices *antVertice;   //Ponteiro para uma lista de vertices que aponta para o vertice anterior.
                                 // Apesar de existir um ponteiro para o vertice anterior, o Grafo é direcionado. Esse ponteiro só é usado
                                // para melhorar o desempenho do código.
}Vertices;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de vertices do grafo e um ponteiro para outra estrutura do tipo Vertices.
typedef struct Grafo{
  char *nomeGrafo;      //Vetor de caracteres que representa o nome do grafo.
  int N_Vertices;       //Inteiro que representa o numero de vertices do grafo.
  int N_Arestas;         //Inteiro que representa o numero de arestas do grafo.

  struct Vertices *pontVerticeInicio;   //Ponteiro para uma lista de vertices que aponta para o inicio da lista.
  struct Vertices *pontVerticeFim;     //Ponteiro para uma lista de vertices que aponta para o fim da lista.
}Grafo;

//Funcao cria_Grafo --- Recebe como Parametro um vetor de caracteres(NomedoGrafo)
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo(char *NomedoGrafo);

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G);

//Funcao destroi_Grafo --- Recebe como Parametro uma lista de vertices(ListaVertice) e
//libera cada espaço de memoria alocado dinamicamente destinado a uma estrutura do tipo aresta.
void destroi_ListadeAresta(Grafo **ListaVertice);

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e
//libera cada espaço de memoria alocado dinamicamente destinado a uma estrutura do tipo vertice.
void destroi_ListadeVertice(Grafo **G);

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e libera cada espaço de memoria alocado dinamicamente.
void destroi_Grafo(Grafo **G);

//Funcao PardeVertice_Existe --- Recebe como Parametros duas listas de adjacencia(ListaV1 e ListaV2).
//Retorna true se existir aresta entre as duas e falso caso nao exista.
bool ParDeVertice_Existe(Vertices *ListaV1, Vertices *ListaV2);

 //Funcao retorna_NomeGrafo --- Recebe como Parametro um Grafo(G) e imprime na tela um vetor de caracteres que representa o nome do grafo.
char* retorna_NomeGrafo(Grafo *G);

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os vertices e arestas.
void imprime_Grafo(Grafo *G);

//Funcao procura_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
//Retorna uma lista de Vertices que possui o vertice(V) ou NULL caso não encontre o vertice(V).
Vertices *procura_Vertice(Grafo *G, int Vertice);

 //Funcao adiciona_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
void adiciona_Vertice(Grafo **G, int V);

 //Funcao remove_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(Vertice).
void remove_Vertice(Grafo **G, int Vertice);

 //Funcao atualiza_Vertice --- Recebe como Parametros um Grafo(G), um Vertice(Vertice) e um Vertice Atualizado(VerticeAtualizado).
void atualiza_Vertice(Grafo **G, int Vertice, int VerticeAtualizado);

//Funcao retorna_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
//Que retorna o Valor de Vertice(Se o vertice for encontrado) ou retorna 0, caso não encontre o vertice.
int retorna_Vertice(Grafo *G, int Vertice);

//Funcao procura_Aresta --- Recebe como Parametros um ponteiro para Grafo(G) e dois Vertices(V1 e V2).
//Retorna uma lista de Arestas que possui os vertices(V1 e V2) ou NULL caso não encontre o vertice(V).
Arestas *procura_Aresta(Grafo *G, int V1, int V2);

//Funcao adiciona_Aresta --- Recebe como Parametros um Grafo(G), um Vertice de Origem(VOrig) e um Vertice de Destino(VDest).
void adiciona_Aresta(Grafo **G, int VOrig, int VDest);

//Funcao retorna_Aresta --- Recebe como Parametros um Grafo(G) e dois Vertices(V1 e V2).
//Que retorna o Valor da Aresta(Se o vertice for encontrado) ou retorna 0, caso não encontre o vertice.
int retorna_Aresta(Grafo *G, int V1, int V2);

//Funcao verifica_Vizinhos(Dado um vertice V1 - procura todas os Vertices vizinhos de (V1) --- Recebe como Parametros um Grafo(G) e um Vertice(V1).
Vertices *verifica_Vizinhos(Grafo *G, int V1);

//Funcao verifica_Adjacencia(Se existe uma aresta entre dois vertices) --- Recebe como Parametros um Grafo(G), dois Vertices(V2 e V1).
void verifica_Adjacencia(Grafo *G, int V1, int V2);

//Funcao remove_Aresta --- Recebe como Parametros um Grafo(G), dois Vertices(VOrig e VDest).
void remove_Aresta(Grafo **G, int VOrig, int VDest);

//Funcao atualiza_Aresta --- Recebe como Parametros um Grafo(G), dois Vertices(V1 e V2) e um Vertice Atualizado(VerticeAtualizado).
void atualiza_Aresta(Grafo **G, int V1, int V2, int ArestaAtualizada);

#endif