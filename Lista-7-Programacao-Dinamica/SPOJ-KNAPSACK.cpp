#include <iostream>
#include <vector>
#include <algorithm>
#define endl "\n"//agiliza

using namespace std;

struct Item {//estrutura pros itens da mochila
    int size,value;
    Item(int s, int v) : size(s), value(v) {}
};

class Knapsack{//classe pra implementar o algoritmo da mochila
public:
    int knapsack(int S, int N, vector<Item>& items){//funcao pra retornar o val maximo
    vector<vector<int>> MAT(N + 1, vector<int>(S + 1, 0));//matriz pra guardar res. parcial
        int i,j;
        for(i = 1; i <= N; i++){//passa pelos itens
            for(j = 1; j <= S; j++){//e plos tamanhos da mochila
                int valor = items[i - 1].value,tamanho = items[i - 1].size;//recebe o val e tam do item atual
                
                    if(tamanho <= j){//se pode por na mochila
                    MAT[i][j] = max(MAT[i - 1][j], MAT[i - 1][j - tamanho] + valor);//poe o res. parcial na matriz
                    } 
                    else{
                    MAT[i][j] = MAT[i - 1][j];//senao puder,e o mesmo do passo passado
                    }
            }
        }
    return MAT[N][S];//retorna o maior poss.
    }
};

int main(){
ios::sync_with_stdio(0);
cin.tie(0);
cin.tie(0);//agilizam
int S, N, i, tam, val;
    cin >> S >> N;
    vector<Item> items;//array dos itens
    for(i = 0; i < N; i++){
        cin >> tam >> val;
    items.push_back(Item(tam, val));//novo tipo Item recebe esse tam e val
    }
    Knapsack ks;//cria a mochila
    cout << ks.knapsack(S, N, items) << endl;//imprime o resultado
return 0;
}
