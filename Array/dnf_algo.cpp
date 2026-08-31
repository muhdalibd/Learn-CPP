#include <iostream>
#include <vector>
using namespace std;

void dnfAlgo(vector<int>& v){
    int low , mid, high = 0;
    high = v.size()-1;
    while(mid <= high){
        if(v[mid] == 0){
            swap(v[low], v[mid]);
            low++; mid++;
        }
        else if(v[mid] == 2){
            swap(v[high], v[mid]);
            mid++; high--;
        }
        mid ++;
    }
    return;
}

int main(){

    vector<int> v = {0,1,2,0,1,2};
    // dnfAlgo(v);

    int low = 0, mid = 0;
    int high = v.size()-1;
    while(mid <= high){
        if(v[mid] == 0){
            swap(v[low], v[mid]);
            low++; mid++;
        }
        else if(v[mid] == 1){
            mid ++;
        }
        else if(v[mid] == 2){
            swap(v[mid], v[high]);
            high--;
        }
    }

    for(auto x : v){
        cout << x <<" ";
    }

    return 0;
}