/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
 */

/* retorna um número aleatório entre min e max, inclusive. */
long aleat(long min, long max)
{
  // Função que retorna o número aleatório
  long a = rand() % (max - min + 1) + min;
  return a;
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc(long a, long b)
{
  // Pega o valor absoluto de a e de b
  a = labs(a);
  b = labs(b);
  long aux;

  // Garante que o a seja maior (ou igual) a b
  if (b > a)
  {
    aux = a;
    a = b;
    b = aux;
  }

  // Realiza o MDC pelo método de Euclides
  while (b != 0)
  {
    aux = a % b;
    a = b;
    b = aux;
  }

  return a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  long d = (a * b) / mdc(a, b);
  return d;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r(struct racional r)
{
  long maxdiv;
  /*Verifica se o racional é valido. Se não for, devolve ele igual.
   *Se for, verifica se é possível simplificá-lo, dentro das especificações*/
  if (valido_r(r))
  {
    maxdiv = mdc(r.den, r.num);
    r.num = r.num / maxdiv;
    r.den = r.den / maxdiv;

    if ((r.den < 0) && (r.num < 0))
    {
      r.num = -r.num;
      r.den = -r.den;
    }
    else if ((r.den < 0) && (r.num > 0))
    {
      r.num = -r.num;
      r.den = -r.den;
    }
  }
  return r;
}

/* implemente as demais funções de racional.h aqui */

struct racional cria_r(long numerador, long denominador)
{
  struct racional r;
  r.den = denominador;
  r.num = numerador;
  return r;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r(struct racional r)
{
  int v = 1;
  if (r.den == 0)
    v = 0;
  return v;
}

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r(long min, long max)
{
  struct racional r;
  long numerador, denominador;
  // O numerador e o denominador recebem o número aleatório que a função aleat devolve
  numerador = aleat(min, max);
  denominador = aleat(min, max);
  // O r recebe o racional criado pela função cria_r
  r = cria_r(numerador, denominador);
  return r;
}

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r(struct racional r)
{
  if (valido_r(r))
  {
    r = simplifica_r(r);
    if (r.num == 0 || r.den == 1)
      printf("%ld", r.num);
    else if (r.num == r.den)
      printf("1");
    else
      printf("%ld/%ld", r.num, r.den);
  }
  else
    printf("NaN");
}

/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r(struct racional r1, struct racional r2)
{
  if (!valido_r(r1) || !valido_r(r2))
    return -2;

  float a1, a2;
  a1 = (float)r1.num / r1.den;
  a2 = (float)r2.num / r2.den;

  if (a1 < a2)
    return -1;
  if (a2 < a1)
    return 1;
  return 0;
}

struct racional num_propor(struct racional r, long m)
{
  r.num = r.num * (m / r.den);
  return r;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if ((!r3) || (!valido_r(r1)) || (!valido_r(r2)))
    return 0;

  int mmcomun = mmc(r1.den, r2.den);
  r1 = num_propor(r1, mmcomun);
  r2 = num_propor(r2, mmcomun);

  r3->den = mmcomun;
  r3->num = r1.num + r2.num;

  return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if ((!r3) || (!valido_r(r1)) || (!valido_r(r2)))
    return 0;

  int mmcomun = mmc(r1.den, r2.den);
  r1 = num_propor(r1, mmcomun);
  r2 = num_propor(r2, mmcomun);

  r3->den = mmcomun;
  r3->num = r1.num - r2.num;

  return 1;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if ((!r3) || (!valido_r(r1)) || (!valido_r(r2)))
    return 0;
  r3->num = r1.num * r2.num;
  r3->den = r1.den * r2.den;
  return 1;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if ((!r3) || (!valido_r(r1)) || (!valido_r(r2)))
    return 0;
  r3->num = r1.num * r2.den;
  r3->den = r1.den * r2.num;
  return 1;
}
