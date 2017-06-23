#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int Const = 0;

//Estrutura do tipo grafo com um vetor de caracteres representando o nome do grafo, um inteiro representando
//o numero de usuarios do grafo e um ponteiro para outra estrutura do tipo usuarios.
typedef struct amigos{
  char nomeAmigo[100]; 

  struct amigos *proxAmigo, *antAmigo;
}amigos;

//Estrutura do tipo usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct usuarios{
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
  struct usuarios *listaAdj[26];
}Grafo;


//Funcao cria_Grafo
//Aloca espaço de memoria para criar uma estrutura do tipo Grafo que atribui NomedoGrafo para estrutura.
Grafo *cria_Grafo();

int verifica_letra(char nome);

usuarios *procura_usuario(Grafo *G);

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
  int i = 0, j = 0;

  printf("Numero de usuarios = %d\n", G->N_usuarios);
  while(i < 26){
    if((G->listaAdj[i]) != NULL){
      printf("[%c] -> %s\n", ('A'+i), (G->listaAdj[i])->nome);
      for(j = 0; j < 26; j++){
        if(j == 0){
          printf("       Amigos %s = {", (G->listaAdj[i])->nome);
        }
        if(((G->listaAdj[i])->Amigos[j]) != NULL){
          printf(" %s ", ((G->listaAdj[i])->Amigos[j])->nomeAmigo);
        }
        if(j == 25){
          printf("}\n");
        }
      }
    }
    else{
      printf("[%c] -> Esta vazio\n", ('A'+i));
    }
    i++;
  }
}


//Funcao procura_usuario --- Recebe como Parametros um Grafo(G).
//Retorna um usuario ou NULL caso não encontre o usuario.
usuarios *procura_usuario(Grafo *G){
  struct usuarios *User;
  bool encontrado = false;
  char nom[100];
  int letra;

  printf("Digite o nome do usuario:\n");
  scanf(" %[^\n]", nom);

  letra = verifica_letra(nom[0]);
  User = ((G->listaAdj[letra]));
  while(User != NULL){
    if(strcmp(nom, User->nome) == 0){
      encontrado = true;
    }
    User = User->prox;
  }
  if(encontrado){
    return User;
  }
  else{
        printf("\nERRO : Usuario %s Nao Encontrado!!\n", nom);
    return NULL;
  }
}


 //Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G) e dois usuarios.
void adiciona_amigos(Grafo **G, usuarios **User1, usuarios **User2, int cons){
  int letra;
  struct amigos *pont, *amigo;

  amigo = (amigos*)malloc(sizeof(amigos));
  strcpy(amigo->nomeAmigo, (*User2)->nome);
  amigo->proxAmigo = NULL;
  amigo->antAmigo = NULL;


  letra = verifica_letra(((*User2)->nome[0]));
  if(((*User1)->Amigos[letra]) == NULL){
    ((*User1)->Amigos[letra]) = (amigo);
  }
  else{
    pont = ((*User1)->Amigos[letra]);
    while(pont->proxAmigo != NULL){
      pont = pont->proxAmigo; 
    }
    pont->proxAmigo = (amigo);
    amigo->antAmigo = pont;
    amigo->proxAmigo = NULL;
  }
  (*User1)->numeroAmigos++;
    printf("%s\n", ((*User1)->Amigos[letra])->nomeAmigo);
  if(cons == 0){
    adiciona_amigos(&(*G), &(*User2), &(*User1), 1);
  }
}

int verifica_letra(char nome){
  int cont = 0, letra = -1;

  while(cont < 26){
    if((nome == ('A'+cont)) || ((nome) == ('a'+cont))){
      letra = cont;
      cont = 26;
    }
    else{
      cont++;
    }
  }
  return letra;
}

usuarios *cria_pessoa(Grafo **G){
  char nom[100], cidade[30], cep[20], cpf[12];
  int cont = 0, letra;
  struct usuarios *pont, *user;

  user = (usuarios*)malloc(sizeof(usuarios));
  printf("Digite o seu nome: ");
  scanf(" %[^\n]", nom);
  getchar();
  strcpy(user->nome, nom);
  printf("Digite o seu cpf: ");
  scanf(" %[^\n]", cpf);
  strcpy(user->cpf, cpf);
  printf("Digite o sua cidade: ");
  scanf(" %[^\n]", cidade);
  strcpy(user->cidade, cidade);
  printf("Digite o seu cep: ");
  scanf(" %[^\n]", cep);
  strcpy(user->cep, cep);

 
  letra = verifica_letra(nom[0]);
  if(((*G)->listaAdj[letra]) == NULL){
    ((*G)->listaAdj[letra]) = user;

    for (cont = 0; cont < 26; ++cont){
      ((*G)->listaAdj[letra])->Amigos[cont] = NULL;
    }
    ((*G)->listaAdj[letra])->ant = NULL;
    ((*G)->listaAdj[letra])->prox = NULL;
    (((*G)->listaAdj[letra])->numeroAmigos) = 0;
  }
  else{
    pont = ((*G)->listaAdj[letra]);
    while(pont->prox != NULL){
      pont = pont->prox; 
    }
    pont->prox = (user);
    ((user)->ant) = pont;
    ((user)->prox) = NULL;
    (user)->numeroAmigos = 0;
  }
  (*G)->N_usuarios++;
  
  return user;
}

int main(int argc, char const *argv[]){
  struct Grafo *G;
  struct usuarios *user1, *user2;

  G = cria_Grafo();
  user1 = cria_pessoa(&G); 
  user2 = cria_pessoa(&G); 
  adiciona_amigos(&G, &user1, &user2, Const);
  imprime_Grafo(G);
  procura_usuario(G);

  return 0;
}