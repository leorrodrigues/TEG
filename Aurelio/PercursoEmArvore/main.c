/************************************************************************
* Alexandre Maros & Aurelio Grott                                       *
* 2015/1 - UDESC                                                        *
* Compilar: gcc main.c -o main Lista.c                                  *
* Algoritmo de Percurso em Arvore                                       *
* (Pos-Ordem, Em-Ordem, Pre-Ordem)                                      *
* Foi implementando usando Lista de Adjacencia e DFS.                   *
* Como ele muda diretamente com a lista, as implementacoes das funcoes  *
* de percurso, estao no arquivo Lista.c, junto com seus comentarios     *
*************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"

void mostra_inteiro(void *info);
void listaAdjacente(Lista *listaAdj, int *nVert);

int main()
{
    int opcao;

    do
    {
        printf("> TEG\n");
        printf("1. Percurso em Arvore.\n"
               "0. Sair.\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            percurso();
            break;
        default:
            break;
        }
    } while(opcao != 0);

    return 0;
}

void percurso()
{
    int nVertices, i;

    // Inicializa listaAdjacente e cria apatir do arquivo grafo.txt
    Lista listaAdj;
    inicializa_lista(&listaAdj, sizeof(Lista));
    listaAdjacente(&listaAdj, &nVertices);

    /* Imprimir Lista
    for (i = 0; i < nVertices; i++)
    {
        Lista l;
        leNaPosicao(&listaAdj, &l, i);
        printf("%d: ", i);
        mostra_lista(l, mostra_inteiro);
        printf("-\n");
    }
    */

    // Vetor que guarda os vertices visitados
    int *visitados;
    visitados = (int*) calloc(nVertices, sizeof(int));

    // Roda os algoritmos.
    // As implementacoes das funcoes estao no final do arquivo Lista.c
    printf("Pre-ordem:\n");
    dfs_preordem(&listaAdj, 0, visitados);
    printf("\n\n");

    printf("Pos-ordem:\n");
    memset(visitados, 0, sizeof(int) * nVertices);
    dfs_posordem(&listaAdj, 0, visitados);
    printf("\n\n");

    printf("Em-ordem:\n");
    memset(visitados, 0, sizeof(int) * nVertices);
    dfs_emordem(&listaAdj, 0, visitados);
    printf("\n");
}



void listaAdjacente(Lista *listaAdj, int *nVert)
{
    char buffer[200];
    int temp, vertAtual, offset;
    int nVertices = 0;
    int i, j;

    FILE *arquivo = fopen("grafo.txt", "r"); // ABre o grafo
    if(arquivo == NULL) // Se falhou abrir o arquivo
    {
        printf("Erro ao abrir arquivo!");
    }
    else
    {
        while( fgets(buffer, sizeof(buffer), arquivo) ) // Enquanto nao chegar no final do arquivo
        {
            char *pBuffer = buffer; // Ponteiro para o buffer, para poder mover o ponteiro na hora de converter para inteiros

            Lista l;
            inicializa_lista(&l, sizeof(int));
            if (sscanf(pBuffer, "%d:%n", &vertAtual, &offset) == 1)
            {
                nVertices++;
                pBuffer += offset;
                while (sscanf(pBuffer, " %d%n", &temp, &offset) == 1) // Le numero por numero ate chegar ao final da linha
                {
                    pBuffer += offset; // Aponta o ponteiro para o proximo numero
                    insereNoFim(&l, &temp);
                }
                insereNoFim(listaAdj, &l);
            }
        }
    }
    *nVert = nVertices;

}

void mostra_inteiro(void *info)
{
    int *n = (int*) info;
    printf("%d -> ", *n);
}
