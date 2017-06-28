#include <ncurses.h>
#include <menu.h>
#include <form.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <form.h>

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct listaAmigos{
  char nomeAmigo[100];

  struct amigos *proxAmigo, *antAmigo;
}listaAmigos;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct amigos{
  char nomeAmigo[100];

  struct amigos *proxAmigo, *antAmigo;
}amigos;

//Estrutura do tipo usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct usuarios{
  int id;
  char nome[100];
  char cidade[30];
  char cep[20];
  char cpf[12];
  char email[21];
  char endereco[21];
  char senha[21];
  int numeroAmigos;             //Inteiro que representa o numero de amigos de um usuario.

  struct amigos *Amigos[26];
  struct usuarios *prox, *ant;
}usuarios;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct Grafo{
  int N_usuarios;
  struct usuarios *listaAdj[26];
}Grafo;

//Funcao cria_Grafo
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo();

usuarios *testaUsuario(usuarios *User);

amigos *verifica_amizades(usuarios **User);

usuarios *procura_usuario(Grafo *G);

usuarios *procura_nome(Grafo *G, char *nom);

usuarios *editar_pessoa(Grafo **G);

usuarios *cria_pessoa(Grafo **G);

void menu(Grafo **G);

void salva_Arquivo(Grafo **G);

int verifica_letra(char nome);

void destroi_Grafo(Grafo **G);

void exclui_usuario(Grafo **G, usuarios **User);

void excluir_amigo(Grafo **G, usuarios **User, usuarios **User1, int cons);

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G);

//Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G);

//Funcao imprime amigos --- Recebe como Parametro um usuario(User) e imprime na tela todas as Amizades de um usuario.
void imprime_amigos(usuarios *User);

//Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, usuarios **User);

int cria_pessoa_interface(Grafo *G);