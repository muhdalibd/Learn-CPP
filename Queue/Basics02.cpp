#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Queue {
private:
    Node* head;
    Node* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    // Copy constructor for deep copy
    Queue(const Queue& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    // Assignment operator
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            // Clear current queue
            while (!empty()) {
                pop();
            }
            // Copy from other
            Node* current = other.head;
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    void push(int val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void pop() {
        if (empty()) {
            return;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    int front() const {
        if (empty()) {
            return -1;
        }
        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    int getSize() const {
        return size;
    }
};

// This function now works correctly with deep copy
void printQ(const Queue& q) {
    Queue temp = q;  // Deep copy via copy constructor
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
}

// Alternative: Print without copying (modifies the queue)
void printAndEmptyQ(Queue& q) {
    while (!q.empty()) {
        cout << q.front() << " ";
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

    cout << "Original queue: ";
    printQ(q);  // Doesn't modify q
    
    cout << "Front element: " << q.front() << endl;  // Outputs: 8
    
    cout << "Queue again: ";
    printQ(q);  // Still has all elements! (8 7 9 4 6)
    
    cout << "Emptying queue: ";
    printAndEmptyQ(q);  // This empties q
    
    cout << "After emptying, front: " << q.front() << endl;  // Outputs: -1
    
    return 0;
}