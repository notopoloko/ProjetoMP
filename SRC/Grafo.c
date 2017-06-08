#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grafo.h"

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
Grafo *cria_Grafo(){
  struct Grafo *G;
  int i = 0;

  G = (Grafo *)malloc(sizeof(*G));
  G->N_Usuarios = 0;
  while(i < 24){
    G->listaAdj[i] = NULL;
    i++;
  }
}

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G){
  if(G->N_Usuarios != 0){
    return true;
  }
  else{
    printf("ERRO: Nao existem usuarios na rede\n");
    return false;
  }
}

void destroi_Listadeamizade(Usuarios **Lusuario){
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
  struct Usuarios *usuarioAnt, *usuarioAtual;
  int cont;

  cont = (*G)->N_Usuarios;
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

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os Usuarios e Amizades.
void imprime_Grafo(Grafo *G){
  struct Usuarios *LAux;
  struct Amizades *amizadeAux;

  if(existe_Grafo(G)){
    printf("\n%s", G->nomeGrafo);
    LAux = G->pontusuarioInicio;
    printf("\n\n");
    while(LAux != NULL){
      printf("[%d] ", LAux->nomeusuario);
      amizadeAux = LAux->pontamizadeInicio;
      while(amizadeAux != NULL){
        printf("---> (%d) ", amizadeAux->nomeamizade);
        amizadeAux = amizadeAux->proxamizade;
      }
      printf("\n");
      LAux = LAux->proxusuario;
    }
    printf("\n");
  }
}

//Funcao procura_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Retorna uma lista de Usuarios que possui o usuario(V) ou NULL caso não encontre o usuario(V).
Usuarios *procura_usuario(Grafo *G, int usuario){
  struct Usuarios *Lista, *Lista2, *LErro;
  bool encontrado = false;
  int cont;
  
  LErro = (Usuarios *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeusuario = -1; //Valor fixado para erro.
  LErro->proxusuario = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antusuario = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.

  Lista = (G->pontusuarioInicio);
  cont = G->N_Usuarios;
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

 //Funcao adiciona_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
void adiciona_usuario(Grafo **G, Usuarios **User){
  struct Usuarios *pont;
  int cont = 0;

  while(cont < 24){
    if(((*User)->nome[0]) == ('A'+cont)){
      if(((*G)->listaAdj[cont]) == NULL){
        ((*G)->listaAdj[cont]) = (*User);
        (((*G)->listaAdj[cont])->prox) = NULL;
        (((*G)->listaAdj[cont])->ant) = NULL;
      }
      else{
        pont = ((*G)->listaAdj[cont]);
        while(pont->prox != NULL){
          pont = pont->prox; 
        }
        (pont->prox) = (*User);
        ((*User)->ant) = pont;
        ((*User)->prox) = NULL;
      }
      cont = 24;
    }
    else{
      cont++;
    }
  }
}
/*
 //Funcao remove_usuario --- Recebe como Parametros um Grafo(G) e um usuario(usuario).
void remove_usuario(Grafo **G, Usuarios **User){
  struct Usuarios *pont;
  int cont = 0;

  while(cont < 24){
    pont = ((*G)->listaAdj[cont]);
    if(((*User)->nome[0]) == ('A'+cont)){
      if(pont->ant == NULL){
        pont = NULL;
        pont = (pont->prox);
        pont->ant = NULL;
      }
      else{
        while(pont->prox != NULL){
          pont = pont->prox; 
        }
        if(pont->prox == NULL){
          pont = NULL;
          pont = (pont->prox);
          pont->ant = NULL;
        }
        (pont->prox) = (*User);
        ((*User)->ant) = pont;
        ((*User)->prox) = NULL;
      }
      cont = 24;
    }
    else{
      cont++;
    }
  }

  if(existe_Grafo(*G)){
    LAux = procura_usuario((*G), usuario);
    if((*G)->pontusuarioInicio != (*G)->pontusuarioFim){
      if(LAux != NULL){
        if(LAux->antusuario != NULL && LAux->proxusuario != NULL){
          LAux->antusuario->proxusuario = LAux->proxusuario;
          LAux->proxusuario->antusuario = LAux->antusuario; 
        }
        else{
          if(LAux->antusuario == NULL){ 
            (*G)->pontusuarioInicio = LAux->proxusuario;
            LAux->antusuario = NULL;
          }
          if(LAux->proxusuario == NULL){ 
            (*G)->pontusuarioFim = LAux->antusuario;   
            LAux->proxusuario = NULL; 
          }
        }
        destroi_Listadeamizade(&LAux);
        free(LAux);
        LAux->proxusuario = NULL;
        LAux->antusuario = NULL;
        LAux = NULL;
        (*G)->N_Usuarios-= 1;
        // printf("\nMostra Grafo:\n");
        //printf("\nusuario [%d] Removido!!", usuario);
      }
      else{
        printf("\nERRO : usuario %d Nao Encontrado!!\n", usuario);
      }  
    }  
    else{
      free(LAux);
      LAux->proxusuario = NULL;
      LAux->antusuario = NULL;
      LAux = NULL;
      (*G)->pontusuarioInicio = NULL;
      (*G)->pontusuarioFim = NULL;
      (*G)->N_Usuarios-= 1;
    }
  }
}

//Funcao procura_amizade --- Recebe como Parametros um Lista de Usuarios(ListaV1) e dois Usuarios(VOrig e VDest).
//Retorna uma lista de Amizades que possui os Usuarios(VOrig e VDest) ou NULL caso não encontre o usuario(V).
Amizades *procura_amizade(Grafo *G, int VOrig, int VDest){
  struct Amizades *apontaArst, *LErro;
  struct Usuarios *ListaV1, *ListaV2, *apontaVert;
  bool encontrado = false;
 
  LErro = (Amizades *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeamizade = -1; //Valor fixado para erro.
  LErro->proxamizade = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antamizade = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  ListaV1 = procura_usuario(G, VOrig);
  ListaV2 = procura_usuario(G, VDest);

  apontaVert = G->pontusuarioInicio;
  apontaArst = ListaV1->pontamizadeInicio;
  if(ParDeusuario_Existe(ListaV1, ListaV2)){
  
  while(apontaArst != NULL){
      if(apontaArst->usuarioOrig == ListaV1 && apontaArst->usuarioDest == ListaV2){
        encontrado = true;
        return apontaArst;
      }
      apontaArst = apontaArst->proxamizade;
    }
    if(!encontrado){
      printf("ERRO : Nao existe amizade entre os Usuarios. Retorna Valor -1.\n");
      return LErro;
    }
  }
  else{
      printf("ERRO : Nao existe amizade entre os Usuarios. Retorna Valor -1.\n");
  return LErro;
  }
}

//Funcao atualiza_amizade --- Recebe como Parametros um Grafo(G), dois Usuarios(V1 e V2) e um usuario Atualizado(usuarioAtualizado).
void atualiza_amizade(Grafo **G, int V1, int V2, int amizadeAtualizada){
  struct Amizades *amizadeAux;

  amizadeAux = procura_amizade(*G ,V2, V1);
   // printf("\nNome da amizade Antiga = %d\n", amizadeV1->nomeamizade); 
   if(amizadeAux != NULL){ 
     amizadeAux->nomeamizade = amizadeAtualizada; 
     amizadeAux->nomeamizade = amizadeAtualizada;   
    //printf("Nome da amizade Nova = %d\n", amizadeV1->nomeamizade);  
   }
   else{
    printf("ERRO : Nao existe amizade entre os Usuarios %d e %d.\n", V1, V2);
   }  
}

 //Funcao atualiza_usuario --- Recebe como Parametros um Grafo(G), um usuario(usuario) e um usuario Atualizado(usuarioAtualizado).
void atualiza_usuario(Grafo **G, int usuario, int usuarioAtualizado){
  struct Usuarios *LAux, *apontaVert, *LAux2;
  struct Amizades *amizadeAux, *apontaArst;
  bool encontrado = false;
  
  if(existe_Grafo(*G)){
    LAux = procura_usuario(*G, usuario);
    apontaVert = (*G)->pontusuarioInicio;
    apontaArst = apontaVert->pontamizadeInicio;

    if(LAux !=  NULL){
      while(apontaVert != NULL){
        if(apontaVert->nomeusuario == usuario){
          apontaVert->nomeusuario = usuarioAtualizado;
        }
        while(apontaArst != NULL){
          if(apontaArst->usuarioDest == LAux || apontaArst->usuarioOrig == LAux){
            apontaArst->nomeamizade = usuarioAtualizado;
            if(apontaArst->usuarioDest == LAux){
              apontaArst->usuarioDest == LAux;
            }
            if(apontaArst->usuarioOrig == LAux){
              apontaArst->usuarioOrig == LAux;
            }
          }
          apontaArst = apontaArst->proxamizade;
        }
        apontaVert = apontaVert->proxusuario;
      }
    }
  }
  else{
    printf("ERRO: Grafo Inexistente!!\n");
  }
}


//Funcao retorna_usuario --- Recebe como Parametros um Grafo(G) e um usuario(V).
//Que retorna o Valor de usuario(Se o usuario for encontrado) ou retorna 0, caso não encontre o usuario.
int retorna_usuario(Grafo *G, int usuario){
  struct Usuarios *Lista, *Lista2;
  bool encontrado = false;
  int VarAux;
  
  if(existe_Grafo(G)){
    Lista = (G->pontusuarioInicio);  
    while(Lista != NULL){
      if(Lista->nomeusuario == usuario){
        encontrado = true;
        Lista2 = Lista;
      }
      Lista = Lista->proxusuario;
    }
    if(encontrado){
      //printf("\nusuario [%d]\n", Lista2->nomeusuario);
      VarAux = Lista2->nomeusuario;
    }
    else{
        printf("ERRO : usuario %d Nao Encontrado!!\n", usuario);
      VarAux = -1; 
    }
  }
  return VarAux;
}

//Funcao Pardeusuario_Existe --- Recebe como Parametros duas listas de adjacencia(ListaV1 e ListaV2).
//Retorna true se existir amizade entre as duas e falso caso nao exista.
bool ParDeusuario_Existe(Usuarios *ListaV1, Usuarios *ListaV2){
  if(ListaV2 != NULL && ListaV1 != NULL){
    return true;
  }
  else{
    if(ListaV1 == NULL && ListaV2 == NULL){
      printf("ERRO : Nenhum usuario existe!!\n");
      return false;    
    }
    if(ListaV1 != NULL){
      printf("ERRO : Unico usuario existente = [%d]\n", ListaV1->nomeusuario);
      return false;    
    }
    if(ListaV2 != NULL){
      printf("ERRO : Unico usuario existente = [%d]\n", ListaV2->nomeusuario);
      return false;    
    }
  }
}

//Funcao adiciona_amizade --- Recebe como Parametros um Grafo(G), um usuario de Origem(VOrig) e um usuario de Destino(VDest).
void adiciona_amizade(Grafo **G, int VOrig, int VDest){
  struct Usuarios *ListaOrig, *ListaDest, *apontaVizinhosOrig, *apontaVizinhosDest;;
  struct Amizades *amizadeAux, *amizadeAux2;
 
  if(existe_Grafo(*G)){
    //printf("\nTestando existencia dos Usuarios %d e %d ......\n", VOrig, VDest);
    ListaOrig = procura_usuario(*G, VOrig);
    ListaDest = procura_usuario(*G, VDest);

    if(ParDeusuario_Existe(ListaOrig, ListaDest)){
      amizadeAux = (Amizades *)malloc(sizeof(*amizadeAux));
      amizadeAux->nomeamizade = VDest;
      amizadeAux->usuarioOrig = ListaOrig;
      amizadeAux->usuarioDest = ListaDest;
      amizadeAux->proxamizade = NULL;
      amizadeAux->antamizade = NULL;

      if(ListaOrig->pontamizadeInicio == NULL){
        ListaOrig->pontamizadeInicio = amizadeAux;
        ListaOrig->pontamizadeFim = amizadeAux;
      }
      else{
        ListaOrig->pontamizadeFim->proxamizade = amizadeAux; 
        amizadeAux->antamizade = ListaOrig->pontamizadeFim;
        ListaOrig->pontamizadeFim = amizadeAux;
      }
      ListaOrig->N_Amizadesdousuario+= 1;
      (*G)->N_Amizades+= 1;
      //printf("amizade Adicionada com Sucesso!!\n");
    }
  }
}

//Funcao retorna_amizade --- Recebe como Parametros um Grafo(G) e dois Usuarios(V1 e V2).
//Que retorna o Valor da amizade(Se o usuario for encontrado) ou retorna 0, caso não encontre o usuario.
int retorna_amizade(Grafo *G, int V1, int V2){
  struct Amizades *amizadeAux;
  struct Usuarios *ListaAux, *ListaAux2;
  bool encontrado = false;

  if(existe_Grafo(G)){
    ListaAux = procura_usuario(G, V1);
    ListaAux2 = procura_usuario(G, V2);
    if(ParDeusuario_Existe(ListaAux, ListaAux2)){
      amizadeAux = procura_amizade(G, V1, V2);
      if(amizadeAux->nomeamizade != -1){
        return amizadeAux->nomeamizade;
      }
      else{
        printf("ERRO: amizade nao encontrada!\n");
        return -1;
      }
    }
  }
  else{
    printf("ERRO: amizade nao encontrada!\n");
    return -1;
  }
}

//Funcao verifica_Vizinhos(Dado um usuario V1 - procura todas as Amizades de V1) --- Recebe como Parametros um Grafo(G) e um usuario(V1).
//Retorna Null se nao houver vizinhos ou retorna uma lista de Amizades se houver vizinhos
Usuarios *verifica_Vizinhos(Grafo *G, int V1){
  struct Usuarios *ListaV1, *LErro;
  struct Amizades *apontaArst;
  bool encontrado = false;

  LErro = (Usuarios *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeusuario = -1; //Valor fixado para erro.
  LErro->proxusuario = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antusuario = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  
  ListaV1 = procura_usuario(G, V1);

  if(ListaV1 != NULL){
    if(ListaV1->pontamizadeInicio){
      printf("Os vizinhos do usuario %d São: ", V1);
      if(ListaV1->pontamizadeInicio != NULL){
        apontaArst = ListaV1->pontamizadeInicio;
        while(apontaArst != NULL){
        printf("[%d] ", apontaArst->nomeamizade);
        apontaArst = apontaArst->proxamizade;
       }
        printf("\n");
        return ListaV1;
      }
    }
    else{
      return LErro;
    }
  }
  else{
    printf("ERRO : usuario %d Inexistente!!\n", V1);
    return LErro;
  }     
}

//Funcao verifica_Adjacencia(Se existe uma amizade entre dois Usuarios) --- Recebe como Parametros um Grafo(G), dois Usuarios(V2 e V1).
void verifica_Adjacencia(Grafo *G, int V1, int V2){
  struct Usuarios *ListaV1, *ListaV2;
  struct Amizades *apontaArst;
  bool encontrado = false;

  ListaV1 = procura_usuario(G, V1);
  ListaV2 = procura_usuario(G, V2);
  apontaArst = ListaV1->pontamizadeInicio;
  while(apontaArst != NULL){
      if(apontaArst->usuarioDest == ListaV2 || apontaArst->usuarioOrig == ListaV2){
        encontrado = true;
      }
      apontaArst = apontaArst->proxamizade;
  
  }
  if(!encontrado){
    printf("\nOs Usuarios %d e %d nao sao Adjacentes\n", V1, V2);     
  } 
  else{
    printf("\nOs Usuarios %d e %d sao Adjacentes\n", V1, V2);
  }
}

//Funcao remove_amizade --- Recebe como Parametros um Grafo(G), dois Usuarios(VOrig e VDest).
void remove_amizade(Grafo **G, int VOrig, int VDest){
  struct Usuarios *ListaOrig, *ListaDest;
  struct Amizades *amizadeV1;

  if(existe_Grafo(*G)){
    ListaOrig = procura_usuario(*G, VOrig);
    ListaDest = procura_usuario(*G, VDest);
    if(ParDeusuario_Existe(ListaOrig, ListaDest)){
      amizadeV1 = procura_amizade(*G, VOrig, VDest);
      if(ListaOrig->pontamizadeFim != ListaOrig->pontamizadeInicio){
        if(amizadeV1 != NULL){
          if(amizadeV1->antamizade != NULL && amizadeV1->proxamizade != NULL){
            amizadeV1->antamizade->proxamizade = amizadeV1->proxamizade;
            amizadeV1->proxamizade->antamizade = amizadeV1->antamizade; 
          }
          else{
            if(amizadeV1->antamizade == NULL){ 
              ListaOrig->pontamizadeInicio = amizadeV1->proxamizade;
              amizadeV1->antamizade = NULL;
            }
            if(amizadeV1->proxamizade == NULL){ 
              ListaOrig->pontamizadeFim = amizadeV1->antamizade;   
              amizadeV1->proxamizade = NULL; 
            }
          }
          free(amizadeV1);
          amizadeV1->proxamizade = NULL;
          amizadeV1->antamizade = NULL;
          amizadeV1 = NULL;
          (*G)->N_Amizades-= 1;
          ListaOrig->N_Amizadesdousuario-= 1;
        }
        //printf("\nA amizade entre %d e %d foi removida!!\n", VOrig, VDest);
        else{
          printf("\nERRO : Nao existe amizade entre %d e %d\n", VOrig, VDest);     
        }
      }
      else{
        free(amizadeV1);
        amizadeV1->proxamizade = NULL;
        amizadeV1->antamizade = NULL;
        amizadeV1 = NULL;
        ListaOrig->pontamizadeInicio = NULL;
        ListaOrig->pontamizadeFim = NULL;
        ListaOrig->N_Amizadesdousuario-= 1;
        (*G)->N_Amizades-= 1;
      }
    }
  }
}
*/