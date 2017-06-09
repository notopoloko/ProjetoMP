#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estrutura do tipo usuarios com um inteiro representando o nome da amizade, e dois inteiros que representam o usuario de origem e o usuario de destino.
//Apresenta tambem um ponteiro(Tipo Amizades) que aponta para proxima amizade.
typedef struct amizades{ 
  char nomeAmizade[100];
  struct usuarios *nextFriend, *prevFriend;
}amizades;

//Estrutura do tipo usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct usuarios{
  char *nome;   
  char *cidade;
  char *cep;      
  char *cpf;
  int numeroAmigos;             //Inteiro que representa o numero de amigos de um usuario.

  struct Amizades *Amigos;
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

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G);

/*/
 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G);

//Funcao procura_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Retorna uma lista de usuarios que possui o usuario(V) ou NULL caso não encontre o usuario(V).
usuarios *procura_usuario(Grafo *G, int usuario);
*/

 //Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, usuarios **User);

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
Grafo *cria_Grafo(){
  struct Grafo *G;
  int i = 0;

  G = (Grafo *)malloc(sizeof(*G));
  G->N_usuarios = 0;
  while(i < 26){
    G->listaAdj[i] = NULL;
    i++;
  }
  return G;
}

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G){
  if(G->N_usuarios != 0){
    return true;
  }
  else{
    printf("ERRO: Nao existem usuarios na rede\n");
    return false;
  }
}
/*
void destroi_Listadeamizade(usuarios **Lusuario){
  struct Amizades *amizadeAtual;
  int cont;

  cont = (*Lusuario)->N_Amizadesdousuario;
  while(cont--){
    amizadeAtual = (*Lusuario)->pontamizadeFim;
    if(amizadeAtual->antamizade != NULL){
      (*Lusuario)->pontamizadeFim = amizadeAtual->antamizade;
      free(amizadeAtual);
      amizadeAtual->proxamizade = NULL;
      amizadeAtual->antamizade = NULL;
      amizadeAtual = NULL;
    }
    else{
      (*Lusuario)->pontamizadeFim = NULL;
      (*Lusuario)->pontamizadeInicio = NULL;
    }
  }
}

void destroi_Listadeusuario(Grafo **G){
  struct usuarios *usuarioAnt, *usuarioAtual;
  int cont;

  cont = (*G)->N_usuarios;
  while(cont--){
    usuarioAtual = (*G)->pontusuarioFim;
    destroi_Listadeamizade(&usuarioAtual);
    if(usuarioAtual->antusuario != NULL){
      (*G)->pontusuarioFim = usuarioAtual->antusuario;
      free(usuarioAtual);
      usuarioAtual->proxusuario = NULL;
      usuarioAtual->antusuario = NULL;
      usuarioAtual = NULL;
    }
    else{
      (*G)->pontusuarioInicio = NULL;
      (*G)->pontusuarioFim = NULL;
    }
  }
}

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e libera cada espaço de memoria alocado dinamicamente.
void destroi_Grafo(Grafo **G){
  if(existe_Grafo(*G)){
    destroi_Listadeusuario(G);
    free((*G));
    (*G) = NULL;
  }
}
*/
 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G){
  int i = 0;

  printf("Numero de usuarios = %d\n", G->N_usuarios);
  while(i < 26){
    if((G->listaAdj[i]) != NULL){
      printf("[%c] -> %s\n", ('A'+i), (G->listaAdj[i]->nome));
    }
    else{
      printf("[%c] -> Esta vazio\n", ('A'+i));
    }
    i++;
  }
}
/*
//Funcao procura_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Retorna uma lista de usuarios que possui o usuario(V) ou NULL caso não encontre o usuario(V).
usuarios *procura_usuario(Grafo *G, int usuario){
  struct usuarios *Lista, *Lista2, *LErro;
  bool encontrado = false;
  int cont;
  
  LErro = (usuarios *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeusuario = -1; //Valor fixado para erro.
  LErro->proxusuario = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antusuario = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.

  Lista = (G->pontusuarioInicio);
  cont = G->N_usuarios;
  while(cont--){
    if(Lista->nomeusuario == usuario){
      encontrado = true;
      Lista2 = Lista;
      cont = 0;
    }
    Lista = Lista->proxusuario;
  }
  if(encontrado){
    return Lista2;
  }
  else{
        printf("\nERRO : usuario %d Nao Encontrado!!\n", usuario);
    return LErro;
  }
}
*/

 //Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, usuarios **User){
  int cont = 0;

  while(cont < 26){
    if(((*User)->nome[0]) == ('A'+cont)){
      if(((*G)->listaAdj[cont]) == NULL){
        ((*G)->listaAdj[cont]) = (*User);
        (((*G)->listaAdj[cont])->prox) = NULL;
        (((*G)->listaAdj[cont])->ant) = NULL;
      }
      else{
        printf("valor = %d %s\n", cont, (*G)->listaAdj[cont]->nome);
        while(((*G)->listaAdj[cont])->prox != NULL){
          ((*G)->listaAdj[cont]) = ((*G)->listaAdj[cont])->prox; 
        }
        (((*G)->listaAdj[cont])->prox) = (*User);
        ((*User)->ant) = ((*G)->listaAdj[cont]);
        ((*User)->prox) = NULL;
      }
      cont = 26;
    }
    else{
      cont++;
    }
  }
  (*G)->N_usuarios++;
}

usuarios *cria_pessoa(){
  char nom[100], cidade[30], cep[20], cpf[12];
  struct usuarios *user;

  user = (usuarios*)malloc(sizeof(usuarios));

  printf("Digite o seu nome\n");
  scanf(" %[^\n]s", nom);
  (user->nome) = nom;
  printf("Digite o seu cpf\n");
  scanf(" %[^\n]s", cpf);
  user->cpf = cpf;
  printf("Digite o sua cidade\n");
  scanf(" %[^\n]s", cidade);
  user->cidade = cidade;
  printf("Digite o seu cep\n");
  scanf(" %[^\n]s", cep);
  user->cep = cep;
  user->Amigos = NULL;
  user->ant = NULL;
  user->prox = NULL;
  system("cls || clear"); 

  return user;
}

int main(int argc, char const *argv[]){
  struct usuarios *user;
  Grafo *g;

  g = cria_Grafo();
  user = cria_pessoa();
  printf("Usuario %s criado com sucesso!\n\n", (user)->nome);
  adiciona_usuario(&g, &user);
  imprime_Grafo(g);

  return 0;
}