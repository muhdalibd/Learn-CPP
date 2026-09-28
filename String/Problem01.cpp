#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "aeiou";
    int k = 2;
    int curr = 0;
    for(char ch : s){
        int val = ch - 'a' + 1;
        curr += val / 10 + val % 10;
    }

    cout << curr << endl;

    for (int i = 1; i < k; ++i) {
        int sum = 0;
        int x = curr;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        curr = sum;
    }

    cout << curr << endl;
}
