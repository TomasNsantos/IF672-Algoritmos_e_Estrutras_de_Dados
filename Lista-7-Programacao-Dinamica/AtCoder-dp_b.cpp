#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define endl "\n"//agiliza

vector<int> alt_pedras;//guarda a altura de cada pedra
vector<int> sub_sol;//guarda as solucoes dos subproblemas q compoem o principal

int K,N;//limite de pulo do sapo e total de pedras

int calc_resposta(int x){//func. de recursao com prog. din. pra calcular o custo de chegar na pedra x
    int j,resposta = 1000000000;//inicializa a resposta como muito mais que o o max possivel;mexer nisso fez 5 casos teste passarem
   
    if(x == N){//se tiver na pedra desejada
        return 0;//custo 0
    }

    else if(sub_sol[x] != -100){//se a resposta do subprol ja foi calculada
        return sub_sol[x];//retorna ela
    }

    //checa para todos os pulos possiveis a partir de x
    for(j = 1; j <= K; j++){
        if(x + j <= N){
            resposta = min(resposta, calc_resposta(x + j) + abs(alt_pedras[x] - alt_pedras[x + j]));
            //calcula o custo do pulo para a pedra x+j e soma com o resultado do subprob. recursivo
        }
    }

    sub_sol[x] = resposta;//guarda a resposta em sub_sol
    return resposta;//e retorna ela
}

int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cin.tie(0);//agilizam

    int i;
    cin >> N >> K;

    //poe o tamanho e inicializa o sub_sol com -100 em tudo
    sub_sol.resize(N + 1, -100);

    alt_pedras.resize(N + 1);//poe o tamanho no vetor das pedras
    for(i = 1; i <= N; i++){//e le a altura delas
        cin >> alt_pedras[i];
    }

    cout << calc_resposta(1) << endl;//comeca da primeira pedra

    return 0;
}

