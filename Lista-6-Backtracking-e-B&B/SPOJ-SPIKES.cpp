#include <iostream>
#include <vector>
#define endl "\n"

using namespace std;

int n, m, pulos,primeiro_i, primeiro_j;//variaveis pra linha,coluna e limite e e pra pos inicial no lab.
char labirinto[40][40];//matriz com o tamanho max. possivel

bool dfs(int i, int j, vector<vector<bool>>& visitei , int k){//dfs recebe as coord. atuais,uma matriz de boole pra guardar os pontos visitados e quantos pulos ainda tem
    if(i < 0 || i >= n || j < 0 || j >= m){//checa se esta fora do lab.,pq nao pode ja que ele cercado por muro
        return false;
    }
    if(labirinto[i][j] == 'x'){//encontrou o tesouro
        return true;
    }
    if(labirinto[i][j] == '#' || (labirinto[i][j] == 's' && k == 0) || visitei[i][j]){ //tem parede,tem espinho e gastou todos os pulos ou ja visitou
        return false;
    }
    //if(labirinto[i][j] == '.' && k < abs(i - primeiro_i) + abs(j - primeiro_j)){//ve se ainda da pra andar com o num de pulos
      //  return false;
   // }

    visitei[i][j] = true;//marca a posicao

    //mexe para as direções imediatas usando DFS,enquanto puder(ainda tiver pulos)via backtrack
    if(dfs(i, j+1, visitei, k-(labirinto[i][j]=='s'))){//para a direita(//se tiver um espinho,tira 1 de k,aqui e nos outros)
        return true;
    }
    if(dfs(i, j-1, visitei, k-(labirinto[i][j]=='s'))){//para a esquerda
        return true;
    }
    if(dfs(i+1, j, visitei, k-(labirinto[i][j]=='s'))){//para baixo
        return true;
    }
    if(dfs(i-1, j, visitei, k-(labirinto[i][j]=='s'))){//para cima
        return true;
    }
    
    //se nao encontrou o tesouro depois dessa chamada recursiva
    visitei[i][j] = false;//desmarca a posicao 

    return false;//e retorna falso
}

int main(){
ios::sync_with_stdio(0);
cin.tie(0);//agiliza
    cin >> n >> m >> pulos;//recebe as linhas,colunas e o limite de pulos

    int i,j; //variaveis pra iterar 
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            cin >> labirinto[i][j];
            if(labirinto[i][j] == '@'){//acha onde e o comeco
                primeiro_i = i;//e passa as variaveis pra la
                primeiro_j = j;
            }
        }
    }

    vector<vector<bool>> visitei(n, vector<bool>(m, false));//declara a matriz dos pra guardar os visitados
    if(dfs(primeiro_i, primeiro_j, visitei, pulos/2)){//se conseguiu encontrar o tesouro(dfs deu 1)
        cout << "SUCCESS" << endl;
    }
    else{//senao
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}

