#include <iostream>
using namespace std;

//  Functional Recursion
int printFactorial(int n);

//  Parameterized Recursion
int getFactorial(int n, int x);


int main(){
    int num;
    cin >> num;
    // cout << printFactorial(num) << endl;

    int ans = 1;
    cout << getFactorial(num, ans) << endl;

    return 0;
}


int printFactorial(int n){
    if(n == 0 || n == 1){
        return 1;
    }
    return n * printFactorial(n-1);
}


int getFactorial(int n, int x){
    if(n == 0 || n == 1){
        return x;
    }
    return getFactorial(n-1, n*x);
}