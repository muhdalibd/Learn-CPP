#include <iostream>
using namespace std;

void countSort(int arr[], int n);

int main(){
    int arr[] = {2, 3, 0, 0, 1, 2, 1, 3, 3, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    countSort(arr, n);
    for(auto x : arr){
        cout << x << " ";
    }
    return 0;
}

void countSort(int arr[], int n){
    int maxNum = arr[0];
    for(int i=1; i<n; i++){
        if(arr[i] > maxNum){
            maxNum = arr[i];
        }
    }

    // int count[maxNum+1] = {0};
    int *count = new int[(maxNum+1)]();
    for(int i=0; i<n; i++){
        count[arr[i]]++;
    }

    int idx = 0;
    for(int i=0; i<=maxNum; i++){
        while(count[i] > 0){
            arr[idx++] = i;
            count[i]--;
        }
    }

    delete []count;
}