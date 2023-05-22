#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct No {
    No* esquerda;
    No* direita;
    string nome;
    int matricula;
    int altura;
};

/**
 * @brief Devolve a altura relativa a um determinado nó
 * 
 * @param No 
 * @return int 
 */
int pegaAltura(No* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

/**
 * @brief Calcula o fator de balanceamento do nó dado
 * 
 * @param No 
 * @return int 
 */
int pegaFatorDeBalanceamento(No* no) {
    if (no == nullptr) return 0;
    return pegaAltura(no->esquerda) - pegaAltura(no->direita);
}

/**
 * @brief Recalcula a altura de um nó em caso de inserção ou exclusão de um elemento
 * 
 * @param No 
 */
void atualizaAltura(No* no) {
    int alturaEsquerda = pegaAltura(no->esquerda);
    int alturaDireita = pegaAltura(no->direita);
    no->altura = 1 + max(alturaEsquerda, alturaDireita);
}

/**
 * @brief Rotaciona para a direita o nó, reajusta os ponteiros necessários e recalcula a altura dos nós envolvidos
 * 
 * @param No 
 * @return No* 
 */
No* rotacionarDireita(No* no) {
    No* novaRaiz = no->esquerda;
    no->esquerda = novaRaiz->direita;
    novaRaiz->direita = no;
    atualizaAltura(no);
    atualizaAltura(novaRaiz);
    return novaRaiz;
}

/**
 * @brief Rotaciona o nó para a esquerda, faz o reajuste dos ponteiros e recalcula a altura dos nós envolvidos
 * 
 * @param No 
 * @return No* 
 */
No* rotacionarEsquerda(No* no) {
    No* novaRaiz = no->direita;
    no->direita = novaRaiz->esquerda;
    novaRaiz->esquerda = no;
    atualizaAltura(no);
    atualizaAltura(novaRaiz);
    return novaRaiz;
}

/**
 * @brief Função que realiza toda a operação de balanceamento de um nó, incluindo atualização de sua altura e as rotações necessárias para manter as propriedades de uma árvore AVL
 * 
 * @param No 
 * @return No* 
 */
No* balancear(No* no) {
    atualizaAltura(no);
    int balanceFactor = pegaFatorDeBalanceamento(no);
    if (balanceFactor > 1) {
        if (pegaFatorDeBalanceamento(no->esquerda) < 0) no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }
    if (balanceFactor < -1) {
        if (pegaFatorDeBalanceamento(no->direita) > 0) no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }
    return no;
}

/**
 * @brief Insere um nó dentro da árove de forma recursiva
 * 
 * @param No 
 * @param nome 
 * @param matricula 
 * @return No* 
 */
No* inserir(No* no, string nome, int matricula) {
    if (no == nullptr) {
        No* novoNO = new No;
        novoNO->esquerda = nullptr;
        novoNO->direita = nullptr;
        novoNO->nome = nome;
        novoNO->matricula = matricula;
        novoNO->altura = 1;
        return novoNO;
    }
    if (matricula < no->matricula) no->esquerda = inserir(no->esquerda, nome, matricula);
    else no->direita = inserir(no->direita, nome, matricula);
    return balancear(no);
}

/**
 * @brief Exibe a árvore AVL de acordo com o padrão inorder
 * 
 * @param No 
 */
void percursoInorder(No* no) {
    if (no == nullptr) return;
    percursoInorder(no->esquerda);
    cout << "Nome: " << no->nome << ", Matrícula: " << no->matricula << endl;
    percursoInorder(no->direita);
}

/**
 * @brief Exibe a árvore AVL de acordo com o padrão preorder
 * 
 */
void preorder();

/**
 * @brief Exibe a árvore AVL de acordo com o padrão posorder
 * 
 */
void posorder();

/**
 * @brief Destrói, de forma recursiva, a árvore recebida
 * 
 * @param No 
 */
void apagaArvore(No* no) {
    if (no == nullptr) return;
    apagaArvore(no->esquerda);
    apagaArvore(no->direita);
    delete no;
}

/**
 * @brief Realiza a busca de um determinado número de matrícula dentro da árvore AVL
 * 
 * @param No 
 * @param matricula 
 */
void procura(No* no, int matricula) {
    if (no == nullptr) {
        cout << "Matricula nao encontrada" << endl;
	}
	else if (matricula == no->matricula){
		cout << "Nome: " << no->nome << ", Matrícula: " << no->matricula << endl;
	}else if (matricula < no->matricula)
        procura( no->esquerda, matricula );
    else 
        procura(no->direita, matricula);
}


int main() {
    No* raiz = nullptr;

     string nome;
     int matricula;

    auto tempo_montagem_arvore1 = chrono::steady_clock::now();

     while(cin>>matricula>>nome){
          raiz = inserir(raiz, nome, matricula);
     }

    auto tempo_montagem_arvore2 = chrono::steady_clock::now();
    auto tempo_total_montagem_arvore = chrono::duration_cast<chrono::nanoseconds>(tempo_montagem_arvore2 - tempo_montagem_arvore1).count();


    auto tempo_percorrer_arvore1 = chrono::steady_clock::now();
    percursoInorder(raiz);
    auto tempo_percorrer_arvore2 = chrono::steady_clock::now();
    auto tempo_total_percorrer_arovre = chrono::duration_cast<chrono::nanoseconds>(tempo_percorrer_arvore2 - tempo_percorrer_arvore1).count();

    apagaArvore(raiz);

    cout<<"O tempo total para a montagem da árvore é de "<<tempo_total_montagem_arvore<<" nanosegundos"<< endl;
    cout<<"O tempo total para a percorrer toda a árvore ordenada é de "<<tempo_total_percorrer_arovre<<" nanosegundos"<< endl;

    

    return 0;
}
