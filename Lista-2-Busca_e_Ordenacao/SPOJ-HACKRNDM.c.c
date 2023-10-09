#include<stdio.h>
#include<stdlib.h>

int comparador (const void *a, const void *b)//precisa disso pro qsort funcionar
{
    return ( *(int*)a - *(int*)b );
}

int Busca_binaria(int numeros[], int l, int r, int x){//BB iterativa
    int m;
    while (l <= r){
        m = l + (r-l)/2;
 
        if (numeros[m] == x){
            return m;  
        }
        if (numeros[m] < x){
            l = m + 1; 
        }
        else{
            r = m - 1; 
        }
    }
 
    return -1; 
}

int conta_pares_k(int numeros[], int n, int k){
    int quantos = 0;
    qsort(numeros, n, sizeof(int), comparador);//existe qsort em stdlib.h em C,LEMBRAR
    //com o array ordenado,pode fazer a busca binaria procurando so numero+k

    for (int i = 0; i < n; i++){
        if (Busca_binaria(numeros, i+1, n-1, numeros[i]+k) != -1){
            quantos++;
        }
    }

    return quantos;
}

int main()
{
    int n,k,i,pares=0;
    scanf("%d %d", &n, &k);
    int numeros[n];
    for(i = 0; i < n; i++) {
        scanf("%d", &numeros[i]);
    }
    //acha a resposta
    pares = conta_pares_k(numeros, n, k);
    printf("%d", pares);
    return 0;
}