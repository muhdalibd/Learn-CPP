#include <iostream>
using namespace std;

/*
    Search an element in a Linked List -GfG
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

bool searchKey(Node* head, int val){
    Node* temp = head;
    while(temp != NULL){
        if(temp->data == val){
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool findKey(Node* head, int val){
    if(head == NULL){
        return false;
    }
    if(head->data == val){
        return true;
    }
    findKey(head->next, val);
}

int main(){
    Node* a = new Node(4);
    Node* b = new Node(7);
    Node* c = new Node(6);
    Node* d = new Node(9);
    Node* e = new Node(1);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = NULL;

    // cout << searchKey(a, 6) << endl;
    // cout << searchKey(a, 5) << endl;

    cout << findKey(a, 6) << endl;
    cout << findKey(a, 5) << endl;
    return 0;
}