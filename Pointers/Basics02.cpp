#include <iostream>
using namespace std;

void printNum(int *numPtr){
    cout << *numPtr << endl;
}

void printLetter(char *letterPtr){
    cout << *letterPtr << endl;
}

void printAny(void *anyDataType, char whichDataType){
    switch (whichDataType){
    case 'i':
        cout << *((int*)anyDataType) << endl;
        // cout << *((char*)anyDataType) << endl;
        break;

    case 'c':
        cout << *((char*)anyDataType) << endl;
        break;

    case 'f':
        cout << *((float*)anyDataType) << endl;
        break;
    default:
        break;
    }
}

int main(){
    // int num = 5;
    // printNum(&num);

    // char letter = 'a';
    // printLetter(&letter);

    // int std = 15;
    // cout << &std << endl;
    // float *a = (float*) std;
    // cout << a << endl;
    // cout << *a << endl;

    float num = 3.25;
    printAny(&num, 'f');

    char letter = 'x';
    printAny(&letter, 'c');

    int score = 5;
    printAny(&score, 'i');
    return 0;
}