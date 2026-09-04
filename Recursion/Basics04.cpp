#include <iostream>
using namespace std;

int getPower(int n, int x);
int getPower(int n, int x, int ans);

int main(){
    int num, pow;
    cin >> num >> pow;
    cout << getPower(num, pow) << endl;
    cout << getPower(num, pow, 1) << endl;
    return 0;
}


int getPower(int n, int x){
    if(x == 1){
        return n;
    }
    if(x % 2 != 0){
        return n * getPower(n*n, x/2);
    }
    return getPower(n*n, x/2);
}


int getPower(int n, int x, int ans){
    if(x == 0){
        return ans;
    }
    // ans = ans*n;
    return getPower(n, x-1, ans*n);
}