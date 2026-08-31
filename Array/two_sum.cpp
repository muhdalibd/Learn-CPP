#include <iostream>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target){
    int i = 0, j = nums.size()-1;
    while(i < j){
        int sum = nums[i] + nums[j];
        if(sum == target){
            return {i,j};
        }
        else if(sum > target){
            j--;
        }
        else{
            i++;
        }
    }
    return {-1, -1};
}

int main(){
    vector<int> v = {1, 2, 4, 6, 8, 9};
    int target = 14;
    vector<int> ans = twoSum(v, target);
    for(int i=0; i<2; i++){
        cout << ans[i] <<" ";
    }
    return 0;
}