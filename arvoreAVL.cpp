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
}
//marco
int getBalance(Node *N){
}
//khalil
Node* insert(Node* node, int key){

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
