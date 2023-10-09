#include <stdio.h>
//faz usando Union-Find(DSU) no lugar de DFS,como falaram no chat do Discord

int pais[10000];//array pra implementar o DSU//10000 pq o limite e 100,100^2 e 10000 e nao dava pra alterar por const em C
int N;

int find(int x){//encontra a raiz do conjunto de x
    if(pais[x] == x){
        return x;
    }
    return pais[x] = find(pais[x]);//e faz compressao de caminho(path compression)
}

void unite(int x, int y){//une os conjuntos x e y
    x = find(x);
    y = find(y);
    if(x != y){
        pais[x] = y;//e faz y ser o pai do novo conjunto
    }
}

int main(){
    int N,K,i,j,M,Q,parede,linha,coluna,A,B;//variaveis do main:num de casos,iteradores,inteiro pra linha,coluna,parede,e 2 pra 2 pontos da cons.
    scanf("%d", &K);

    for(i = 0; i < K; ++i){
        scanf("%d %d %d", &N, &M, &Q);//num do lado do labirinto, de paredes retiradas dele e de consultas pra fazer

        for(j = 0; j < N * N; ++j){
            pais[j] = j;//inicializa o pai de cada cel. como ele mesmo
        }

        for(j = 0; j < M; ++j){
            scanf("%d", &parede);//le qual parede vai remover

            linha = parede / (2 * N - 1);//essa vai ser a posicao da linha da celula removida
            coluna = parede % (2 * N - 1);//e essa a da coluna

            if(coluna >= N - 1){//se e uma parede horizontal
                coluna -= N - 1;
                unite(linha * N + coluna, (linha + 1) * N + coluna);//une as celulas a acima e abixo da parede
            } 
            else{//senao
                unite(linha * N + coluna, linha * N + coluna + 1);//une as celulas a esquerda e a direita da parede
            }
        }

        for(j = 0; j < Q; ++j){//le as Q consultas
            scanf("%d %d", &A, &B);

            // Verifica se os pontos estao conectados atraves de seus representantes
            if(find(A) == find(B)){//se A e B tiverem o mesmo pai
                printf("%d.%d 1\n", i, j);//estao ligadas
            } 
            else{//senao
                printf("%d.%d 0\n", i, j);//nao estao
            }
        }
        printf("\n");//separador de casos
    }
   // printf("\n");//linha em branco extra do fim,pra ficar igual ao output esperado//sem essa linha
    return 0;
}