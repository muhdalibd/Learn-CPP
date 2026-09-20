#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int stdID;
    float cgpa;

    void display(){
        cout << name <<" "<< stdID <<" "<< cgpa << endl; 
    }
    void display(string name){
        // cout << name <<" "<< stdID <<" "<< cgpa << endl;     //  Here, Argument Print
        cout << this->name <<" "<< stdID <<" "<< cgpa << endl;  //  Argument doesn't Print
    }
};


int main(){
    int x;
    // cout << &x << endl;
    
    Student s1;
    // cout << &s1;

    //  Show Garbage Values
    // cout << s1.name << endl;
    // cout << s1.stdID << endl;
    // cout << s1.cgpa << endl;
    
    s1.name = "Mr Xinag Jhu";
    s1.stdID = 2308121;
    s1.cgpa = 3.75;

    //  Show the Given Value
    // cout << s1.name << endl;
    // cout << s1.stdID << endl;
    // cout << s1.cgpa << endl;

    s1.display();
    s1.display("Mr King Fau");

    Student s2;
    s2.name = "Donald Trump";
    s2.display("Mr King Fau");

    return 0;
}