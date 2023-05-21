#include <iostream>
#include <string>
#include <chrono>

using namespace std;

struct Node {
    string nome;
    int matricula;
    Node* next;
};

Node* insert(Node* head, string nome, int matricula) {
    Node* newNode = new Node;
    newNode->nome = nome;
    newNode->matricula = matricula;
    newNode->next = nullptr;

    if (head == nullptr) {
        return newNode;
    }

    if (matricula < head->matricula) {
        newNode->next = head;
        return newNode;
    }

    Node* current = head;
    while (current->next != nullptr && current->next->matricula < matricula) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    return head;
}

void displayList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << "Nome: " << current->nome << ", Matrícula: " << current->matricula << endl;
        current = current->next;
    }
}

void destroyList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int main() {
    Node* head = nullptr;

    string nome;
    int matricula;

     auto tempo_montagem_lista1 = chrono::steady_clock::now();
     while(cin>>matricula>>nome){
          head = insert(head, nome, matricula);
     }
     auto tempo_montagem_lista2 = chrono::steady_clock::now();
     auto tempo_total_montagem_lista = chrono::duration_cast<chrono::nanoseconds>(tempo_montagem_lista2 - tempo_montagem_lista1).count();


    // Exemplo de exibição da lista
    displayList(head);

     cout<<"O tempo para montar a lista foi de "<<tempo_total_montagem_lista<<" nanosegundos"<<endl;
    // Liberar a memória da lista
    destroyList(head);

    return 0;
}
