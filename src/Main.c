#include <Grafo.h>

char *choices[] = {"Criar usuario", "Login", "Editar usuario","Excluir usuario","Procurar transacao","Fazer transacao","Sair",(char *)NULL};

int main(){
    WINDOW *tela;
    ITEM **itens;
    int ch,width;
    MENU *menu;
    int numero,i;
    ITEM *cur_item;

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
                    endwin();
                    return 0;
                }else if(!strcmp("Criar usuario",item_name(current_item(menu)))){
                    unpost_menu(menu);
                    for(i=0; i<numero;i++)free_item(itens[i]);
                    free_menu(menu);
                    endwin();
                    cria_pessoa();
                }else if(!strcmp("Login",item_name(current_item(menu)))){
                    login_user();
                }

                break;
        }wrefresh(tela);
    }
}