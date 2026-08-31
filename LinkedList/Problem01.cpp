#include <iostream>
using namespace std;
/*
    Length of a Linked List - GfG
*/

class Node {
public:
    int data;
    Node* next;

    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};

int getLength(Node* head){
    Node* temp = head;
    int len = 0;
    while(temp != NULL){
        len ++;
        temp = temp->next;
    }
    return len;
}

int countNodes(Node* head){
    if(head == NULL){
        return 0;
    }
    return 1 + getLength(head->next);
}

int main(){
    Node* a = new Node(1);
    Node* b = new Node(2);
    Node* c = new Node(3);
    Node* d = new Node(4);
    Node* e = new Node(5);
    Node* f = new Node(6);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    f->next = NULL;

    cout << getLength(a) << endl;
    cout << countNodes(a) << endl;
    return 0;
}