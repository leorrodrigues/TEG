#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void limpa(void){
    system("/usr/bin/clear");
}

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
int inserefim_sublista(Dados *posicao,int valor);
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

int inserefim_sublista(Dados *posicao,int valor){
    SubDados *aux,*final;
    while(posicao->proximo!=NULL){
        posicao=posicao->proximo;
    }
    final=(SubDados *)malloc(sizeof(SubDados));
    final->proximo=NULL;
    final->valor=valor;
    final->anterior=NULL;
    final->visitado=0;
    aux=posicao->valores;
    if(aux==NULL){
        aux=(SubDados *)malloc(sizeof(SubDados));
        aux->proximo=NULL;
        aux->valor=valor;
        aux->anterior=NULL;
        aux->visitado=0;
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
            printf("%i %i-> ",aux2->valor,aux2->visitado);
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
}

Dados *dms(Dados *arvore){
    Dados *aux;
    int x,y;
    aux=arvore;
    for(aux->valores;aux->valores->proximo!=NULL;aux->valores=aux->valores->proximo){
        x=arvore->valor;//armazenamos o valor do no
        while(arvore->valores->visitado!=0){//fazemos esta funcao para descobrirmos o no adjacente que nao tenha sido visitado
            if(arvore->valores->proximo!=NULL){//fazemos esta verificacao para nao dar coredump
                arvore->valores=arvore->valores->proximo;
            }
            else{
                //puts("PUXANDO A FUNCAO PELO AUX");
                return(dms(arvore));//Caso tenha ido ate o final e seja nulo, terminamos a funcao dms
            }
        }
        y=arvore->valores->valor;//guardamos o valor do no adjacente.
        arvore->valores->visitado=1;//Falamos que ja visitamos este no.
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);//voltamos a sublista p/inicio.
        //Agora devemos percorrer ate encontrarmos o vertice com valor de Y
        while(arvore->valor!=y){
            if(arvore->proximo!=NULL){
                arvore=arvore->proximo;
            }
            else{//Caso seja nulo, volte para o inicio da lista
                for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior);
            }
        }
        //Ao sair desta funcao, ja temos o ponteiro arvore apontando para o devido valor da lista, agora procuramos o valor da
        //sublista que corresponda ao valor de X
        while(arvore->valores->valor!=x){
            arvore->valores=arvore->valores->proximo;
        }
        //Agora possuimos o devido valor da sublista que contem o valor de X
        arvore->valores->visitado=1;//Marcamos como visitado este valor da sublista
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);//voltamos a sublista p/inicio.
        //agora realizamos a chamada recursiva da funcao
        //exibe(arvore);
        //puts("PUXANDO A FUNCAO NORMAL");
        //exibe(arvore);
        return(dms(arvore));
    }
    if(aux->valores->proximo==NULL){
        aux->valores->visitado=1;
        x=arvore->valor;//armazenamos o valor do no
        y=arvore->valores->valor;//guardamos o valor do no adjacente.
        //Agora devemos percorrer ate encontrarmos o vertice com valor de Y
        while(arvore->valor!=y){
            if(arvore->proximo!=NULL){
                arvore=arvore->proximo;
            }
            else{//Caso seja nulo, volte para o inicio da lista
                for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior);
            }
        }
        //sublista que corresponda ao valor de X
        while(arvore->valores->valor!=x){
            if(arvore->valores->proximo!=NULL){
                arvore->valores=arvore->valores->proximo;
            }
        }
        //Agora possuimos o devido valor da sublista que contem o valor de X
        arvore->valores->visitado=1;//Marcamos como visitado este valor da sublista
        //return(dms(arvore));
    }
    for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior)//usamos este aninhamento de for para voltarmos a lista ao estado inicial
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    //puts("FINAL:");
    //exibe(arvore);
    //getchar();
    //limpa();
    //arvore=principal;
    //aux=principal;
    //printf("VALOR AUX: %i VALORES AUX: %i PROXIMO AUX: %i\n",aux->valor,aux->valores->valor,aux->valores->proximo);
    //return(arvore);
}

void conexo(){
    Dados *arvore;
    int i,cont=1,flag=0;
    arvore=principal;
    for(;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo)
        cont++;//Utilizamos este contador para sabermos quantas vezes repetimos a funcao dms
    for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);//Utilizamos para retornar ao inicio sublista
    for(i=0;i<=cont;i++){
        dms(arvore);
    }
    //Agora que realizamos a funcao, veremos se todos os vertices foram visitados, se algum nao foi visitado, temos um
    //grafo desconexo
    arvore=principal;
    do{
        do{
            if(arvore->valores->visitado==0){
                flag=1;
                break;
            }
            if(arvore->valores->proximo!=NULL)
                arvore->valores=arvore->valores->proximo;
        }while(arvore->valores->proximo!=NULL);
        if(flag==1)
            break;
        if(arvore->proximo!=NULL)
            arvore=arvore->proximo;
    }while(arvore->proximo!=NULL);
    if(flag==0){//Se o grafo for conexo, encerramos a funcao
        puts("GRAFO CONEXO!\n");
        return;
    }
    else{
        puts("GRAFO DISCONEXO!\n");
    }
    //Agora voltamos o ponteiro de arvore para o inicio
    //for(;arvore->anterior!=NULL;arvore=arvore->anterior)
        //for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    //for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    //Agora possuimos o ponteiro corrigido, se o grafo e desconexo, devemos refazer as iteracoes ate achar o conexo
    int qnt_disconexo=1;//inicializamos em 1 pois ja sabemos que o grafo e disconexo
    while(flag!=0){
        //*****************************************************************************
        //Utilizamos esta funcao para saber se ainda ha mais disconexos
        cont=1;
        for(;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo)
            cont++;//Utilizamos este contador para sabermos quantas vezes repetimos a funcao dms
        for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);//Utilizamos para retornar ao inicio sublista
        for(i=0;i<=cont;i++){
            //printf("valor: %i\n",arvore->valor);
            dms(arvore);
        }
        //*****************************************************************************
        //executamos esta funcao para checar se ainda existem vertices nao visitados
        arvore=principal;
        flag=0;
        do{
            do{
                if(arvore->valores->visitado==0){
                    //exibe(arvore);
                    flag=1;
                    break;
                }
                if(arvore->valores->proximo!=NULL)
                    arvore->valores=arvore->valores->proximo;
            }while(arvore->valores->proximo!=NULL);
            if(flag==1)
                break;
            if(arvore->proximo!=NULL)
                arvore=arvore->proximo;
        }while(arvore->proximo!=NULL);
        //exibe(arvore);
        //exibe(principal);
        //*******************************************************************************
        qnt_disconexo++;
    }
    for(;arvore->anterior!=NULL;arvore=arvore->anterior)
        for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    for(;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    //exibe(arvore);
    printf("Quantidade de componentes do Grafos Disconexo: %i\n",qnt_disconexo);
    getchar();
}

int main(){
    lista_adjacencia();
    exibe(principal);
    puts("\n");
    conexo();
    return 0;
}
