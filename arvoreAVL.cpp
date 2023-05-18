#include<bits/stdc++.h>
using namespace std;

class Node{
	public:
	int key;
	Node *left;
	Node *right;
	int height;
};

int height(Node *N){
	if (N == NULL)
		return 0;
	return N->height;
}

int max(int a, int b){
	return (a > b)? a : b;
}

Node* newNode(int key){
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}
//eduardo
Node *rightRotate(Node *y){

}
//rafael
Node *leftRotate(Node *x){
    Node *y, *z;
    y = x->right; // y aponta à direita da raiz 
    z = y->left; // z aponta filho esquerdo de y
    y->left = x; // raiz passa a ser filho esquerdo y
    x->right = z; // o filho direito de x aponta z

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
//marco
int getBalance(Node *N){
}
//khalil (teste)
Node* insert(Node* node, int key){
//regular BST insertion
    if(node == nullptr) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;
 
    //updating the node height after insertion
    node->height = 1 + max(height(node->left),
                        height(node->right));
 
    //getting balance to see if the node is unbalanced
    int balance = getBalance(node);
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root){
	if( root != nullptr ){
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main(){
	
	return 0;
}
