//Implementação da árvore AVL balanceada
#include <iostream>

using namespace std;

struct nodulo {
    nodulo* filho_direita;
    nodulo* filho_esquerda;
    string nome;
    int matricula;
    int altura;
};

int determinar_altura(nodulo* Nodulo) {
    if (Nodulo == nullptr) return 0;
    return Nodulo->altura;
}

int fator_balanceamento(nodulo* Nodulo) {
    if (Nodulo == nullptr) return 0;
    return determinar_altura(Nodulo->filho_esquerda) - determinar_altura(Nodulo->filho_direita);
}

void modificar_altura(nodulo* Nodulo) {
    int altura_esquerda = determinar_altura(Nodulo->filho_esquerda);
    int altura_direita = determinar_altura(Nodulo->filho_direita);
    Nodulo->altura = 1 + max(altura_esquerda, altura_direita);
}

nodulo* rotacao_direita(nodulo* Nodulo) {
    nodulo* novo_raiz = Nodulo->filho_esquerda;
    Nodulo->filho_esquerda = novo_raiz->filho_direita;
    novo_raiz->filho_direita = Nodulo;
    modificar_altura(Nodulo);
    modificar_altura(novo_raiz);
    return novo_raiz;
}

nodulo* rotacao_esquerda(nodulo* Nodulo) {
    nodulo* novo_raiz = Nodulo->filho_direita;
    Nodulo->filho_direita = novo_raiz->filho_esquerda;
    novo_raiz->filho_esquerda = Nodulo;
    modificar_altura(Nodulo);
    modificar_altura(novo_raiz);
    return novo_raiz;
}

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

void percorrer_preorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
    percorrer_preorder(Nodulo->filho_esquerda);
    percorrer_preorder(Nodulo->filho_direita);
}

void percorrer_inorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    percorrer_inorder(Nodulo->filho_esquerda);
    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
    percorrer_inorder(Nodulo->filho_direita);
}

void percorrer_posorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    percorrer_posorder(Nodulo->filho_esquerda);
    percorrer_posorder(Nodulo->filho_direita);
    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
}

void destruir_arvore(nodulo* Nodulo) {
    if (Nodulo == nullptr) return;
    destruir_arvore(Nodulo->filho_esquerda);
    destruir_arvore(Nodulo->filho_direita);
    delete Nodulo;
}

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

