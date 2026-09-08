# LeetCode Array Problems for Building Logic

## Beginner Level (Easy Problems)

### 1. Basic Array Operations
```cpp
// Problem: Two Sum (LeetCode 1)
// Find two numbers that add up to target
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    for(int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if(mp.find(complement) != mp.end()) {
            return {mp[complement], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}

// Problem: Best Time to Buy and Sell Stock (LeetCode 121)
// Max profit from single transaction
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    for(int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}

// Problem: Contains Duplicate (LeetCode 217)
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for(int num : nums) {
        if(seen.count(num)) return true;
        seen.insert(num);
    }
    return false;
}

// Problem: Plus One (LeetCode 66)
vector<int> plusOne(vector<int>& digits) {
    for(int i = digits.size() - 1; i >= 0; i--) {
        if(digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    digits.insert(digits.begin(), 1);
    return digits;
}
```

### 2. Array Manipulation
```cpp
// Problem: Move Zeroes (LeetCode 283)
void moveZeroes(vector<int>& nums) {
    int nonZeroIndex = 0;
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] != 0) {
            swap(nums[nonZeroIndex], nums[i]);
            nonZeroIndex++;
        }
    }
}

// Problem: Remove Duplicates from Sorted Array (LeetCode 26)
int removeDuplicates(vector<int>& nums) {
    if(nums.empty()) return 0;
    int uniqueIndex = 0;
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] != nums[uniqueIndex]) {
            uniqueIndex++;
            nums[uniqueIndex] = nums[i];
        }
    }
    return uniqueIndex + 1;
}

// Problem: Rotate Array (LeetCode 189)
void rotate(vector<int>& nums, int k) {
    k = k % nums.size();
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

// Problem: Merge Sorted Array (LeetCode 88)
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    while(j >= 0) {
        if(i >= 0 && nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
}
```

## Intermediate Level (Medium Problems)

### 3. Two Pointers Technique
```cpp
// Problem: 3Sum (LeetCode 15)
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    
    for(int i = 0; i < nums.size() - 2; i++) {
        if(i > 0 && nums[i] == nums[i-1]) continue;
        
        int left = i + 1, right = nums.size() - 1;
        while(left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if(sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while(left < right && nums[left] == nums[left+1]) left++;
                while(left < right && nums[right] == nums[right-1]) right--;
                left++; right--;
            }
            else if(sum < 0) left++;
            else right--;
        }
    }
    return result;
}

// Problem: Container With Most Water (LeetCode 11)
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while(left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxWater = max(maxWater, width * h);
        
        if(height[left] < height[right]) left++;
        else right--;
    }
    return maxWater;
}

// Problem: Trapping Rain Water (LeetCode 42)
int trap(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;
    
    while(left < right) {
        if(height[left] < height[right]) {
            if(height[left] >= leftMax) leftMax = height[left];
            else water += leftMax - height[left];
            left++;
        } else {
            if(height[right] >= rightMax) rightMax = height[right];
            else water += rightMax - height[right];
            right--;
        }
    }
    return water;
}
```

### 4. Sliding Window
```cpp
// Problem: Maximum Subarray (LeetCode 53) - Kadane's Algorithm
int maxSubArray(vector<int>& nums) {
    int currentSum = nums[0];
    int maxSum = nums[0];
    
    for(int i = 1; i < nums.size(); i++) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    return maxSum;
}

// Problem: Maximum Product Subarray (LeetCode 152)
int maxProduct(vector<int>& nums) {
    int maxProd = nums[0];
    int minProd = nums[0];
    int result = nums[0];
    
    for(int i = 1; i < nums.size(); i++) {
        if(nums[i] < 0) swap(maxProd, minProd);
        
        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        
        result = max(result, maxProd);
    }
    return result;
}

// Problem: Subarray Sum Equals K (LeetCode 560)
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0, count = 0;
    
    for(int num : nums) {
        sum += num;
        if(prefixSum.find(sum - k) != prefixSum.end()) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    return count;
}

// Problem: Longest Substring Without Repeating Characters (LeetCode 3)
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;
    int maxLength = 0;
    int left = 0;
    
    for(int right = 0; right < s.length(); right++) {
        if(lastSeen.find(s[right]) != lastSeen.end()) {
            left = max(left, lastSeen[s[right]] + 1);
        }
        lastSeen[s[right]] = right;
        maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
}
```

### 5. Binary Search on Arrays
```cpp
// Problem: Search in Rotated Sorted Array (LeetCode 33)
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(nums[mid] == target) return mid;
        
        if(nums[left] <= nums[mid]) {
            if(nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if(nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

// Problem: Find First and Last Position of Element (LeetCode 34)
vector<int> searchRange(vector<int>& nums, int target) {
    auto lower = lower_bound(nums.begin(), nums.end(), target);
    auto upper = upper_bound(nums.begin(), nums.end(), target);
    
    if(lower == nums.end() || *lower != target) {
        return {-1, -1};
    }
    
    return {(int)(lower - nums.begin()), (int)(upper - nums.begin() - 1)};
}

// Problem: Search a 2D Matrix (LeetCode 74)
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.empty() || matrix[0].empty()) return false;
    
    int rows = matrix.size(), cols = matrix[0].size();
    int left = 0, right = rows * cols - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        int midValue = matrix[mid / cols][mid % cols];
        
        if(midValue == target) return true;
        else if(midValue < target) left = mid + 1;
        else right = mid - 1;
    }
    return false;
}

// Problem: Find Peak Element (LeetCode 162)
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] > nums[mid + 1]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
```

## Advanced Level (Hard Problems)

### 6. Matrix Operations
```cpp
// Problem: Spiral Matrix (LeetCode 54)
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    if(matrix.empty()) return result;
    
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    
    while(top <= bottom && left <= right) {
        for(int j = left; j <= right; j++)
            result.push_back(matrix[top][j]);
        top++;
        
        for(int i = top; i <= bottom; i++)
            result.push_back(matrix[i][right]);
        right--;
        
        if(top <= bottom) {
            for(int j = right; j >= left; j--)
                result.push_back(matrix[bottom][j]);
            bottom--;
        }
        
        if(left <= right) {
            for(int i = bottom; i >= top; i--)
                result.push_back(matrix[i][left]);
            left++;
        }
    }
    return result;
}

// Problem: Rotate Image (LeetCode 48)
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    for(int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

// Problem: Set Matrix Zeroes (LeetCode 73)
void setZeroes(vector<vector<int>>& matrix) {
    bool firstRowZero = false, firstColZero = false;
    
    for(int j = 0; j < matrix[0].size(); j++) {
        if(matrix[0][j] == 0) firstRowZero = true;
    }
    for(int i = 0; i < matrix.size(); i++) {
        if(matrix[i][0] == 0) firstColZero = true;
    }
    
    for(int i = 1; i < matrix.size(); i++) {
        for(int j = 1; j < matrix[0].size(); j++) {
            if(matrix[i][j] == 0) {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }
    
    for(int i = 1; i < matrix.size(); i++) {
        for(int j = 1; j < matrix[0].size(); j++) {
            if(matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
    }
    
    if(firstRowZero) {
        for(int j = 0; j < matrix[0].size(); j++) matrix[0][j] = 0;
    }
    if(firstColZero) {
        for(int i = 0; i < matrix.size(); i++) matrix[i][0] = 0;
    }
}

// Problem: Word Search (LeetCode 79)
bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index) {
    if(index == word.length()) return true;
    if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() 
       || board[i][j] != word[index]) return false;
    
    char temp = board[i][j];
    board[i][j] = '#';
    
    bool found = dfs(board, word, i+1, j, index+1) ||
                 dfs(board, word, i-1, j, index+1) ||
                 dfs(board, word, i, j+1, index+1) ||
                 dfs(board, word, i, j-1, index+1);
    
    board[i][j] = temp;
    return found;
}

bool exist(vector<vector<char>>& board, string word) {
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if(dfs(board, word, i, j, 0)) return true;
        }
    }
    return false;
}
```

### 7. Prefix Sum & Difference Array
```cpp
// Problem: Range Sum Query (LeetCode 303)
class NumArray {
    vector<int> prefixSum;
public:
    NumArray(vector<int>& nums) {
        prefixSum.resize(nums.size() + 1, 0);
        for(int i = 0; i < nums.size(); i++) {
            prefixSum[i+1] = prefixSum[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefixSum[right+1] - prefixSum[left];
    }
};

// Problem: Range Addition (LeetCode 370)
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> result(length, 0);
    
    for(auto& update : updates) {
        int start = update[0], end = update[1], inc = update[2];
        result[start] += inc;
        if(end + 1 < length) result[end+1] -= inc;
    }
    
    for(int i = 1; i < length; i++) {
        result[i] += result[i-1];
    }
    return result;
}

// Problem: Product of Array Except Self (LeetCode 238)
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    
    int leftProduct = 1;
    for(int i = 0; i < n; i++) {
        result[i] *= leftProduct;
        leftProduct *= nums[i];
    }
    
    int rightProduct = 1;
    for(int i = n-1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    return result;
}
```

### 8. Sorting & Searching Advanced
```cpp
// Problem: Merge Intervals (LeetCode 56)
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if(intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for(int i = 1; i < intervals.size(); i++) {
        if(intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

// Problem: Majority Element (LeetCode 169) - Boyer-Moore Voting
int majorityElement(vector<int>& nums) {
    int count = 0, candidate = 0;
    
    for(int num : nums) {
        if(count == 0) candidate = num;
        count += (num == candidate) ? 1 : -1;
    }
    return candidate;
}

// Problem: Sort Colors (LeetCode 75) - Dutch National Flag
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    
    while(mid <= high) {
        if(nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++; mid++;
        } else if(nums[mid] == 1) {
            mid++;
        } else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
}

// Problem: Kth Largest Element (LeetCode 215)
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for(int num : nums) {
        minHeap.push(num);
        if(minHeap.size() > k) {
            minHeap.pop();
        }
    }
    return minHeap.top();
}
```

### 9. Hard Array Problems
```cpp
// Problem: First Missing Positive (LeetCode 41)
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    
    for(int i = 0; i < n; i++) {
        while(nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i]) {
            swap(nums[i], nums[nums[i]-1]);
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(nums[i] != i + 1) return i + 1;
    }
    return n + 1;
}

// Problem: Longest Consecutive Sequence (LeetCode 128)
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int maxLength = 0;
    
    for(int num : numSet) {
        if(!numSet.count(num - 1)) {
            int currentNum = num;
            int currentLength = 1;
            
            while(numSet.count(currentNum + 1)) {
                currentNum++;
                currentLength++;
            }
            maxLength = max(maxLength, currentLength);
        }
    }
    return maxLength;
}

// Problem: Find All Duplicates in Array (LeetCode 442)
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> result;
    
    for(int i = 0; i < nums.size(); i++) {
        int index = abs(nums[i]) - 1;
        if(nums[index] < 0) {
            result.push_back(abs(nums[i]));
        } else {
            nums[index] = -nums[index];
        }
    }
    return result;
}

// Problem: Sliding Window Maximum (LeetCode 239)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;
    
    for(int i = 0; i < nums.size(); i++) {
        // Remove elements outside window
        while(!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        // Remove smaller elements
        while(!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if(i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}
```

## Practice Platform Links

1. **LeetCode** - https://leetcode.com/problemset/arrays/
2. **HackerRank** - https://www.hackerrank.com/domains/algorithms/arrays
3. **Codeforces** - https://codeforces.com/problemset?tags=arrays
4. **GeeksforGeeks** - https://practice.geeksforgeeks.org/explore?category[]=Arrays
5. **CodeChef** - https://www.codechef.com/tags/problems/arrays

## Problem Solving Template
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()

class Solution {
public:
    // Your solution here
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution sol;
    // Test cases
    vector<int> test = {1, 2, 3, 4, 5};
    // Call solution method
    // Print result
    
    return 0;
}
```

## Tips for Building Logic
1. **Start with brute force** - Get a working solution first
2. **Optimize gradually** - Look for patterns and repeated work
3. **Draw diagrams** - Visualize the problem
4. **Test edge cases** - Empty arrays, single element, duplicates
5. **Practice daily** - Solve at least 2-3 problems per day
6. **Review solutions** - Learn from others' approaches
7. **Time yourself** - Simulate competitive conditions