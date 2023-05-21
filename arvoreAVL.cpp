#include<bits/stdc++.h>
using namespace std;

class Node{
	public:
	int key;
	Node *left;
	Node *right;
	int height;
};

/**
 * @brief Devolve a altura relativa a um determinado nó
 * 
 * @param node 
 * @return int 
 */
int height(Node *N){
	if (N == NULL)
		return 0;
	return N->height;
}

/**
 * @brief Testa entre dois número qual é o maior
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int max(int a, int b){
	return (a > b)? a : b;
}

/**
 * @brief Alocação de um novo nó, de acordo com a chave recebida
 * 
 * @param key 
 * @return Node* 
 */
Node* newNode(int key){
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

//Eduardo
/**
 * @brief Rotaciona para a direita o nó e reajusta os ponteiros necessários
 * 
 * @param node 
 * @return Node* 
 */
Node *rightRotate(Node *y){
    Node *x, *z;
    x = y->left;

    z = y->right;

    x->right = y;

    y->left = z; 

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
//rafael
/**
 * @brief Rotaciona para a esquerda o nó e reajusta os ponteiros necessários
 * 
 * @param node 
 * @return Node* 
 */
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
/**
 * @brief Cálcula o índice de balanceamento de um determinado nó
 * 
 * @param N 
 * @return int 
 */
int getBalance(Node *N){   
    if (N == NULL)
        return 0;
	return height(N->left) - height(N->right);
}
//khalil
/**
 * @brief Insere recursivamente elementos na árvore, atualiza suas alturas e realiza os reajuste necessários na árvore caso ela esteja desbalanceada
 * 
 * @param node 
 * @param key 
 * @return Node* 
 */
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

/**
 * @brief Exibição do percurso preorder da árvore
 * 
 * @param root 
 */
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
