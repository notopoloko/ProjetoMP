#include <Grafo.h>

int Const = 0;

char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

amigos *circulo_amigosLista(Grafo **G, usuarios **User){
  struct usuarios *user2;
  struct amigos *pont, *pont2, *lista, *aux, *pont3;
  FILE *fp;

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

  if(lista != NULL){
    pont = lista;
    fp = fopen("../Allusers/CirculoDeAmigos.txt", "w+");
    if(fp == NULL)
      printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
      fprintf(fp, "--------------------- Amigos de Amigos de %s ---------------------------------\n", (*User)->nome);
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

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
void salva_Arquivo(Grafo *G){//checada
  FILE *fp;
  usuarios *pont;
  amigos *pontAmigos;
  int i;

  if(existe_Grafo(G)){
    fp = fopen("../Allusers/BancodeDados.txt","w");
    if (fp == NULL){
    // Verifica se existe um arquivo bancoDados.txt.
      printf("Impossível criar arquivo");
    }           
    else{
      for(i = 0; i < 26; i++){
        pont = G->listaAdj[i];
        while(pont != NULL){
          fprintf(fp,"----------------------------------------------------------------------------\n");
          fprintf(fp,"ID = %d\n", pont->id);
          fprintf(fp,"NOME = %s\n", pont->nome);
          fprintf(fp,"CIDADE = %s\n", pont->cidade);
          fprintf(fp,"ENDERECO = %s\n", pont->endereco);
          fprintf(fp,"CPF = %s\n", pont->cpf);
          fprintf(fp,"CEP = %s\n", pont->cep);
          fprintf(fp,"EMAIL = %s\n", pont->email);
          fprintf(fp,"SENHA = %s\n", pont->senha);
          fprintf(fp,"DESCRICAO = %s\n", pont->descricao);
          fprintf(fp,"NUMERO DE AMIGOS = %d\n", pont->numeroAmigos);
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
    fclose(fp);
  }
}

//ERRO = -1 O erro em todo este programa recebe o valor de -1.

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
Grafo *cria_Grafo(){//checada
  struct Grafo *G;
  int i = 0;

  G = (Grafo *)malloc(sizeof(Grafo));
  G->N_usuarios = 0;
  while(i < 26){
    G->listaAdj[i] = NULL;
    i++;
  }
  return G;
}

/*transacoes *cria_transacao(Grafo **G, usuarios *user){
  struct transacoes *Tr, *pont;
  char nomeT[100], categoriaT[100];
  float val;
  FILE *fp; 
  
  if(existe_Grafo(*G)){
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

    fp = fopen("Transacoes.txt", "a+");
    if(fp == NULL)
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
}*/

transacoes *cria_transacaoAuto(Grafo **G, usuarios *user, char *nomeT, char *categoriaT, float val){
  struct transacoes *Tr, *pont;
  FILE *fp;

  if(existe_Grafo(*G)){
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


    fp = fopen("../Allusers/Transacoes.txt", "a+");
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

transacoes *procura_categoria(Grafo **G, char *categoriaT){
  struct transacoes *Tr, *listadeTransacoes = NULL, *pont, *pont2;

  pont = (*G)->listaT;
  while(pont != NULL){
    if(strcmp(pont->categoria, categoriaT) == 0){
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

  pont = procura_categoria(&(*G), categoriaT);
  while(pont != NULL){
    for(i = 0; (pont->objeto[i]); i++){
      if((pont->objeto[i]) == nomeT[0]){      // Assertiva que verifica se a primeira letra do objeto é igual a letra do nome mandado como parametro.
        j = 1;
        while(((pont->objeto[i+j]) == nomeT[j])){  // Assertiva que verifica se as letras seguintes do objeto são iguais a letra do nome mandado como parametro.
          j++;
        }
        if(j >= 3){ // Assertiva que verifica se o minimo de letras para uma busca por nome foi satisfeita.
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
        }
      }
    }
    pont = pont->proxT;
    i = 0;
  }
  pont = listadeTransacoes;
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
        if(pont->criador->id == amigoT->idAmigo){
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

void exclui_transacao(Grafo **G, transacoes **Transacao){
  struct transacoes *pont;

  pont = (*G)->listaT;
  while(pont != NULL){
    if(pont->idT == (*Transacao)->idT){
      if(((*G)->listaT) == (*Transacao)){
        ((*G)->listaT) = NULL;
        free((*Transacao));
      }
      if((*Transacao)->proxT != NULL && (*Transacao)->antT == NULL){
        ((*G)->listaT) = (*Transacao)->proxT;
        (*Transacao)->proxT->antT = ((*G)->listaT);
        free((*Transacao));
      }
      if((*Transacao)->proxT != NULL && (*Transacao)->antT != NULL){
        (*Transacao)->proxT->antT = (*Transacao)->antT;
        (*Transacao)->antT->proxT = (*Transacao)->proxT;
        free((*Transacao));
      }
      if((*Transacao)->proxT == NULL && (*Transacao)->antT != NULL){
        (*Transacao)->antT->proxT = NULL;
        free((*Transacao));
      }
      pont = NULL;
    }
    else{
      pont = pont->proxT;
    }
  }
  if((*G)->N_transacoes > 0){
    (*G)->N_transacoes--;
  }else{
    (*G)->N_transacoes = 0;
  }
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
      free((*User));
      (*User) = NULL;
    }
    else{
      if((*User)->ant == NULL && (*User)->prox != NULL){
        (*User)->prox->ant = NULL;
        ((*G)->listaAdj[letra]) = (*User)->prox;
        free((*User));
      }
      if((*User)->ant == NULL && (*User)->prox == NULL){
        ((*G)->listaAdj[letra]) = NULL;
        free((*User));
      }
    }
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

  if(existe_Grafo(*G)){
    for(i = 0; i < 26; i++){
      while((*G)->listaAdj[i] != NULL){
        exclui_usuario(&(*G), &((*G)->listaAdj[i]));
      }
    }
    (*G)->N_usuarios = 0;
    free(*G);
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
          printf("        %s\n", pont->nome);
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
      printf(" %s ", pontAmigos->nomeAmigo);
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
      break;
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

 //Funcao excluir_amigo --- Recebe como Parametros um Grafo(G) e um usuario.
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

 //Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G) e dois usuarios.
void adiciona_amigos(Grafo **G, usuarios **User1, usuarios **User2, int cons){
  int letra;
  struct amigos *pont, *amigo;

  amigo = (amigos*)malloc(sizeof(amigos));
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

/*usuarios *editar_pessoa(Grafo **G){
  system("cls || clear");
  char nom[100], cidade[30], cep[20], cpf[12];
  int opc = -1, opc1 = -1;
  struct usuarios *user = NULL, *user2 = NULL;

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
    printf("|5 - Amizades                                           | \n");
    printf("|6 - Excluir conta                                      | \n");
    printf("|0 - Sair                                               | \n");
    printf(" -------------------------------------------------------\n");
    scanf(" %d", &opc);
    switch(opc){
      case(1):
      printf("Digite o novo nome: ");
      scanf(" %[^\n]", nom);
      strcpy(((user)->nome), nom);
      printf("%s\n", user->nome);
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
      strcpy(user->nome, nom);
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

    }
  }
  system("cls || clear");
  return user;
}*/


int cria_pessoa(Grafo *G, usuarios *user){//checada
  int cont = 0, letra;
  usuarios *pont;

  user->id = G->N_usuarios;

  letra = verifica_letra(user->nome[0]);
  if((G->listaAdj[letra]) == NULL){

    (G->listaAdj[letra]) = user;

    for (cont = 0; cont < 26; ++cont){
      (G->listaAdj[letra])->Amigos[cont] = NULL;
    }
    (G->listaAdj[letra])->ant = NULL;
    (G->listaAdj[letra])->prox = NULL;
    (G->listaAdj[letra])->numeroAmigos = 0;
  }else{
    pont = (G->listaAdj[letra]);
    while(pont->prox != NULL){
      pont = pont->prox;
    }
    pont->prox = user;
    user->ant = pont;
    user->prox = NULL;
    user->numeroAmigos = 0;
  }
  G->N_usuarios++;

  return 0;
}

/*void menu(Grafo **G){
  struct usuarios *user1, *user2;
  int opc = -1;

  while(opc != 0){
    printf(" -------------------------------------------------------\n");
    printf("|                           MENU                        | \n");
    printf("|1 - Criar pessoa                                       | \n");
    printf("|2 - Editar pessoa                                      | \n");
    printf("|3 - Adicionar amigo                                    | \n");
    printf("|4 - Imprimir rede social                               | \n");
    printf("|5 - Destroi rede social                                | \n");
    printf("|0 - Sair                                               | \n");
    printf(" -------------------------------------------------------\n");
    scanf(" %d", &opc);
    if(opc < 0 || opc > 4){
      printf("Valor invalido\n");
    }

    switch(opc){
      case(1):
      cria_pessoa(&(*G));
      break;

      case(2):
      editar_pessoa(&(*G));
      break;

      case(3):
      user1 = procura_usuario((*G));
      user2 = procura_usuario((*G));
      if(user1 != NULL && user2 != NULL){
        adiciona_amigos(&(*G), &user1, &user2, Const);
      }else{
        printf("Usuarios invalidos\n");
      }
      break;

      case(4):
      imprime_Grafo((*G));
      break;

      case(5):
      destroi_Grafo(&(*G));
      break;
    }
  }
  salva_Arquivo(&(*G));
}*/

int cria_pessoa_interface(Grafo *G, char *nom){
  FIELD *field[9];
  FORM *my_form;
  int ch,i;
  char *nome,*cidade,*endereco,*cep,*cpf,*email,*senha,*descricao;
  usuarios *user;

  user = (usuarios *)malloc(sizeof(usuarios));
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr,true);

  init_pair(1,COLOR_WHITE, COLOR_BLUE);
  init_pair(2,COLOR_WHITE, COLOR_BLUE);

  field[0] = new_field(1,50,4,18,0,0);
  field[1] = new_field(1,50,6,18,0,0);
  field[2] = new_field(1,50,8,18,0,0);
  field[3] = new_field(1,20,10,18,0,0);
  field[4] = new_field(1,20,12,18,0,0);
  field[5] = new_field(1,50,14,18,0,0);
  field[6] = new_field(1,20,16,18,0,0);
  field[7] = new_field(4,50,18,18,0,0);

  field[8] = NULL;
  for(i=0;i<8;++i){
    set_field_fore(field[i],COLOR_PAIR(1));
    set_field_back(field[i],COLOR_PAIR(2));
    field_opts_off(field[i],O_AUTOSKIP);
  }
  field_opts_off(field[6],O_PUBLIC);
  my_form = new_form(field);
  form_opts_off(my_form, O_BS_OVERLOAD);
  post_form(my_form);
  refresh();
  mvprintw(LINES - 2, 0, "Use as setas para para trocar entre os campos. Para terminar digite ENTER. Pressione F2 para cancelar");
  mvprintw(4,9,"Nome:");
  mvprintw(6,9,"Cidade:");
  mvprintw(8,9,"Endereço:");
  mvprintw(10,9,"Cep:");
  mvprintw(12,9,"CPF:");
  mvprintw(14,9,"E-mail:");
  mvprintw(16,9,"Senha:");
  mvprintw(18,5,"Descreva vc:");

  set_current_field(my_form,field[0]);
  refresh();

  while((ch = getch())!=KEY_F(2)){
    switch(ch){
      case KEY_DOWN:
        form_driver(my_form, REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        form_driver(my_form, REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        form_driver(my_form, REQ_LEFT_CHAR);
        break;
      case KEY_RIGHT:
        form_driver(my_form, REQ_RIGHT_CHAR);
        break;
      case KEY_BACKSPACE:
        form_driver(my_form, REQ_DEL_PREV);
        break;
      case 10:
        form_driver(my_form, REQ_NEXT_FIELD);
        nome = field_buffer(field[0], 0);
        nome[49] = '\0';
        cidade = field_buffer(field[1], 0);
        cidade[49] = '\0';
        endereco = field_buffer(field[2], 0);
        endereco[49] = '\0';
        cep = field_buffer(field[3], 0);
        cep[19] = '\0';
        cpf = field_buffer(field[4], 0);
        cpf[19] = '\0';
        email = field_buffer(field[5], 0);
        email[49] = '\0';
        senha = field_buffer(field[6], 0);
        senha[19] = '\0';
        descricao = field_buffer(field[7], 0);
        descricao[199] = '\0';
        if(test_string(nome)||test_string(cidade)||test_string(endereco)||test_string(cep)||test_string(cpf)||test_string(email)||test_string(senha)||test_string(descricao)){
          mvprintw(LINES - 3, 0, "Por favor, preencha todos os campos");
          break;
        }
        strcpy(user->nome,nome);
        strcpy(nom,nome);
        strcpy(user->cidade,cidade);
        strcpy(user->endereco,endereco);
        strcpy(user->cep,cep);
        strcpy(user->cpf,cpf);
        strcpy(user->email,email);
        strcpy(user->senha,senha);
        strcpy(user->descricao,descricao);

        if(confirm_user(*user)){
          mvprintw(LINES - 4, 0, "Digite para alterar seus dados");
          break;
        }
        refresh();

        cria_pessoa(G, user);

        unpost_form(my_form);
        free_form(my_form);
        for(i=0;i<8;++i)free_field(field[i]);
        clear();
        refresh();
        endwin();
        return 4;//sucesso ao criar um usuário
      default:
        form_driver(my_form, ch);
        break;
    }
  }
  unpost_form(my_form);
  free_form(my_form);
  for(i=0;i<8;++i)free_field(field[i]);
  clear();
  refresh();
  endwin();
  return 2;
}

int test_string(char *string){
  int i;
  for(i=0;i<strlen(string);++i){
    if(string[i] != ' ')return 0;
  }return 1;
}

int confirm_user(usuarios user){

  char *choice[2] = {"Sim", "Nao"};
  ITEM **my_items;
  int c,i;
  MENU *my_menu;
  WINDOW *my_menu_win;

  my_items = (ITEM **)calloc(2, sizeof(ITEM *));
  for(i=0;i<2;++i)my_items[i] = new_item(choice[i],choice[i]);

  my_menu = new_menu((ITEM **)my_items);

  my_menu_win = newwin(3*LINES/4,COLS/2,LINES/5,COLS/2-1);
  menu_opts_off(my_menu, O_SHOWDESC);
  keypad(my_menu_win,true);

  set_menu_win(my_menu,my_menu_win);
  set_menu_sub(my_menu, derwin(my_menu_win,1,10,3*LINES/4-2,COLS/5));
  set_menu_format(my_menu,1,2);

  box(my_menu_win,0,0);
  mvwaddch(my_menu_win,3,0,ACS_LTEE);
  mvwhline(my_menu_win,3,1,ACS_HLINE,COLS/2-2);
  mvwaddch(my_menu_win,3,COLS/2-1,ACS_RTEE);
  mvwprintw(my_menu_win,1,LINES/5,"Deseja criar um perfil com essas informacoes?");
  mvwprintw(my_menu_win,2,LINES/2-2,"INFO:");
  mvwprintw(my_menu_win,6,2,"Nome: %s",user.nome);
  mvwprintw(my_menu_win,8,2,"Cidade: %s",user.cidade);
  mvwprintw(my_menu_win,10,2,"Endereço: %s",user.endereco);
  mvwprintw(my_menu_win,12,2,"CEP: %s",user.cep);
  mvwprintw(my_menu_win,14,2,"CPF: %s",user.cpf);
  mvwprintw(my_menu_win,16,2,"E-mail: %s",user.email);
  mvwprintw(my_menu_win,18,2,"Senha: %s",user.senha);
  mvwprintw(my_menu_win,20,2,"Descricao: %s",user.descricao);

  refresh();
  post_menu(my_menu);
  wrefresh(my_menu_win);

  while(c = wgetch(my_menu_win)){
    switch(c){
      case KEY_LEFT:
        menu_driver(my_menu,REQ_LEFT_ITEM);
        break;
      case KEY_RIGHT:
        menu_driver(my_menu,REQ_RIGHT_ITEM);
        break;
      case 10:
        if(strcmp("Nao",item_name(current_item(my_menu)))){
          unpost_menu(my_menu);
          free_menu(my_menu);
          free_item(my_items[0]);
          free_item(my_items[1]);
          delwin(my_menu_win);
          return 0;
          }
        else{
          unpost_menu(my_menu);
          free_menu(my_menu);
          free_item(my_items[0]);
          free_item(my_items[1]);
          wclear(my_menu_win);
          wrefresh(my_menu_win);
          delwin(my_menu_win);
          return 1;
        }
    }wrefresh(my_menu_win);
  }
}


int primaria_interface(){
    WINDOW *tela;
    ITEM **itens;
    int ch,width;
    MENU *menu;
    int numero,i;
    char *choices[] = {"Criar usuario", "Login","Sair",(char *)NULL};

    initscr();
    start_color();
    cbreak;
    noecho();
    init_pair(1, COLOR_RED,COLOR_BLACK);/*inicialização das cores do título do menu*/
    numero = ARRAY_SIZE(choices);/*número de opções disponíveis para serem colocas no menu*/
    itens = (ITEM **)calloc(numero, sizeof(ITEM*));
    for(i = 0; i < numero; i++)itens[i] = new_item(choices[i],choices[i]);
    menu = new_menu((ITEM **)itens);
    set_menu_mark(menu, "  - ");
    menu_opts_off(menu, O_SHOWDESC);
    tela = newwin(10,40,LINES/2-5,COLS/2-20);
    keypad(tela, TRUE);
    set_menu_win(menu,tela);
    set_menu_sub(menu, derwin(tela, 6,38,3,1));
    set_menu_format(menu,numero,1);
    box(tela,0,0);
    mvwaddch(tela, 2, 0, ACS_LTEE);
    mvwhline(tela, 2, 1, ACS_HLINE, 38);
    mvwaddch(tela, 2, 39, ACS_RTEE);
    width = strlen("BEM-VINDO");
    mvwprintw(tela, 1,(40-width)/2, "BEM-VINDO");
    post_menu(menu);
    wrefresh(tela);
    while(ch = wgetch(tela)){
        switch(ch){
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                if(!strcmp("Sair",item_name(current_item(menu)))){
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    delwin(tela);
                    endwin();
                    return 0;
                }else if(!strcmp("Criar usuario",item_name(current_item(menu)))){
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    delwin(tela);
                    endwin();
                    return 1;
                }else if(!strcmp("Login",item_name(current_item(menu)))){
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    delwin(tela);
                    endwin();
                    return 3;
                }
        }wrefresh(tela);
    }
    return 0;
}

int login_user_interface(Grafo *g, char *nom){
  FIELD *field[3];
  FORM *my_form;
  int ch,check;
  char *name, *senha;

  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr,true);

  init_pair(1,COLOR_WHITE, COLOR_BLUE);
  init_pair(2,COLOR_RED, COLOR_BLUE);
  field[0] = new_field(1,50,LINES/2,COLS/2-25,0,0);
  field[1] = new_field(1,20,LINES/2+2,COLS/2-10,0,0);
  field[2] = NULL;

  set_field_fore(field[0],COLOR_PAIR(1));
  set_field_back(field[0],COLOR_PAIR(1));
  field_opts_off(field[0], O_AUTOSKIP);

  field_opts_off(field[1], O_AUTOSKIP);
  set_field_fore(field[1],COLOR_PAIR(1));
  set_field_back(field[1],COLOR_PAIR(1));

  my_form = new_form(field);

  post_form(my_form);
  set_current_field(my_form,field[0]);
  attron(COLOR_PAIR(2));
  mvprintw(LINES/2-4,COLS/2-3,"LOGIN");
  attroff(COLOR_PAIR(2));
  mvprintw(LINES-2,0,"Use as setas para mudar os campos e pressione ENTER para terminar. Cancele com F2");
  mvprintw(LINES/2,COLS/2-31,"Nome:");
  mvprintw(LINES/2+2,COLS/2-17,"Senha:");
  refresh();
  while((ch = getch())!=KEY_F(2)){
    switch(ch){
      case KEY_DOWN:
        form_driver(my_form,REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        form_driver(my_form, REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        form_driver(my_form, REQ_LEFT_CHAR);
        break;
      case KEY_RIGHT:
        form_driver(my_form, REQ_RIGHT_CHAR);
        break;
      case KEY_BACKSPACE:
        form_driver(my_form, REQ_DEL_PREV);
        break;
      case 10:
        form_driver(my_form,REQ_NEXT_FIELD);
        name = field_buffer(field[0],0);
        senha = field_buffer(field[1],0);
        name[49] = '\0';
        strcpy(nom,name);
        senha[19] = '\0';
        if(test_string(name)||test_string(senha)){
          mvprintw(LINES - 4, 0, "Preencha os campos");
          break;
        }
        check = check_user(g,name,senha);
        switch(check){
          case 0:
            mvprintw(LINES - 3, 0, "Nao há esse usuario");
            break;
          case 1:
            mvprintw(LINES - 3, 0, "Senha incorreta   ");
            break;
        }
        if(check == 2){
        unpost_form(my_form);
        free_form(my_form);
        free_field(field[0]);
        free_field(field[1]);
        clear();
        refresh();
        endwin();
        return 4;
        }else break;

      default:
        form_driver(my_form,ch);
        break;
    }
  }
  unpost_form(my_form);
  free_form(my_form);
  free_field(field[0]);
  free_field(field[1]);
  clear();
  refresh();
  endwin();
  return 2;
}

int check_user(Grafo* G, char *name, char *senha){
  usuarios *user;

  if(!(user = procura_nome(G,name)))return 0;
  else if(strcmp(senha,user->senha))return 1;
  else return 2;
}

int logged_user_interface(Grafo *g,char *name){
    ITEM **itens;
    int ch,width;
    MENU *menu;
    int numero,i;
    char *choices[] = {"Editar suas informacoes", "Excluir conta", "Procurar Transacao","Adicionar Transacao","Adicionar amigos","Ver amigos","Sair",(char *)NULL};
    usuarios *user;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    numero = ARRAY_SIZE(choices);/*número de opções disponíveis para serem colocas no menu*/
    itens = (ITEM **)calloc(numero, sizeof(ITEM*));
    for(i = 0; i < numero; i++)itens[i] = new_item(choices[i],choices[i]);
    menu = new_menu((ITEM **)itens);
    set_menu_mark(menu, "  - ");
    menu_opts_off(menu, O_SHOWDESC);
    set_menu_format(menu,numero,1);
    width = strlen("BEM-VINDO");
    mvprintw(LINES/4-7,COLS/4-20,"Ola, %s",name);
    mvprintw(LINES/4-5,COLS/4-20, "BEM-VINDO");
    set_menu_sub(menu,derwin(stdscr,7,38,LINES/4-2,COLS/4-25));
    post_menu(menu);
    refresh();
    if(!(user = procura_nome(g,name))){
      printw("Nao achei");
      refresh();
      return 2;
    }
    while(ch = getch()){
        switch(ch){
            case KEY_DOWN:
                mvprintw(LINES - 2, 0, "Use as setas para para trocar entre os campos. Para ir digite ENTER.");
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                mvprintw(LINES - 2, 0, "Use as setas para para trocar entre os campos. Para ir digite ENTER.");
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                if(!strcmp("Sair",item_name(current_item(menu)))){
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    clear();
                    refresh();
                    endwin();
                    return 2;
                }else if(!strcmp("Editar suas informacoes",item_name(current_item(menu)))){
                    edit_user_interface(g,user,name);
                    mvprintw(LINES/4-7,COLS/4-20,"Ola, %s",name);
                    if(!(user = procura_nome(g,name))){
                      printw("Nao achei");
                      refresh();
                      return 2;
                    }
                    menu_driver(menu, REQ_DOWN_ITEM);
                    refresh();
                    break;
                }else if(!strcmp("Excluir conta",item_name(current_item(menu)))){
                    exclui_usuario(&g,&user);
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    clear();
                    refresh();
                    endwin();
                    return 2;
                }else if(!strcmp("Adicionar amigos",item_name(current_item(menu)))){
                  adiciona_amigos_interface(g,user);
                  break;
                }else if(!strcmp("Ver amigos",item_name(current_item(menu)))){
                  if(!ver_amigos_interface(g,user))mvprintw(LINES-3,1,"Vc nao tem amigos ainda");
                  break;
                }
        }
    }
    return 0;
}

int edit_user_interface(Grafo *g,usuarios *user,char *nom){
  WINDOW *my_form_win;
  FIELD *field[9];
  FORM *my_form;
  int ch,i,rows,cols;
  char *nome,*cidade,*endereco,*cep,*cpf,*email,*senha,*descricao;
  usuarios *user1;


  init_pair(1,COLOR_WHITE, COLOR_BLUE);
  init_pair(2,COLOR_WHITE, COLOR_BLUE);

  field[0] = new_field(1,50,4,14,0,0);
  field[1] = new_field(1,50,6,14,0,0);
  field[2] = new_field(1,50,8,14,0,0);
  field[3] = new_field(1,20,10,14,0,0);
  field[4] = new_field(1,20,12,14,0,0);
  field[5] = new_field(1,50,14,14,0,0);
  field[6] = new_field(1,20,16,14,0,0);
  field[7] = new_field(4,50,18,14,0,0);

  field[8] = NULL;
  for(i=0;i<8;++i){
    set_field_fore(field[i],COLOR_PAIR(1));
    set_field_back(field[i],COLOR_PAIR(2));
    field_opts_off(field[i],O_AUTOSKIP);
  }
  set_field_buffer(field[0],0,user->nome);
  set_field_buffer(field[1],0,user->cidade);
  set_field_buffer(field[2],0,user->endereco);
  set_field_buffer(field[3],0,user->cep);
  set_field_buffer(field[4],0,user->cpf);
  set_field_buffer(field[5],0,user->email);
  set_field_buffer(field[6],0,user->senha);
  set_field_buffer(field[7],0,user->descricao);

  my_form = new_form(field);
  set_current_field(my_form,field[0]);
  scale_form(my_form,&rows,&cols);
  my_form_win = newwin(rows+4,cols+4,LINES/2-10,1);
  keypad(my_form_win,true);
  set_form_win(my_form,my_form_win);
  set_form_sub(my_form,derwin(my_form_win,rows,cols,1,1));

  box(my_form_win,0,0);
  form_opts_off(my_form, O_BS_OVERLOAD);
  post_form(my_form);

  wrefresh(my_form_win);
  mvprintw(LINES - 2, 0, "Use as setas para para trocar entre os campos. Para terminar digite ENTER. Pressione F2 para cancelar");
  mvwprintw(my_form_win,4,2,"Nome:");
  mvwprintw(my_form_win,6,2,"Cidade:");
  mvwprintw(my_form_win,8,2,"Endereço:");
  mvwprintw(my_form_win,10,2,"Cep:");
  mvwprintw(my_form_win,12,2,"CPF:");
  mvwprintw(my_form_win,14,2,"E-mail:");
  mvwprintw(my_form_win,16,2,"Senha:");
  mvwprintw(my_form_win,18,2,"Descreva vc:");
  refresh();
  while((ch = wgetch(my_form_win))!=KEY_F(2)){
    switch(ch){
      case KEY_DOWN:
        form_driver(my_form, REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        form_driver(my_form, REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        form_driver(my_form, REQ_LEFT_CHAR);
        break;
      case KEY_RIGHT:
        form_driver(my_form, REQ_RIGHT_CHAR);
        break;
      case KEY_BACKSPACE:
        form_driver(my_form, REQ_DEL_PREV);
        break;
      case 10:
        exclui_usuario(&g,&user);
        user1 = (usuarios*)malloc(sizeof(usuarios));
        form_driver(my_form, REQ_NEXT_FIELD);
        nome = field_buffer(field[0], 0);
        nome[49] = '\0';
        cidade = field_buffer(field[1], 0);
        cidade[49] = '\0';
        endereco = field_buffer(field[2], 0);
        endereco[49] = '\0';
        cep = field_buffer(field[3], 0);
        cep[19] = '\0';
        cpf = field_buffer(field[4], 0);
        cpf[19] = '\0';
        email = field_buffer(field[5], 0);
        email[49] = '\0';
        senha = field_buffer(field[6], 0);
        senha[19] = '\0';
        descricao = field_buffer(field[7], 0);
        descricao[199] = '\0';
        if(test_string(nome)||test_string(cidade)||test_string(endereco)||test_string(cep)||test_string(cpf)||test_string(email)||test_string(senha)||test_string(descricao)){
          mvprintw(LINES - 3, 0, "Por favor, preencha todos os campos");
          break;
        }
        strcpy(user1->nome,nome);
        strcpy(nom,nome);
        strcpy(user1->cidade,cidade);
        strcpy(user1->endereco,endereco);
        strcpy(user1->cep,cep);
        strcpy(user1->cpf,cpf);
        strcpy(user1->email,email);
        strcpy(user1->senha,senha);
        strcpy(user1->descricao,descricao);
        cria_pessoa(g,user1);

        wclear(my_form_win);
        wrefresh(my_form_win);
        delwin(my_form_win);
        unpost_form(my_form);
        free_form(my_form);
        for(i=0;i<8;++i)free_field(field[i]);
        return 0;
      default:
        form_driver(my_form,ch);
        break;
    }
    wrefresh(my_form_win);
  }
  wclear(my_form_win);
  wrefresh(my_form_win);
  delwin(my_form_win);
  unpost_form(my_form);
  free_form(my_form);
  for(i=0;i<8;++i)free_field(field[i]);
  return 0;
}

int adiciona_amigos_interface(Grafo *g, usuarios *user){
  WINDOW *my_form_win;
  FIELD *field[2];
  FORM *my_form;
  int ch,rows,cols;
  char *nome;
  usuarios *user1;

  field[0] = new_field(1,50,2,1,0,0);
  set_field_fore(field[0],COLOR_PAIR(1));
  set_field_back(field[0],COLOR_PAIR(2));
  field_opts_off(field[0],O_AUTOSKIP);
  field[1] = NULL;
  set_current_field(my_form,field[0]);

  my_form = new_form(field);
  scale_form(my_form,&rows,&cols);

  my_form_win = newwin(rows+25,cols+15,LINES/3,COLS/2);
  keypad(my_form_win,true);

  set_form_win(my_form,my_form_win);
  set_form_sub(my_form,derwin(my_form_win,rows,cols,2,2));

  box(my_form_win,0,0);
  post_form(my_form);
  mvwprintw(my_form_win,1,1,"Digite o nome do usuario e aperte ENTER. F2 para cancelar");
  wrefresh(my_form_win);

  while((ch = wgetch(my_form_win)) != KEY_F(2)){
    switch(ch){
      case KEY_LEFT:
        form_driver(my_form,REQ_LEFT_CHAR);
        break;
      case KEY_RIGHT:
        form_driver(my_form,REQ_RIGHT_CHAR);
        break;
      case KEY_BACKSPACE:
        form_driver(my_form,REQ_DEL_PREV);
      case 10:
        form_driver(my_form,REQ_NEXT_FIELD);
        nome = field_buffer(field[0],0);
        nome[49] = '\0';
        if(test_string(nome)){
          mvwprintw(my_form_win,2,1,"Preencha o campo  ");
          break;
        }
        if(!(user1 = procura_nome(g,nome))){
          mvwprintw(my_form_win,2,1,"Nao localizado   ");
          break;
        }else{
          mvwprintw(my_form_win,2,1,"Usuario encontrado");
          mvwprintw(my_form_win,8,1,"NOME = %s",user1->nome);
          mvwprintw(my_form_win,10,1,"Cidade = %s",user1->cidade);
          mvwprintw(my_form_win,12,1,"EMAIL = %s",user1->email);
          mvwprintw(my_form_win,14,1,"Descricao = %s",user1->descricao);
          mvwprintw(my_form_win,18,1,"ENTER para adicionar e F2 para voltar a pesquisa");
          ch = wgetch(my_form_win);
          if(ch == 10){
            if(!eh_amigo(user1,user)){
              adiciona_amigos(&g,&user,&user1,0);
              unpost_form(my_form);
              free_form(my_form);
              free_field(field[0]);
              wclear(my_form_win);
              wrefresh(my_form_win);
              delwin(my_form_win);
              return 0;
            }else{
              mvwprintw(my_form_win,2,1,"Ja sao amigos     ");
            }
          }else if(ch == KEY_F(2))break;
        }
      default:
        form_driver(my_form, ch);
        break;
    }
  }
  unpost_form(my_form);
  free_form(my_form);
  free_field(field[0]);
  wclear(my_form_win);
  wrefresh(my_form_win);
  delwin(my_form_win);
  return 0;
}

int ver_amigos_interface(Grafo *g,usuarios *user){
  ITEM **my_items;
  int c,i;
  MENU *my_menu;
  WINDOW *my_menu_win;
  amigos *migos,*pont;
  char **nomes,name[50];
  usuarios *user1;

  if(migos = verifica_amizades(&user))nomes = (char**)malloc(user->numeroAmigos*sizeof(char*));
  else return 0;
  pont = migos;
  for(i=0;pont != NULL;i++){
    nomes[i] = pont->nomeAmigo;
    pont = pont->proxAmigo;
  }

  my_items = (ITEM **)calloc(user->numeroAmigos,sizeof(ITEM*));
  for(i=0;i<user->numeroAmigos;++i)my_items[i] = new_item(nomes[i],nomes[i]);
  
  my_menu = new_menu((ITEM **)my_items);
  menu_opts_off(my_menu,O_SHOWDESC);

  my_menu_win = newwin(LINES/2,COLS-20,LINES/2,1);
  keypad(my_menu_win,true);

  set_menu_win(my_menu,my_menu_win);
  set_menu_sub(my_menu,derwin(my_menu_win,15,55,3,2));

  box(my_menu_win,0,0);
  post_menu(my_menu);
  wrefresh(my_menu_win);

  while((c = wgetch(my_menu_win))!=KEY_F(2)){
    switch(c){
      case KEY_UP:
        menu_driver(my_menu,REQ_UP_ITEM);
        break;
      case KEY_DOWN:
        menu_driver(my_menu,REQ_DOWN_ITEM);
        break;
      case 10:
        strcpy(name,item_name(current_item(my_menu)));
        name[49] = '\0';
        user1 = procura_nome(g,name);
        mvwprintw(my_menu_win,4,60,"NOME = %s",user1->nome);
        mvwprintw(my_menu_win,6,60,"ENDERECO = %s",user1->endereco);
        mvwprintw(my_menu_win,8,60,"EMAIL = %s",user1->email);
        mvwprintw(my_menu_win,10,60,"CIDADE = %s",user1->cidade);

    }
    wrefresh(my_menu_win);
  }
  unpost_menu(my_menu);
  free_menu(my_menu);
  for(i=0;i<user->numeroAmigos;i++)free_item(my_items[i]);
  free(nomes);
  wclear(my_menu_win);
  wrefresh(my_menu_win);
  delwin(my_menu_win);
  return 1;
}