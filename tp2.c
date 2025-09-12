/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define MAX 100

/* coloque aqui as funções auxiliares que precisar neste arquivo */
int bubbleSort(struct racional rac[], int n)
{
  int i, j;
  struct racional aux;

  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      /*chama a função compara_r para verificar se o número no indice i do vetor é maior que o do indice j,
        se for então ele troca os números racionais de lugar*/
      if ((compara_r(rac[i], rac[j])) == 1)
      {
        aux = rac[j];
        rac[j] = rac[i];
        rac[i] = aux;
      }
    }
  }
  return 0;
}

/* programa principal */
int main()
{
  /* a completar! */
  struct racional rac[MAX], aux, adicao, *ptr;

  adicao.num = 0;
  adicao.den = 1;
  ptr = &adicao;

  int n, i, j, tam;
  for (i = 0; i < n; i++)
  {
    rac[i].num = 0;
    rac[i].den = 1;
  }

  scanf("%d", &n);
  while ((n < 0) || (n > 100))
    scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%ld", &rac[i].num);
    scanf("%ld", &rac[i].den);
  }
  // Imprime o vetor como foi lido
  printf("VETOR= ");
  for (i = 0; i < n; i++)
  {
    imprime_r(rac[i]);
    printf(" ");
  }

  for (i = 0; i < tam; i++)
  {
    tam = n;
    j = compara_r(rac[i], rac[n - 1]);
    if (j == -2)
    {
      if (!valido(rac[n - 1]))
      {
        n -= 1;
        tam = n;
      }
      while (!valido_r(rac[tam - 1]) && (tam - 1 > i))
        tam -= 1;
      
      if ( i < tam -1)
      {
        aux = rac[i];
        rac[i] = rac[tam - 1];
        rac[tam - 1] = aux;
      }

      if(i == tam -1)
        n -= 1;
    }
  }

  printf("VETOR = ");
  for (i = 0; i < n; i++)
  {
    imprime_r(rac[i]);
    printf(" ");
  }
  printf("\n");

  return (0);
}
