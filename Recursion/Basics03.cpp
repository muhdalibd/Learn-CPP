#include <iostream>
using namespace std;

// //  Functional Recursion
// int isPalindrome(int n);

//  Parameterized Recursion
bool isPalindrome(string str, int i, int j);


int main(){
    int num;
    cin >> num;

    string str = to_string(num);
    int left = 0;
    int right = str.size()-1;

    cout << isPalindrome(str, left, right) << endl;
    return 0;
}


bool isPalindrome(string str, int i, int j){
    if(i >= j){
        return true;
    }
    if(str[i] != str[j]){
        return false;
    }
    return isPalindrome(str, i+1, j-1);
}