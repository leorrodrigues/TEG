#include "matris.h"

void getch(void){
    system("read b");
}

void limpa(void){
    system("/usr/bin/clear");
}

int main(){
    int opcao;
    do{
        puts("Digite 1 para Matris de Adjacencia\n");
        puts("Digite 2 para Matris de Incidencia Nao Ordenado\n");
        puts("Digite 3 para Matris de Incidencia Ordenado\n");
        puts("Digite 0 para Encerrar o Programa\n");
        scanf("%i",&opcao);
        limpa();
        if(opcao==1)
            matris_adjacencia();
        else if(opcao==2)
            matris_incidencia(1);
        else if(opcao==3)
            matris_incidencia(2);
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

