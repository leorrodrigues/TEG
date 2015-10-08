/***********************************************************************
* Alexandre Maros & Aurelio Grott                                      *
* 2015/1 - UDESC                                                       *
*                                                                      *
* Compilar: gcc main.c -o main                                         *
* Algoritmo de verificacao se o grafo eh conexo. Desenvolvido como     *
* exercicio para a aula de Teoria dos Grafos. Identifica se um grafo   *
* dado eh conexo ou nao. Caso a resposta seja negativa, ele conta      *
* quantos componentes o grafo tem. Para a solucao desse algoritmo,     *
* foi utilizado a busca em profundidade(dfs) em cima de matrizes de    *
* adjacencia. Ele cria uma matriz bidirecional, nao importa se o grafo *
* seja direcionado ou nao, para que o dfs consiga fazer a busca em     *
* todos os vertices.                                                   *
************************************************************************/

/*
0: 1 2 5 6
1: 0
2: 0
3: 4 5
4: 3 5 6
5: 0 3 4
6: 0 4
7: 8
8: 7
9: 10 11 12
10: 9
11: 9 12
12: 9 11
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tamMax 200

void criaMatAdjacente(int **matAdj, int *nVerticesTot, FILE *arquivo);
void dfs(int i, int **matAdj, int nVerticesTot, int *visitados);
void verificaConectividade();

int main()
{
    int opcao;

    do
    {
        printf("> TEG\n");
        printf("1. Verifica conectividade.\n"
            "0. Sair.\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            verificaConectividade();
            break;

        default:
            break;
        }
    } while (opcao != 0);

    return 0;
}

void verificaConectividade()
{
    int **matAdj;
    int visitados[tamMax];
    int i, j, nVertices;

    // Alocacao para a matAdj[tamMax][tamMax]
    matAdj = (int**)calloc(tamMax, sizeof(int*));
    for (i = 0; i < tamMax; i++)
    {
        for (j = 0; j < tamMax; j++)
        {
            matAdj[i] = (int*)calloc(tamMax, sizeof(int));
        }
    }
    // Fim da alocao para a mtriz

    FILE *fp = fopen("grafo.txt", "r");

    //Carrega a matriz adjacente
    criaMatAdjacente(matAdj, &nVertices, fp);


    // COMECO IMPRESSAO MATRIZ
    printf("Matriz:\n");
    for (i = 0; i < nVertices; i++){
        for (j = 0; j < nVertices; j++){
            printf("%d ", matAdj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // FIM IMPRESSAO MATRIZ

    // Zera o vetor auxiliar que guarda quais vertces ja foram visitados para o algoritmo de busca em profundidade
    memset(visitados, 0, sizeof(int) * tamMax);

    //Executa o algoritmo de busca em profundidade
    dfs(0, matAdj, nVertices, visitados);

    // Contar quantos vertices foram visitados
    // Se visitados == nVertices entao o grafo eh conexo
    int nVisitados = 0;
    for (i = 0; i < nVertices; i++)
    {
        if (visitados[i] == 1)
            nVisitados++;
    }

    if (nVisitados == nVertices)
    {
        printf("O grafo eh conexo\n");
    }
    else
    {
        // O primeiro grafo analisado e disconexo
        // Entao inicializamos a variavel contadora em 1
        int grafosDesconexos = 1;

        // Executa o algoritmo de busca em profundidade em todos os vertices que nao foram
        // visitados inicialmente. Procurando outros grafos disconexos.
        for (i = 0; i < nVertices; i++)
        {
            if (visitados[i] == 0)
            {
                // Se achou um vertice que nao foi visitado roda a busca e incrementa a variavel que conta
                // a quantiade de grafos desconexos.
                dfs(i, matAdj, nVertices, visitados);
                grafosDesconexos++;
            }
        }

        printf("O grafo eh desconexo e possui %d componentes.\n", grafosDesconexos);
    }
}

void dfs(int i, int **matAdj, int nVerticesTot, int *visitados)
{
    int j;
    // Marca que visitou o vertice
    visitados[i] = 1;
    // De 0 ate o numero de vertices total do grafico
    for (j = 0; j < nVerticesTot; j++)
    {
        // Se ele nao visitou o vertice j e ah uma ligcao entre o vertice i e o vertice j execute a recursao
        if (!visitados[j] && matAdj[i][j] >= 1)
        {
            dfs(j, matAdj, nVerticesTot, visitados);
        }
    }
}

void criaMatAdjacente(int **matAdj, int *nVerticesTot, FILE *arquivo)
{
    // Essa string eh usada para guardar temporarimente as ligacoes de um determinado vertice
    char buffer[200];
    // Guardar o vertice atual
    int vertAtual;
    //int que recebera o valor do vertice que vertAtual esta sendo ligado
    int num;
    int nVertices = 0;

    // Temp e usada para guardar a ligacao temporaria, offset e usado na hora do sscanf para controlar a leitura
    int temp, offset, i, j;

    // Se falhou abrir o arquivo
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!");
        return;
    }
    else
    {
        // Enquanto nao chegar no final do arquivo
        while (fgets(buffer, sizeof(buffer), arquivo))
        {
            // Ponteiro para o buffer, para poder mover o ponteiro na hora de converter para inteiros
            char *pBuffer = buffer;

            // Le o vertice a ser analisado. Numero antes do ":" no arquivo corresponde a linha da matriz
            // sscanf retorna quantos parametros foram lidos, usamos esse if pra verificar se a linha
            // nao estava vazia.
            if(sscanf(pBuffer, "%d:%n", &vertAtual, &offset) == 1)
            {
                pBuffer += offset;
                // Le numero por numero ate chegar ao final da linha
                while (sscanf(pBuffer, " %d%n", &num, &offset) == 1) 
                {
                    // Aponta o ponteiro para o proximo numero
                    pBuffer += offset; 

                    // Adiciona na posicao [verticeAtual][numeroLido] +1, indicando que ha uma aresta ali
                    matAdj[vertAtual][num]++;
                    // Nesse exemplo, fazemos o contrario tambem, pois queremos a matriz bidirecional para o dfs percorrer ambos os lados.
                    matAdj[num][vertAtual]++;
                }
                //aumenta o numero de vertice
                nVertices++;
            }
            
        }
        *nVerticesTot = nVertices;
    }
}
