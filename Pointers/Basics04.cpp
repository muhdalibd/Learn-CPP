#include <iostream>
using namespace std;

//  want to print two value, pass these as reference
void getMinMax(int *num, int size, int *min, int *max){
    for(int i=1; i<size; i++){
        if(*(num+i) < *min){
            *min = *(num+i);
        }
        if(*(num+i) > *max){
            *max = *(num+i);
        }
    }
    return;
}

int main(){
    int num[] = {5, 4, -2, 29, 6};
    int len = sizeof(num)/sizeof(num[0]);
    int min = *num;
    int max = *num;
    // cout << min << endl;
    getMinMax(num, len, &min, &max);
    cout << min <<" "<< max << endl;
    return 0;
}