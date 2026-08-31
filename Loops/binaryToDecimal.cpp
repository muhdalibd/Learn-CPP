#include <iostream>
using namespace std;

int BinaryToDecimal(int n);
int DecimalToBinary(int n);

int main(){
    int decNum = BinaryToDecimal(101101);
    cout << decNum << endl;
    int biNum = DecimalToBinary(45);
    cout << biNum << endl;
    return 0;
}

int BinaryToDecimal(int n) {
    int decNum = 0;
    int pow = 1; // Tracks the power of 2 (1, 2, 4, 8, 16...)
    while (n > 0) {
        int lastDigit = n % 10; // Extract the rightmost binary digit
        n = n / 10;             // Remove the rightmost digit
        decNum = decNum + (lastDigit * pow); // Multiply by power of 2 and add to total
        pow = pow * 2;                       // Move to the next power of 2
    }
    return decNum;
}

int DecimalToBinary(int n) {
    int biNum = 0;
    int pow = 1; // Tracks the place value (1, 10, 100, 1000...)
    while (n > 0) {
        int rem = n % 2;
        n = n / 2;
        biNum = biNum + (rem * pow); // Add the digit to its correct place
        pow = pow * 10;              // Move to the next place value
    }
    return biNum;
}
