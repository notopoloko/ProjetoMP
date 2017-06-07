#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Grafo.h"

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
Grafo *cria_Grafo(char *NomedoGrafo){
  struct Grafo *G;
  //Testa Nome//
  if(NomedoGrafo){ // Testa se nome existe.
    G = (Grafo *)malloc(sizeof(*G));
    G->N_Vertices = 0;
    G->N_Arestas = 0;
    G->nomeGrafo = NomedoGrafo;
    G->pontVerticeInicio = NULL;
   // printf("\nGrafo Criado Com Sucesso!!\n");

  return G;
  }
  else{
    printf("Nao foi criado um nome para o grafo\nInsira um nome valido\n");
    return NULL;
  }
}

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G){
  if(G != NULL){
    return true;
  }
  else{
   printf("ERRO: Grafo Inexistente\n");
    return false;
  }
}

void destroi_ListadeAresta(Vertices **LVertice){
  struct Arestas *ArestaAtual;
  int cont;

  cont = (*LVertice)->N_ArestasdoVertice;
  while(cont--){
    ArestaAtual = (*LVertice)->pontArestaFim;
    if(ArestaAtual->antAresta != NULL){
      (*LVertice)->pontArestaFim = ArestaAtual->antAresta;
      free(ArestaAtual);
      ArestaAtual->proxAresta = NULL;
      ArestaAtual->antAresta = NULL;
      ArestaAtual = NULL;
    }
    else{
      (*LVertice)->pontArestaFim = NULL;
      (*LVertice)->pontArestaInicio = NULL;
    }
  }
}

void destroi_ListadeVertice(Grafo **G){
  struct Vertices *VerticeAnt, *VerticeAtual;
  int cont;

  cont = (*G)->N_Vertices;
  while(cont--){
    VerticeAtual = (*G)->pontVerticeFim;
    destroi_ListadeAresta(&VerticeAtual);
    if(VerticeAtual->antVertice != NULL){
      (*G)->pontVerticeFim = VerticeAtual->antVertice;
      free(VerticeAtual);
      VerticeAtual->proxVertice = NULL;
      VerticeAtual->antVertice = NULL;
      VerticeAtual = NULL;
    }
    else{
      (*G)->pontVerticeInicio = NULL;
      (*G)->pontVerticeFim = NULL;
    }
  }
}

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e libera cada espaço de memoria alocado dinamicamente.
void destroi_Grafo(Grafo **G){
  if(existe_Grafo(*G)){
    destroi_ListadeVertice(G);
    free((*G));
    (*G) = NULL;
  }
}

 //Funcao retorna_NomeGrafo --- Recebe como Parametro um Grafo(G) e imprime na tela um vetor de caracteres que representa o nome do grafo.
char *retorna_NomeGrafo(Grafo *G){
  if(existe_Grafo(G)){
    return (G)->nomeGrafo;
  }
  else{
    printf("ERRO: Grafo Inexistente\n");
    return Erro;
  }
}

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os vertices e arestas.
void imprime_Grafo(Grafo *G){
  struct Vertices *LAux;
  struct Arestas *ArestaAux;

  if(existe_Grafo(G)){
    printf("\n%s", G->nomeGrafo);
    LAux = G->pontVerticeInicio;
    printf("\n\n");
    while(LAux != NULL){
      printf("[%d] ", LAux->nomeVertice);
      ArestaAux = LAux->pontArestaInicio;
      while(ArestaAux != NULL){
        printf("---> (%d) ", ArestaAux->nomeAresta);
        ArestaAux = ArestaAux->proxAresta;
      }
      printf("\n");
      LAux = LAux->proxVertice;
    }
    printf("\n");
  }
}

//Funcao procura_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
//Retorna uma lista de Vertices que possui o vertice(V) ou NULL caso não encontre o vertice(V).
Vertices *procura_Vertice(Grafo *G, int Vertice){
  struct Vertices *Lista, *Lista2, *LErro;
  bool encontrado = false;
  int cont;
  
  LErro = (Vertices *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeVertice = -1; //Valor fixado para erro.
  LErro->proxVertice = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antVertice = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.

  Lista = (G->pontVerticeInicio);
  cont = G->N_Vertices;
  while(cont--){
    if(Lista->nomeVertice == Vertice){
      encontrado = true;
      Lista2 = Lista;
      cont = 0;
    }
    Lista = Lista->proxVertice;
  }
  if(encontrado){
    return Lista2;
  }
  else{
        printf("\nERRO : Vertice %d Nao Encontrado!!\n", Vertice);
    return LErro;
  }
}

 //Funcao adiciona_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
void adiciona_Vertice(Grafo **G, int V){
  struct Vertices *LAux;

  if(existe_Grafo(*G)){
    LAux = (Vertices *)malloc(sizeof(*LAux));
    LAux->nomeVertice = V;
    LAux->N_ArestasdoVertice = 0;
    LAux->proxVertice = NULL;
    LAux->antVertice = NULL;

    if((*G)->pontVerticeInicio == NULL){
      (*G)->pontVerticeInicio = LAux;
      (*G)->pontVerticeFim = LAux;

      (*G)->pontVerticeInicio->pontArestaInicio = NULL;
      (*G)->pontVerticeInicio->pontArestaFim = NULL;

      (*G)->pontVerticeFim->pontArestaInicio = NULL;
      (*G)->pontVerticeFim->pontArestaFim = NULL;
    }
    else{
      (*G)->pontVerticeFim->proxVertice = LAux;
      LAux->antVertice = (*G)->pontVerticeFim;
      (*G)->pontVerticeFim = LAux;
      (*G)->pontVerticeFim->pontArestaInicio = NULL;
      (*G)->pontVerticeFim->pontArestaFim = NULL;   
    }
    (*G)->N_Vertices+= 1;
     // printf("\nVertice %d Adicionado!!", LAux->nomeVertice);
    //}
  }
}

 //Funcao remove_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(Vertice).
void remove_Vertice(Grafo **G, int Vertice){
  struct Vertices *LAux;
  
  if(existe_Grafo(*G)){
    LAux = procura_Vertice((*G), Vertice);
    if((*G)->pontVerticeInicio != (*G)->pontVerticeFim){
      if(LAux != NULL){
        if(LAux->antVertice != NULL && LAux->proxVertice != NULL){
          LAux->antVertice->proxVertice = LAux->proxVertice;
          LAux->proxVertice->antVertice = LAux->antVertice; 
        }
        else{
          if(LAux->antVertice == NULL){ 
            (*G)->pontVerticeInicio = LAux->proxVertice;
            LAux->antVertice = NULL;
          }
          if(LAux->proxVertice == NULL){ 
            (*G)->pontVerticeFim = LAux->antVertice;   
            LAux->proxVertice = NULL; 
          }
        }
        destroi_ListadeAresta(&LAux);
        free(LAux);
        LAux->proxVertice = NULL;
        LAux->antVertice = NULL;
        LAux = NULL;
        (*G)->N_Vertices-= 1;
        // printf("\nMostra Grafo:\n");
        //printf("\nVertice [%d] Removido!!", Vertice);
      }
      else{
        printf("\nERRO : Vertice %d Nao Encontrado!!\n", Vertice);
      }  
    }  
    else{
      free(LAux);
      LAux->proxVertice = NULL;
      LAux->antVertice = NULL;
      LAux = NULL;
      (*G)->pontVerticeInicio = NULL;
      (*G)->pontVerticeFim = NULL;
      (*G)->N_Vertices-= 1;
    }
  }
}

//Funcao procura_Aresta --- Recebe como Parametros um Lista de Vertices(ListaV1) e dois Vertices(VOrig e VDest).
//Retorna uma lista de Arestas que possui os vertices(VOrig e VDest) ou NULL caso não encontre o vertice(V).
Arestas *procura_Aresta(Grafo *G, int VOrig, int VDest){
  struct Arestas *apontaArst, *LErro;
  struct Vertices *ListaV1, *ListaV2, *apontaVert;
  bool encontrado = false;
 
  LErro = (Arestas *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeAresta = -1; //Valor fixado para erro.
  LErro->proxAresta = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antAresta = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  ListaV1 = procura_Vertice(G, VOrig);
  ListaV2 = procura_Vertice(G, VDest);

  apontaVert = G->pontVerticeInicio;
  apontaArst = ListaV1->pontArestaInicio;
  if(ParDeVertice_Existe(ListaV1, ListaV2)){
  
  while(apontaArst != NULL){
      if(apontaArst->VerticeOrig == ListaV1 && apontaArst->VerticeDest == ListaV2){
        encontrado = true;
        return apontaArst;
      }
      apontaArst = apontaArst->proxAresta;
    }
    if(!encontrado){
      printf("ERRO : Nao existe aresta entre os vertices. Retorna Valor -1.\n");
      return LErro;
    }
  }
  else{
      printf("ERRO : Nao existe aresta entre os vertices. Retorna Valor -1.\n");
  return LErro;
  }
}

//Funcao atualiza_Aresta --- Recebe como Parametros um Grafo(G), dois Vertices(V1 e V2) e um Vertice Atualizado(VerticeAtualizado).
void atualiza_Aresta(Grafo **G, int V1, int V2, int ArestaAtualizada){
  struct Arestas *ArestaAux;

  ArestaAux = procura_Aresta(*G ,V2, V1);
   // printf("\nNome da aresta Antiga = %d\n", ArestaV1->nomeAresta); 
   if(ArestaAux != NULL){ 
     ArestaAux->nomeAresta = ArestaAtualizada; 
     ArestaAux->nomeAresta = ArestaAtualizada;   
    //printf("Nome da aresta Nova = %d\n", ArestaV1->nomeAresta);  
   }
   else{
    printf("ERRO : Nao existe aresta entre os Vertices %d e %d.\n", V1, V2);
   }  
}

 //Funcao atualiza_Vertice --- Recebe como Parametros um Grafo(G), um Vertice(Vertice) e um Vertice Atualizado(VerticeAtualizado).
void atualiza_Vertice(Grafo **G, int Vertice, int VerticeAtualizado){
  struct Vertices *LAux, *apontaVert, *LAux2;
  struct Arestas *ArestaAux, *apontaArst;
  bool encontrado = false;
  
  if(existe_Grafo(*G)){
    LAux = procura_Vertice(*G, Vertice);
    apontaVert = (*G)->pontVerticeInicio;
    apontaArst = apontaVert->pontArestaInicio;

    if(LAux !=  NULL){
      while(apontaVert != NULL){
        if(apontaVert->nomeVertice == Vertice){
          apontaVert->nomeVertice = VerticeAtualizado;
        }
        while(apontaArst != NULL){
          if(apontaArst->VerticeDest == LAux || apontaArst->VerticeOrig == LAux){
            apontaArst->nomeAresta = VerticeAtualizado;
            if(apontaArst->VerticeDest == LAux){
              apontaArst->VerticeDest == LAux;
            }
            if(apontaArst->VerticeOrig == LAux){
              apontaArst->VerticeOrig == LAux;
            }
          }
          apontaArst = apontaArst->proxAresta;
        }
        apontaVert = apontaVert->proxVertice;
      }
    }
  }
  else{
    printf("ERRO: Grafo Inexistente!!\n");
  }
}


//Funcao retorna_Vertice --- Recebe como Parametros um Grafo(G) e um Vertice(V).
//Que retorna o Valor de Vertice(Se o vertice for encontrado) ou retorna 0, caso não encontre o vertice.
int retorna_Vertice(Grafo *G, int Vertice){
  struct Vertices *Lista, *Lista2;
  bool encontrado = false;
  int VarAux;
  
  if(existe_Grafo(G)){
    Lista = (G->pontVerticeInicio);  
    while(Lista != NULL){
      if(Lista->nomeVertice == Vertice){
        encontrado = true;
        Lista2 = Lista;
      }
      Lista = Lista->proxVertice;
    }
    if(encontrado){
      //printf("\nVertice [%d]\n", Lista2->nomeVertice);
      VarAux = Lista2->nomeVertice;
    }
    else{
        printf("ERRO : Vertice %d Nao Encontrado!!\n", Vertice);
      VarAux = -1; 
    }
  }
  return VarAux;
}

//Funcao PardeVertice_Existe --- Recebe como Parametros duas listas de adjacencia(ListaV1 e ListaV2).
//Retorna true se existir aresta entre as duas e falso caso nao exista.
bool ParDeVertice_Existe(Vertices *ListaV1, Vertices *ListaV2){
  if(ListaV2 != NULL && ListaV1 != NULL){
    return true;
  }
  else{
    if(ListaV1 == NULL && ListaV2 == NULL){
      printf("ERRO : Nenhum vertice existe!!\n");
      return false;    
    }
    if(ListaV1 != NULL){
      printf("ERRO : Unico Vertice existente = [%d]\n", ListaV1->nomeVertice);
      return false;    
    }
    if(ListaV2 != NULL){
      printf("ERRO : Unico Vertice existente = [%d]\n", ListaV2->nomeVertice);
      return false;    
    }
  }
}

//Funcao adiciona_Aresta --- Recebe como Parametros um Grafo(G), um Vertice de Origem(VOrig) e um Vertice de Destino(VDest).
void adiciona_Aresta(Grafo **G, int VOrig, int VDest){
  struct Vertices *ListaOrig, *ListaDest, *apontaVizinhosOrig, *apontaVizinhosDest;;
  struct Arestas *ArestaAux, *ArestaAux2;
 
  if(existe_Grafo(*G)){
    //printf("\nTestando existencia dos vertices %d e %d ......\n", VOrig, VDest);
    ListaOrig = procura_Vertice(*G, VOrig);
    ListaDest = procura_Vertice(*G, VDest);

    if(ParDeVertice_Existe(ListaOrig, ListaDest)){
      ArestaAux = (Arestas *)malloc(sizeof(*ArestaAux));
      ArestaAux->nomeAresta = VDest;
      ArestaAux->VerticeOrig = ListaOrig;
      ArestaAux->VerticeDest = ListaDest;
      ArestaAux->proxAresta = NULL;
      ArestaAux->antAresta = NULL;

      if(ListaOrig->pontArestaInicio == NULL){
        ListaOrig->pontArestaInicio = ArestaAux;
        ListaOrig->pontArestaFim = ArestaAux;
      }
      else{
        ListaOrig->pontArestaFim->proxAresta = ArestaAux; 
        ArestaAux->antAresta = ListaOrig->pontArestaFim;
        ListaOrig->pontArestaFim = ArestaAux;
      }
      ListaOrig->N_ArestasdoVertice+= 1;
      (*G)->N_Arestas+= 1;
      //printf("Aresta Adicionada com Sucesso!!\n");
    }
  }
}

//Funcao retorna_Aresta --- Recebe como Parametros um Grafo(G) e dois Vertices(V1 e V2).
//Que retorna o Valor da Aresta(Se o vertice for encontrado) ou retorna 0, caso não encontre o vertice.
int retorna_Aresta(Grafo *G, int V1, int V2){
  struct Arestas *ArestaAux;
  struct Vertices *ListaAux, *ListaAux2;
  bool encontrado = false;

  if(existe_Grafo(G)){
    ListaAux = procura_Vertice(G, V1);
    ListaAux2 = procura_Vertice(G, V2);
    if(ParDeVertice_Existe(ListaAux, ListaAux2)){
      ArestaAux = procura_Aresta(G, V1, V2);
      if(ArestaAux->nomeAresta != -1){
        return ArestaAux->nomeAresta;
      }
      else{
        printf("ERRO: Aresta nao encontrada!\n");
        return -1;
      }
    }
  }
  else{
    printf("ERRO: Aresta nao encontrada!\n");
    return -1;
  }
}

//Funcao verifica_Vizinhos(Dado um vertice V1 - procura todas as arestas de V1) --- Recebe como Parametros um Grafo(G) e um Vertice(V1).
//Retorna Null se nao houver vizinhos ou retorna uma lista de arestas se houver vizinhos
Vertices *verifica_Vizinhos(Grafo *G, int V1){
  struct Vertices *ListaV1, *LErro;
  struct Arestas *apontaArst;
  bool encontrado = false;

  LErro = (Vertices *)malloc(sizeof(*LErro)); // alocando memoria para uma estrutura que reprensenta um erro.
  LErro->nomeVertice = -1; //Valor fixado para erro.
  LErro->proxVertice = LErro; //Aponta o ponteiro de proximo para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  LErro->antVertice = LErro;//Aponta o ponteiro de anterior para si mesmo para evitar o que o erro seja ligado a outra estrutura.
  
  ListaV1 = procura_Vertice(G, V1);

  if(ListaV1 != NULL){
    if(ListaV1->pontArestaInicio){
      printf("Os vizinhos do Vertice %d São: ", V1);
      if(ListaV1->pontArestaInicio != NULL){
        apontaArst = ListaV1->pontArestaInicio;
        while(apontaArst != NULL){
        printf("[%d] ", apontaArst->nomeAresta);
        apontaArst = apontaArst->proxAresta;
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
    printf("ERRO : Vertice %d Inexistente!!\n", V1);
    return LErro;
  }     
}

//Funcao verifica_Adjacencia(Se existe uma aresta entre dois vertices) --- Recebe como Parametros um Grafo(G), dois Vertices(V2 e V1).
void verifica_Adjacencia(Grafo *G, int V1, int V2){
  struct Vertices *ListaV1, *ListaV2;
  struct Arestas *apontaArst;
  bool encontrado = false;

  ListaV1 = procura_Vertice(G, V1);
  ListaV2 = procura_Vertice(G, V2);
  apontaArst = ListaV1->pontArestaInicio;
  while(apontaArst != NULL){
      if(apontaArst->VerticeDest == ListaV2 || apontaArst->VerticeOrig == ListaV2){
        encontrado = true;
      }
      apontaArst = apontaArst->proxAresta;
  
  }
  if(!encontrado){
    printf("\nOs vertices %d e %d nao sao Adjacentes\n", V1, V2);     
  } 
  else{
    printf("\nOs vertices %d e %d sao Adjacentes\n", V1, V2);
  }
}

//Funcao remove_Aresta --- Recebe como Parametros um Grafo(G), dois Vertices(VOrig e VDest).
void remove_Aresta(Grafo **G, int VOrig, int VDest){
  struct Vertices *ListaOrig, *ListaDest;
  struct Arestas *ArestaV1;

  if(existe_Grafo(*G)){
    ListaOrig = procura_Vertice(*G, VOrig);
    ListaDest = procura_Vertice(*G, VDest);
    if(ParDeVertice_Existe(ListaOrig, ListaDest)){
      ArestaV1 = procura_Aresta(*G, VOrig, VDest);
      if(ListaOrig->pontArestaFim != ListaOrig->pontArestaInicio){
        if(ArestaV1 != NULL){
          if(ArestaV1->antAresta != NULL && ArestaV1->proxAresta != NULL){
            ArestaV1->antAresta->proxAresta = ArestaV1->proxAresta;
            ArestaV1->proxAresta->antAresta = ArestaV1->antAresta; 
          }
          else{
            if(ArestaV1->antAresta == NULL){ 
              ListaOrig->pontArestaInicio = ArestaV1->proxAresta;
              ArestaV1->antAresta = NULL;
            }
            if(ArestaV1->proxAresta == NULL){ 
              ListaOrig->pontArestaFim = ArestaV1->antAresta;   
              ArestaV1->proxAresta = NULL; 
            }
          }
          free(ArestaV1);
          ArestaV1->proxAresta = NULL;
          ArestaV1->antAresta = NULL;
          ArestaV1 = NULL;
          (*G)->N_Arestas-= 1;
          ListaOrig->N_ArestasdoVertice-= 1;
        }
        //printf("\nA aresta entre %d e %d foi removida!!\n", VOrig, VDest);
        else{
          printf("\nERRO : Nao existe aresta entre %d e %d\n", VOrig, VDest);     
        }
      }
      else{
        free(ArestaV1);
        ArestaV1->proxAresta = NULL;
        ArestaV1->antAresta = NULL;
        ArestaV1 = NULL;
        ListaOrig->pontArestaInicio = NULL;
        ListaOrig->pontArestaFim = NULL;
        ListaOrig->N_ArestasdoVertice-= 1;
        (*G)->N_Arestas-= 1;
      }
    }
  }
}