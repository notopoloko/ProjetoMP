#include <Grafo.h>

//void menu(){
int main(){  
    int opc = 1;

    while(opc != 0){
        raw();
        printw(" ______________________________________________\n");
        printw("|                  FACECOPY                    |\n");
        printw("|1 - Criar usuario                             |\n");
        printw("|2 - Editar usuario                            |\n");
        printw("|3 - Excluir usuario                           |\n");
        printw("|4 - Procurar transacao                        |\n");
        printw("|5 - Fazer transacao                           |\n");
        printw("|0 - Sair                                      |\n");
        printw("|______________________________________________|\n");
        refresh();
        getstr(nv_vert);
        clear();
          
        scanf(" %d", &opc);
        system("cls || clear"); 
        switch(opc) {    
          case(1):
          cria_usuario();
          break;
          case(2):
          show(ini);
          break;
          case(3):
          delete(&ini, &cont);
          break;
          case(4):
          lenght(&cont);
          break;
          case(5):
          printf("Antes:\n");
          show(ini);
          ord(&ini, &cont);
          printf("Depois:\n");
          show(ini);
          break;
        }
    }

    return 0;
}