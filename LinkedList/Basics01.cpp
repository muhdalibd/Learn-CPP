#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    // Node(int val) {
    //     this->val = val;
    //     this->next = NULL;
    // }
};

void printList(Node* head){
    Node* temp = head;
    while(temp != NULL){
        cout << temp->val <<" ";
        temp = temp->next;
    }
    cout << endl;
}


void inserAtTheFront(Node** head, int newVal){
    //  1. Prepare a newNode
    //  2. Put it in front of current head
    //  3. Move head of the list to point to the newNode
    Node* newNode = new Node();
    newNode->val = newVal;
    newNode->next = *head;
    *head = newNode;
}

void inserAtTheEnd(Node** head, int newVal){
    //  1. Prepare a newNode
    //  2. If Linked List is empty, newNode will be a head node
    //  3. Find the last node
    //  4. Insert newNode after last node (at the end)
    Node* newNode = new Node();
    newNode->val = newVal;
    newNode->next = NULL;
    if(*head == NULL){
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAfter(Node* prev, int newVal){
    // 1. Check if previous node is NULL
    // 2. Prepare a newNode
    // 3. Insert newNode after previous
    if(prev == NULL){
        return;
    }
    Node* newNode = new Node();
    newNode->val = newVal;
    newNode->next = prev->next;
    prev->next = newNode;
}


int main(){
    Node* head = new Node();
    Node* second = new Node();
    Node* third = new Node();

    head->val = 5;
    second->val = 7;
    third->val = 8;

    head->next = second;
    second->next = third;
    third->next = NULL;

    printList(head);


    inserAtTheFront(&head, 3);
    printList(head);
    inserAtTheEnd(&head, 9);
    printList(head);
    insertAfter(third, 4);
    printList(head);

    return 0;
}