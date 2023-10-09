#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//tentativa lista 1A
//primeiro ordena a lista dos precos de chocolate(qs ou mergesort),depois busca por qual cada cupom permite levar de graca(bus bin) e por ultimo
//imprime o valor que vai ter que gastar para levar tudo usando cada cupom x individualmente(nao pode usar 2 cupons ao mesmo tempo)

int comparador (const void *a, const void *b)	//precisa disso pro qsort funcionar
{
  return (*(int *) a - *(int *) b);
}

int main (){
  long long int n, i, m, valor_a_pagar = 0, valor_dos_chocolates = 0;
  //recebe os valores q vai precisar
  scanf ("%lld", &n);
  int preco_chocolates[n];
  for (i = 0; i < n; i++)
    {
      scanf ("%d",&preco_chocolates[i]);
      valor_dos_chocolates = valor_dos_chocolates + preco_chocolates[i];
    }
    
qsort (preco_chocolates, n, sizeof (int), comparador);//ordena os chocolates por preco
    
  //recebe o numero de cupons
  scanf ("%lld", &m);
  long long int cupons_quantas[m];
  for (i = 0; i < m; i++)
    {
      scanf ("%lld", &cupons_quantas[i]);	//nao vai ter 2 cupons com o mesmo valor de barras mais caras que ele permite comprar levando a mais barata entre as x mais caras de graca
    }
  //calculo dificil=agora ve quanto tem que pagar
  for (i = 0; i < m; i++)
    {
      valor_a_pagar = valor_dos_chocolates - (preco_chocolates[n - cupons_quantas[i]]);
      printf ("%lld\n",valor_a_pagar);
    }
  return 0;
}

