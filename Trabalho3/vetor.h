#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void submenu(int *vert,int *adj,int cont,int cont2);

void euleriano(int *vert,int *adj,int cont,int cont2);

void vetor_adjacencia(){
    FILE *fp;
    char str[50],ch,*p_ch,ch2[3];//String que recebera cada linha do arquivo
    int *vert,*adj,flag=0,cont=0,cont2=0,cont3=0,i,j,leitura=0;
    p_ch=&ch2;
    vert=(int *)malloc(sizeof(int));
    adj=(int *)malloc(sizeof(int));
    fp=fopen("entrada.txt","r");
    if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("Erro na abertura do arquivo de entrada\n");
    }
    else{//Caso o arquivo tenha sido aberto sem erros.
        //Enquanto nao chegar ao fim do arquivo armazene
        //as linhas lidas na string str.
        while((ch=fgetc(fp))!=EOF){
            if((ch!=':') && (ch!=' ') && (ch!='\n')){//caso ch seja diferente de : e de espacos em branco
                ch2[leitura]=ch;
                leitura++;
                ch2[leitura]='\0';
            }
            else{
                j=atoi(p_ch);
                if(ch==':'){
                    cont++;
                    vert=(int *)realloc(vert,sizeof(int)*cont);
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch==' ' && j!=0 && ch!='\n'){
                    cont2++;
                    cont3++;
                    adj=(int *)realloc(adj,sizeof(int)*cont3);
                    adj[cont3-1]=j;
                    vert[cont-1]=cont2;
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch=='\n'){
                    cont2++;
                    cont3++;
                    adj=(int *)realloc(adj,sizeof(int)*cont3);
                    adj[cont3-1]=j;
                    vert[cont-1]=cont2;
                    cont2=0;
                    leitura=0;
                    strcpy(ch2,"\0");
                }
            }
        }
    }
    fclose(fp);
    submenu(vert,adj,cont,cont3);
    /* Cont e o tamanho de VERT e cont3 o tamanho de ADJ*/
}


void submenu(int *vert,int *adj,int cont,int cont2){
    int opcao,i,j,k=0;
    puts("Digite 1 para mostrar o grafo\n");
    puts("Digite 2 para encontrar um caminho euleriano\n");
    puts("Digite 0 para retornar ao menu anterior\n");
    printf("::>");
    scanf("%i",&opcao);
    if(opcao==1){
        limpa();
        for(i=0;i<cont;i++){
            printf("Indice:%i Grau: %i Vizinhos: ",i+1,vert[i]);
            for(j=0;j<vert[i];j++){
                printf("%i ",adj[k]);
                k++;
            }
            puts("\n");
        }
    }
    if(opcao==2){
        euleriano(vert,adj,cont,cont2);

    }
    if(opcao==0){
        limpa();
        return;
    }
}

void euleriano(int *vert,int *adj,int cont,int cont2){
    limpa();
    int vert_cop[cont],adj_cop[cont2],i,j,k=0,vet_in,vet_sai,euleriano[cont],vazio=0,soma_grau=0,soma_grau2=0,aux=0;
    for(i=0;i<cont;i++){
        vert_cop[i]=vert[i];
        for(j=0;j<vert[i];j++){
            adj_cop[k]=adj[k];
            k++;
        }
    }
    k=0;
    /*puts("Vetores copia\n");
    for(i=0;i<cont;i++){
        printf("Indice:%i Grau: %i Vizinhos: ",i+1,vert_cop[i]);
        for(j=0;j<vert_cop[i];j++){
            printf("%i ",adj_cop[k]);
            k++;
        }
        puts("\n");
    }*/
    k=0;
    /*VERIFICAMOS SE OS GRAUS DE CADA VERTICE SAO PAR*/
    for(i=0;i<cont;i++){
        if(vert_cop[i]%2!=0){
            printf("O grafo possui o vertice %i com grau impar!\nPortanto nao temos um caminho euleriano\n",i+1);
            return;
        }
    }
    puts("O grafo possui todos os vertices com grau par!\nProcurando o caminho euleriano...");
    printf("Digite o vetor de inicio\n::>");
    int flag=0;;
    while(flag==0){
        scanf("%i",&vet_in);
        if(vet_in>cont||vet_in<1){
            puts("Entrada invalida!\n");
            sleep(2);
            limpa();
            puts("O grafo possui todos os vertices com grau par!\nProcurando o caminho euleriano...");
            printf("Digite o vetor de inicio\n::>");
        }
        else{
            flag=1;
        }
    }
    limpa();
    vet_sai=vet_in;
    do{
        for(i=0;i<vet_sai-1;i++){
            soma_grau+=vert[i];
        }
        while(adj[soma_grau]==0){
            soma_grau++;
        }
        for(i=0;i<adj[soma_grau]-1;i++){
            soma_grau2+=vert[i];
        }
        aux=adj[soma_grau];
        while(adj[soma_grau2]!=vet_sai){
            soma_grau2++;
        }
        euleriano[k]=vet_sai;
        adj[soma_grau2]=0;
        adj[soma_grau]=0;
        vert_cop[adj[soma_grau]-1]--;
        vert_cop[vet_sai-1]--;
        vet_sai=aux;
        soma_grau2=0;
        soma_grau=0;
        vazio=0;
        for(i=0;i<cont2-1;i++){
            if(adj[i]==0){
                vazio++;
            }
        }
        k++;
        euleriano[k]=vet_sai;
    }while(vazio!=cont2-1);
    if(vet_in==vet_sai){
        printf("Caminho euleriano encontrado\n");
        for(i=0;i<k;i++){
            printf("%i ->",euleriano[i]);
        }
        printf("%i\n",euleriano[i]);
    }
}
