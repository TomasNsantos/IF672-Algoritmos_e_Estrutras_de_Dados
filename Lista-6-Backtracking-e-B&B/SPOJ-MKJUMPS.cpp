//tentativa
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define endl "\n"//agiliza

using namespace std;

int n;//tamanho de cada linha e parador
int board[10][10];//inteiro do tabuleiro
bool visitados[100][100];//matriz pra marcar se o cavalo parou nos quadrados // o problema era o tamanho aqui
int Max_cont;//guarda o num de quadrados do xadrez que o cavalo chegou
int todos_quadrados;//guarda o num de quadrados do xadrez

int limites_linha[100][2]; //matriz pra armazena os limites de cada linha,em [0] tem o inicio e em [1] o fim// e aqui

//arrays pro movimento do cavalo
int d_linha[] = {-2, -2, -1, -1, 1, 1, 2, 2};//a combinacao de d_linha[i] e d_coluna[i]
int d_coluna[] = {-1, 1, -2, 2, -2, 2, -1, 1};//cria o mivimento em L possível do cavalo

bool quad_existe(int x, int y){//checa se o quadrado existe(o cavalo pode parar nele)
    if(x < 1 || x > n||y < limites_linha[x][0] || y > limites_linha[x][1]){//se ta fora dos limites do tabuleiro ou da linha
        return false;//nao existe
    }
    else return true;//senao o quadrado existe
}

void Zera_linha(int linha, int colunas, bool visitados[][100]){//reseta a linha marcando ela como nao visitada
    for (int j = 1; j <= colunas; j++){
        visitados[linha][j] = false;
    }
}

void DFS(int lin, int col,int conta_func){//backtracking pra ver o caminho pos. do cavalo
    int i;//usa pra iterar
    
	for(i = 0; i < 8; i++){ // testa os 8 movimentos possíveis do cavalo
        int temp_x = lin + d_linha[i],temp_y = col + d_coluna[i];//coordenada horizontal e vertical do quadrado
		if(quad_existe(temp_x, temp_y) && !(visitados[temp_x][temp_y])){
		//se a o quadrado e real e nao visitado
			visitados[temp_x][temp_y] = true;//marca a visita
			DFS(temp_x, temp_y, conta_func+ 1);//entra em recursao
			visitados[temp_x][temp_y] = false; //e desmarca a visita pra passar pelos outros
		}
	}

    if(conta_func > Max_cont){//se o num maximo de quadrados visitados e menos q o atual
		Max_cont = conta_func ;//atualiza o maximo
    }
	
	return; 
}

int main(){
ios::sync_with_stdio(0);
cin.tie(0);//agiliza
    int num_do_caso = 1,i;//iteradores
    int I_col,F_col;// I_col e a 1a coluna da linha atual e F_col a ultima

	while(cin >> n && n!=0){
		todos_quadrados = 0;//zera a contagem do tab.
		for(i = 1; i <= n; i++){
			cin >> I_col >> F_col;  // le o inicio e o fim linha atual
			limites_linha[i][0] = I_col + 1;  // define o comeco da linha i
			limites_linha[i][1] = limites_linha[i][0] + F_col - 1 ;//e o seu fim
			todos_quadrados = todos_quadrados + F_col;//e atualiza a contagem do tab.

		    Zera_linha(i, limites_linha[i][1] - limites_linha[i][0] + 1, visitados);//reinicia a linha
		}
        
        visitados[1][1] = true;//marca o quadrado inicial como visitado
		Max_cont = 0;//zera o maximo de quad. visitados
		DFS(1,1,1);// chamando a função pra marcar tudo que ele pode visitar a partir de (1,1)

		// imprimindo a resposta
		cout << "Case " << num_do_caso++ << ", " << todos_quadrados - Max_cont;
		if((todos_quadrados-Max_cont) == 1){
		    cout << " square";//isso tava dando errado,tem q ser no singular
		}
		else{
		    cout << " squares";
		}
		cout << " can not be reached." << endl;
    }

    return 0;
}
