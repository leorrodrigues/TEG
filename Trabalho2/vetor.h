#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void submenu(int *vert,int *adj,int cont,int cont2);

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
    int k=0;
    fclose(fp);
    submenu(vert,adj,cont,cont3);
}

void submenu(int *vert,int *adj,int cont,int cont2){
    FILE *fp;
    int opcao,i,j,k=0;
    do{
        limpa();
        puts("Digite 1 para mostrar o grafo\n");
        puts("Digite 2 para remover um vertice\n");
        puts("Digite 0 para voltar ao menu anterior");
        printf("::>");
        scanf("%i",&opcao);
        if(opcao==1){
            limpa();
            k=0;
            for(i=0;i<cont;i++){
                printf("Indice:%i Grau: %i Vizinhos: ",i+1,vert[i]);
                for(j=0;j<vert[i];j++){
                    printf("%i ",adj[k]);
                    k++;
                }
                puts("\n");
            }
            puts("Digite algo para continuar...");
            __fpurge(stdin);
            getchar();
        }
        else if(opcao==2){
            int vet_exclusao,aux,aux2,soma_grau=0;
            limpa();
            printf("Digite o vertice que deseja excluir\n::>");
            scanf("%i",&vet_exclusao);
            vet_exclusao--;
            if(vet_exclusao>=cont || vet_exclusao <=0){
                puts("Valor invalido\nDigite algo para continuar...");
                __fpurge(stdin);
                getchar();
            }
            else{
                aux=vert[vet_exclusao];
                aux2=aux;
                /*FUNCAO PARA RETIRAR OS ELEMENTOS*/
                k=0;
                for(i=0;i<cont;i++){
                    for(j=0;j<vert[i];j++){
                        if(adj[k]==vet_exclusao+1){
                           // printf("ADJ[%i]: %i \tVET_EX: %i \tK: %i \tVERT[%i]: %i\n",k,adj[k],vet_exclusao,k,i,vert[i]);
                            adj[k]=0;
                            vert[i]--;
                            aux++;
                            //printf("ADJ[%i]: %i \tVET_EX: %i \tK: %i \tVERT[%i]: %i\n",k,adj[k],vet_exclusao,k,i,vert[i]);
                            //puts("\n\n");
                        }
                        k++;
                    }
                }
                vert[vet_exclusao]=0;
                for(i=0;i<vet_exclusao;i++){
                    soma_grau+=vert[i];
                }
                for(i=0;i<aux2;i++){
                    adj[soma_grau]=0;
                    soma_grau++;
                }
                /*FUNCAO PARA ORDENAR VERT*/
                for(i=0;i<cont;i++){
                    for(j=0;j<cont-1;j++){
                        if(vert[j]==0){
                            aux2=vert[j+1];
                            vert[j+1]=vert[j];
                            vert[j]=aux2;
                        }
                    }
                }
                for(i=0;i<cont2;i++){
                    for(j=0;j<cont2-1;j++){
                        if(adj[j]==0){
                            //printf("AUX2: %i \tADJ[%i]: %i \tADJ[%i]: %i\n",aux2,j,adj[j],j+1,adj[j+1]);
                            aux2=adj[j+1];
                            adj[j+1]=adj[j];
                            adj[j]=aux2;
                        }
                    }
                }
                cont--;
                vert=(int *)realloc(vert,sizeof(int)*cont);
                for(i=0;i<cont2;i++){
                    if(adj[i]==vet_exclusao+1){
                        adj[j]=0;
                    }
                }
                for(i=0;i<cont2;i++){
                    for(j=0;j<cont2-1;j++){
                        if(adj[j]==0){
                            //printf("AUX2: %i \tADJ[%i]: %i \tADJ[%i]: %i\n",aux2,j,adj[j],j+1,adj[j+1]);
                            aux2=adj[j+1];
                            adj[j+1]=adj[j];
                            adj[j]=aux2;
                        }
                    }
                }
                cont2-=aux;
                adj=(int *)realloc(adj,sizeof(int)*cont2);
                for(i=0;i<cont2;i++){
                    if(adj[i]>vet_exclusao){
                        adj[i]--;
                    }
                }
                fp=fopen("entrada.txt","w");
                if(fp){
                    k=0;
                    for(i=0;i<cont;i++){
                        fprintf(fp,"%i: ",i+1);
                        for(j=0;j<vert[i];j++){
                            fprintf(fp,"%i ",adj[k]);
                            k++;
                        }
                        fprintf(fp,"\n");
                    }
                }
                fclose(fp);
                puts("Vertice removido com sucesso!\nDigite algo para continuar...");
                __fpurge(stdin);
                getchar();
            }
        }
        else if(opcao==0){
            return;
        }
    }while(opcao!=0);
}
