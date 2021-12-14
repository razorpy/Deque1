#include <new>

using namespace std;

template <typename T> 
struct Deque {
    T *v; int tam_v, esquerda, direita, n; // direita vai ser q nem o fim
};

template <typename T>
bool redimensionar (Deque<T> &D, int novo_tam){

    T *aux = new (nothrow) T[novo_tam];
    if (aux == nullptr) return 1;

    D.tam_v = novo_tam;

    int meioant = D.esquerda + (D.direita-D.esquerda)/2,
        meionovo = (novo_tam-1)/2;
    int esqn = meionovo + (D.esquerda-D.direita)/2,
        dirn = meionovo + D.direita-meioant;

    for (int i = esqn, j = D.esquerda; i < dirn; ++i, ++j){
        aux[i] = D.v[j];
    }
    D.esquerda = esqn; 
    D.direita = dirn;

    delete[] D.v;
    D.v = aux;
    return 0;
}

template <typename T> 
bool inicializar (Deque<T> &D){
    D.v = new (nothrow) T[1];
    if (D.v == nullptr) return 1;
    D.tam_v = 1; D.esquerda = 0; D.direita = 0; D.n = 0; // uma a mais q realmente tem
    return 0;
}

template <typename T>
void terminar(Deque<T> &D){
    delete[] D.v;
}

template <typename T> 
bool vazio (Deque<T> &D){
    return D.n == 0;
}

template <typename T> 
bool inserir_esq (Deque<T> &D, T e){
    bool resp = 0;
    D.esquerda--;
    if (D.esquerda <= 0) {
        resp = redimensionar(D, 2*D.tam_v);
    }
    D.v[D.esquerda] = e;
    D.n++; // numero de elementos aumenta
    return resp;
}

template <typename T> 
bool inserir_dir (Deque<T> &D, T e){
    bool resp = 0;
    //inserir antes de incrementar
    D.v[D.direita] = e;
    D.direita++;
    if (D.direita >= D.tam_v){
        resp = redimensionar(D, 2*D.tam_v);
    }
    D.n++;
    return resp;
}

template <typename T> 
T remover_esq (Deque<T> &D){
    D.esquerda++; D.n--;
    return D.v[D.esquerda-1];
}

template <typename T> 
T remover_dir (Deque<T> &D){
    D.direita--; D.n--;
    return D.v[D.direita];
}

#include <iostream>

int main () {
    Deque<double> D;
    if (inicializar(D)) {cout << "erro\n"; return 1;}

    for (;;){

        cout << "\n{ ";
        for (int i = D.esquerda; i < D.direita; ++i){
            cout << D.v[i] << ' ';
        }
        cout << "}\n\n";

        cout << "Posicao Esquerda: " << D.esquerda << endl
             << "Posicao Direita: "  << D.direita  << endl
             << "Tamanho do vetor: " << D.tam_v    << endl << endl;
        

        cout << "Digite a opcao desejada:\n\n"
           << "  I: Inserir no deque\n"
           << "  V: esta Vazia?\n"
           << "  E: Esquerda\n"
           << "  D: Direita\n"
           << "  S: Sair\n\n"
           << "Digite a Opcao Desejada: ";

        char opcao;  cin >> opcao;

        if (opcao == 'I'){
            cout << "Numero a ser inserido: ";  double n;  cin >> n;
            cout << "Esquerda ou direita? "; char op; cin >> op;
            if (op == 'E'){
                if (inserir_esq(D, n)) {cout << "erro\n"; return 1;}
            }else{
                if (inserir_dir(D, n)) {cout << "erro\n"; return 1;}
            } 
        }

        else if (opcao == 'V'){
            if (vazio(D)) cout << "Vazio\n";
            else          cout << "Não vazio\n";
        }

        else if (opcao == 'E'){
            if (vazio(D)) cout << "Vazio\n";
            else          cout << remover_esq(D) << endl;
        }

        else if (opcao == 'D'){
            if (vazio(D)) cout << "Vazio\n";
            else          cout << remover_dir(D) << endl;
        }

        else {
            break;
        }

        
    }
    terminar(D);
    
}