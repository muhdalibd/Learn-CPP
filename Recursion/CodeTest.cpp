#include <iostream>
using namespace std;

double getPower(double n, int x){
    if(x == 0){
        return 1;
    }
    if(x < 0){
        n = 1/n;
        x = -x;
    }
    if(x % 2 != 0){
        return n * getPower(n*n, x/2);
    }
    return getPower(n*n, x /2);
}

int main(){
    cout << getPower(2.0, -15);
    return 0;
}