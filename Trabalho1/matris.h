#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int submenu(int **grafo,int t,int qnt_col,int opcao);

void matris_adjacencia(){
    FILE *fp=fopen("entrada.txt","r");
    char str[50],ch,*p_ch;//String que recebera cada linha do arquivo
                 //de entrada.
    int opcao,i,j,k=0, qnt_linhas=1,qnt_colunas=0,**matris,*vet_colunas,**grafo;
    matris=(int **)malloc(sizeof(int *));//aloca espaco na memoria
    matris[0]=(int *)malloc(sizeof(int));
    vet_colunas=(int *)malloc(sizeof(int));
    p_ch=&ch;
    //para uma matris de inteiros.
    if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("Erro na abertura do arquivo de entrada\n");
    }
    else{//Caso o arquivo tenha sido aberto sem erros.
        //Enquanto nao chegar ao fim do arquivo armazene
        //as linhas lidas na string str.
        while((ch=fgetc(fp))!=EOF){
            if(ch=='\n'){//Caso encontre uma nova linha
                qnt_linhas++;//aumentamos o contador de linhas
                k++;
                vet_colunas=(int *)realloc(vet_colunas,sizeof(int)*k);
                vet_colunas[k-1]=qnt_colunas;
                qnt_colunas=0;//zeramos o contador das colunas
                matris=(int **)realloc(matris,sizeof(int *)*qnt_linhas);//reallocamos o tamanho de linhas da matris
                matris[qnt_linhas-1]=(int *)malloc(sizeof(int));
                //puts("\n");
            }
            else if((ch!=':') && (ch!=' ')){//caso ch seja diferente de : e de espacos em branco
                j=atoi(p_ch);//pegamos o valor numerico de ch
                qnt_colunas++;//aumentamos o valor de colunas
                matris[qnt_linhas-1]=(int *)realloc((matris[qnt_linhas-1]),sizeof(int)*qnt_colunas);//alocamos tamanho para
                //de colunas para colocarmos o valor de j.
                matris[qnt_linhas-1][qnt_colunas-1]=j;
               // printf("%i ",matris[qnt_linhas-1][qnt_colunas-1]); //DESCOMENTE ESSA LINHA PARA TESTAR A MATRIS!
            }
        }
        if(ch==EOF){
             k++;
             vet_colunas=(int *)realloc(vet_colunas,sizeof(int)*k);
             vet_colunas[k-1]=qnt_colunas;
             qnt_colunas=0;
        }
        grafo=(int **)malloc(sizeof(int *)*(qnt_linhas));
            for(i=0;i<qnt_linhas;i++){
                grafo[i]=(int *)malloc(sizeof(int)*(qnt_linhas));
            }
        //utilizamos este for para inicializarmos a matris
        //com todos os elementos com valor 0
        int lin_aux,col_aux;
        for(i=0;i<qnt_linhas;i++){
            for(j=0;j<qnt_linhas;j++){
                grafo[i][j]=0;
            }
        }
        for(i=0;i<qnt_linhas-1;i++){
            for(j=1;j<vet_colunas[i];j++){
                if(grafo[i][matris[i][j]-1]!=0){
                    grafo[i][matris[i][j]-1]+=1;
                }
                else if(grafo[i][matris[i][j]-1]==0){
                    grafo[i][matris[i][j]-1]=1;
                }
            }
        }
        do{
            limpa();
            //ESCREVENDO A MATRIS DO GRAFO PRONTO!
            puts("Matris de Adjacencia\n");
            puts("--------------------------------------------------\n");
            for(i=0;i<qnt_linhas-1;i++){
                for(j=0;j<qnt_linhas-1;j++){
                    printf("|%i\t",grafo[i][j]);
                }
                puts("|\n");
            }
            puts("--------------------------------------------------\n");
            opcao=submenu(grafo,qnt_linhas-1,qnt_linhas-1,1);
        }while(opcao!=0);
    }
    fclose(fp);
}

void matris_incidencia(int opcao){
    FILE *fp=fopen("entrada.txt","r");
    char str[50],ch,*p_ch;//String que recebera cada linha do arquivo
                 //de entrada.
    int **grafo,opcao2;
    int i,j,p=0,k=0,t=0,x=0,qnt_linhas=1,qnt_colunas=0,**matris,*vet_colunas,*vet_arestas,somatorio=0,flag=0,*vet_aux;
    matris=(int **)malloc(sizeof(int *));//aloca espaco na memoria
    matris[0]=(int *)malloc(sizeof(int));
    vet_colunas=(int *)malloc(sizeof(int));
    vet_arestas=(int *)malloc(sizeof(int));
    vet_aux=(int *)malloc(sizeof(int));
    p_ch=&ch;
    //para uma matris de inteiros.
    if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("Erro na abertura do arquivo de entrada\n");
    }
    else{//Caso o arquivo tenha sido aberto sem erros.
        //Enquanto nao chegar ao fim do arquivo armazene
        //as linhas lidas na string str.
        while((ch=fgetc(fp))!=EOF){
            if(ch=='\n'){//Caso encontre uma nova linha
                qnt_linhas++;//aumentamos o contador de linhas
                k++;
                vet_colunas=(int *)realloc(vet_colunas,sizeof(int)*k);
                vet_colunas[k-1]=qnt_colunas;
                somatorio+=qnt_colunas;
                qnt_colunas=0;//zeramos o contador das colunas
                matris=(int **)realloc(matris,sizeof(int *)*qnt_linhas);//reallocamos o tamanho de linhas da matris
                matris[qnt_linhas-1]=(int *)malloc(sizeof(int));
                //puts("\n");
                flag=0;
                x=0;
            }
            else if((ch!=':') && (ch!=' ')){//caso ch seja diferente de : e de espacos em branco
                j=atoi(p_ch);//pegamos o valor numerico de ch
                qnt_colunas++;//aumentamos o valor de colunas
                matris[qnt_linhas-1]=(int *)realloc((matris[qnt_linhas-1]),sizeof(int)*qnt_colunas);//alocamos tamanho para
                //de colunas para colocarmos o valor de j.
                matris[qnt_linhas-1][qnt_colunas-1]=j;
               // printf("%i ",matris[qnt_linhas-1][qnt_colunas-1]); //DESCOMENTE ESSA LINHA PARA TESTAR A MATRIS!
                if(flag==0){
                    p++;//UTILIZAMOS P COMO UMA VARIAVEL CONTADORA
                    vet_aux=(int *)realloc(vet_aux,sizeof(int)*p);
                    vet_aux[p-1]=j;//UTILIZAMOS VET_AUX PARA GUARDAR OS PIMEIROS ELEMENTOS DA PRIMEIRA COLUNA DO FP
                }
                else if(flag==1){
                    t++;//Utilizamos t como uma variavel contadora
                    x++;
                    vet_arestas=(int *)realloc(vet_arestas,sizeof(int)*t);
                    vet_arestas[t-1]=j;//utilizamos vet_arestas para guardar os elementos que nao sao da primeira coluna
                    if(x>1){//Se e a segunda vez que e lido um numero na mesma linha
                        p++;
                        vet_aux=(int *)realloc(vet_aux,sizeof(int)*p);
                        vet_aux[p-1]=vet_aux[p-2];
                    }
                }
                flag=1;
            }
        }
        if(ch==EOF){
             k++;
             vet_colunas=(int *)realloc(vet_colunas,sizeof(int)*k);
             vet_colunas[k-1]=qnt_colunas;
             somatorio+=qnt_colunas;
             qnt_colunas=0;
        }
        if(opcao==1){//Chamamos o codigo da matris incidencia nao direcionado
            grafo=(int **)malloc(sizeof(int *)*(t));
            for(i=0;i<t;i++){
                grafo[i]=(int *)malloc(sizeof(int)*(qnt_linhas));
            }
            for(i=0;i<t;i++){
                for(j=0;j<qnt_linhas;j++){
                    grafo[i][j]=0;
                }
            }
            j=0;
            k=0;
            /*for(i=0;i<t;i++){
                if(k==vet_colunas[j]-1){
                    j++;
                    k=0;
                }
                grafo[vet_arestas[i]-1][j]++;
                k++;
            }*/
            for(i=0;i<t;i++){
                grafo[i][vet_aux[i]-1]=1;
                grafo[i][vet_arestas[i]-1]=1;
            }
            do{
                limpa();
                //ESCREVENDO A MATRIS DO GRAFO PRONTO!
                puts("Matris de Incidencia Nao Ordenada\n\n");
                puts("--------------------------------------------------\n");
                for(i=0;i<t;i++){
                    for(j=0;j<qnt_linhas-1;j++){
                        printf("|%i\t",grafo[i][j]);
                    }
                    puts("|\n");
                }
            puts("--------------------------------------------------\n");
            opcao2=submenu(grafo,t,qnt_linhas-1,2);
            }while(opcao2!=0);
        }
        else if(opcao==2){//Chamamos o codigo para matris incidencia ordenado
             grafo=(int **)malloc(sizeof(int *)*(t));
            for(i=0;i<t;i++){
                grafo[i]=(int *)malloc(sizeof(int)*(qnt_linhas));
            }
            for(i=0;i<t;i++){
                for(j=0;j<qnt_linhas;j++){
                    grafo[i][j]=0;
                }
            }
            j=0;
            k=0;
            for(i=0;i<t;i++){
                grafo[i][vet_aux[i]-1]=1;
                grafo[i][vet_arestas[i]-1]=-1;
            }
            do{
                limpa();
                puts("Matris de Incidencia Ordenada\n\n");
                puts("-------------------------------------------------\n");
                for(i=0;i<t;i++){
                    for(j=0;j<qnt_linhas;j++){
                        printf("|%i\t",grafo[i][j]);
                    }
                    puts("|\n");
                }
                puts("--------------------------------------------------\n");
                opcao2=submenu(grafo,t,qnt_linhas,3);
            }while(opcao2!=0);
        }
    }
    fclose(fp);
}

int submenu(int **grafo,int t,int qnt_col,int opcao){
    FILE *fp;
    int opcao2,vet_exclusao,tamanho,i,j,k,vez=1,cont,gravar=0;
    char ch;
    if(!fp){
        puts("Erro na abertura do arquivo!\n");
    }
    else{
        puts("\tOPERACOES\t\n");
        puts("--------------------------------\n");
        puts("Digite 1 para excluir um vertice\n");
        puts("Digite 2 para inserir um vertice\n");
        puts("Digite 0 para voltar ao menu anterior\n");
        puts("--------------------------------\n");
        scanf("%i",&opcao2);
        if(opcao2==1){
            gravar=1;
            printf("Digite o vertice que deseja excluir\n:>>");
            scanf("%i",&vet_exclusao);
            vet_exclusao--;
            if(vet_exclusao>t-1 || vet_exclusao<0){
                puts("Vetor inesistente\n");
                gravar=0;
            }
            else{
                for(i=0;i<qnt_col;i++){
                    grafo[vet_exclusao][i]=0;
                }
            }
        }
        else if(opcao2==2){
            gravar=1;
        }
        else if(opcao2==0){
            return 0;
        }
    }
    if(gravar==1){
        limpa();
        /*GRAVAMOS AGORA O GRAFO MODIFICADO EM ARQUIVO!*/
        if(opcao==1){
            fp=fopen("entrada.txt","w");
            for(i=0;i<t;i++){
                for(j=0;j<qnt_col;j++){
                    printf("%i |",grafo[i][j]);
                    if(grafo[i][j]!=0){
                       if(vez==1){
                            fprintf(fp,"%i: %i",i+1,j+1);
                            vez=0;
                       }
                       else{
                            for(k=0;k<grafo[i][j];k++)
                                fprintf(fp," %i",j+1);
                       }
                    }
                    if(j==qnt_col-1){
                        fprintf(fp,"\n");
                        puts("\n");
                        vez=1;
                    }
                }
                puts("\n");
            }
            fclose(fp);
        }
        else if(opcao==2){
            fp=fopen("entrada.txt","r");
            int contador_numeros=0,*contador_total,qnt_linhas=0,i,indice=0,aux=0,soma=0;
            contador_total=(int *)malloc(sizeof(int));
            if(fp){
                while((ch=fgetc(fp))!=EOF){
                    if(ch!=':' && ch!=' ' && ch!='\n'){
                        contador_numeros++;
                    }
                    if(ch=='\n'){
                        qnt_linhas++;
                        contador_total=(int *)realloc(contador_total,sizeof(int)*qnt_linhas);
                        contador_total[qnt_linhas-1]=contador_numeros-1;
                        contador_numeros=0;
                    }
                }
            }
            fclose(fp);
            fp=fopen("entrada.txt","w");
            if(fp){
                for(i=0;i<qnt_linhas;i++){
                    soma+=contador_total[i];
                    if(soma>vet_exclusao){
                        contador_total[i]--;
                        break;
                    }
                }
                for(i=0;i<t;i++){
                    for(j=0;j<qnt_col;j++){
                        printf("%i |",grafo[i][j]);
                        if(j!=indice && grafo[i][j]==1){
                            if(vez==1){
                                fprintf(fp,"%i: %i",indice+1,j+1);
                                vez=0;
                                aux++;
                            }
                            else{
                                fprintf(fp," %i",j+1);
                                aux++;
                            }
                        }
                    }
                    if(aux==contador_total[indice]){
                        indice++;
                        fprintf(fp,"\n");
                        puts("\n");
                        vez=1;
                        aux=0;
                    }
                }
            }
            fclose(fp);
        }
        else if(opcao==3){
            fp=fopen("entrada.txt","r");
            int contador_numeros=0,*contador_total,qnt_linhas=0,indice=0,aux=0,soma=0,*aux_lin;
            contador_total=(int *)malloc(sizeof(int));
            aux_lin=(int *)malloc(sizeof(int));
            vez=1;
            if(fp){
                while((ch=fgetc(fp))!=EOF){
                    if(ch!=':' && ch!=' ' && ch!='\n'){
                        if(vez==1){
                            aux=ch;
                            aux-=48;
                            aux_lin[qnt_linhas]=aux;
                            aux=0;
                            vez=0;
                        }
                        contador_numeros++;
                    }
                    if(ch=='\n'){
                        qnt_linhas++;
                        aux_lin=(int *)realloc(aux_lin,sizeof(int)*qnt_linhas);
                        contador_total=(int *)realloc(contador_total,sizeof(int)*qnt_linhas);
                        contador_total[qnt_linhas-1]=contador_numeros-1;
                        contador_numeros=0;
                        vez=1;
                    }
                }
            }
            fclose(fp);
            fp=fopen("entrada.txt","w");
            if(fp){
               for(i=0;i<qnt_linhas;i++){
                    soma+=contador_total[i];
                    if(soma>vet_exclusao){
                        contador_total[i]--;
                        break;
                    }
                }
                for(i=0;i<t;i++){
                    for(j=0;j<qnt_col;j++){
                        if(j!=(grafo[i][j]==1)&& grafo[i][j]==-1){
                            if(vez==1){
                                fprintf(fp,"%i: %i",aux_lin[indice],j+1);
                                vez=0;
                                aux++;
                            }
                            else{
                                fprintf(fp," %i",j+1);
                                aux++;
                            }
                        }
                    }
                    if(aux==contador_total[indice]){
                        indice++;
                        fprintf(fp,"\n");
                        vez=1;
                        aux=0;
                    }
                }
            }
            fclose(fp);
        }
    }
    puts("Vertice removido com sucesso!\n");
    getchar();
    sleep(1);
    return 0;
}
