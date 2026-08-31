#include <iostream>
using namespace std;

int main(){
    int num[] = {1, 2, 3, 4, 5};
    // cout << num << endl;
    // cout << &num[0] << endl;
    // cout << &num[1] << endl;
    // cout << &num[2] << endl;
    // cout << &num[3] << endl;
    // cout << &num[4] << endl;

    // cout << &num[2] << endl;
    // cout << (num+2) << endl;

    // cout << num[2] << endl;
    // cout << *(num+2) << endl;

    int arr[5];
    for(int i=0; i<5; i++){
        // cin >> arr[i];
        cin >> *(arr+i);
    }
    for(int i=0; i<5; i++){
        cout << *(arr+i) <<" ";
    }
    cout << endl;

//  Accessing out-of-bounds elements causes undefined behavior (i<=5)
    for(int i=0; i<=5; i++){
        cout << *(arr+i) <<" ";
    }
    cout << endl;
    return 0;
}