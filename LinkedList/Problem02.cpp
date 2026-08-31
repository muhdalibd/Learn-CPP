#include <iostream>
#include <vector>
using namespace std;

/*
    Print Linked List - GfG
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

// Using Iterative Method
void printLL(Node* head){
    Node* temp = head;
    while(temp != NULL){
        cout << temp->data <<" ";
        temp = temp->next;
    }
    cout << endl;
}

// Using Recursion Method
void printList(Node* head){
    if(head == NULL){
        return;
    }
    cout << head->data <<" ";
    printList(head->next);
    // cout << head->data <<" ";
}

// Using Recursion Method
void printHelper(Node* head, vector<int>& ans) {
    if (head == NULL) return;

    ans.push_back(head->data);
    printHelper(head->next, ans);
}

vector<int> printL(Node* head) {
    vector<int> ans;
    printHelper(head, ans);
    return ans;
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

    // printLL(a);
    // printList(a);

    vector<int> ans = printL(a);
    for(int x : ans){
        cout << x <<" ";
    }
    return 0;
}