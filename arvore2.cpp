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

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + max(leftHeight, rightHeight);
}

Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

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

void inOrderTraversal(Node* node) {
    if (node == nullptr) return;
    inOrderTraversal(node->left);
    cout << "Nome: " << node->nome << ", Matrícula: " << node->matricula << endl;
    inOrderTraversal(node->right);
}


void preorder();

void posorder();

void destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

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

using namespace chrono;

//using namespace steady_clock;

int main() {
    Node* root = nullptr;

     string nome;
     int matricula;

    auto tempo_montagem_arvore1 = steady_clock::now();

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
