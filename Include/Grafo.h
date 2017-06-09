#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grafo.h>
#include <curses.h>

#ifndef TIPO_GRAFO
#define TIPO_GRAFO
#define SUCCESS 1

typedef struct user{
    char Nome;
    struct list *friends;
}user;

typedef struct list{
    struct list *brotherhood;
}list;


typedef struct listAmigos{
    struct Usuarios *proximo, *anterior;
}listAmigos;

//Estrutura do tipo Usuarios com um inteiro representando o nome da amizade, e dois inteiros que representam o usuario de origem e o usuario de destino.
//Apresenta tambem um ponteiro(Tipo Amizades) que aponta para proxima amizade.
typedef struct Amizades{ 
  char nome;
  struct Usuarios *nextFriend, *prevFriend;
}Amizades;

//Estrutura do tipo Usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo Usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct Usuarios{
  char nome[100];   
  char cidade[30];
  char cep[20];      
  char cpf[20];
  int numeroAmigos;             //Inteiro que representa o numero de amigos de um usuario.

  struct Amizades *Amigos;
  struct Usuarios *prox, *ant;
}Usuarios;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de Usuarios do grafo e um ponteiro para outra estrutura do tipo Usuarios.
typedef struct Grafo{
  int N_Usuarios;       //Inteiro que representa o numero de Usuarios do grafo.


  struct Usuarios *listaAdj[23];
  //struct Usuarios *Inicio;   //Ponteiro para uma lista de Usuarios que aponta para o inicio da lista.
  //struct Usuarios *Fim;     //Ponteiro para uma lista de Usuarios que aponta para o fim da lista.
}Grafo;

//Funcao cria_Grafo
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo();

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G);

//Funcao destroi_Grafo --- Recebe como Parametro uma lista de Usuarios(Listausuario) e
//libera cada espaço de memoria alocado dinamicamente destinado a uma estrutura do tipo amizade.
void destroi_Listadeamizade(Grafo **Listausuario);

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e
//libera cada espaço de memoria alocado dinamicamente destinado a uma estrutura do tipo usuario.
void destroi_Listadeusuario(Grafo **G);

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e libera cada espaço de memoria alocado dinamicamente.
void destroi_Grafo(Grafo **G);

//Funcao Pardeusuario_Existe --- Recebe como Parametros duas listas de adjacencia(ListaV1 e ListaV2).
//Retorna true se existir amizade entre as duas e falso caso nao exista.
bool ParDeusuario_Existe(Usuarios *ListaV1, Usuarios *ListaV2);

 //Funcao retorna_NomeGrafo --- Recebe como Parametro um Grafo(G) e imprime na tela um vetor de caracteres que representa o nome do grafo.
char* retorna_NomeGrafo(Grafo *G);

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os Usuarios e Amizades.
void imprime_Grafo(Grafo *G);

//Funcao procura_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Retorna uma lista de Usuarios que possui o usuario(V) ou NULL caso não encontre o usuario(V).
Usuarios *procura_usuario(Grafo *G, int usuario);

 //Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, Usuarios **User);

 //Funcao remove_usuario --- Recebe como Parametros um Grafo(G) e um usuario(usuario).
void remove_usuario(Grafo **G, Usuarios **User);

 //Funcao atualiza_usuario --- Recebe como Parametros um Grafo(G), um usuario(usuario) e um usuario Atualizado(usuarioAtualizado).
void atualiza_usuario(Grafo **G, int usuario, int usuarioAtualizado);

//Funcao retorna_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Que retorna o Valor de usuario(Se o usuario for encontrado) ou retorna 0, caso não encontre o usuario.
int retorna_usuario(Grafo *G, int usuario);

//Funcao procura_amizade --- Recebe como Parametros um ponteiro para Grafo(G) e dois Usuarios(V1 e V2).
//Retorna uma lista de Amizades que possui os Usuarios(V1 e V2) ou NULL caso não encontre o usuario(V).
Amizades *procura_amizade(Grafo *G, int V1, int V2);

//Funcao adiciona_amizade --- Recebe como Parametros um Grafo(G), um usuario de Origem(VOrig) e um usuario de Destino(VDest).
void adiciona_amizade(Grafo **G, int VOrig, int VDest);

//Funcao retorna_amizade --- Recebe como Parametros um Grafo(G) e dois Usuarios(V1 e V2).
//Que retorna o Valor da amizade(Se o usuario for encontrado) ou retorna 0, caso não encontre o usuario.
int retorna_amizade(Grafo *G, int V1, int V2);

//Funcao verifica_Vizinhos(Dado um usuario V1 - procura todas os Usuarios vizinhos de (V1) --- Recebe como Parametros um Grafo(G) e um usuario(V1).
Usuarios *verifica_Vizinhos(Grafo *G, int V1);

//Funcao verifica_Adjacencia(Se existe uma amizade entre dois Usuarios) --- Recebe como Parametros um Grafo(G), dois Usuarios(V2 e V1).
void verifica_Adjacencia(Grafo *G, int V1, int V2);

//Funcao remove_amizade --- Recebe como Parametros um Grafo(G), dois Usuarios(VOrig e VDest).
void remove_amizade(Grafo **G, int VOrig, int VDest);

//Funcao atualiza_amizade --- Recebe como Parametros um Grafo(G), dois Usuarios(V1 e V2) e um usuario Atualizado(usuarioAtualizado).
void atualiza_amizade(Grafo **G, int V1, int V2, int amizadeAtualizada);



#endif