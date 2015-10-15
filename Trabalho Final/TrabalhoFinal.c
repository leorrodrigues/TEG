#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void limpa(void){
    system("/usr/bin/clear");
}

//Estrutura para salvar a tabela do dijkstra
typedef struct tabela{
    int vertice;
    int estimativa;
    int precedente;
} tabela;

//Estrutura da lista que será criada
typedef struct lista {
    struct sublista *valores;
    struct lista *proximo;
    struct lista *anterior;
    int valor;
} Dados;

typedef struct sublista{
    int valor;
    int visitado;
    int peso;
    struct sublista *proximo;
    struct sublista *anterior;
}SubDados;

//Funções para manusear os dados (irão retornar dados)
int   checa_vazio    (Dados *dados);

//Funções para mostrar dados
void  exibe_dados    (Dados *dados);
void  exibe_tamanho  (Dados *nova);

//Funções do Menu
void insere(int valor);
Dados *inserefim_lista(Dados *dados,int valor);
int inserefim_sublista(Dados *posicao,int valor, int peso);
void listavazia(void);

//Inicializando os dados da lista
Dados *principal = NULL;

void insere(int valor){
    principal=inserefim_lista(principal,valor);
}

//Inserção de dados no final de uma lista
Dados *inserefim_lista(Dados *dados,int valor) {
    //Criando listas auxiliares
    Dados *final,*aux,*inicio;
    //Alocando dados para a posição final da lista
    final = (Dados *)malloc(sizeof(Dados));
    final->valor = valor;
    //Ainda nao temos valores na sublista.
    final->valores=NULL;
    //A pŕoxima posição será Nulo
    final->proximo=NULL;
    final->anterior=NULL;
    //A lista auxiliar será igual a Principal
    aux=principal;
    if(aux==NULL){
        aux=(Dados *)malloc(sizeof(Dados));
        aux->valores=NULL;
        aux->proximo=NULL;
        aux->valor=valor;
        aux->anterior=NULL;
        inicio=aux;
        return(inicio);
    }
    inicio=principal;
    //Enquanto o próximo de auxiliar não for Nulo
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    //O último valor, será Nulo, e depois apontando para
    //o Final
    aux->proximo=NULL;
    aux->proximo=final;
    final->anterior=aux;
    return(inicio);
}

int inserefim_sublista(Dados *posicao,int valor,int peso){
    SubDados *aux,*final;
    while(posicao->proximo!=NULL){
        posicao=posicao->proximo;
    }
    final=(SubDados *)malloc(sizeof(SubDados));
    final->proximo=NULL;
    final->valor=valor;
    final->anterior=NULL;
    final->visitado=0;
    final->peso=peso;
    aux=posicao->valores;
    if(aux==NULL){
        aux=(SubDados *)malloc(sizeof(SubDados));
        aux->proximo=NULL;
        aux->valor=valor;
        aux->anterior=NULL;
        aux->visitado=0;
        aux->peso=peso;
        posicao->valores=aux;
        return 0;
    }
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=NULL;
    aux->proximo=final;
    final->anterior=aux;
    return 0;
}

//Função que testa se a lista está vazia
void listavazia(void){
    if (principal == NULL)
        fprintf(stdout, "\n\nLista esta Vazia!\n\n ");
    getchar();
}

Dados *retorna_lista(Dados *aux){
    for(aux;aux->anterior!=NULL;aux=aux->anterior)
        for(aux->valores;aux->valores->anterior!=NULL;aux->valores=aux->valores->anterior);
    for(aux->valores;aux->valores->anterior!=NULL;aux->valores=aux->valores->anterior);
    return(aux);
}

//Exibindo dados da lista
void exibe(Dados *aux) {
    //Se não estiver vazio, exibe os dados
    if (!checa_vazio(aux))
        exibe_dados(aux);
}

//Exibindo todos os dados do menu
void exibe_dados(Dados *dados) {
    Dados *aux;
    SubDados *aux2;
    aux=dados;
    puts("Lista de Adjacencia sem Pesos\n");
    for (aux; aux != NULL; aux = aux->proximo) {
        aux2=aux->valores;
        printf("%i: ",aux->valor);
        for(aux2;aux2!=NULL;aux2=aux2->proximo){
            printf("%i %i %i-> ",aux2->valor,aux2->visitado,aux2->peso);
        }
        printf("NULL\n");
    }
}

//Função que testa se a lista esta vazia
int checa_vazio(Dados *dados) {
    //Se a lista estiver vazia
    if (dados == NULL) {
            fprintf(stdout, "Lista vazia!\n");
            getchar();
            return 1;
    } else
            return 0;
}

void *lista_adjacencia(){
    FILE *fp=fopen("entrada.txt","r");
    int j,flag=0,leitura=0,flag2=1,p;
    char str[50],ch,*p_ch,ch2[3];//String que recebera cada linha do arquivo
    p_ch=&ch2;
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
                j=atoi(p_ch);//pegamos o valor numerico de ch
                if(ch==':'){
                    insere(j);
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch==' ' && j!=0){
                    if(flag2==1){
                        p=j;
                        flag2=2;
                    }
                    else if(flag2==2){
                        inserefim_sublista(principal,p,j);
                        flag2=1;
                    }
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch=='\n'){
                    inserefim_sublista(principal,p,j);
                    leitura=0;
                    strcpy(ch2,"\0");
                    flag2=1;
                }
            }
        }
    }
}

tabela *dms(Dados *aux,tabela *t1){
    int cont=0,acumulador=100,temp=0,i,x,flag=0;
    //Para utilizarmos dijkstra, precisamos percorrer os visinhos do primeiro no
    while(aux->valores->proximo!=NULL){
        cont++;//aumentamos o contador para saber em qual no da sublista estamos
        aux->valores->visitado=1;
        if((aux->valores->peso)<acumulador){//verificamos qual no tem menor peso
            acumulador=aux->valores->peso;//guardamos o valor do no
            temp=cont;//guardamos a posicao deste no
        }
        /*Temos que atualizar a tabela*/
        if(t1[aux->valores->valor-1].estimativa>aux->valores->peso+t1[aux->valor-1].estimativa){
            t1[aux->valores->valor-1].estimativa=aux->valores->peso+t1[aux->valor-1].estimativa;
            t1[aux->valores->valor-1].precedente=aux->valor;
        }
        /********************************/
        if(aux->valores->proximo!=NULL)//caso nao seja nulo o proximo elemento
            aux->valores=aux->valores->proximo;//va para o proximo elemento
    }
    if(aux->valores->proximo==NULL){//caso esteja no ultimo elemento refaz o bloco de codigo acima
        cont++;
        aux->valores->visitado=1;
        if((aux->valores->peso)<acumulador){
            acumulador=aux->valores->peso;
            temp=cont;
        }
        /*Temos que atualizar a tabela*/
        if(t1[aux->valores->valor-1].estimativa>aux->valores->peso+t1[aux->valor-1].estimativa){
            t1[aux->valores->valor-1].estimativa=aux->valores->peso+t1[aux->valor-1].estimativa;
            t1[aux->valores->valor-1].precedente=aux->valor;
        }
        /***************************************************************/
    }//agora temos o valor do vertice visinho que contem o melhor no e seu valor de peso.
    for(aux->valores;aux->valores->anterior!=NULL;aux->valores=aux->valores->anterior);//retornamos para o inicio da sublista
    /*printf("Cont %i temp %i acumulador %i",cont,temp,acumulador);*/
    /******************************************************************/
    //Usamos para imprimir a tabela
    /*for(i=0;i<5;i++){
        printf("\n%i %i %i\n",t1[i].vertice,t1[i].estimativa,t1[i].precedente);
    }*/
    /******************************************************************/
    for(i=1;i<temp;i++){
        aux->valores=aux->valores->proximo;
    }//posicionamos o ponteiro na posicao de menor peso
    x=aux->valores->valor;//guardamos o valor do no
    for(aux->valores;aux->valores->anterior!=NULL;aux->valores=aux->valores->anterior);//voltamos o ponteiro da sublista p/inicio
    while(aux->valor!=x){
        if(aux->proximo!=NULL)
            aux=aux->proximo;
        else
            aux=retorna_lista(aux);//voltamos o ponteiro para o inicio da lista.
    }
    /********************************************************************/
    //Vemos o movimento realizado nao levou a um no que ja foi todo visitado
    flag=1;
    while(aux->valores->proximo!=NULL){
        if(aux->valores->visitado==0)
            flag=0;
        if(aux->valores->proximo!=NULL)
            aux->valores=aux->valores->proximo;
    }
    if(aux->valores->visitado==0)
        flag=0;
    for(aux->valores;aux->valores->anterior!=NULL;aux->valores=aux->valores->anterior);
    /*Se todos os vertices foram visitados e nao se pode fazer mais uma jogada devemos procurar o vertice que nao tenha sido
    visitado ainda*/
    if(flag==1){
        aux=retorna_lista(aux);//voltamos a lista para o inicio
        while(aux->valores->visitado==1){
            if(aux->valores->proximo!=NULL)
                aux->valores=aux->valores->proximo;
            else
                if(aux->proximo!=NULL)
                    aux=aux->proximo;
                else
                    return(t1);
        }
    }
    /******************************************************************/
    return(dms(aux,t1));
}

void dijkstra(){
    Dados *aux;
    tabela *t1;
    int cont=1,i,j;
    aux=principal;
    for(aux;aux->proximo!=NULL;aux=aux->proximo)
        cont++;
    aux=retorna_lista(aux);
    for(j=0;j<cont;j++){
        t1=(tabela *)malloc(sizeof(tabela));
        for(i=0;i<cont;i++){
            t1[i].precedente=(tabela *)malloc(sizeof(int));
            t1[i].estimativa=(tabela *)malloc(sizeof(int));
            t1[i].vertice=(tabela *)malloc(sizeof(int));
        }
        for(i=0;i<cont;i++){
            t1[i].vertice=i+1;
            t1[i].estimativa=1000;
            t1[i].precedente=NULL;
        }
        t1[j].precedente=1;
        t1[j].estimativa=0;
        for(i=0;i<j;i++)
            aux=aux->proximo;
        t1=dms(aux,t1);
        printf("\033[31;2m");
        puts("\t\t\tTABELA DIJKSTRA\t\n");
        printf("VERTICES:");
        for(i=0;i<cont;i++){
            printf("\t%i",t1[i].vertice);
        }
        puts("");
        printf("ESTIMATIVAS:");
        for(i=0;i<cont;i++){
            printf("\t%i",t1[i].estimativa);
        }
        puts("");
        printf("PRECEDENTES:");
        for(i=0;i<cont;i++){
            printf("\t%i",t1[i].precedente);
        }
        puts("");
        printf("\033[m");
        principal=NULL;
        lista_adjacencia();
        aux=principal;
    }
}

int main(){
    lista_adjacencia();
    dijkstra();
    puts("\n");
    return 0;
}
