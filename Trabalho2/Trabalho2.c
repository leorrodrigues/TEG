#include "fila.h"
#include "vetor.h"

void getch(void){
    system("read b");
}

void limpa(void){
    system("/usr/bin/clear");
}

int main(){
    int opcao;
    do{
        puts("Digite 1 para Lista de Adjacencia sem pesos\n");
        puts("Digite 2 para Lista de Adjacencia com pesos\n");
        puts("Digite 3 para Vetor de Adjacencia\n");
        puts("Digite 0 para Encerrar o Programa\n");
        scanf("%i",&opcao);
        limpa();
        if(opcao==1)
            lista_adjacencia();
        else if(opcao==2)
            lista_adjacencia_pesos();
        else if(opcao==3)
            vetor_adjacencia();
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
