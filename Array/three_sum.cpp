#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> threeSum(vector<int> &v, int target){
    vector<vector<int>> ans;
    int n = v.size()-1;
    for(int i=0; i<n-2; i++){
        for(int j=i+1; j<n-1; j++){
            for(int k=j+1; k<n; k++){
                int sum = v[i]+v[j]+v[k];
                if(sum == target){
                    ans.push_back({v[i], v[j], v[k]});
                }
            }
        }
    }
    return ans;
}

int main(){
    vector<int> v = {1, 2, -1, 0, 3, -2, 0, -4};
    int target = 0;
    vector<vector<int>> ans = threeSum(v, target);

    for(auto x : ans){
        for(int i=0; i<x.size(); i++){
            cout << x[i] <<" ";
        }
        cout << endl;
    }
    return 0;
}