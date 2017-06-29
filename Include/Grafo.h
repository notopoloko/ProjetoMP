#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef TIPO_GRAFO
#define TIPO_GRAFO
#define SUCCESS 1

//Estrutura com uma string com o nome do objeto(objeto), um inteiro (id), e o criador da transação(criador).
typedef struct transacoes{
  char objeto[100];
  int idT;
  int avaliacao;  

  struct transacoes *proxT, *antT;
  struct usuarios *criador;
}transacoes;

//Estrutura com o nome de um amigo, um id  de um amigo e ponteiros para o proximo amigo.
typedef struct amigos{
  char nomeAmigo[100];
  int idAmigo;

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


//Funcao cria_Grafo
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo();

//Funcao cria_transacao --- Recebe como Parametro grafo(G) e um usuario(User); e retorna uma transacao.
transacoes *cria_transacao(Grafo **G, usuarios *user);

//Funcao circulo_amigos --- Recebe como Parametro um usuario(User); e retorna uma lista de amigos de amigos.
amigos *circulo_amigosLista(Grafo **G, usuarios **User);

//Funcao verifica_amizades --- Recebe como Parametro um usuario(User) e retorna uma lista de amigos de User.
amigos *verifica_amizades(usuarios **User);

usuarios *testaUsuario(usuarios *User);

usuarios *procura_usuario(Grafo *G);

usuarios *procura_nome(Grafo *G, char *nom);

usuarios *editar_pessoa(Grafo **G);

usuarios *cria_pessoa(Grafo **G);

usuarios *cria_pessoaAuto(Grafo **G, char *nom, char *cpf, char *cep, char *cidade);

usuarios *edita_cidade(Grafo **G, usuarios **user, char *cidade);

usuarios *edita_cep(Grafo **G, usuarios **user, char *cep);

usuarios *edita_cpf(Grafo **G, usuarios **user, char *cpf);

usuarios *edita_nome(Grafo **G, usuarios **user, char *nom);

//Funcao salva_Arquivo --- Recebe como Parametros um Grafo(G) e armazena os dados do grafo em um arquivo.
FILE *salva_Arquivo(Grafo **G);

void menu(Grafo **G);

bool eh_amigo(usuarios *User, usuarios *User2);

int tamanho_Arquivo(char *nomeArquivo);

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

//Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G), dois usuarios(User e User1) e um inteiro.
void adiciona_amigos(Grafo **G, usuarios **User, usuarios **User1, int cons);

#endif