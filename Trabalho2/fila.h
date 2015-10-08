#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


//Estrutura da lista que será criada
typedef struct lista {
    struct sublista *valores;
    struct lista *proximo;
    int valor;
} Dados;

typedef struct sublista{
    int valor;
    struct sublista *proximo;
}SubDados;

typedef struct lista_peso{
    struct sublista_peso *valores;
    struct lista_peso *proximo;
    int valor;
} Dados_peso;

typedef struct sublista_peso{
    int valor;
    int peso;
    struct sublista_peso *proximo;
} SubDados_Peso;
//Funções para manusear os dados (irão retornar dados)
int   checa_vazio    (Dados *dados);

//Funções para mostrar dados
void  exibe_dados    (Dados *dados);
void  exibe_dados2   (Dados_peso *dados);
void  exibe_tamanho  (Dados *nova);

//Funções do Menu
void insere(int valor);
void insere_peso(int valor);
Dados *inserefim_lista(Dados *dados,int valor);
Dados_peso *inserefim_lista_peso(Dados_peso *dados_peso,int valor);
int inserefim_sublista(Dados *posicao,int valor);
int inserefim_sublista_pesos(Dados_peso *posicao,int valor,int peso);
void listavazia(void);

//Inicializando os dados da lista
Dados *principal = NULL;
Dados_peso *principal_peso=NULL;

void insere(int valor){
    principal=inserefim_lista(principal,valor);
}

void insere_peso(int valor){
    principal_peso=inserefim_lista_peso(principal_peso,valor);
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
    //A lista auxiliar será igual a Principal
    aux=principal;
    if(aux==NULL){
        aux=(Dados *)malloc(sizeof(Dados));
        aux->valores=NULL;
        aux->proximo=NULL;
        aux->valor=valor;
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
    return(inicio);
}

Dados_peso *inserefim_lista_peso(Dados_peso *dados_peso,int valor){
     //Criando listas auxiliares
    Dados_peso *final,*aux,*inicio;
    //Alocando dados para a posição final da lista
    final = (Dados_peso *)malloc(sizeof(Dados_peso));
    final->valor = valor;
    //Ainda nao temos valores na sublista.
    final->valores=NULL;
    //A pŕoxima posição será Nulo
    final->proximo=NULL;
    //A lista auxiliar será igual a Principal
    aux=principal_peso;
    if(aux==NULL){
        aux=(Dados_peso *)malloc(sizeof(Dados_peso));
        aux->valores=NULL;
        aux->proximo=NULL;
        aux->valor=valor;
        inicio=aux;
        return(inicio);
    }
    inicio=principal_peso;
    //Enquanto o próximo de auxiliar não for Nulo
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    //O último valor, será Nulo, e depois apontando para
    //o Final
    aux->proximo=NULL;
    aux->proximo=final;
    return(inicio);
}

int inserefim_sublista(Dados *posicao,int valor){
    SubDados *aux,*final;
    while(posicao->proximo!=NULL){
        posicao=posicao->proximo;
    }
    final=(SubDados *)malloc(sizeof(SubDados));
    final->proximo=NULL;
    final->valor=valor;
    aux=posicao->valores;
    if(aux==NULL){
        aux=(SubDados *)malloc(sizeof(SubDados));
        aux->proximo=NULL;
        aux->valor=valor;
        posicao->valores=aux;
        return 0;
    }
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=NULL;
    aux->proximo=final;
    return 0;
}


int inserefim_sublista_pesos(Dados_peso *posicao,int valor,int peso){
    SubDados_Peso *aux,*final;
    while(posicao->proximo!=NULL){
        posicao=posicao->proximo;
    }
    final=(SubDados_Peso *)malloc(sizeof(SubDados_Peso));
    final->proximo=NULL;
    final->valor=valor;
    final->peso=peso;
    aux=posicao->valores;
    if(aux==NULL){
        aux=(SubDados_Peso *)malloc(sizeof(SubDados_Peso));
        aux->proximo=NULL;
        aux->valor=valor;
        aux->peso=peso;
        posicao->valores=aux;
        return 0;
    }
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    aux->proximo=NULL;
    aux->proximo=final;
    return 0;
}

//Função que testa se a lista está vazia
void listavazia(void){
    if (principal == NULL)
        fprintf(stdout, "\n\nLista esta Vazia!\n\n ");
    getchar();
}

//Exibindo dados da lista
void exibe() {
    //Se não estiver vazio, exibe os dados
    if (!checa_vazio(principal))
        exibe_dados(principal);
}

void exibe_peso(){
    if(!checa_vazio_peso(principal_peso))
        exibe_dados2(principal_peso);
}

//Exibindo todos os dados do menu
void exibe_dados(Dados *dados) {
    Dados *aux;
    SubDados *aux2;
    SubDados_Peso *aux3;
    aux=principal;
    puts("Lista de Adjacencia sem Pesos\n");
    for (aux; aux != NULL; aux = aux->proximo) {
        aux2=aux->valores;
        printf("%i: ",aux->valor);
        for(aux2;aux2!=NULL;aux2=aux2->proximo){
            printf("%i -> ",aux2->valor);
        }
        printf("NULL\n");
    }
    getchar();
}

void exibe_dados2(Dados_peso *dados){
    Dados_peso *aux;
    SubDados_Peso *aux2;
    aux=principal_peso;
    puts("Lista de Adjacencia com Pesos\n");
    for(aux;aux != NULL;aux=aux->proximo){
        aux2=aux->valores;
        printf("%i: ",aux->valor);
        for(aux2;aux2!=NULL;aux2=aux2->proximo){
            printf("%i ",aux2->valor);
            printf("%i -> ",aux2->peso);
        }
        puts("NULL\n");
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

int checa_vazio_peso(Dados_peso *dados){
    if(dados==NULL){
        printf(stdout,"Lista Vazia!\n");
        getchar();
        return 1;
    }
    else
        return 0;
}

void lista_adjacencia(){
    FILE *fp=fopen("entrada.txt","r");
    int j,flag=0,leitura=0;
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
                    inserefim_sublista(principal,j);
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch=='\n'){
                    inserefim_sublista(principal,j);
                    leitura=0;
                    strcpy(ch2,"\0");
                }
            }
        }
    }
    exibe();
    principal=NULL;
}

void lista_adjacencia_pesos(){
    FILE *fp=fopen("entrada.txt","r");
    int j,x,flag=0,flag2=1,leitura=0;
    char str[50],ch,*p_ch,ch2[3];//String que recebera cada linha do arquivo
    p_ch=&ch2;
    if(!fp){//Caso o arquivo nao tenha sido aberto corretamente
        printf("Erro na abertura do arquivo de entrada\n");
    }
    else{//Caso o arquivo tenha sido aberto sem erros.
        //Enquanto nao chegar ao fim do arquivo armazene
        //as linhas lidas na string str.
        while((ch=fgetc(fp))!=EOF){
            if((ch!=':') && (ch!=' ') && (ch!='\n')){
                ch2[leitura]=ch;
                leitura++;
                ch2[leitura]='\0';
            }
            else{
                j=atoi(p_ch);
                if(ch==':'){
                    insere_peso(j);
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch==' ' && j!=0){
                    if(flag2==1){
                        x=j;
                        flag2=2;
                    }
                    else if(flag2==2){
                        inserefim_sublista_pesos(principal_peso,x,j);
                        flag2=1;
                    }
                    leitura=0;
                    strcpy(ch2,"\0");
                }
                else if(ch=='\n' && j!=0){
                    inserefim_sublista_pesos(principal_peso,x,j);
                    leitura=0;
                    strcpy(ch2,"\0");
                    flag2=1;
                }
            }
        }
    }
    exibe_peso();
    principal_peso=NULL;
}
