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
    if(pont->idAmigo == (User2)->id){
      encontrado = true;
    }
    pont = pont->proxAmigo;
  }
  return encontrado;
}

//Funcao circulo_amigos --- Recebe como Parametro um usuario(User) e retorna uma lista de amigos de amigos.
amigos *circulo_amigosLista(Grafo **G, usuarios **User){
  struct usuarios *user2;
  struct amigos *pont, *pont2, *lista, *aux, *pont3;

  pont = verifica_amizades(&(*User));
  lista = NULL;
  while(pont != NULL){
    user2 = procura_nome((*G), pont->nomeAmigo);
    pont2 = verifica_amizades(&user2);  
    while(pont2 != NULL){
      if((eh_amigo((*User), (procura_nome((*G), pont2->nomeAmigo))) == false)){
        if((*User)->id != pont2->idAmigo){
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
        }
      }
      pont2 = pont2->proxAmigo;
    }
    pont = pont->proxAmigo;
  }
  return lista;
}

//Funcao salva_Arquivo --- Recebe como Parametros um Grafo(G) e armazena os dados do grafo em um arquivo.
FILE *salva_Arquivo(Grafo **G){
  FILE *fp; 
  usuarios *pont;
  amigos *pontAmigos;
  int i;

  if(existe_Grafo(*G)){
    fp = fopen("BancodeDados.txt","w+");
    if (fp == NULL){
    // Verifica se existe um arquivo bancoDados.txt.
      printf("Impossível criar arquivo");
    }           
    else{
      for(i = 0; i < 26; i++){
        pont = ((*G)->listaAdj[i]);
        while(pont != NULL){
          //fprintf(fp,"----------------------------------------------------------------------------\n");
          fprintf(fp,"Nome = %s\n", pont->nome);
          //fprintf(fp,"CPF = %s", pont->cpf);
          //fprintf(fp,"Cep = %s", pont->cep);
          //fprintf(fp,"Cidade = %s", pont->cidade);
          //fprintf(fp,"Numero de amigos = %d", pont->numeroAmigos);
          pontAmigos = verifica_amizades(&pont);
          if(pontAmigos == NULL){
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
    fp = fopen("BancodeDados.txt","r");
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
  while(i < 26){
    G->listaAdj[i] = NULL;
    i++;
  }
  return G;
}

transacoes *cria_transacao(Grafo **G, usuarios *user){
  struct transacoes *Tr, *pont;
  char nomeT[100];
  
  Tr = (transacoes*)malloc(sizeof(transacoes));
  
  printf("Digite o nome da transacao: \n");
  scanf(" %[^\n]", nomeT);
  strcpy(Tr->objeto, nomeT);
  Tr->idT = (*G)->N_transacoes;
  Tr->criador = user;
  if((*G)->N_transacoes == 0){
    (*G)->listaT = Tr;
    (*G)->listaT->antT = NULL;
    (*G)->listaT->proxT = NULL;
  }else{
    pont = (*G)->listaT;
    while(pont->proxT != NULL){
      pont = pont->proxT;
    }
    pont->proxT = Tr;
    Tr->antT = pont;
    Tr->proxT = NULL;
  }
  (*G)->N_transacoes++;
}

int tamanho_Arquivo(char *nomeArquivo){
  FILE *fp= fopen(nomeArquivo, "r");
  int tamanho;

  if(fp == NULL){
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
  if(G->N_usuarios != 0){
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
    if((*User)->ant != NULL && (*User)->prox != NULL){
      (*User)->ant->prox = (*User)->prox;
      (*User)->prox->ant = (*User)->ant;
    }
    if((*User)->ant == NULL && (*User)->prox != NULL){
      (*User)->prox->ant = NULL;
      ((*G)->listaAdj[letra]) = (*User)->prox;
    }
    if((*User)->ant == NULL && (*User)->prox == NULL){
      ((*G)->listaAdj[letra]) = NULL;
    }
    if((*User)->ant != NULL && (*User)->prox == NULL){
      (*User)->ant->prox = NULL;
    }
    free((*User));
    (*G)->N_usuarios--;
  }
} 

//Funcao verifica_amizades --- Recebe como Parametro um usuario(User) e retorna uma lista de amigos de User.
amigos *verifica_amizades(usuarios **User){
  int cont = 0, i = 0;
  struct amigos *listaAmigos, *pont, *pont2, *iterator;

  listaAmigos = NULL;
  if((*User)->numeroAmigos != 0){
    while(cont != ((*User)->numeroAmigos)){
      pont = ((*User)->Amigos[i]);
      while(pont != NULL){
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

  if(existe_Grafo(*G)){
    for(i = 0; i < 26; i++){
      pont = (*G)->listaAdj[i];
      while(pont != NULL){
        exclui_usuario(&(*G), &(pont));
        pont = pont->prox;
      }
    }
    fp = fopen("BancodeDados.txt","w+");
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
       // printf("\nUsuario %s Nao Encontrado!!\n", nom);
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
      //Assertiva pro caso de Só um amigo.
      if(strcmp(pont->nomeAmigo, (*User1)->nome) == 0){
        if(pont->proxAmigo == NULL && pont->antAmigo == NULL){
          free(((*User)->Amigos[letra]));
          ((*User)->Amigos[letra]) = NULL;
        }
        //Assertiva pro caso do amigo ser o primeiro da hashtable.
        if(pont->antAmigo == NULL && pont->proxAmigo != NULL){
          ((*User)->Amigos[letra]) = pont->proxAmigo;
          pont->proxAmigo->antAmigo = NULL;
          free(pont);
        }
        //Assertiva pra um amigo entre outros amigos.
        if(pont->antAmigo != NULL && pont->proxAmigo != NULL){
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
    if(cons == 0){
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

  if((*User1)->id != (*User2)->id){
    amigo = (amigos*)malloc(sizeof(amigos));
    amigo->idAmigo = (*User2)->id;
    strcpy(amigo->nomeAmigo, (*User2)->nome);

    letra = verifica_letra(((*User2)->nome[0]));
    if(((*User1)->Amigos[letra]) == NULL){
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
    (*User1)->numeroAmigos++;
    if(cons == 0){
      adiciona_amigos(&(*G), &(*User2), &(*User1), 1);
    }
  }else{
    printf("O usuario nao pode se adicionar como amigo\n");
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

usuarios *testaUsuario(usuarios *User){
  if(User == NULL){
    printf("Usuario nao encontrado\n");
  }else{
    printf("Usuario %s encontrado!\n", User->nome);
  }

  return User;
}

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

usuarios *edita_cidade(Grafo **G, usuarios **user, char *cidade){
  strcpy((*user)->cidade, cidade);

  return (*user);
}

usuarios *edita_cep(Grafo **G, usuarios **user, char *cep){
  strcpy((*user)->cep, cep);

  return (*user);
}

usuarios *edita_cpf(Grafo **G, usuarios **user, char *cpf){
  strcpy((*user)->cpf, cpf);

  return (*user);
}

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
      case(1):
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
      break;

      case(2):
      printf("Digite a nova cidade: ");
      scanf(" %[^\n]", cidade);
      strcpy(user->cidade, cidade);
      opc = 0;
      break;

      case(3):
      printf("Digite o novo cep: ");
      scanf(" %[^\n]", cep);
      strcpy(user->cep, cep);
      opc = 0;
      break;

      case(4):
      printf("Digite o novo cpf: ");
      scanf(" %[^\n]", cpf);
      strcpy(user->cpf, cpf);
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
          if(user2 != NULL){
            if(user->id != user2->id){
              if(opc1 == 1){
                  adiciona_amigos(&(*G), &user, &user2, 0);
                  printf("Amigo adicionado!!\n");
                  imprime_amigos(user);
              }
              if(opc1 == 2){
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
      case(6):
        exclui_usuario(&(*G), &user);
        opc = 0;
      break;
      case(7):
        cria_transacao(&(*G), user);
        opc = 0;
      break;

    }
  }
  system("cls || clear");
  return user;
}

usuarios *cria_pessoa(Grafo **G){
  char nom[100], cidade[30], cep[20], cpf[12];
  int cont = 0, letra;
  struct usuarios *pont, *user;

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

usuarios *cria_pessoaAuto(Grafo **G, char *nom, char *cpf, char *cep, char *cidade){
  int cont = 0, letra;
  struct usuarios *pont, *user;

  user = (usuarios*)malloc(sizeof(usuarios));
  user->id = (*G)->N_usuarios;
  strcpy(user->nome, nom);
  strcpy(user->cpf, cpf);
  strcpy(user->cidade, cidade);
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
      case(1):
      cria_pessoa(&(*G));
      break;

      case(2):
      editar_pessoa(&(*G));
      break;

      case(3):
      imprime_Grafo((*G));
      break;

      case(4):
      destroi_Grafo(&(*G));
      break;
    }
  }
  salva_Arquivo(&(*G));
}