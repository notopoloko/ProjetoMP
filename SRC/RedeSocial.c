#include <stdio.h>
#include "Grafo.h"

//Variavel global que representa uma constante.
int Const = 0;

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

//Funcao eh_amigo --- Recebe como Parametro dois usuarios(User e User2) e retorna um valor booleano.
bool eh_amigo(usuarios *User, usuarios *User2){
  struct amigos *pont;
  bool encontrado = false;

  pont = verifica_amizades(&(User));
  while(pont != NULL){
    if(pont->idAmigo == (User2)->id){  // Assertiva para verificar se dois usuarios são amigos.
      encontrado = true;
    }
    pont = pont->proxAmigo;
  }
  return encontrado;
}

//Funcao circulo_amigos --- Recebe como Parametro um grafo(G) e um usuario(User) e retorna uma lista de amigos de amigos.
amigos *circulo_amigosLista(Grafo **G, usuarios **User){
  struct usuarios *user2;
  struct amigos *pont, *pont2, *lista, *aux, *pont3;
  FILE *fp;

  pont = verifica_amizades(&(*User)); // cria uma lista de amigos de user.
  lista = NULL;
  while(pont != NULL){
    user2 = procura_nome((*G), pont->nomeAmigo); // Retorna um usuario(user2) partindo da lista de amigos de user.
    pont2 = verifica_amizades(&user2);  // Retorna uma lista de amigos de user2.
    while(pont2 != NULL){
      if((eh_amigo((*User), (procura_nome((*G), pont2->nomeAmigo))) == false)){  // Assertiva para verificar se um elemento da
                                                                                  // lista de amigos de user2 é amigo de user.
        if((*User)->id != pont2->idAmigo){  // Asertiva para que o proprio user não seja adicionado a nova lista de amigos de amigos de user.

          //Esse bloco de codigo é responsavel por criar uma lista de amigos de amigos de user.
          pont3 = (amigos*)malloc(sizeof(amigos));
          strcpy(pont3->nomeAmigo, pont2->nomeAmigo);
          pont3->idAmigo = pont2->idAmigo;
          if(lista == NULL){
            lista = pont3;
            lista->proxAmigo = NULL;
            lista->antAmigo = NULL;
          }else{
            aux = lista;
            while(aux->proxAmigo != NULL){
                aux = aux->proxAmigo;
            }
            aux->proxAmigo = pont3;
            pont3->antAmigo = aux;
            pont3->proxAmigo = NULL;
          }
          // Fim do bloco de criação de lista
        }
      }
      pont2 = pont2->proxAmigo;
    }
    pont = pont->proxAmigo;
  }
  //Esse bloco de codigo é responsavel por criar um arquivo com a lista de amigos de amigos de user.
  if(lista != NULL){ // Assertiva para verificar se a lista existe.
    pont = lista;
    fp = fopen("/home/aeron/proj4/ProjetoMP/LIB/CirculoDeAmigos.txt", "w+");
    if(fp == NULL) // Assertiva para verificar se o arquivo existe.
      printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
      fprintf(fp, "--------------------- AmigosDeAmigos de %s ---------------------------------\n", (*User)->nome);
      while(pont != NULL){
        fprintf(fp, "Id = %d\n", pont->idAmigo);
        fprintf(fp, "Nome = %s\n", pont->nomeAmigo);
        pont = pont->proxAmigo;
      }
      fprintf(fp, "---------------------------------------------------------------------------------\n\n");
    }
    fclose(fp);
  }

  return lista;
}

//Funcao salva_Arquivo --- Recebe como Parametros um Grafo(G) e armazena os dados do grafo em um arquivo.
FILE *salva_Arquivo(Grafo **G){
  FILE *fp; 
  usuarios *pont;
  amigos *pontAmigos;
  int i;

  if(existe_Grafo(*G)){ // Assertiva para verificar a existencia do Grafo
    fp = fopen("/home/aeron/proj4/ProjetoMP/LIB/BancodeDados.txt","w+");
    if (fp == NULL){
    // Verifica se existe um arquivo bancoDados.txt.
      printf("Impossível criar arquivo");
    }           
    else{
      for(i = 0; i < 26; i++){
        pont = ((*G)->listaAdj[i]);
        while(pont != NULL){
          fprintf(fp,"----------------------------------------------------------------------------\n");
          fprintf(fp,"Nome = %s\n", pont->nome);
          fprintf(fp,"CPF = %s\n", pont->cpf);
          fprintf(fp,"Cep = %s\n", pont->cep);
          fprintf(fp,"Cidade = %s\n", pont->cidade);
          fprintf(fp,"Numero de amigos = %d\n", pont->numeroAmigos);
          pontAmigos = verifica_amizades(&pont);
          if(pontAmigos == NULL){ // Assertiva que verifica se uma lista de amigos nao existe
              fprintf(fp, "Amigos = { }\n");
          }
          else{ 
            fprintf(fp, "Amigos = {");
            while(pontAmigos != NULL){
              fprintf(fp, " %s ", pontAmigos->nomeAmigo);
              pontAmigos = pontAmigos->proxAmigo;
            }
            fprintf(fp, "}\n");
          }
          pont = pont->prox;
        }
      }
    }
  }else{
    fp = fopen("/home/aeron/proj4/ProjetoMP/LIB/BancodeDados.txt","r");
  }
  fclose(fp);
  return fp;
}

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
Grafo *cria_Grafo(){
  struct Grafo *G;
  int i = 0;

  G = (Grafo *)malloc(sizeof(*G));
  G->N_usuarios = 0;
  G->listaT = NULL;
  G->N_transacoes = 0;
  while(i < 26){ //Laço para declarar todas hashtable como NULL.
    G->listaAdj[i] = NULL;
    i++;
  }
  return G;
}

//Funcao conclui_transacao --- Recebe como parametros um grafo(G), uma transação(Transacao) e um valor inteiro(aval).
// Retorna um usuário criador da transação.
usuarios *conclui_transacao(Grafo **G, transacoes **Transacao, int aval){
  struct usuarios *User;

  User = (*Transacao)->criador;
  if((User->avaliacao) != 0){ // Assertiva para testar se o usuario foi avaliado.
    aval = ((User->avaliacao) + aval) / 2;  // Se o usuario for avaliado, a nova avaliação é somada a a avaliação antiga.
                                            // A nova avaliaçao será uma media disso.
  }

  User->avaliacao = aval;
  exclui_transacao(&(*G), &(*Transacao));
  
  return User;
}

//Funcao exclui_transacao --- Recebe como parametros um grafo(G) e uma transação(Transacao).
void exclui_transacao(Grafo **G, transacoes **Transacao){
  struct transacoes *pont;

  pont = (*G)->listaT;
  while(pont != NULL){ // Verifica se existe transações e entra em uma laço que percorre toda a lista de transações.
    if(pont->idT == (*Transacao)->idT){   //Assertiva para verificar se Transacao equivale a um elemento da lista de transaçãoes.
      if(((*G)->listaT) == (*Transacao)){
        ((*G)->listaT) = NULL;
        free((*Transacao));
      }
      if((*Transacao)->proxT != NULL && (*Transacao)->antT == NULL){   //Assertiva para verificar se Transacao é o inicio da lista.
        ((*G)->listaT) = (*Transacao)->proxT;
        (*Transacao)->proxT->antT = ((*G)->listaT);
        free((*Transacao));
      }
      if((*Transacao)->proxT != NULL && (*Transacao)->antT != NULL){  //Assertiva para verificar se Transacao está entre outras transações.
        (*Transacao)->proxT->antT = (*Transacao)->antT;
        (*Transacao)->antT->proxT = (*Transacao)->proxT;
        free((*Transacao));
      }
      if((*Transacao)->proxT == NULL && (*Transacao)->antT != NULL){  //Assertiva para verificar se Transacao é o fim da lista.
        (*Transacao)->antT->proxT = NULL;
        free((*Transacao));
      }
      pont = NULL;
    }
    else{
      pont = pont->proxT;
    }
  }
  if((*G)->N_transacoes > 0){   //Assertiva para verificar se existe transações na lista.
    (*G)->N_transacoes--;
  }else{
    (*G)->N_transacoes = 0;
  }
}

//Funcao cria_transacao --- Recebe como parametros um grafo(G) e um usuario(user).
// Retorna uma transação criada.
transacoes *cria_transacao(Grafo **G, usuarios *user){
  struct transacoes *Tr, *pont;
  char nomeT[100], categoriaT[100];
  float val;
  FILE *fp; 
  
  if(existe_Grafo(*G)){ // Assertiva para verificar a existencia do Grafo
    Tr = (transacoes*)malloc(sizeof(transacoes));
    
    printf("Digite a categoria da transacao: \n");
    scanf(" %[^\n]", categoriaT);
    strcpy(Tr->categoria, categoriaT);
    printf("Digite o titulo da transacao: \n");
    scanf(" %[^\n]", nomeT);
    strcpy(Tr->objeto, nomeT);
    printf("Digite o o valor do objeto de transacao: \n");
    scanf(" %f", &val);
    Tr->idT = (*G)->N_transacoes;
    Tr->criador = user;
    Tr->valor = val;
    //Esse bloco de codigo é responsavel por adicionar uma transação à lista de transações.
    if((*G)->listaT == NULL){
      (*G)->listaT = Tr;
      (*G)->listaT->antT = NULL;
      (*G)->listaT->proxT = NULL;
    }else{
      pont = (*G)->listaT;
      while(pont->proxT != NULL){
        pont = pont->proxT;
      }
      Tr->antT = pont;
      Tr->proxT = NULL;
      pont->proxT = Tr;
    }
    //Fim do bloco de criação de transação
    (*G)->N_transacoes++;

    fp = fopen("Transacoes.txt", "a+");
    if(fp == NULL) // Verifica se o arquivo existe.
      printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
      fprintf(fp, "Id = %d\n", Tr->idT);
      fprintf(fp, "Nome = %s\n", Tr->objeto);
      fprintf(fp, "Categoria = %s\n", Tr->categoria);
      fprintf(fp, "Criador = %s\n", Tr->criador->nome);
      fprintf(fp, "Valor = %f\n", Tr->valor);
    }
    fclose(fp);
  }

  return Tr;
}

//Funcao cria_transacao --- Recebe como parametros um grafo(G) e um usuario(user).
// Retorna uma transação criada.
// Esta função é uma copia da função cria_transacao, ela foi utilizada nos testes do Gteste para agilizar o processo de testes.
transacoes *cria_transacaoAuto(Grafo **G, usuarios *user, char *nomeT, char *categoriaT, float val){
  struct transacoes *Tr, *pont;
  FILE *fp;

  if(existe_Grafo(*G)){ // Assertiva para verificar a existencia do Grafo
    Tr = (transacoes*)malloc(sizeof(transacoes));
    strcpy(Tr->categoria, categoriaT);
    strcpy(Tr->objeto, nomeT);
    Tr->idT = (*G)->N_transacoes;
    Tr->criador = user;
    Tr->valor = val;
    Tr->proxT = NULL;
    Tr->antT = NULL;
    if((*G)->listaT == NULL){
      (*G)->listaT = Tr;
      (*G)->listaT->antT = NULL;
      (*G)->listaT->proxT = NULL;
    }else{
      pont = (*G)->listaT;
      while(pont->proxT != NULL){
        pont = pont->proxT;
      }
      Tr->antT = pont;
      Tr->proxT = NULL;
      pont->proxT = Tr;
    }
    (*G)->N_transacoes++;


    fp = fopen("/home/aeron/proj4/ProjetoMP/LIB/Transacoes.txt", "a+");
    if(fp == NULL)
      printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
      fprintf(fp, "Id = %d\n", Tr->idT);
      fprintf(fp, "Nome = %s\n", Tr->objeto);
      fprintf(fp, "Categoria = %s\n", Tr->categoria);
      fprintf(fp, "Criador = %s\n", Tr->criador->nome);
      fprintf(fp, "Valor = %.2f\n\n", Tr->valor);
    }
    fclose(fp);
  }
  return Tr;
}

//Funcao procura_transacao --- Recebe como parametros um grafo(G) e uma string(categoriaT).
// Retorna uma transação.
transacoes *procura_categoria(Grafo **G, char *categoriaT){
  struct transacoes *Tr, *listadeTransacoes = NULL, *pont, *pont2;

  pont = (*G)->listaT;
  while(pont != NULL){
    if(strcmp(pont->categoria, categoriaT) == 0){ // Assertiva para verificar se uma categoria da lista de transações é igual à categoriaT.

      // Esse bloco de código é responsavel pela criação de uma lista de transações que tiverem a categoria igual à categoriaT.
      Tr = (transacoes*)malloc(sizeof(transacoes));
      Tr->idT = pont->idT;
      Tr->criador = pont->criador;
      Tr->valor = pont->valor;
      strcpy(Tr->categoria, pont->categoria);
      strcpy(Tr->objeto, pont->objeto);
      if(listadeTransacoes == NULL){
        listadeTransacoes = Tr;
        listadeTransacoes->proxT = NULL;
        listadeTransacoes->antT = NULL;
      }else{
        pont2 = listadeTransacoes;
        while(pont2->proxT != NULL){
          pont2 = pont2->proxT;
        }
        Tr->antT = pont;
        Tr->proxT = NULL;
        pont2->proxT = Tr;
      }
      // Fim do bloco
    }
    pont = pont->proxT;
  }

  return listadeTransacoes;
}

//Funcao procura_nomeT --- Recebe como Parametro um grafo(G), uma string(categoria) e uma string (nomeT).
//E retorna uma lista de transacoes.
transacoes *procura_nomeT(Grafo **G, char *categoriaT, char *nomeT){
  struct transacoes *listadeTransacoes = NULL, *pont, *Tr, *pont2;
  int i , j;

  pont = procura_categoria(&(*G), categoriaT);  // retorna uma lista de transações com categorias iguais à categoria enviada como parametro da função.
  while(pont != NULL){
    for(i = 0; (pont->objeto[i]); i++){
      if((pont->objeto[i]) == nomeT[0]){      // Assertiva que verifica se a primeira letra do objeto é igual a letra do nome mandado como parametro.
        j = 1;
        while(((pont->objeto[i+j]) == nomeT[j])){  // Assertiva que verifica se as letras seguintes do objeto são iguais a letra do nome mandado como parametro.
          j++;
        }
        if(j >= 3){ // Assertiva que verifica se o minimo de letras para uma busca por nome foi satisfeita.

         // Esse bloco de código é responsavel pela criação de uma lista de transações que tiverem o nome do objeto igual ao nomeT.
          Tr = (transacoes*)malloc(sizeof(transacoes));
          Tr->idT = pont->idT;
          Tr->criador = pont->criador;
          Tr->valor = pont->valor;
          strcpy(Tr->categoria, pont->categoria);
          strcpy(Tr->objeto, pont->objeto);
          if(listadeTransacoes == NULL){
            listadeTransacoes = Tr;
            listadeTransacoes->proxT = NULL;
            listadeTransacoes->antT = NULL;
          }else{
            pont2 = listadeTransacoes;
            while(pont2->proxT != NULL){
              pont2 = pont2->proxT;
            }
            Tr->antT = pont2;
            Tr->proxT = NULL;
            pont2->proxT = Tr;
          }
          //Fim do bloco
        }
      }
    }
    pont = pont->proxT;
  }

  return listadeTransacoes;
}

// Funcao procura_transacaoDeAmigos - Recebe um Grafo(G), um usuario (User) e uma string (Categoria) como parametros.
// Procura em uma lista de transações se existe a categoria enviada como parametro e depois pesquisa se algum de seus amigos é o criador dessa transação.
transacoes *procura_transacaoDeAmigos(Grafo **G, usuarios *User, char *categoriaT){
  struct transacoes *listadeTransacoes = NULL, *pont, *Tr, *pont2;
  struct amigos *amigoT;

  amigoT = verifica_amizades(&(User));
  pont = procura_categoria(&(*G), categoriaT);
  if(pont != NULL){ 
    while(pont != NULL){
      while(amigoT != NULL){
        if(pont->criador->id == amigoT->idAmigo){  // Assertiva que verifica se o criador de uma transações representa uma amigo de user.

          //Esse bloco é responsavel por criar uma lista de transações em que seus criadores sejam amigos de user.
          Tr = (transacoes*)malloc(sizeof(transacoes));
          Tr->idT = pont->idT;
          Tr->criador = pont->criador;
          Tr->valor = pont->valor;
          strcpy(Tr->categoria, pont->categoria);
          strcpy(Tr->objeto, pont->objeto);
          if(listadeTransacoes == NULL){
            listadeTransacoes = Tr;
            listadeTransacoes->proxT = NULL;
            listadeTransacoes->antT = NULL;
          }else{
            pont2 = listadeTransacoes;
            while(pont2->proxT != NULL){
              pont2 = pont2->proxT;
            }
            Tr->antT = pont2;
            Tr->proxT = NULL;
            pont2->proxT = Tr;
          }
          //Fim do bloco
        }
        amigoT = amigoT->proxAmigo;
      }
      pont = pont->proxT;
    }
  }else{
    printf("Categoria nao encontrada\n");
  }

  return listadeTransacoes;
}

//Funcao tamanho_Arquivo - Recebe como parametro uma string (nomeArquivo).
//Retorna um valor inteiro que representa o tamanho do arquivo.
int tamanho_Arquivo(char *nomeArquivo){
  FILE *fp= fopen(nomeArquivo, "r");
  int tamanho;

  if(fp == NULL){ // Verifica se o arquivo existe.
      return 0;
  }else{
    fseek(fp, 0, SEEK_END);
    tamanho = ftell(fp);
    fclose(fp);

    return tamanho;
  }
}

//Funcao existe_Grafo --- Recebe como Parametro um Grafo(G) e retorna um valor verdadeiro,caso o grafo exista, e falso, caso nao exista grafo.
bool existe_Grafo(Grafo *G){
  if(G->N_usuarios != 0){  // Verifica se o numero de usuarios é maior que 0.
    return true;
  }
  else{
    //printf("Nao existem usuarios na rede\n");
    return false;
  }
}

//Funcao exclui_usuario --- Recebe como Parametro um Grafo(G), libera o espaço de memoria alocado para um usuario.
void exclui_usuario(Grafo **G, usuarios **User){
  int letra;
  struct amigos *amigo, *pont;
  struct usuarios *User2;

  if((*User) != NULL){ //Assertiva para testar existencia de um usuario.
    letra = verifica_letra((*User)->nome[0]);
    amigo = (verifica_amizades(&(*User)));
    if(amigo != NULL){ //Assertiva para testar se um usuario tem amizades.
      pont = amigo;
      while(pont != NULL){
        User2 = procura_nome((*G), pont->nomeAmigo);
        excluir_amigo(&(*G), &(*User), &User2, 0);
        pont = pont->proxAmigo;
      }
      free(amigo);
    }
    if((*User)->ant != NULL && (*User)->prox != NULL){ // Verifica se o usuario a ser excluido está entre outros usuarios.
      (*User)->ant->prox = (*User)->prox;
      (*User)->prox->ant = (*User)->ant;
    }
    if((*User)->ant == NULL && (*User)->prox != NULL){ // Verifica se o usuario a ser excluido está no inicio da lista e se existe outros usuarios a sua frente.
      (*User)->prox->ant = NULL;
      ((*G)->listaAdj[letra]) = (*User)->prox;
    }
    if((*User)->ant == NULL && (*User)->prox == NULL){ // Verifica se o usuario a ser excluido está no inicio da lista e se não existe outros usuarios a sua frente.
      ((*G)->listaAdj[letra]) = NULL;
    }
    if((*User)->ant != NULL && (*User)->prox == NULL){ // Verifica se o usuario a ser excluido está no final da lista.
      (*User)->ant->prox = NULL;
    }
    free((*User));
    (*G)->N_usuarios--;
  }
} 

//Funcao verifica_amizades --- Recebe como Parametro um usuario(User).
//Retorna uma lista de amigos de User.
amigos *verifica_amizades(usuarios **User){
  int cont = 0, i = 0;
  struct amigos *listaAmigos, *pont, *pont2, *iterator;

  listaAmigos = NULL;
  if((*User)->numeroAmigos != 0){ // Assertiva para verificar se o usuario tem amigos.
    while(cont != ((*User)->numeroAmigos)){
      pont = ((*User)->Amigos[i]);
      while(pont != NULL){
        // Bloco de codigo responsavel por criar a lista de amigos de User.
        pont2 = (amigos*)malloc(sizeof(amigos));
        strcpy(pont2->nomeAmigo, pont->nomeAmigo);
        pont2->idAmigo = pont->idAmigo;
        if(cont == 0){
          listaAmigos = pont2;
          listaAmigos->proxAmigo = NULL;
          listaAmigos->antAmigo = NULL;
        }else{
          iterator = listaAmigos;
          while(iterator->proxAmigo != NULL){
            iterator = iterator->proxAmigo;
          }
          iterator->proxAmigo = pont2;
          pont2->antAmigo = iterator;
          pont2->proxAmigo = NULL;
        }
        // Fim do bloco
        pont = pont->proxAmigo;
        cont++;
      }
      i++;
    }
  }
  return listaAmigos;
}

//Funcao destroi_Grafo --- Recebe como Parametro um Grafo(G) e libera cada espaço de memoria alocado dinamicamente.
void destroi_Grafo(Grafo **G){
  int i;
  FILE *fp;
  struct usuarios *pont;

  if(existe_Grafo(*G)){ // Verifica se o Grafo existe.
    for(i = 0; i < 26; i++){
      pont = (*G)->listaAdj[i];
      while(pont != NULL){
        exclui_usuario(&(*G), &(pont));
        pont = pont->prox;
      }
    }
    fp = fopen("/home/aeron/proj4/ProjetoMP/LIB/BancodeDados.txt","w");
    fclose(fp);
    free(*G);
    cria_Grafo();
  }
}
 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G){
  int i = 0;
  struct usuarios *pont;

  if(G->N_usuarios > 0){
    printf("Numero de usuarios = %d\n", G->N_usuarios);
    while(i < 26){
      if((G->listaAdj[i]) != NULL){
        printf("\n[%c] ->\n", ('A'+i));
        pont = G->listaAdj[i];
        while(pont != NULL){
          printf("        %s (%d)\n", pont->nome, pont->id);
          imprime_amigos(pont);
          pont = pont->prox;
        }
      }
      else{
        printf("\n[%c] -> Esta vazio\n", ('A'+i));
      }
      i++;
    }
  }else{
    printf("Rede Social sem usuarios\n");
  }
}

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_amigos(usuarios *User){
  amigos *pontAmigos;

  pontAmigos = verifica_amizades(&(User));
  if(pontAmigos == NULL){
      printf("Amigos %s = { }\n", (User)->nome);
  }
  else{
    printf("Amigos %s = {", (User)->nome);
    while(pontAmigos != NULL){
      printf(" %s  (%d)", pontAmigos->nomeAmigo, pontAmigos->idAmigo);
      pontAmigos = pontAmigos->proxAmigo;
    }
    printf("}\n\n");
  }
}

//Funcao procura_nome --- Recebe como Parametros um Grafo(G) e um nome.
//Retorna um usuario ou NULL caso não encontre o usuario.
usuarios *procura_nome(Grafo *G, char *nom){
  struct usuarios *User, *user1;
  bool encontrado = false;
  int letra;

  letra = verifica_letra(nom[0]);
  User = ((G->listaAdj[letra]));
  while(User != NULL){
    if(strcmp(nom, User->nome) == 0){
      encontrado = true;
      user1 = User;
    }
    User = User->prox;
  }
  if(encontrado){
    //printf("Usuario %s encontrado!\n", user1->nome);
    return user1;
  }
  else{
   //printf("\nUsuario %s Nao Encontrado!!\n", nom);
    return NULL;
  }
}

//Funcao procura_usuario --- Recebe como Parametros um Grafo(G).
//Retorna um usuario ou NULL caso não encontre o usuario.
usuarios *procura_usuario(Grafo *G){
  struct usuarios *User, *user1;
  bool encontrado = false;
  char nom[100];
  int letra;

  printf("Digite o nome do usuario:\n");
  getchar();
  scanf(" %[^\n]", nom);

  letra = verifica_letra(nom[0]);
  User = ((G->listaAdj[letra]));
  while(User != NULL){
    if(strcmp(nom, User->nome) == 0){
      encontrado = true;
      user1 = User;
    }
    User = User->prox;
  }
  if(encontrado){
    //printf("Usuario %s encontrado!\n", user1->nome);
    return user1;
  }
  else{
    //printf("\nUsuario %s Nao Encontrado!!\n", nom);
    return NULL;
  }
}

 //Funcao excluir_amigo --- Recebe como Parametros um Grafo(G), um usuario e um inteiro que serve como um marcador.
void excluir_amigo(Grafo **G, usuarios **User, usuarios **User1, int cons){
  int letra;
  struct amigos *pont;

  if((*User)->numeroAmigos != 0){
    letra = verifica_letra(((*User1)->nome[0]));
    pont = ((*User)->Amigos[letra]);
    while(pont != NULL){
      if(strcmp(pont->nomeAmigo, (*User1)->nome) == 0){   //Assertiva pro caso de Só um amigo.
        if(pont->proxAmigo == NULL && pont->antAmigo == NULL){
          free(((*User)->Amigos[letra]));
          ((*User)->Amigos[letra]) = NULL;
        }
        if(pont->antAmigo == NULL && pont->proxAmigo != NULL){       //Assertiva pro caso do amigo ser o primeiro da hashtable.
          ((*User)->Amigos[letra]) = pont->proxAmigo;
          pont->proxAmigo->antAmigo = NULL;
          free(pont);
        }
        if(pont->antAmigo != NULL && pont->proxAmigo != NULL){       //Assertiva pra um amigo entre outros amigos.
          pont->antAmigo->proxAmigo = pont->proxAmigo;
          pont->proxAmigo->antAmigo = pont->antAmigo;
          free(pont);
        }
        pont = NULL;
        (*User)->numeroAmigos--;
      }
      else{
        pont = pont->proxAmigo;
      }
    }
    if(cons == 0){ // cons representa uma constante. Quando cons = 0 significa que é o primeiro acesso a esta função.
      excluir_amigo(&(*G), &(*User1), &(*User), 1);
    }
  }else{
      printf("Usuario sem amizades para exclusão\n");
  }
}

 //Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G), dois usuarios e um inteiro que serve como um marcador.
void adiciona_amigos(Grafo **G, usuarios **User1, usuarios **User2, int cons){
  int letra;
  struct amigos *pont, *amigo;

  if((*User1)->id != (*User2)->id){  // Assertiva responsavel por não deixar que um usuário se auto adicione como amigo.
    // Bloco de codigo responsavel por adicionar elementos a hashtable de amigos.
    amigo = (amigos*)malloc(sizeof(amigos));
    amigo->idAmigo = (*User2)->id;
    strcpy(amigo->nomeAmigo, (*User2)->nome);
    letra = verifica_letra(((*User2)->nome[0]));
    if(((*User1)->Amigos[letra]) == NULL){ // Verifica se a lista está vazia.
      ((*User1)->Amigos[letra]) = (amigo);
      ((*User1)->Amigos[letra])->proxAmigo = NULL;
      ((*User1)->Amigos[letra])->antAmigo = NULL;
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
    // Fim do bloco.
    (*User1)->numeroAmigos++;
    if(cons == 0){  // cons representa uma constante. Quando cons = 0 significa que é o primeiro acesso a esta função.
      adiciona_amigos(&(*G), &(*User2), &(*User1), 1);
    }
  }else{
    printf("O usuario nao pode se adicionar como amigo\n");
  }
}

// Funcao Verifica_letra --- Recebe como parametro um caracter.
// Retorna -1, caso o caracter não represente uma  letra, ou um valor de 0 a 26 caso contrario.
int verifica_letra(char nome){
  int cont = 0, letra = -1;

  while(cont < 26){  // 26 representa o total de letras do alfabeto.
    if((nome == ('A'+cont)) || ((nome) == ('a'+cont))){  // Verifica se o caracter é igual uma letra mais o contador.
      letra = cont;
      cont = 26;
    }
    else{
      cont++;
    }
  }
  return letra;
}

// Funcao edita_nome --- Recebe como parametros um grafo(G), um usuario (user) e uma string(nom).
// Retorna um usuario com a modificação feita.
usuarios *edita_nome(Grafo **G, usuarios **user, char *nom){
  struct usuarios *userAux2, *userAux;
  struct amigos *Aux;

  userAux = cria_pessoaAuto(&(*G), nom, ((*user)->cpf), ((*user)->cep), ((*user)->cidade));
  userAux->id = (*user)->id;
  Aux = verifica_amizades(&(*user));
  while(Aux != NULL){
    userAux2 = procura_nome((*G), Aux->nomeAmigo);
    adiciona_amigos(&(*G), &userAux2, &userAux, 0);
    Aux = Aux->proxAmigo;
  }
  exclui_usuario(&(*G), &(*user));

  return userAux;
}

// Funcao edita_cidade --- Recebe como parametros um grafo(G), um usuario (user) e uma string(cidade).
// Retorna um usuario com a modificação feita.
usuarios *edita_cidade(Grafo **G, usuarios **user, char *cidade){
  strcpy((*user)->cidade, cidade);

  return (*user);
}

// Funcao edita_cep --- Recebe como parametros um grafo(G), um usuario (user) e uma string(cep).
// Retorna um usuario com a modificação feita.
usuarios *edita_cep(Grafo **G, usuarios **user, char *cep){
  strcpy((*user)->cep, cep);

  return (*user);
}

// Funcao edita_cpf --- Recebe como parametros um grafo(G), um usuario (user) e uma string(cpf).
// Retorna um usuario com a modificação feita.
usuarios *edita_cpf(Grafo **G, usuarios **user, char *cpf){
  strcpy((*user)->cpf, cpf);

  return (*user);
}

// Funcao editar_pessoa --- Recebe como parametro um grafo(G).
// Retorna um usuario com as modificações feitas.
usuarios *editar_pessoa(Grafo **G){
  system("cls || clear");
  char nom[100], cidade[30], cep[20], cpf[12];
  int opc = -1, opc1 = -1;
  struct usuarios *user = NULL, *user2 = NULL, *userAux2, *userAux;
  struct amigos *Aux;

  while(user == NULL){
    getchar();
    printf("\nAlterar usuario\n\n");
    printf("Digite o nome do usuario:\n");
    scanf(" %[^\n]", nom);
    user = procura_nome((*G), nom);
  }
  while(opc != 0){
    printf(" -------------------------------------------------------\n");
    printf("              Alterar configuracoes de %s               \n", user->nome);
    printf("|1 - Nome                                               | \n");
    printf("|2 - Cidade                                             | \n");
    printf("|3 - Cep                                                | \n");
    printf("|4 - Cpf                                                | \n");
    printf("|5 - Transacoes                                         | \n");
    printf("|6 - Amizades                                           | \n");
    printf("|7 - Excluir conta                                      | \n");
    printf("|0 - Sair                                               | \n");
    printf(" -------------------------------------------------------\n");
    scanf(" %d", &opc);
    switch(opc){
      case(1): // Case que representa a alteração de nome do usuario.
      printf("Digite o novo nome: ");
      scanf(" %[^\n]", nom);
      userAux = cria_pessoaAuto(&(*G), nom, (user->cpf), (user->cep), (user->cidade));
      userAux->id = user->id;
      Aux = verifica_amizades(&user);
      while(Aux != NULL){
        userAux2 = procura_nome((*G), Aux->nomeAmigo);
        adiciona_amigos(&(*G), &userAux2, &userAux, 0);
        Aux = Aux->proxAmigo;
      }
      exclui_usuario(&(*G), &(user));
      opc = 0;
      //printf("Nome Alterado!!!\n");
      break;

      case(2): // Case que representa a alteração da cidade do usuario.
      printf("Digite a nova cidade: ");
      scanf(" %[^\n]", cidade);
      strcpy(user->cidade, cidade);
      //printf("Cidade Alterada!!!\n");
      opc = 0;
      break;

      case(3): // Case que representa a alteração de cep do usuario.
      printf("Digite o novo cep: ");
      scanf(" %[^\n]", cep);
      strcpy(user->cep, cep);
      //printf("Cep Alterado!!!\n");
      opc = 0;
      break;

      case(4): // Case que representa a alteração de cpf do usuario.
      printf("Digite o novo cpf: ");
      scanf(" %[^\n]", cpf);
      strcpy(user->cpf, cpf);
      //printf("Cpf Alterado!!!\n");
      opc = 0;
      break;

      case(5):
      imprime_amigos(user);
      opc = 0;
      while(opc1 != 0){
        printf(" -------------------------------------------------------\n");
        printf("|                 Escolha uma acao                      | \n");
        printf("|1 - Adiciona amigo                                     | \n");
        printf("|2 - Exclui amigo                                       | \n");
        printf("|0 - Sair                                               | \n");
        printf(" -------------------------------------------------------\n");
        scanf("%d", &opc1);
        if(opc1 != 0){
          system("cls || clear");
          imprime_amigos(user);
          user2 = procura_usuario((*G));
          if(user2 != NULL){ // Verifica se user2 existe.
            if(user->id != user2->id){ // verifica se user e user2 é o mesmo usuario.
              if(opc1 == 1){  // if que representa a adição de um amigo.
                  adiciona_amigos(&(*G), &user, &user2, 0);
                  printf("Amigo adicionado!!\n");
                  imprime_amigos(user);
              }
              if(opc1 == 2){  // if que representa a exclusão de um amigo.
                  excluir_amigo(&(*G), &user, &user2, 0);
                  imprime_amigos(user);
              }
            }else{
              system("clear || cls");
            }
          }else{
            printf("\nUsuario nao encontrado!!\n");
            imprime_amigos(user);
          }
        }
      }
      break;
      case(6): // Case que representa a exclusão de um usuario.
        exclui_usuario(&(*G), &user);
        opc = 0;
      break;
      case(7): // Case que representa a criação de uma transação.
        cria_transacao(&(*G), user);
        opc = 0;
      break;

    }
  }
  system("cls || clear");
  return user;
}

// Funcao cria_pessoa --- Recebe como parametro um grafo(G).
// Retorna o usuario criado.
usuarios *cria_pessoa(Grafo **G){
  char nom[100], cidade[30], cep[20], cpf[12];
  int cont = 0, letra;
  struct usuarios *pont, *user;
  
  // Bloco de codigos responsavel pela adição de um usuario ao grafo.
  user = (usuarios*)malloc(sizeof(usuarios));
  printf("Digite o seu nome: ");
  user->id = (*G)->N_usuarios;
  scanf(" %[^\n]", nom);
  getchar();
  strcpy(user->nome, nom);
  printf("Digite o seu cpf: ");
  scanf(" %[^\n]", cpf);
  strcpy(user->cpf, cpf);
  printf("Digite a sua cidade: ");
  scanf(" %[^\n]", cidade);
  strcpy(user->cidade, cidade);
  printf("Digite o seu cep: ");
  scanf(" %[^\n]", cep);
  strcpy(user->cep, cep);
  user->avaliacao = 0;


  letra = verifica_letra(nom[0]);
  if(((*G)->listaAdj[letra]) == NULL){  // Verifica se a lista de usuario está vazia.
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
  // Fim do bloco.
  (*G)->N_usuarios++;

  return user;
}

// Funcao cria_pessoaAuto --- Recebe como parametros um grafo(G) e quatro strings(nom, cpf, cep, cidade).
// Retorna o usuario criado.
// Copia da função cria_pessoa com objetivo de facilitar a execução de testes com Gteste.
usuarios *cria_pessoaAuto(Grafo **G, char *nom, char *cpf, char *cep, char *cidade){
  int cont = 0, letra;
  struct usuarios *pont, *user;

  // Bloco de codigos responsavel pela adição de um usuario ao grafo.
  user = (usuarios*)malloc(sizeof(usuarios));
  user->id = (*G)->N_usuarios;
  strcpy(user->nome, nom);
  strcpy(user->cpf, cpf);
  strcpy(user->cidade, cidade);
  strcpy(user->cep, cep);
  user->avaliacao = 0;


  letra = verifica_letra(nom[0]);
  if(((*G)->listaAdj[letra]) == NULL){  // Verifica se a lista de usuario está vazia.
    ((*G)->listaAdj[letra]) = user;

    for (cont = 0; cont < 26; ++cont){
      ((*G)->listaAdj[letra])->Amigos[cont] = NULL;
    }
    ((*G)->listaAdj[letra])->ant = NULL;
    ((*G)->listaAdj[letra])->prox = NULL;
    (((*G)->listaAdj[letra])->numeroAmigos) = 0;
  }
  else{  // Verifica se a lista de usuario não está vazia.
    pont = ((*G)->listaAdj[letra]);
    while(pont->prox != NULL){
      pont = pont->prox;
    }
    pont->prox = (user);
    ((user)->ant) = pont;
    ((user)->prox) = NULL;
    (user)->numeroAmigos = 0;
  }
  // Fim do bloco.
  (*G)->N_usuarios++;

  return user;
}

// Funcao menu --- Recebe como parametros um grafo (G).
void menu(Grafo **G){
  struct usuarios *user1, *user2;
  int opc = -1;

  while(opc != 0){
    system("clear || cls");
    printf(" -------------------------------------------------------\n");
    printf("|                           MENU                        | \n");
    printf("|1 - Criar pessoa                                       | \n");
    printf("|2 - Editar pessoa                                      | \n");
    printf("|3 - Imprimir rede social                               | \n");
    printf("|4 - Destroi rede social                                | \n");
    printf("|0 - Sair                                               | \n");
    printf(" -------------------------------------------------------\n");
    scanf(" %d", &opc);
    switch(opc){
      case(1): // Case para criação de usuario.
      cria_pessoa(&(*G));
      break;

      case(2): // Case para edição de usuario.
      editar_pessoa(&(*G));
      break;

      case(3):  // Case para impressão de grafo.
      imprime_Grafo((*G));
      break;

      case(4):  // Case para destruição de grafo.
      destroi_Grafo(&(*G));
      break;
    }
  }
  salva_Arquivo(&(*G)); // Criação do arquivo BancoDeDados que contem todas as informações do grafo.
}