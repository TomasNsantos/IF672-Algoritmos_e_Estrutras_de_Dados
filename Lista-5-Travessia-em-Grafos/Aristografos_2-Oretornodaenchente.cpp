#include <iostream>
//floyd-warshall nao funciona depois das adicoes,tenta c/ dijkstra
#define endl "\n"//agiliza
#define ALT 100000//valor super alto pra simular infinito e poder rodar
//precisa modificar so o add,eu acho
using namespace std;

//Funcao para encontrar o vertice com a distancia minima

int menor_dist(int dist[], bool array_vert[], int V){
    int i;//iterador
    int min = ALT;//inicializa super alto
    int indice_min;//guarda o indice do vert. mais prox.

    for(i = 0; i < V; i++){//passa por todo o grafo e
        if(array_vert[i] == 0 && dist[i] <= min){//se nao ta no cam. e for menor q o atual
            min = dist[i];//se torna o novo menor
            indice_min = i;//atualiza o indice
        }
    }
    return indice_min;
}

//Funcao Dijkstra
void dijkstra(int graph[500][500], int origem, int destino, int V){
    int i,u,v,k;//variaveis e iteradores
    int dist[V];//array das distan. min.
    bool array_vert[V];//array booleano pra guardar os vertices que ja tao no cam. min.

    for(i = 0; i < V; i++){//inicializa tudo como
        dist[i] = ALT;//"infinito"
        array_vert[i] = 0;//e fora da arvore
    }

    dist[origem] = 0;//a dist. do vert. original = 0

    for(k = 0; k < V - 1; k++){
         u = menor_dist(dist, array_vert, V);//acha o vertice de distancia min.
        array_vert[u] = 1;//e marca ele como incluido na arv.

        for(v = 0; v < V; v++){
            if(array_vert[v] == 0 && (graph[u][v] != ALT) && (dist[u] != ALT) &&
            dist[u] + graph[u][v] < dist[v]) {//se achar um caminho menor
                dist[v] = dist[u] + graph[u][v];//atualiza a dist. min.
            }
        }
    }

    if(dist[destino] == ALT){
        cout << "-1" << endl;//sem rota
    } 
    else{//mas se tiver
        cout << dist[destino] << endl;//imprime ela
    }
}

int main() {

ios :: sync_with_stdio(0);
cin.tie(0);
cout.tie(0);//agilizadores

    int Q, R, N,i,j,tipo,A,B,M;//declara tudo
    cin >> Q >> R >> N;

    int graph[500][500];//torce pra nao ter caso teste maior q esse

    //Inicializa o grafo
    for(i = 0; i < Q; i++){
        for(j = 0; j < Q; j++){
            graph[i][j] = ALT;//com tudo alto
        }
    }

    //ADD as 1as ruas
    for(i = 0; i < R; i++){
        cin >> A >> B >> M;
        graph[A][B] = M;
    }

    //Faz os eventos
    for(i = 0; i < N; i++){
        cin >> tipo;
        if(tipo == 1){//REMOVE rua
            cin >> A >> B;
            graph[A][B] = ALT;//RUA ALAGADA=NAO DA PRA IR=VALOR ALTO
        } 
        else if(tipo == 2){//consulta caminho
            cin >> A >> B;
            dijkstra(graph, A, B, Q);
        }
    }

    return 0;
}

