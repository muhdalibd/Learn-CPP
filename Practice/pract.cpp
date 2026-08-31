#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& arr) {
    int n = arr.size();
    if(n <= 2) return n;

    int k = 2;
    for(int i=2; i<n; i++){
        if(arr[i] != arr[k-2]){
            arr[k] = arr[i];
            k ++;
        }
    }
    return k;
}

int main(){
    vector<int> arr = {1, 1, 1, 2, 2, 3, 3};
    int k = removeDuplicates(arr);
    for(int i=0; i<k; i++){
        cout << arr[i] << " ";
    }
    return 0;
}