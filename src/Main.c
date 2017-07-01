#include <Grafo.h>

int main(){
    int ch;
    Grafo *graph;

    ch = primaria_interface();
    graph = cria_Grafo();

    while(ch != 0){
        switch(ch){
            case 1:
                ch = cria_pessoa_interface(graph);
                break;
            case 2:
                primaria_interface();
                break;
        }
    }
    salva_Arquivo(&graph);
    destroi_Grafo(&graph);
    return 0;
}