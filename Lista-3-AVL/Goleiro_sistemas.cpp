#include <iostream>
#define endl "\n" // agiliza
//so precisou por a atualizacao da altura e do tam. direto nas rotacoes
//e mudar a achada do RNK 
using namespace std;

//PARTE BASICA DE AVL
// Defini�ao da estrutura do no da arvore AVL
struct Nodo {
    int num_bytes;
    int id;
    int RNK_dele;//dica chat discord:atributo para armazenar o acumulado de bytes transmitidos na arv. com raiz nesse no
    int altura;
    Nodo* esquerda;
    Nodo* direita;
    
    // Construtor da estrutura
    Nodo(int _id, int _num_bytes) : id(_id), num_bytes(_num_bytes), RNK_dele(0), altura(1), esquerda(nullptr), direita(nullptr) {}
};

//FUNC que retorna a altura de um no da arvore
int Altura(Nodo* N) {
    if (N){
        return N->altura;
    }
    return 0;
}

//FUNC que calcula o fator de balanceamento de um no da arvore
int FatorBalanceamento(Nodo* N) {
    if (N){
        return Altura(N->esquerda) - Altura(N->direita); //altura da subarv.esq. - altura da subarv.dir.
    }
    return 0;
}

//FUNC que atualiza a altura de um no da arvore
void AtualizarAltura(Nodo* N){
    if (N){
        int altura_esquerda = Altura(N->esquerda);
        int altura_direita = Altura(N->direita);
        N->altura = 1 + max(altura_esquerda, altura_direita); // a altura vai ser (1 + a da maior entre as 2 subarvs).
    }
}

Nodo* RotacaoEsquerda(Nodo* pai) {//rotacao simples a esquerda

    Nodo* temp = pai->direita;
    pai->direita = temp->esquerda;
    temp->esquerda = pai; 
    //atualiza a altura do pai
    AtualizarAltura(pai);
    //e a de temp
    AtualizarAltura(temp);
    //e atualiza o RNK de temp levando em conta o de pai
    temp->RNK_dele += pai->RNK_dele + pai->num_bytes;
    return temp; //retorna o novo no que agora e a raiz da subarv.
}

Nodo* RotacaoDireita(Nodo* pai) {// rotacao simples a direita

    Nodo* temp = pai->esquerda;
    pai->esquerda = temp->direita; 
    temp->direita = pai; 
    //atualiza a altura do pai
    AtualizarAltura(pai);
    //e a de temp
    AtualizarAltura(temp);
    //e atualiza o RNK de pai levando em conta o de temp
    pai->RNK_dele -= temp->RNK_dele + temp->num_bytes;
    return temp;//retorna o novo no que agora e a raiz da subarv.
}

//FUNC que balanceia as subarvs. a partir de um no,fazendo as rots. que precisar//pedaco da insercao anterior
Nodo* balanceia(Nodo* N) {
    int fator_temp = FatorBalanceamento(N);
    if(fator_temp > 1){
        if(FatorBalanceamento(N->esquerda) > 0){
            N = RotacaoDireita(N); // Rotacao LL
        }
        else{//rotacao LR
            N->esquerda = RotacaoEsquerda(N->esquerda); // rotacao RR no filho esquerdo
            N = RotacaoDireita(N); // rotacao LL no pai
        }
    } 
    else if(fator_temp < -1){
        if(FatorBalanceamento(N->direita) > 0){//rotacao RL
            N->direita = RotacaoDireita(N->direita); // rotacao LL no filho direito
            N = RotacaoEsquerda(N); // rotacao RR no pai
        } 
        else{
            N = RotacaoEsquerda(N); // rotacao RR
        }
    }
    return N;
}

//PARTE PARTICULAR DA QUESTAO(3 FUNCOES PRINCIPAIS)
//FUNCAO que insere um novo no na arvore AVL e deixa ela balanceada
Nodo* Inserir_disp(Nodo* raiz, int id, int W) {//versao mais compacta ja que foi dividida em 2 funcs
    if(raiz == nullptr){//se a arvore estiver vazia
        return new Nodo(id,W);//cria um novo disp. para ser a raiz
    } 
    else if(id < raiz->id){// checa se tem que inserir na subarv. esq.
        raiz->RNK_dele += W;//e se tiver q, atualiza o RNK do no atual, para manter o calc. do RNK certo
        raiz->esquerda = Inserir_disp(raiz->esquerda, id, W);
        raiz->altura = max(Altura(raiz->esquerda), Altura(raiz->direita)) + 1;
        raiz = balanceia(raiz);
    } 
    else if(id > raiz->id){// checa se tem que inserir na subarv. dir.
        raiz->direita = Inserir_disp(raiz->direita, id, W);
        raiz->altura = max(Altura(raiz->esquerda), Altura(raiz->direita)) + 1;
        raiz = balanceia(raiz);
    } 
    else{// se X for igual ao ID da raiz
        raiz->num_bytes += W;//nao cria outro disp., s� atualiza o valor da raiz
    }
    return raiz;//retorna o ponteiro para o disp. original
}

// FUNCAO pra achar o no com ID X e retornar peso e profundidade dele
bool Acha_WEI(Nodo* raiz, int X, int& wei, int& profundidade){//virou binario pra entrar no if
    int alt_temp = 0;
    while(raiz != nullptr){//enquanto tiver ponto para ser explorado
        if(X > raiz->id){//se o id do disp. atual for menor que X, procura na subarv. dir.
            raiz = raiz->direita;
            alt_temp++;
        } 
        else if(X < raiz->id){//senao, procura na subarv. esq.
            raiz = raiz->esquerda;
            alt_temp++;
        } 
        else{//se achou
            profundidade = alt_temp;
            wei = raiz->num_bytes;
            return 1;//retorna 1
        }
    }
    //se nao achou dps de procurar
    wei = 0;
    profundidade = -1;//fica inutil na main essa mudanca
    return 0;//redundancia pra nao dar warning e ver se da o mesmo resultado q no GDB


}

//FUNCAO que retorna o RNK de um no com ID X na AVL
int Acha_RNK(Nodo* raiz, int X) {
    int acumulado = 0;
    while(raiz != nullptr){//enquanto tiver ponto para ser explorado
        if(X == raiz->id){//se o id do disp. atual for X, entao achou
           return raiz->RNK_dele + acumulado; //volta o RNK do no que tem esse ponto como ID e o q acumulou
        } 
        if(raiz->id > X && raiz->esquerda){//se X for menor que o ID do no atual, o no procurado est� na subarvore esquerda.
            raiz = raiz->esquerda;
        }
        else if(raiz->id < X && raiz->direita){//senao,vai pra direita,caso haja
            acumulado += raiz->RNK_dele + raiz->num_bytes;//e bote o RNK_dele e a quantidade de bytes do no atual no total
            raiz = raiz->direita;
        } 
        else{// Se o ID do no atual for menor que o ID procurado
            if(raiz->id < X){
                return raiz->RNK_dele + raiz->num_bytes + acumulado;
            }
            else{
                return raiz->RNK_dele + acumulado;
            }
        }
    }
    return 0;//se nao achar volta 0
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);//agiliza
    Nodo* raiz = nullptr;//cria a arvore AVL (inicialmente vazia)
    int somatoria = 0;
    string instrucao;
    int X, W;

    while (cin >> instrucao && instrucao != "END"){//entra nesse loop e so sai quando der END
        if(instrucao == "ADD"){//comando para adicionar
            cin >> X >> W;//recebem os valores depois do ADD, do id do disp. novo e seu valor
            raiz = Inserir_disp(raiz, X, W);//bota o disp. novo na AVL
            somatoria += W;//acrescenta o valor dele no valor total de todos os dispositivos
            cout << somatoria << endl;//e imprime o valor total
        } 
         else if(instrucao == "WEI"){//comando para achar o disp de id X e seu valor
            cin >> X;//recebe o valor depois do WEI, do disp. procurado
            int pacotes, profundidade;
            if(Acha_WEI(raiz, X, pacotes, profundidade)){//acha o valor em pacotes transmitidos pelo dispositivo(se tiver) e sua profundidade (altura de cima pra baixo))
                cout << pacotes << " " << profundidade << endl;//imprime o valor passado por X e a profundidade que X est�
            } 
            else{//se nao foi achado um dispositivo com o id pedido
                cout << "0 -1" << endl;//imprime o padrao
            }
        }      
        else if(instrucao == "RNK"){//comando para achar o valor de todos disp. menores que X
            cin >> X;//recebe o valor depois do RNK, do ponto de divisao da procura
            cout << Acha_RNK(raiz, X) << endl;
        }
    }

    return 0;
}