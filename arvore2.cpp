#include <iostream>
#include <string>
using namespace std;

struct Node {
    Node* left;
    Node* right;
    string nome;
    int matricula;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
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
        if (getBalanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
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
    if (matricula < node->matricula)
        node->left = insert(node->left, nome, matricula);
    else
        node->right = insert(node->right, nome, matricula);
    return balance(node);
}

void inOrderTraversal(Node* node) {
    if (node == nullptr)
        return;
    inOrderTraversal(node->left);
    cout << "Nome: " << node->nome << ", Matrícula: " << node->matricula << endl;
    inOrderTraversal(node->right);
}

void preorder();
void posorder();

void destroyTree(Node* node) {
    if (node == nullptr)
        return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

int main() {
    Node* root = nullptr;

     string nome;
     int matricula;

     //colocar um timer aqui

     while(cin>>matricula>>nome){
          root = insert(root, nome, matricula);
     }

     //colocar outro timer aqui

    inOrderTraversal(root);

     //colocar outro timer aqui

    destroyTree(root);

    return 0;
}
