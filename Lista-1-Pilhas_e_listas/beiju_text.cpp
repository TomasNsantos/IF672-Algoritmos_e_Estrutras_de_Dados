#include <iostream>
#include <string>

using namespace std;

struct No {
    char letra;
    No *anterior;
    No *proximo;
    No(char c, No *p = nullptr, No *n = nullptr) : letra(c), anterior(p), proximo(n) {}
};

class Lis_dup {//define a lista duplamente encadeada
public://torna as funcoes publicas pra depois usar no main
    Lis_dup() : head(nullptr), tail(nullptr) {}//ponteiros pro 1o e pro ultimo no
    No* insert(char c, No *pos) {
        No *Novo_no = new No(c);
        if (pos == nullptr){//se pos for nullptr,o novo no vai pro inicio da lista
            if (head == nullptr){
                head = tail = Novo_no;
            } 
            else{
                Novo_no->proximo = head;
                head->anterior = Novo_no;
                head = Novo_no;
            }
        } 
        else{//se pos nao e nullptr,ou seja,pos aponta para algum,o novo no
        //e inserido depois do apontado por pos
            Novo_no->anterior = pos;
            Novo_no->proximo = pos->proximo;
            if(pos->proximo != nullptr){
                pos->proximo->anterior = Novo_no;
            } 
            else{
                tail = Novo_no;
            }
            pos->proximo = Novo_no;
        }
        return Novo_no;
    }
    void push_back(char c){//novo no com c no fim da lista
        No *Novo_no = new No(c);
        if(tail == nullptr){//lista vazia=no no inicio
            head = tail = Novo_no;
        } 
        else{
            tail->proximo = Novo_no;
            Novo_no->anterior = tail;
            tail = Novo_no;
        }
    }
    void print() const{//imprime todos os caracteres da lista
        No *current = head;
        while (current != nullptr){
            cout << current->letra;
            current = current->proximo;
        }
        cout << endl;
    }
    No *head;
    No *tail;
};

int main(){
    string linha;
    while(getline(cin, linha)){
        Lis_dup list;//cria a lista dupla
        No *pos = nullptr;//ponteiro para no comeca como nullptr
        bool entre_colch = false;//cria variavel booleana para saber qdo esta entre colchetes
        for (auto i : linha){
            if(i == '['){
                entre_colch = true;
                pos = nullptr;
            } 
            else if(i == ']'){
                entre_colch = false;
                pos = nullptr;
            } 
            else{//garante a saida desejada
                if(entre_colch){
                    if(pos == nullptr){//ta entre colc. e o ponteiro para no e nullptr,
                    //bota no inicio da lista
                        pos = list.insert(i, nullptr);
                    } 
                    else{//entre colc. e nao e o ptr pra no nao e nullptr
                    //bota na pos atual
                        pos = list.insert(i, pos);
                    }
                } 
                else{//nao ta entre colc.
                //bota no fim da lista
                    list.push_back(i);
                }
            }
        }
        list.print();//imprime a lista
    }
    return 0;
}
