#include <Grafo.h>

int main(){
    int ch;
    Grafo *graph;
    char nome_user[50];

    graph = cria_Grafo();
    ch = primaria_interface();

    while(ch != 0){
        switch(ch){
            case 1:
                ch = cria_pessoa_interface(graph,nome_user);
                break;
            case 2:
                ch = primaria_interface();
                break;
            case 3:
                ch = login_user_interface(graph,nome_user);
                break;
            case 4:
                ch = logged_user_interface(graph,nome_user);
                break;
        }
    }
    salva_Arquivo(graph);
    destroi_Grafo(&graph);
    return 0;
}