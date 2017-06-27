#include <Grafo.h>

int K = 0;

//ERRO = -1 O erro em todo este programa recebe o valor de -1.
char Erro[] = "Erro"; // Vetor de caracteres que é retornado na funcao retorna nome, caso um grafo seja inexistente.

//Funcao cria_Grafo --- Recebe como Parametro um Grafo(G) e aloca espaço de memoria para criar uma estrutura do tipo Grafo.
//Os if's ajudam caso haja alguma falha na alocação de memória. A falha será propagada para a função que a chama
//A lista de usuários possui uma cabeça para ajudar nas operações e vai de acordo com a especificação
Grafo *cria_Grafo(){
  struct Grafo *G;
  struct usuarios *user;
  int i = 0;

  if((G = (Grafo *)malloc(sizeof(Grafo))) == NULL)return NULL;
  if((user = (usuarios*)malloc(sizeof(usuarios))) == NULL)return NULL;
  G->lista = user;
  G->N_usuarios = 0;
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
*/

//Funcao exclui_usuario --- Recebe como Parametro um Grafo(G), libera o espaço de memoria alocado para um usuario.
void exclui_usuario(Grafo *G, usuarios *User){//verificar depois da função criar usuário
  int letra;
  struct amigos *amigo, *pont;
  struct usuarios *User2;

  if((*User) != NULL){
    amigo = (verifica_amizades(&(*User)));
    if(amigo != NULL){
      pont = amigo;
      User2 = procura_nome((*G), amigo->nomeAmigo);
      while(pont != NULL){
        excluir_amigo(&(*G), &(*User), &User2);
        pont = pont->proxAmigo;
        free(amigo);
        amigo = pont;
      }
      amigo = NULL;
    }else{
      if((*User)->ant != NULL && (*User)->prox != NULL){
        (*User)->ant->prox = (*User)->prox;
        (*User)->prox->ant = (*User)->ant;
      }
      else{
        letra = verifica_letra((*User)->nome[0]);
        if((*User)->ant == NULL && (*User)->prox != NULL){
          (*User)->prox->ant = NULL;
          (*User)->prox->ant = (*User)->ant;
          ((*G)->listaAdj[letra]) = (*User)->prox;
          free((*User));
          (*User) = NULL;
        }
        if((*User)->ant == NULL && (*User)->prox == NULL){
          free((*User));
          (*User) = NULL;
          ((*G)->listaAdj[letra]) = (*User);
        }
      }
    }
  }
}

//Funcao verifica_amizades --- Recebe como Parametro um usuario(User) e retorna uma lista de amigos de User.
amigos *verifica_amizades(usuarios **User){
  int cont = 0, i = 0;
  struct amigos *listaAmigos, *pont, *pont2;

  listaAmigos = (amigos*)malloc(sizeof(amigos));
  listaAmigos = NULL;

  if((*User)->numeroAmigos != 0){
    while(/*i < 26 &&*/(cont != ((*User)->numeroAmigos))){
      pont = ((*User)->Amigos[i]);
      while(pont != NULL){
        if(cont == 0){
          listaAmigos = pont;
          listaAmigos->proxAmigo = NULL;
          listaAmigos->antAmigo = NULL;
          pont2 = listaAmigos;
        }else{
          pont2->proxAmigo = pont;
          pont->antAmigo = pont2;
          pont2 = pont;
        }
        pont2->proxAmigo = NULL;
        pont2->antAmigo = NULL;
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
  if(existe_Grafo(*G)){
  }
}

 //Funcao imprime Grafo --- Recebe como Parametro um Grafo(G) e imprime na tela todos os usuarios e Amizades.
void imprime_Grafo(Grafo *G){
  system("cls || clear");
  int i = 0;
  struct usuarios *pont;

  if(G->N_usuarios > 0){
    printf("Numero de usuarios = %d\n", G->N_usuarios);
    while(i < 26){
      if((G->listaAdj[i]) != NULL){
        printf("\n[%c] ->\n", ('A'+i));
        pont = G->listaAdj[i];
        while(pont != NULL){
          printf("        %s", pont->nome);
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
  int j;

  for(j = 0; j < 26; j++){
    if(j == 0){
      printf("\nAmigos %s = {", User->nome);
    }
    if((User->Amigos[j]) != NULL){
      printf(" %s ", User->Amigos[j]->nomeAmigo);
    }
    if(j == 25){
      printf("}\n\n");
    }
  }
}

//Funcao procura_nome --- Recebe como Parametros um Grafo(G) e um nome.
//Retorna um usuario ou NULL caso não encontre o usuario.
usuarios *procura_nome(Grafo *G, char *nom){
  system("cls || clear");
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
    printf("Usuario %s encontrado!\n", user1->nome);
    return user1;
  }
  else{
        printf("\nUsuario %s Nao Encontrado!!\n", nom);
    return NULL;
  }
}

//Funcao procura_usuario --- Recebe como Parametros um Grafo(G).
//Retorna um usuario ou NULL caso não encontre o usuario.
usuarios *procura_usuario(Grafo *G){
  system("cls || clear");
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

 //Funcao excluir_amigo --- Recebe como Parametros um Grafo(G) e um usuario.
void excluir_amigo(Grafo **G, usuarios **User, usuarios **User1){
  int letra;
  struct amigos *pont;

  if((*User1) != NULL){
    letra = verifica_letra(((*User1)->nome[0]));
    pont = ((*User)->Amigos[letra]);
    while(pont != NULL){
      if(strcmp(pont->nomeAmigo, (*User1)->nome) == 0){
        if(pont->proxAmigo == NULL && pont->antAmigo == NULL){
          free(((*User)->Amigos[letra]));
          ((*User)->Amigos[letra]) = NULL;
          ((*User)->Amigos[letra])->proxAmigo = NULL;
          ((*User)->Amigos[letra])->antAmigo = NULL;
        }
        if(pont->antAmigo == NULL && pont->proxAmigo != NULL){
          ((*User)->Amigos[letra]) = pont->proxAmigo;
          pont->proxAmigo->antAmigo = NULL;
          free(pont);
        }
        if(pont->antAmigo != NULL && pont->proxAmigo != NULL){
          pont->antAmigo->proxAmigo = pont->proxAmigo;
          pont->proxAmigo->antAmigo = pont->antAmigo;
          free(pont);
        }
        pont = NULL;
      }
      else{
        pont = pont->proxAmigo;
      }
    }
    (*User)->numeroAmigos--;
  }
}

 //Funcao adiciona_amigos --- Recebe como Parametros um Grafo(G) e dois usuarios.
void adiciona_amigos(Grafo **G, usuarios **User1, usuarios **User2, int cons){
  system("cls || clear");
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

usuarios *editar_pessoa(Grafo **G){
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
    printf("|              Alterar configuracoes de %s              | \n", user->nome);
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
          printf("Usuario que sera excluido\n");
          user2 = procura_usuario((*G));
        }
        if(user2 != NULL){
          if(user->nome != user2->nome){
            if(opc1 == 1){
                adiciona_amigos(&(*G), &user, &user2, K);
                printf("Amigo adicionado!!\n");
            }
            if(opc1 == 2){
                excluir_amigo(&(*G), &user, &user2);
                printf("Amigo excluido!!\n");
            }
          }else{
            system("clear || cls");
            printf("So e possivel excluir conta no menu anterior\n");
          }
        }else{
          printf("Usuario nao encontrado!!\n");
        }
      }
      break;
      case(6):
        exclui_usuario(&(*G), &user);
      break;

    }
  }
  system("cls || clear");
  return user;
}

void cria_pessoa(usuarios user){

  FILE *fp;
  fp = fopen("../Allusers/Alluserinfo","ab");
  fwrite(&user,sizeof(usuarios),1,fp);
  fclose(fp);
}

int cria_pessoa_interface(Grafo *G){
  FIELD *field[7];
  FORM *my_form;
  int ch,i,number=0, position = 0;
  char *nome,*cidade,*endereco,*cep,*cpf,*email;
  usuarios user;

  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr,true);

  init_pair(1,COLOR_WHITE, COLOR_BLUE);
  init_pair(2,COLOR_WHITE, COLOR_BLUE);

  field[0] = new_field(1,30,4,18,0,0);
  field[1] = new_field(1,15,6,18,0,0);
  field[2] = new_field(1,20,8,18,0,0);
  field[3] = new_field(1,20,10,18,0,0);
  field[4] = new_field(1,20,12,18,0,0);
  field[5] = new_field(1,20,14,18,0,0);

  field[6] = NULL;
  for(i=0;i<6;++i){
    set_field_fore(field[i],COLOR_PAIR(1));
    set_field_back(field[i],COLOR_PAIR(2));
    field_opts_off(field[i],O_AUTOSKIP);
  }
  my_form = new_form(field);
  form_opts_off(my_form, O_BS_OVERLOAD);
  post_form(my_form);
  refresh();
  mvprintw(LINES - 2, 0, "Use as setas para para trocar entre os campos. Para terminar digite ENTER");
  mvprintw(4,9,"Nome:");
  mvprintw(6,9,"Cidade:");
  mvprintw(8,9,"Endereço:");
  mvprintw(10,9,"Cep:");
  mvprintw(12,9,"CPF:");
  mvprintw(14,9,"E-mail:");

  set_current_field(my_form,field[0]);
  refresh();

  while(ch = getch()){
    switch(ch){
      case KEY_DOWN:
        if(number!=3)number++;
        form_driver(my_form, REQ_NEXT_FIELD);
        break;
      case KEY_UP:
        if(number!=0)number--;
        form_driver(my_form, REQ_PREV_FIELD);
        break;
      case KEY_LEFT:
        if(position != 0) position--;
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
        cidade = field_buffer(field[1], 0);
        endereco = field_buffer(field[2], 0);
        cep = field_buffer(field[3], 0);
        cpf = field_buffer(field[4], 0);
        email = field_buffer(field[5], 0);

        strcpy(user.nome,nome);
        strcpy(user.cidade,cidade);
        strcpy(user.endereco,endereco);
        strcpy(user.cep,cep);
        strcpy(user.cpf,cpf);
        strcpy(user.email,email);
        cria_pessoa(user,G);
        mvprintw(LINES - 3, 0, "%s %s %s %s",nome,cidade,cep,cpf);
        getch();
        unpost_form(my_form);
        free_form(my_form);
        for(i=0;i<4;++i)free_field(field[i]);
        endwin();
        return 1;//sucesso ao criar um usuário
      default:
        form_driver(my_form, ch);
        break;
    }
  }
}