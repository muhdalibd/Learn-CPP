#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node(){}
    Node(int val){
        // val = this->val;     //  ERROR
        this->val = val;
        // next = nullptr;
        this->next = NULL;
    }
};

void printLL(Node *head){
    Node *temp = head;
    while(temp != nullptr){
        cout << temp->val << " ";
        temp = temp->next;
    }
}

int main(){
    // Node *a = new Node();
    // cout << a << endl;       //  Address of Node a

    Node *b = new Node(3);
    Node *c = new Node(8);
    Node *d = new Node(9);
    Node *e = new Node(2);
    Node *f = new Node(7);

    // cout << c << endl;          //  0x11198c0
    // b->next = c;
    // cout << b->next << endl;    //  0x11198c0

    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    f->next = NULL;

    printLL(b);
    return 0;
}