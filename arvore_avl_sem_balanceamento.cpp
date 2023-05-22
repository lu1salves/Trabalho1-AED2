//Implementação da Árvore AVL sem o balanceamento 
//As operações dependendo do tipo de árvore a ser montada, podem ficar O(N)
#include <iostream>

using namespace std;

struct nodulo {
    string nome;
    int matricula;
    nodulo* filho_esquerda;
    nodulo* filho_direita;
};

nodulo* criar_no(string nome, int matricula) {
    nodulo* novo_no = new nodulo;
    novo_no->nome = nome;
    novo_no->matricula = matricula;
    novo_no->filho_esquerda = nullptr;
    novo_no->filho_direita = nullptr;
    return novo_no;
}

nodulo* inserir_no(nodulo* Nodulo, string nome, int matricula) {
    if (Nodulo == nullptr) {
        return criar_no(nome, matricula);
    }

    if (matricula < Nodulo->matricula) {
        Nodulo->filho_esquerda = inserir_no(Nodulo->filho_esquerda, nome, matricula);
    } else if (matricula > Nodulo->matricula) {
        Nodulo->filho_direita = inserir_no(Nodulo->filho_direita, nome, matricula);
    }

    return Nodulo;
}

void percorrer_inorder(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }

    percorrer_inorder(Nodulo->filho_esquerda);
    cout << "Nome: " << Nodulo->nome << ", Matrícula: " << Nodulo->matricula << endl;
    percorrer_inorder(Nodulo->filho_direita);
}

void destroyTree(nodulo* Nodulo) {
    if (Nodulo == nullptr) {
        return;
    }
    destroyTree(Nodulo->filho_esquerda);
    destroyTree(Nodulo->filho_direita);
    delete Nodulo;
}

