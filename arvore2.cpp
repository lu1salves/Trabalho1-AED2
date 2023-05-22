#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    string nome;
    int matricula;
    int height;
};

/**
 * @brief Função para pegar algum nó
 * @brief Devolva a altura relativa a um determinado nó
 * @param node 
 * @return int 
 */
int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

/**
 * @brief Calcula o fator de balanceamento do nó dado
 * 
 * @param node 
 * @return int 
 */
int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/**
 * @brief Recalcula a altura de um nó em caso de inserção ou exclusão de um elemento
 * 
 * @param node 
 */
void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + max(leftHeight, rightHeight);
}

/**
 * @brief Rotaciona para a direita o nó e reajusta os ponteiros necessários
 * 
 * @param node 
 * @return Node* 
 */
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

/**
 * @brief Rotaciona o nó para a esquerda e faz o reajuste dos ponteiros
 * 
 * @param node 
 * @return Node* 
 */
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

/**
 * @brief Função que realiza toda a operação de balanceamento de um nó, incluindo atualização de sua altura e as rotações necessárias para manter as propriedades de uma árvore AVL
 * 
 * @param node 
 * @return Node* 
 */
Node* balance(Node* node) {
    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) < 0) node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0) node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

/**
 * @brief Insere um nó dentro da árove de forma recursiva
 * 
 * @param node 
 * @param nome 
 * @param matricula 
 * @return Node* 
 */
Node* insert(Node* node, string nome, int matricula) {
    if (node == nullptr) {
        Node* newNode = new Node;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nome = nome;
        newNode->matricula = matricula;
        newNode->height = 1;
        return newNode;
    }
    if (matricula < node->matricula) node->left = insert(node->left, nome, matricula);
    else node->right = insert(node->right, nome, matricula);
    return balance(node);
}

/**
 * @brief Exibe a árvore AVL de acordo com o padrão inorder
 * 
 * @param node 
 */
void inOrderTraversal(Node* node) {
    if (node == nullptr) return;
    inOrderTraversal(node->left);
    cout << "Nome: " << node->nome << ", Matrícula: " << node->matricula << endl;
    inOrderTraversal(node->right);
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
 * @param node 
 */
void destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

/**
 * @brief Realiza a busca de um determinado número de matrícula dentro da árvore AVL
 * 
 * @param node 
 * @param matricula 
 */
void find(Node* node, int matricula) {
    if (node == nullptr) {
        cout << "Matricula nao encontrada" << endl;
	}
	else if (matricula == node->matricula){
		cout << "Nome: " << node->nome << ", Matrícula: " << node->matricula << endl;
	}else if (matricula < node->matricula)
        find( node->left, matricula );
    else 
        find(node->right, matricula);
}


int main() {
    Node* root = nullptr;

     string nome;
     int matricula;

    auto tempo_montagem_arvore1 = chrono::steady_clock::now();

     while(cin>>matricula>>nome){
          root = insert(root, nome, matricula);
     }

    auto tempo_montagem_arvore2 = chrono::steady_clock::now();
    auto tempo_total_montagem_arvore = chrono::duration_cast<chrono::nanoseconds>(tempo_montagem_arvore2 - tempo_montagem_arvore1).count();


    auto tempo_percorrer_arvore1 = chrono::steady_clock::now();
    inOrderTraversal(root);
    auto tempo_percorrer_arvore2 = chrono::steady_clock::now();
    auto tempo_total_percorrer_arovre = chrono::duration_cast<chrono::nanoseconds>(tempo_percorrer_arvore2 - tempo_percorrer_arvore1).count();

    destroyTree(root);

    cout<<"O tempo total para a montagem da árvore é de "<<tempo_total_montagem_arvore<<" nanosegundos"<< endl;
    cout<<"O tempo total para a percorrer toda a árvore ordenada é de "<<tempo_total_percorrer_arovre<<" nanosegundos"<< endl;

    

    return 0;
}
