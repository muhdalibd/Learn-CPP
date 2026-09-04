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


// 1. Optimized Standard Recursion
int getPower(int n, int x){
    // FIX: Changed base case from (x == 1) to (x == 0). 
    // If x was 0 in your original code, x/2 would infinitely loop at 0.
    if(x == 0){
        return 1;
    }
    
    // OPTIMIZATION: Use bitwise AND (& 1) instead of modulo
    if(x & 1){
        // OPTIMIZATION: Use bitwise right shift (>> 1) instead of division
        return n * getPower(n*n, x >> 1);
    }
    return getPower(n*n, x >> 1);
}


// 2. Optimized Tail Recursion
int getPower(int n, int x, int ans){
    if(x == 0){
        return ans;
    }
    
    // FIX: Your original code subtracted 1 (x-1), which took O(x) steps.
    // By applying the squaring logic here, we reduce it to O(log x) steps.
    if(x & 1){
        return getPower(n*n, x >> 1, ans * n);
    }
    
    return getPower(n*n, x >> 1, ans);
}


//  Best Optimized Solution
long long getPower(long long n, long long x) {
    long long ans = 1;
    
    while (x > 0) {
        // If x is odd, multiply the current base to the answer
        if (x & 1) {
            ans *= n;
        }
        // Square the base and halve the power
        n *= n;
        x >>= 1; 
    }
    
    return ans;
}