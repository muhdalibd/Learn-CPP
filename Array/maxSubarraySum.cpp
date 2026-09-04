#include <iostream>
#include <vector>
using namespace std;

// int maxSubarraySum(vector<int>& arr, int k) {
//     int maxSum = 0;
//     for(int i=0; i<=arr.size()-k; i++){
//         int sum = 0;
//         for(int j=i; j<k+i; j++){
//             sum += arr[j];
//         }
//         maxSum = max(sum, maxSum);
//     }
//     return maxSum;
// }

int maxSubarraySum(vector<int>& arr, int k) {
    int maxSum = 0;
    for(int i=0; i<=arr.size()-k; i++){
        int sum = 0;
        for(int j=i; j<k+i; j++){
            if(arr[j]!= arr[j+1] && arr[j+1] != arr[j+2]){
                sum += arr[j];
            }
        }
        maxSum = max(sum, maxSum);
    }
    return maxSum;
}

int main(){
    // vector<int> v = {100, 200, 300, 400};
    vector<int> v = {1, 5, 4, 2, 9, 9, 9};
    cout << maxSubarraySum(v, 3);
    return 0;
}