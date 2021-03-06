#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <form.h>
#include <ncurses.h>
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

//Estrutura com uma string com o nome do objeto(objeto), um inteiro (id), e o criador da transação(criador).
typedef struct transacoes{
  char objeto[50];
  char categoria[30];
  char valor[10];  
  int idT;

  struct transacoes *proxT, *antT;
  struct usuarios *criador;
}transacoes;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct amigos{
  char nomeAmigo[50];
  int idAmigo;

  struct amigos *proxAmigo, *antAmigo;
}amigos;

//Estrutura do tipo usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct usuarios{
  int id;
  char nome[50];
  char cidade[50];
  char endereco[50];
  char cep[20];
  char cpf[20];
  char email[50];
  char senha[20];
  char descricao[200];
  int avaliacao;
  int numeroAmigos;             //Inteiro que representa o numero de amigos de um usuario.

  struct amigos *Amigos[26];
  struct usuarios *prox, *ant;
}usuarios;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct Grafo{
  int N_usuarios;
  int N_transacoes;

  struct usuarios *listaAdj[26];
  struct transacoes *listaT;
}Grafo;

Grafo *cria_Grafo();

transacoes *cria_transacao(Grafo **G, usuarios *user);

transacoes *cria_transacaoAuto(Grafo **G, usuarios *user, char *nomeT, char *categoriaT, char *value);

transacoes *procura_categoria(Grafo **G, char *categoriaT);

transacoes *procura_nomeT(Grafo **G, char *categoriaT, char *nomeT);

transacoes *procura_transacaoDeAmigos(Grafo **G, usuarios *User, char *categoriaT);

usuarios *conclui_transacao(Grafo **G, transacoes **Transacao, int aval);

void exclui_transacao(Grafo **G, transacoes **Transacao);

amigos *circulo_amigosLista(Grafo **G, usuarios **User);

amigos *verifica_amizades(usuarios **User);

usuarios *testaUsuario(usuarios *User);

usuarios *procura_nome(Grafo *G, char *nom);

usuarios *editar_pessoa(Grafo **G);

int cria_pessoa(Grafo *G, usuarios *user);

void salva_Arquivo(Grafo *G);

bool eh_amigo(usuarios *User, usuarios *User2);

int verifica_letra(char nome);

void destroi_Grafo(Grafo **G);

void exclui_usuario(Grafo **G, usuarios **User);

int excluir_amigo(Grafo **G, usuarios **User, usuarios **User1, int cons);

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G);

//Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G);

//Funcao imprime amigos --- Recebe como Parametro um usuario(User) e imprime na tela todas as Amizades de um usuario.
void imprime_amigos(usuarios *User);

//Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_amigos(Grafo **G, usuarios **User, usuarios **User1, int cons);

int cria_pessoa_interface(Grafo *G,char*);

int primaria_interface();

int test_string(char*);

int confirm_user(usuarios);

int login_user_interface(Grafo *, char*);

int check_user(Grafo*, char*,char*);

int logged_user_interface(Grafo *, char*);

int edit_user_interface(Grafo*, usuarios*,char*);

int adiciona_amigos_interface(Grafo *,usuarios*);

int ver_amigos_interface(Grafo*,usuarios*);

int options_friend_interface(Grafo*, usuarios*,usuarios*);

int ver_transa_interface(Grafo*,usuarios*,char*);

int add_trans_interface(Grafo*,usuarios*);

int show_trans_interface(Grafo*,usuarios*,char*,char*);

int procura_transacao_interface(Grafo*,usuarios*);

int procura_interface(Grafo*,usuarios*);

int procura_categoria_interface(Grafo*,usuarios*,char*);

int procura_nomeT_interface(Grafo*,usuarios*,char*,char*);