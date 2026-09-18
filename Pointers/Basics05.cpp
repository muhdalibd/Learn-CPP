#include <iostream>
using namespace std;

int main(){
    int size;
    cin >> size;
    // int arr[size];  //  expresion must have constant value

    int *arr = new int[size];   //  created in runtime

    for(int i=0; i<size; i++){
        cin >> arr[i];
    }
    for(int i=0; i<size; i++){
        // cout << arr[i] << " ";
        cout << *(arr+i) << " ";
    }

    delete[] arr;
    arr = NULL;

    return 0;
}