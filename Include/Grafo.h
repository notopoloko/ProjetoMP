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
  char categoria[100];
  float valor;  
  int idT;

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


//Funcao cria_Grafo
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo();

//Funcao cria_transacao --- Recebe como Parametro um grafo(G) e um usuario(User); e retorna uma transacao.
transacoes *cria_transacao(Grafo **G, usuarios *user);

//Funcao cria_transacaoAuto --- Recebe como Parametro um grafo(G), um usuario(User), uma string(nomeT), uma string(categoriaT) e um float(val)
//E retorna uma transacao.
transacoes *cria_transacaoAuto(Grafo **G, usuarios *user, char *nomeT, char *categoriaT, float val);

//Funcao procura_categoria --- Recebe como Parametro um grafo(G) e uma string(categoria).
//E retorna uma lista de transacoes.
transacoes *procura_categoria(Grafo **G, char *categoriaT);

//Funcao procura_nomeT --- Recebe como Parametro um grafo(G), uma string(categoria) e uma string (nomeT).
//E retorna uma lista de transacoes.
transacoes *procura_nomeT(Grafo **G, char *categoriaT, char *nomeT);

//Funcao procura_transacaoDeAmigos --- Recebe como Parametro grafo(G), um usuario(User) e uma string (categoriaT).
//Retorna uma transacao.
transacoes *procura_transacaoDeAmigos(Grafo **G, usuarios *User, char *categoriaT);

//Funcao conclui_transacao --- Recebe como Parametro grafo(G), transacoes(Transacao) e um inteiro(ava1).
//Retorna um usuario.
usuarios *conclui_transacao(Grafo **G, transacoes **Transacao, int aval);

//Funcao exclui_transacao --- Recebe como Parametro grafo(G) e transacoes(Transacao).
void exclui_transacao(Grafo **G, transacoes **Transacao);

//Funcao circulo_amigos --- Recebe como Parametro um usuario(User); e retorna uma lista de amigos de amigos.
amigos *circulo_amigosLista(Grafo **G, usuarios **User);

//Funcao verifica_amizades --- Recebe como Parametro um usuario(User) e retorna uma lista de amigos de User.
amigos *verifica_amizades(usuarios **User);

//Funcao testaUsuario --- Recebe como Parametro um usuario(User); e retorna um usuario.
usuarios *testaUsuario(usuarios *User);

//Funcao procura_usuario --- Recebe como Parametro grafo(G); e retorna um usuario.
usuarios *procura_usuario(Grafo *G);

//Funcao procura_nome --- Recebe como Parametro grafo(G) e uma string(nom); e retorna um usuario.
usuarios *procura_nome(Grafo *G, char *nom);

//Funcao editar_pessoa --- Recebe como Parametro grafo(G); e retorna um usuario.
usuarios *editar_pessoa(Grafo **G);

//Funcao cria_pessoa --- Recebe como Parametro grafo(G); e retorna um usuario.
usuarios *cria_pessoa(Grafo **G);

//Funcao cria_pessoaAuto --- Recebe como Parametro grafo(G), uma string(nome), uma string(cpf),uma string(cep) e uma string(cidade).
//Retorna um usuario.
usuarios *cria_pessoaAuto(Grafo **G, char *nom, char *cpf, char *cep, char *cidade);

//Funcao edita_cidade --- Recebe como Parametro grafo(G), um usuario(User) e uma string(cidade); e retorna um usuario.
usuarios *edita_cidade(Grafo **G, usuarios **user, char *cidade);

//Funcao edita_cep --- Recebe como Parametro grafo(G), um usuario(User) e uma string(cep); e retorna um usuario.
usuarios *edita_cep(Grafo **G, usuarios **user, char *cep);

//Funcao edita_cep --- Recebe como Parametro grafo(G), um usuario(User) e uma string(cpf); e retorna um usuario.
usuarios *edita_cpf(Grafo **G, usuarios **user, char *cpf);

//Funcao edita_cep --- Recebe como Parametro grafo(G), um usuario(User) e uma string(nom); e retorna um usuario.
usuarios *edita_nome(Grafo **G, usuarios **user, char *nom);

//Funcao salva_Arquivo --- Recebe como Parametros um Grafo(G) e armazena os dados do grafo em um arquivo.
FILE *salva_Arquivo(Grafo **G);

//Funcao menu --- Recebe como Parametros um Grafo(G).
void menu(Grafo **G);

//Funcao eh_amigo --- Recebe como Parametros um usuario(User) e um usuario(User2); e retorna um booleano.
bool eh_amigo(usuarios *User, usuarios *User2);

//Funcao tamanho_Arquivo --- Recebe como Parametros uma string(nomeArquivo);e retorna um inteiro.
int tamanho_Arquivo(char *nomeArquivo);

//Funcao verifica_letra --- Recebe como Parametros uma string(nome);e retorna um inteiro.
int verifica_letra(char nome);

//Funcao destroi_Grafo --- Recebe como Parametros um Grafo(G).
void destroi_Grafo(Grafo **G);

//Funcao exclui_usuario --- Recebe como Parametros um Grafo(G) e um usuario(User).
void exclui_usuario(Grafo **G, usuarios **User);

//Funcao e excluir_amigo --- Recebe como Parametros um Grafo(G), um usuarios(User), um usuario(User1) e um inteiro(cons).
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