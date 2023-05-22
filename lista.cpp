#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct nodulo {
    string nome;
    int matricula;
    nodulo* proximo;
};

/**
 * @brief Realiza a inserçao de um elemento dentro da lista encadeada
 * @param Nodulo ponteiro para a struct nodulo
 * @param nome nome do aluno
 * @param matricula matricula do aluno
 * @return nodulo* 
 */
nodulo* insert(nodulo* Nodulo, string nome, int matricula) {
    nodulo* novo_no = new nodulo;
    novo_no->nome = nome;
    novo_no->matricula = matricula;
    novo_no->proximo = nullptr;

    if (Nodulo == nullptr) {
        return novo_no;
    }

    if (matricula < Nodulo->matricula) {
        novo_no->proximo = Nodulo;
        return novo_no;
    }

    nodulo* atual = Nodulo;
    while (atual->proximo != nullptr and atual->proximo->matricula < matricula) {
        atual = atual->proximo;
    }

    novo_no->proximo = atual->proximo;
    atual->proximo = novo_no;

    return Nodulo;
}

/**
 * @brief Exibe todos elementos presentes na lista
 * @param Nodulo ponteiro para o struct nodulo
 */
void imprimir_lista(nodulo* Nodulo) {
    nodulo* atual = Nodulo;
    while (atual != nullptr) {
        cout << "Nome: " << atual->nome << ", Matrícula: " << atual->matricula << endl;
        atual = atual->proximo;
    }
}

/**
 * @brief Desaloca a memória alocada pelos ponteiros na lista ligada
 * @param Nodulo ponteiro para o struct nodulo
 */
void destroyList(nodulo* Nodulo) {
    nodulo* atual = Nodulo;
    while (atual != nullptr) {
        nodulo* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}

/**
 * @brief FUnção que busca um nodulo da lista
 * @param nodulo ponteiro para o struct nodulo
 * @param matricula inteiro que representa a matrícula
 * @return Node* 
 */
nodulo* procura(nodulo* Nodulo, int matricula) {
    nodulo* atual = Nodulo;
    while (atual != nullptr) {
        if (atual->matricula == matricula) {
            return atual;
        }
        atual = atual->proximo;
    }
    return nullptr; // Nó não encontrado
}

int main() {
    nodulo* Nodulo = nullptr;

    string nome;
    int matricula;

    auto tempo_montagem_lista1 = chrono::steady_clock::now();
    while(cin>>matricula>>nome){
        Nodulo = insert(Nodulo, nome, matricula);
    }
    auto tempo_montagem_lista2 = chrono::steady_clock::now();
    auto tempo_total_montagem_lista = chrono::duration_cast<chrono::nanoseconds>(tempo_montagem_lista2 - tempo_montagem_lista1).count();

    auto tempo_procura1 = chrono::steady_clock::now();
    procura(Nodulo, 202103754);
    auto tempo_procura2 = chrono::steady_clock::now();
    auto tempo_procura_total = chrono::duration_cast<chrono::nanoseconds>(tempo_procura2 - tempo_procura1).count();


    imprimir_lista(Nodulo);
    cout<<"O tempo para montar a lista foi de "<<tempo_total_montagem_lista<<" nanosegundos"<<endl;
    
    cout<<"O tempo apra procurar algum elemento na lista ligada foi de "<<tempo_procura_total<<" nanosegundos"<<endl;

    // Liberar a memória da lista
    destroyList(Nodulo);

    return 0;
}
