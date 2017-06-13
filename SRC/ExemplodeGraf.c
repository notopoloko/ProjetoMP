#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estrutura do tipo usuarios com dois inteiros representando o nome do usuario e o numero de Amizades para cada usuario.
//Apresenta tambem um ponteiro(Tipo usuarios) que aponta para proxima usuario e um ponteira para uma estrutura do tipo Amizades.
typedef struct usuarios{
  char *nome;   
  char *cidade;
  char *cep;      
  char *cpf;
  int numeroAmigos;             //Inteiro que representa o numero de amigos de um usuario.

  struct usuarios *Amigos[26];
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
      printf("[%c] -> %s\n", ('A'+i), (G->listaAdj[i])->nome);
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


 //Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G) e dois usuarios.
void adiciona_amigos(Grafo **G, usuarios **User1, usuarios **User2, int cons){
  int cont = 0;

  while(cont < 26){
    if(((*User2)->nome[0]) == ('A'+cont)){
      if(((*User1)->Amigos[cont]) == NULL){
        ((*User1)->Amigos[cont]) = (*User2);
        (*User1)->Amigos[cont]->prox = NULL;
        (*User1)->Amigos[cont]->ant = NULL;
      }
      else{
        while((*User1)->Amigos[cont]->prox != NULL){
          ((*User1)->Amigos[cont]) = ((*User1)->Amigos[cont])->prox; 
        }
        ((*User1)->Amigos[cont]->prox) = (*User2);
        ((*User2)->ant) = ((*User1)->Amigos[cont]);
        ((*User2)->prox) = NULL;
      }
      cont = 26;
      if(cons == 0){
        adiciona_amigos(&(*G), &(*User1), &(*User2), 1);
      }
    }
    else{
      cont++;
    }
  }
  (*User1)->numeroAmigos++;
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

 //Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, usuarios **User){
 /* char nom[100];
  int letra;
  struct usuarios *pont;

  nom = (*User)->nome;
  letra = verifica_letra(nom[0]);
  if(((*G)->listaAdj[letra]) == NULL){
    ((*User)->prox) = NULL;
    ((*User)->ant) = NULL;
  }
  else{
    pont = (*User);
    while(pont->prox != NULL){
      pont = pont->prox; 
    }
    pont->prox = (User);
    ((User)->ant) = pont;
    ((User)->prox) = NULL;
  }

  (*G)->N_usuarios++;
  (User)->numeroAmigos = 0;
*/
}

usuarios *cria_pessoa(Grafo **G){
  char nom[100], cidade[30], cep[20], cpf[12];
  int cont = 0, letra;
  struct usuarios *pont, *user, *pant;

  user = (usuarios*)malloc(sizeof(usuarios));
  printf("Digite o seu nome: ");
  scanf(" %[^\n]", nom);

  printf("Digite o seu cpf: ");
  scanf(" %[^\n]", cpf);
  user->cpf = cpf;
  printf("Digite o sua cidade: ");
  scanf(" %[^\n]", cidade);
  user->cidade = cidade;
  printf("Digite o seu cep: ");
  scanf(" %[^\n]", cep);
  user->cep = cep;
  

  letra = verifica_letra(nom[0]);
  if(((*G)->listaAdj[letra]) == NULL){
    ((*G)->listaAdj[letra]) = user;
    ((*G)->listaAdj[letra]->nome) = nom;

    for (cont = 0; cont < 26; ++cont){
      ((*G)->listaAdj[letra])->Amigos[cont] = NULL;
    }
    ((*G)->listaAdj[letra])->ant = NULL;
    ((*G)->listaAdj[letra])->prox = NULL;
    (((*G)->listaAdj[letra])->numeroAmigos) = 0;
  }
  else{
    pont = ((*G)->listaAdj[letra]);
    while(pont != NULL){
      pant = pont;
      pont = pont->prox; 
    }
    pont = (user);
    pont->nome = nom;
    ((user)->ant) = pant;
    ((user)->prox) = NULL;
    (user)->numeroAmigos = 0;
  }

  (*G)->N_usuarios++;

  
  return user;
}

int main(int argc, char const *argv[]){
  Grafo *g;

  g = cria_Grafo();
  cria_pessoa(&g); 
  imprime_Grafo(g);

  return 0;
}