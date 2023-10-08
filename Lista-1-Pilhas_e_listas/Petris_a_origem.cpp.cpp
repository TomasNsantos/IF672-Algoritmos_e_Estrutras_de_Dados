#include <iostream>
#define endl "\n"//agiliza

using namespace std;

typedef struct Celula {
    int nucleo;         //nucleo(info) da cel(no) 
    struct Celula* next;     //pont. pra o no seguinte da pilha

    //criar o no q recebe a pedra
    Celula(int val){
        nucleo = val;//a info e o valor(cor) da pedra
        next = nullptr;
    }
} No;

typedef struct {
    No* topo;
    int tam;
} Pilha;

//struct pra implemnetar o tetris
struct Petris{
    Celula* pilha = nullptr;  //coluna de pedras,inicialmente vazia

    //Func para adicionar pedra(empilhar) e/ou tirar 2 do topo(desempilhar 2)
    void add_pedra(int pedra){
        if(pilha != nullptr && pedra == pilha->nucleo){//se coluna nao esta vazia e a nova pedra for igual à pedra do topo, desempilha as duas pedras
            Celula* temp = pilha;
            pilha = pilha->next;
            delete temp;//libera a memoria
        } 
        else{
            //empilha nova pedra no topo da pilha
            Celula* nova_pedra = new Celula(pedra);
            nova_pedra->next = pilha;
            pilha = nova_pedra;
        }
    }

    // Func pra achar o qts pedras tem
    int conta_pedras(){
        int k = 0;
        Celula* atual = pilha;
        while(atual != nullptr){
            k++;
            atual = atual->next;
        }
        return k;
    }

    // Func pra achar a pedra do topo
    int acha_topo(){
        if(pilha == nullptr){
            return -1;  //pilha vazia retorna -1
        } 
        else{
            return pilha->nucleo;//a nao-vazia retorna o topo
        }
    }
};

int main(){
ios::sync_with_stdio(0);
cin.tie(0);//agiliza
    int P_casos,i;
    cin >> P_casos;
    string entrada;//vai receber em string,pq tem o END
    int resultados[P_casos][2];//matriz pra armazenar os resultados
    
    cin.ignore();//pula a linha em branco depois de ler os casos

    for(i = 0; i < P_casos; i++){
        Petris jogo;//cria/recria o jogo para esse caso

        while(cin >> entrada){//recebe as entradas(podem ser pedras ou END) enquanto der
            if(entrada == "END"){
                break;//sai desse loop se ler "END"
            }

            if(!entrada.empty()){
                int pedra = stoi(entrada);//faz a string virar inteiro
                jogo.add_pedra(pedra);//pra poder por a pedra no jogo
            }
        }
        resultados[i][0]=jogo.conta_pedras();//salva o resultado do caso
        resultados[i][1]=jogo.acha_topo();
    }

    for(i = 0; i < P_casos; i++){//imprime os resultados de cada caso
        cout << "caso " << i << ": " << resultados[i][0] << " " << resultados[i][1] << endl;
    }

    return 0;
}
