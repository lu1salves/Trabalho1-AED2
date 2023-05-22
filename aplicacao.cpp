#include <iostream>
#include <chrono>

using namespace std;

/**
 * @brief conjunto de dados primitivos que formam o TAD responsável por representar o Nó de uma ávore
 */
struct nodulo {
    nodulo* filho_direita;
    nodulo* filho_esquerda;
    string nome;
    int matricula;
    int altura;
};

/**
 * @brief Função para determinar a altura relativa de algum Nó
 * @param Nodulo, ponteiro para o struct nodulo
 * @return inteiro correspondete a altura
 */
int determinar_altura(nodulo* Nodulo) {
    if (Nodulo == nullptr) return 0;
    return Nodulo->altura;
}

/**
 * @brief Calcula o fator de balanceamento do nó dado
 * @param Nodulo ponteiro para o struct nodulo
 * @return inteiro correspondete ao fator de balanceamento
 */
int fator_balanceamento(nodulo* Nodulo) {
    if (Nodulo == nullptr) return 0;
    return determinar_altura(Nodulo->filho_esquerda) - determinar_altura(Nodulo->filho_direita);
}

/**
 * @brief Recalcula a altura de um nó em caso de inserção ou exclusão de um elemento
 * @param Nodulo ponteiro para o strcut nodulo
 */
void modificar_altura(nodulo* Nodulo) {
    int altura_esquerda = determinar_altura(Nodulo->filho_esquerda);
    int altura_direita = determinar_altura(Nodulo->filho_direita);
    Nodulo->altura = 1 + max(altura_esquerda, altura_direita);
}

/**
 * @brief Rotaciona para a direita o nó e reajusta os ponteiros necessários
 * @param Nodulo ponteiro para o struct nodulo
 * @return posição de memória com o nó que foi rotacionado
 */
nodulo* rotacao_direita(nodulo* Nodulo) {
    nodulo* novo_raiz = Nodulo->filho_esquerda;
    Nodulo->filho_esquerda = novo_raiz->filho_direita;
    novo_raiz->filho_direita = Nodulo;
    modificar_altura(Nodulo);
    modificar_altura(novo_raiz);
    return novo_raiz;
}

/**
 * @brief Rotaciona o nó para a esquerda e faz o reajuste dos ponteiros
 * @param Nodulo ponteiro para o struct nodulo
 * @return posição de memória do Nó rotacionado
 */
nodulo* rotacao_esquerda(nodulo* Nodulo) {
    nodulo* novo_raiz = Nodulo->filho_direita;
    Nodulo->filho_direita = novo_raiz->filho_esquerda;
    novo_raiz->filho_esquerda = Nodulo;
    modificar_altura(Nodulo);
    modificar_altura(novo_raiz);
    return novo_raiz;
}

/**
 * @brief Função que realiza toda a operação de balanceamento de um nó, incluindo atualização de sua altura e as rotações necessárias para manter as propriedades de uma árvore AVL
 * @param Nodulo struct com chaves
 * @return nodulo* posicao de meória do corpo balanceado 
 */
nodulo* balance(nodulo* Nodulo) {
    modificar_altura(Nodulo);
    int numero_balanceamento = fator_balanceamento(Nodulo);
    if (numero_balanceamento > 1) {
        if (fator_balanceamento(Nodulo->filho_esquerda) < 0) Nodulo->filho_esquerda = rotacao_esquerda(Nodulo->filho_esquerda);
        return rotacao_direita(Nodulo);
    }
    if (numero_balanceamento < -1) {
        if (fator_balanceamento(Nodulo->filho_direita) > 0) Nodulo->filho_direita = rotacao_direita(Nodulo->filho_direita);
        return rotacao_esquerda(Nodulo);
    }
    return Nodulo;
}

/**
 * @brief Insere um nó dentro da árove de forma recursiva
 * 
 * @param Nodulo 
 * @param nome do aluno
 * @param matricula do aluno
 * @return *nodulo ponteiro para o tad de nodulo 
 */
nodulo* inserir_nodulo(nodulo* Nodulo, string nome, int matricula) {
    if (Nodulo == nullptr) {
        nodulo* novo_nodulo = new nodulo;
        novo_nodulo->filho_esquerda = nullptr;
        novo_nodulo->filho_direita = nullptr;
        novo_nodulo->nome = nome;
        novo_nodulo->matricula = matricula;
        novo_nodulo->altura = 1;
        return novo_nodulo;
    }
    if (matricula < Nodulo->matricula) Nodulo->filho_esquerda = inserir_nodulo(Nodulo->filho_esquerda, nome, matricula);
    else Nodulo->filho_direita = inserir_nodulo(Nodulo->filho_direita, nome, matricula);
    return balance(Nodulo);
}

/**
 * @brief Função que imprime a árvore na forma preorder
 * @param Nodulo ponteiro que aponta para a struct nodulo
 */
void percorrer_preorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
    percorrer_preorder(Nodulo->filho_esquerda);
    percorrer_preorder(Nodulo->filho_direita);
}

/**
 * @brief Função que imprime a árvore na forma inorder
 * @param Nodulo ponteiro que aponta para a struct nodulo
 */
void percorrer_inorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    percorrer_inorder(Nodulo->filho_esquerda);
    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
    percorrer_inorder(Nodulo->filho_direita);
}

/**
 * @brief FUnção que imprime a árvore na forma posorder
 * @param Nodulo ponteiro que aponta para a struct nodulo
 */
void percorrer_posorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    percorrer_posorder(Nodulo->filho_esquerda);
    percorrer_posorder(Nodulo->filho_direita);
    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
}

/**
 * @brief Desaloca, de maneira recursiva, a memória utilizada pelos ponteiros durante a construção da árvore
 * @param Nodulo ponteiro para a struct nodulo
 */
void destruir_arvore(nodulo* Nodulo) {
    if (Nodulo == nullptr) return;
    destruir_arvore(Nodulo->filho_esquerda);
    destruir_arvore(Nodulo->filho_direita);
    delete Nodulo;
}

/**
 * @brief Realiza a busca de um determinado número de matrícula dentro da árvore AVL
 * 
 * @param Nodulo ponteiro para a struct nodulo
 * @param matricula matricula do aluno
 */
void encontrar_no(nodulo* Nodulo, int matricula) {
    if (Nodulo == nullptr) {
        std::cout << "Matricula nao encontrada" << endl;
	}
	else if (matricula == Nodulo->matricula){
		std::cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
	}else if (matricula < Nodulo->matricula){
        encontrar_no( Nodulo->filho_esquerda, matricula );
    }else{ 
        encontrar_no(Nodulo->filho_direita, matricula);
    }
}


int main() {
    nodulo* root = nullptr;

    string nome;
    int matricula;

    auto tempo_montagem_arvore1 = chrono::steady_clock::now(); //primeiro timer 
    while(cin>>matricula>>nome){
        root = inserir_nodulo(root, nome, matricula);
    }
    auto tempo_montagem_arvore2 = chrono::steady_clock::now(); //segundo timer

    auto tempo_total_montagem_arvore = chrono::duration_cast<chrono::nanoseconds>(tempo_montagem_arvore2 - tempo_montagem_arvore1).count(); //segundo timer - primeiro timer

    auto tempo_percorrer_arvore1 = chrono::steady_clock::now(); //terceiro time
    percorrer_inorder(root);
    auto tempo_percorrer_arvore2 = chrono::steady_clock::now(); //quarto timer
    
    auto tempo_total_percorrer_arovre = chrono::duration_cast<chrono::nanoseconds>(tempo_percorrer_arvore2 - tempo_percorrer_arvore1).count(); //quarto timer - terceiro timer

    auto tempo_encontrar1 = chrono::steady_clock::now(); //quinto timer
    encontrar_no(root, 202103754);
    auto tempo_encontrar2 = chrono::steady_clock::now(); //sexto timer

    auto tempo_total_encontrar = chrono::duration_cast<chrono::nanoseconds>(tempo_encontrar2 - tempo_encontrar1).count(); //sexto timer - quinto timer

    std::cout<<"\n";

    destruir_arvore(root);

    std::cout<<"O tempo total para a montagem da árvore é de "<<tempo_total_montagem_arvore<<" nanosegundos"<< endl;

    std::cout<<"O tempo total para a percorrer toda a árvore ordenada é de "<<tempo_total_percorrer_arovre<<" nanosegundos"<< endl;

    std::cout<<"O tempo total para buscar algum elemento na árvore é de "<<tempo_total_encontrar<<" nanossegundos"<<endl;

    return 0;
}
