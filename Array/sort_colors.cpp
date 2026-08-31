#include <iostream>
#include <vector>
using namespace std;

void sortColors(vector<int>& nums){
    int low, mid, high;
    low = mid = 0;
    high = nums.size()-1;

    while(mid <= high){
        if(nums[mid] == 0){
            swap(nums[low], nums[mid]); 
            low++;  mid++;
        }
        else if(nums[mid] == 2){
            swap(nums[mid], nums[high]); 
            high--;
        }
        else{
            mid ++;
        }
    }
}

int main(){
    vector<int> v = {0, 2, 1, 2, 1, 2, 0, 0, 1, 2, 0, 1, 0, 2, 1};
    sortColors(v);
    for(auto x : v){
        cout << x <<" ";
    }
    return 0;
}