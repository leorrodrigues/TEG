#include "fila.h"

void getch(void){
    system("read b");
}

void limpa(void){
    system("/usr/bin/clear");
}

int main(){
    int opcao;
    lista_adjacencia();
    do{
        puts("Digite 1 para Lista de Adjacencia sem pesos");
        puts("Digite 2 para mostrar o(s) centro(s) da arvore");
        puts("Digite 0 para Encerrar o Programa");
        scanf("%i",&opcao);
        limpa();
        if(opcao==1){
            exibe(principal);
        }
        else if(opcao==2)
            centro_arvore();
        else if(opcao==0){
            puts("Fim do programa\n");
            sleep(3);
            return 0;
        }
        else
            puts("Entrada Inválida!\n");
        puts("Digite algo para continuar...");
        getch();
        limpa();
    }while(opcao!=0);
}
