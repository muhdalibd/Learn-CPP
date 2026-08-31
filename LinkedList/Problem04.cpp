#include <iostream>
using namespace std;

/*
    Insertion in Linked List
    There are several types of insertion based on the position where the new node is to be added:
        1. At the front of the linked list  
        2. Before a given node.
        3. After a given node.
        4. At a specific position.
        5. At the end of the linked list.
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

void printLL(Node* head){
    Node* temp = head;
    while(temp != NULL){
        cout << temp->data <<" ";
        temp = temp->next;
    }
    cout << endl;
}


void insertAtFront(Node** head, int val){
    Node* newNode = new Node(val);
    if(head == NULL){
        *head = newNode;
        return;
    }
    newNode->next = *head;
    *head = newNode;
}

Node *insertAtFront(Node *head, int x) {
    Node* newNode = new Node(x);
    if(head == NULL){
        head = newNode;
    }
    newNode->next = head;
    head = newNode;
    return newNode;
}


void insertAfterNode(Node* node, int x) {
    Node* newNode = new Node(x);

    newNode->next = node->next;
    node->next = newNode;
}

Node* insertAfterKey(Node* head, int key, int val) {
    Node* newNode = new Node(val);
    Node* find = head;
    while(find->data != key){
        find = find->next;
    }
    newNode->next = find->next;
    find->next = newNode;
    return head;
}


void insertBeforeNode(Node* node, int x) {
    // Assumes node != nullptr and node->next != nullptr
    Node* newNode = new Node(node->data); // copy old data
    newNode->next = node->next;
    node->next = newNode;
    node->data = x; // put new value in the original node
}

Node* insertBeforeKey(Node* head, int key, int val){
    Node* newNode = new Node(val);
    if(head->data == key){
        newNode->next = head;
        head = newNode;
        return head;
    }
    Node* find = head;
    while(find->next->data != key){
        find = find->next;
    }
    newNode->next = find->next;
    find->next = newNode;
    return head;
}


Node* insertAtPosition(Node* head, int pos, int val){
    Node* newNode = new Node(val);
    if(pos < 0) return head;
    if(pos == 0){
        newNode->next = head;
        return newNode;
    }
    Node* find = head;
    for(int i=1; i<pos; i++){
        find = find->next;
    }
    newNode->next = find->next;
    find->next = newNode;
    return head;
}


Node *insertAtEnd(Node *head, int x) {
    Node* newNode = new Node(x);
    if(head == NULL){
        head = newNode;
        return head;
    }
    Node* find = head;
    while(find->next != NULL){
        find = find->next;
    }
    find->next = newNode;
    return head;
}


int main(){Node* a = new Node(4);
    Node* b = new Node(7);
    Node* c = new Node(6);
    Node* d = new Node(9);
    Node* e = new Node(1);

    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = NULL;

    printLL(a);

    // insertAtFront(&a, 3);
    // printLL(a);
    // a = insertAtFront(a, 5);
    // printLL(a);

    // a = insertAtEnd(a, 2);
    // a = insertAtEnd(a, 8);
    // printLL(a);

    // insertAfterNode(a, 2);
    // insertAfterNode(e, 5);
    // printLL(a);

    // insertAfterKey(a, 7, 2);
    // insertAfterKey(a, 1, 8);
    // printLL(a);

    // insertBeforeNode(a, 5);
    // insertBeforeNode(e, 8);
    // printLL(a);

    // a = insertBeforeKey(a, 4, 8);
    // a = insertBeforeKey(a, 1, 3);
    // printLL(a);

    // a = insertAtPosition(a, 1, 8);
    // a = insertAtPosition(a, 0, 5);
    // printLL(a);
    

    return 0;
}