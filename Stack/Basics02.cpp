#include <iostream>
#include <list>
using namespace std;

class Stack {
    list<int> ll;
public:
    void push(int val){
        ll.push_front(val);
    }
    void pop(){
        ll.pop_front();
    }
    int top(){
        return ll.front();
    }
    bool empty(){
        return ll.size() == 0;
    }
};

int main(){
    Stack s;
    s.push(50);
    s.push(55);
    s.push(58);

    while(!s.empty()){
        cout << s.top() <<" ";
        s.pop();
    }
    cout << endl; // 58 55 50
    return 0;
}