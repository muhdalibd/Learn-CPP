#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val){
        data = val;
        next = NULL;
    }
};

class Queue {
    Node* head;
    Node* tail;
public:
    Queue(){
        head = tail = NULL;
    }

    void push(int val){
        Node* newNode = new Node(val);
        if(empty()){
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    void pop(){
        if(empty()){
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    int front(){
        if(empty()){
            return -1;
        }
        return head->data;
    }

    bool empty(){
        return head == NULL;
    }
};

void printQ(Queue& q){
    while(!q.empty()){
        cout << q.front() <<" ";
        q.pop();
    }
    cout << endl;
}

int main(){
    Queue q;
    q.push(8);
    q.push(7);
    q.push(9);
    q.push(4);
    q.push(6);

    printQ(q);

    cout << q.front() << endl;  //  -1
    // q.pop();  //  -1
    printQ(q);
    return 0;
}