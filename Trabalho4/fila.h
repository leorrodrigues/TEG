#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


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


int percorre(Dados *arvore,int i,int n){
    limpa();
    int j,x,y,valor_ini,vezes=0,z=0,cont_visitados=0,valor=0,*contador;
    Dados *aux2;
    contador=(int *)malloc(sizeof(int));
    for(j=0;j<i;j++){
        arvore=arvore->proximo;
    }
    valor_ini=arvore->valor;
    /*for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    }//FUNCAO QUE RETORNA A ARVORE AO SEU ESTADO ORIGINAL!*/
    while(cont_visitados!=n){
          cont_visitados=0;
          valor=0;
          while(arvore->valor!=valor_ini){
              if(arvore->proximo==NULL)//Voltamos para o inicio da lista.
                for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior)
                    for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo);
              else
                arvore=arvore->proximo;
          }
          while(arvore->valores!=NULL){//enquanto estivermos olhando a sublista do elemento passado em arvore
                x=arvore->valor;//guardamos o valor do elemento da sublista
                for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
                while(arvore->valores->visitado==1){
                    if(arvore->valores->proximo!=NULL)
                        arvore->valores=arvore->valores->proximo;
                    else
                        break;
                }
                y=arvore->valores->valor;
                arvore->valores->visitado=1;
                while(arvore->valor!=y){//enquanto o valor da LISTA nao for o valor obtido na SUBLISTA
                    if(arvore->proximo==NULL){
                        //retornamos a arvore;
                        for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
                            for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
                        }
                    }
                    else{
                        arvore=arvore->proximo; //caminhamos pela arvore, no a no.
                    }
                }
                valor++;
                while(arvore->valores->valor!=x){//enquanto o subvalor nao for o valor da lista principal
                    if(arvore->valores->proximo!=NULL)
                        arvore->valores=arvore->valores->proximo;
                    else
                        break;
                }
                arvore->valores->visitado=1;
                for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
                while(arvore->valores->valor==1){
                    if(arvore->valores->proximo!=NULL){
                        arvore->valores=arvore->valores->proximo;
                    }
                    else
                        break;
                }
                if(arvore->valores->proximo==NULL){
                    arvore->valores->visitado=1;
                    break;
                }
                //printf("Valor de saida: %i\n",arvore->valor);
               // getchar();
        }
        z++;
        contador=(int *)realloc(contador,sizeof(int)*z);
        contador[z-1]=valor;
        //retornamos a arvore;
        for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
            for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
        }
        for(arvore;arvore->proximo!=NULL;arvore=arvore->proximo){
            for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo)
                if(arvore->valores->visitado==1)
                    cont_visitados++;
            if(arvore->valores->proximo==NULL){
                if(arvore->valores->visitado==1)
                    cont_visitados++;
            }
        }
        for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo)
            if(arvore->valores->visitado==1)
                cont_visitados++;
        if(arvore->valores->proximo==NULL){
            if(arvore->valores->visitado==1)
                cont_visitados++;
        }
        //retornamos a arvore;
        for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
            for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
        }
        //getchar();
        if(vezes==25)
            break;
        vezes++;
    }
    valor=0;
    for(i=0;i<z;i++){
        if(valor<contador[i])
            valor=contador[i];
    }
    for(arvore;arvore->proximo!=NULL;arvore=arvore->proximo){
        for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo){
            arvore->valores->visitado=0;
        }
        if(arvore->valores->proximo==NULL)
            arvore->valores->visitado=0;
    }
    for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo)
        arvore->valores->visitado=0;
    if(arvore->valores->proximo==NULL)
        arvore->valores->visitado=0;
    //retornamos a arvore;
    for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    }
    return(valor);
}

int centro_arvore(){
    Dados *arvore,*arvore2;
    int contador,*excentricidades,i=0,j,centro=100,total_vertices=1,n=1;
    arvore=principal;
    excentricidades=(int *)malloc(sizeof(int));
    /*funcao que descobre quantos vertices a arvore possui*/
    for(arvore;arvore->proximo!=NULL;arvore=arvore->proximo)
        total_vertices++;
    for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior);
    for(arvore;arvore->proximo!=NULL;arvore=arvore->proximo){
        if(arvore->valores!=NULL)
            n++;
        for(arvore->valores;arvore->valores->proximo!=NULL;arvore->valores=arvore->valores->proximo){
            n++;
        }
    }
    for(arvore;arvore->anterior!=NULL;arvore=arvore->anterior){
        for(arvore->valores;arvore->valores->anterior!=NULL;arvore->valores=arvore->valores->anterior);
    }
    /*Precisamos criar uma funcao a qual percora todos os nos, para isto utilizaremos uma funcao WHILE(no->prox!=NULL) ela se chama
    recursivamente, para tendo como retorno, um contador, para sabermos quantas vezes ela "andou", o maior valor do contador, sera
    guardado para fazer o comparativo das excentricidades*/
    while(total_vertices!=0){
        contador=percorre(arvore,i,n);
        i++;
        excentricidades=(int *)realloc(excentricidades,sizeof(int)*i);
        excentricidades[i-1]=contador;
        total_vertices--;
    }
    for(j=0;j<i;j++){
        if(excentricidades[j]<centro)
            centro=excentricidades[j];
            //printf("%i ",excentricidades[j]);
    }
    printf("Vertices que sao o centro(s) da arvore: ");
    for(j=0;j<i;j++){
        if(centro==excentricidades[j]){
            printf("%i ",j+1);
        }
    }
    puts("");
}
