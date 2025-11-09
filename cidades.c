#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

// essa função serve para liberar toda a memória da estrada
// e das cidades que estão ligadas a ela
static void liberarEstrada(Estrada *E)
{

    if (E == NULL)
    {
        return;
    }

    Cidade *cidadeAtual = E->Inicio;

    while (cidadeAtual != NULL)
    {

        Cidade *proxima = cidadeAtual->Proximo;

        free(cidadeAtual);

        cidadeAtual = proxima;
    }

    free(E);
}

// Insere a cidade na lista em ordem crescente de Posicao
static void inserirCidadeOrdenada(Estrada *E, Cidade *novaCidade)
{
    novaCidade->Proximo = NULL;

    if (E->Inicio == NULL || novaCidade->Posicao < E->Inicio->Posicao)
    {
        novaCidade->Proximo = E->Inicio;
        E->Inicio = novaCidade;
        return;
    }

    Cidade *anterior = E->Inicio;
    Cidade *proxima = E->Inicio->Proximo;

    while (proxima != NULL && proxima->Posicao < novaCidade->Posicao)
    {
        anterior = proxima;
        proxima = proxima->Proximo;
    }

    anterior->Proximo = novaCidade;
    novaCidade->Proximo = proxima;
}

// corrigir apóstrofos estranhos no nome da cidade
// static void corrigirApostrofo(char *texto)
// {
//     if (texto == NULL)
//         return;

//     for (int i = 0; texto[i] != '\0'; i++)
//     {
//         if (texto[i] == '’' || texto[i] == '‘')
//         {
//             texto[i] = '\''; // substitui pelo apóstrofo simples
//         }
//     }
// }

Estrada *getEstrada(const char *nomeArquivo)
{

    // abrir o arquivo
    FILE *arq = fopen(nomeArquivo, "r");

    if (arq == NULL)
    {
        return NULL;
    }

    // Criando a lista estrada
    Estrada *E = (Estrada *)malloc(sizeof(Estrada));

    // verificando se a locação de memoria deu certo
    if (E == NULL)
    {
        fclose(arq);
        return NULL;
    }

    E->Inicio = NULL;
    E->N = 0;
    E->T = 0;

    // ler o T (Comprimento da estrada)
    // validar o comprimento de T 3 ≤ T ≤ 1.000.000

    if (fscanf(arq, "%d", &E->T) != 1)
    {
        fclose(arq);
        free(E);
        return NULL;
    }

    if ((E->T < 3 || E->T > 1000000))
    {
        free(E);
        fclose(arq);
        return NULL;
    }

    // Ler o N (Numero de cidades)
    // Validar Numero de cidades 2 ≤ N ≤ 10.000

    if (fscanf(arq, "%d", &E->N) != 1)
    {
        fclose(arq);
        free(E);
        return NULL;
    }

    if (E->N < 2 || E->N > 10000)
    {
        free(E);
        fclose(arq);
        return NULL;
    }

    // Ler cada cidade (N vezes)
    for (int i = 0; i < E->N; i++)
    {
        Cidade *novaCidade = (Cidade *)malloc(sizeof(Cidade));
        if (novaCidade == NULL)
        {
            fclose(arq);
            liberarEstrada(E); // função simples que libera a memória da estrada
            return NULL;
        }

        // verificando a leitura

        if (fscanf(arq, " %d %255[^\n]", &novaCidade->Posicao, novaCidade->Nome) != 2)
        {
            fclose(arq);
            free(novaCidade);
            liberarEstrada(E);
            return NULL;
        }

        // corrigir Apostrofo
        // corrigirApostrofo(novaCidade->Nome);

        // Validação de faixa: 0 < Xi < T
        if (novaCidade->Posicao <= 0 || novaCidade->Posicao >= E->T)
        {
            free(novaCidade);
            fclose(arq);
            liberarEstrada(E);
            return NULL;
        }

        // Checar DUPLICATA (percorre a lista atual)
        int cidade_duplicada = 0;

        Cidade *atual = E->Inicio;

        while (atual != NULL)
        {
            if (atual->Posicao == novaCidade->Posicao)
            {
                cidade_duplicada = 1;
                break;
            }
            atual = atual->Proximo;
        }

        if (cidade_duplicada == 1)
        {
            fclose(arq);
            free(novaCidade);
            liberarEstrada(E);
            return NULL;
        }

        inserirCidadeOrdenada(E, novaCidade);
    }
    fclose(arq);

    return E;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *E = getEstrada(nomeArquivo);
    if (E == NULL) {
        return -1.0; 
    }

    double menorVizinhanca = (double)(E->T); 

    Cidade *atual = E->Inicio;
    while (atual != NULL && atual->Proximo != NULL) {
        double vizinhanca = (double)(atual->Proximo->Posicao - atual->Posicao);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
        atual = atual->Proximo;
    }

    liberarEstrada(E);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *E = getEstrada(nomeArquivo);
    if (E == NULL) {
        return NULL; 
    }

    double menorVizinhanca = (double)(E->T); 
    char *cidadeMenorVizinhanca = NULL;

    Cidade *atual = E->Inicio;
    while (atual != NULL && atual->Proximo != NULL) {
        double vizinhanca = (double)(atual->Proximo->Posicao - atual->Posicao);
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            cidadeMenorVizinhanca = (char *)malloc((strlen(atual->Nome) + 1) * sizeof(char));
            if (cidadeMenorVizinhanca != NULL) {
                strcpy(cidadeMenorVizinhanca, atual->Nome);
            }
        }
        atual = atual->Proximo;
    }

    liberarEstrada(E);
    return cidadeMenorVizinhanca;
}
