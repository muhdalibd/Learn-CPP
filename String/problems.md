# String Problem Set for Building Logic

## Table of Contents
1. [Easy Problems](#easy-problems)
2. [Medium Problems](#medium-problems)
3. [Hard Problems](#hard-problems)
4. [Pattern-Based Categorization](#pattern-based-categorization)
5. [Topic-wise Practice Plan](#topic-wise-practice-plan)

---

## Easy Problems

### 1. Basic String Manipulation

#### **LeetCode 344 - Reverse String**
```cpp
// Problem: Reverse a string in-place
// Input: ["h","e","l","l","o"]
// Output: ["o","l","l","e","h"]

class Solution {
public:
    void reverseString(vector<char>& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }
};
```

#### **LeetCode 125 - Valid Palindrome**
```cpp
// Problem: Check if string is palindrome (alphanumeric only)
// Input: "A man, a plan, a canal: Panama"
// Output: true

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;
            if (tolower(s[left]) != tolower(s[right])) return false;
            left++;
            right--;
        }
        return true;
    }
};
```

#### **LeetCode 14 - Longest Common Prefix**
```cpp
// Problem: Find longest common prefix
// Input: ["flower","flow","flight"]
// Output: "fl"

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        string prefix = strs[0];
        
        for (int i = 1; i < strs.size(); i++) {
            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if (prefix.empty()) return "";
            }
        }
        return prefix;
    }
};
```

#### **LeetCode 13 - Roman to Integer**
```cpp
// Problem: Convert Roman numeral to integer
// Input: "MCMXCIV"
// Output: 1994

class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> roman = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}
        };
        
        int result = 0;
        for (int i = 0; i < s.length(); i++) {
            if (i + 1 < s.length() && roman[s[i]] < roman[s[i + 1]]) {
                result -= roman[s[i]];
            } else {
                result += roman[s[i]];
            }
        }
        return result;
    }
};
```

---

### 2. String Counting and Frequency

#### **LeetCode 387 - First Unique Character**
```cpp
// Problem: Find first non-repeating character
// Input: "leetcode"
// Output: 0 (character 'l')

class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> freq(26, 0);
        
        // Count frequencies
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Find first unique
        for (int i = 0; i < s.length(); i++) {
            if (freq[s[i] - 'a'] == 1) return i;
        }
        return -1;
    }
};
```

#### **LeetCode 242 - Valid Anagram**
```cpp
// Problem: Check if two strings are anagrams
// Input: s = "anagram", t = "nagaram"
// Output: true

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        
        vector<int> count(26, 0);
        for (int i = 0; i < s.length(); i++) {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }
        
        for (int c : count) {
            if (c != 0) return false;
        }
        return true;
    }
};
```

---

### 3. String Matching

#### **LeetCode 28 - Implement strStr()**
```cpp
// Problem: Find substring in string
// Input: haystack = "hello", needle = "ll"
// Output: 2

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        
        int n = haystack.length();
        int m = needle.length();
        
        for (int i = 0; i <= n - m; i++) {
            if (haystack.substr(i, m) == needle) {
                return i;
            }
        }
        return -1;
    }
};
```

---

## Medium Problems

### 1. Substring Problems

#### **LeetCode 3 - Longest Substring Without Repeating Characters**
```cpp
// Problem: Find longest substring without repeating characters
// Input: "abcabcbb"
// Output: 3 ("abc")

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> lastIndex(256, -1);
        int maxLength = 0;
        int start = 0;
        
        for (int end = 0; end < s.length(); end++) {
            if (lastIndex[s[end]] >= start) {
                start = lastIndex[s[end]] + 1;
            }
            lastIndex[s[end]] = end;
            maxLength = max(maxLength, end - start + 1);
        }
        return maxLength;
    }
};
```

#### **LeetCode 5 - Longest Palindromic Substring**
```cpp
// Problem: Find longest palindrome substring
// Input: "babad"
// Output: "bab" or "aba"

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int start = 0, maxLength = 1;
        
        for (int i = 0; i < s.length(); i++) {
            // Odd length palindromes
            int left = i, right = i;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                if (right - left + 1 > maxLength) {
                    start = left;
                    maxLength = right - left + 1;
                }
                left--;
                right++;
            }
            
            // Even length palindromes
            left = i, right = i + 1;
            while (left >= 0 && right < s.length() && s[left] == s[right]) {
                if (right - left + 1 > maxLength) {
                    start = left;
                    maxLength = right - left + 1;
                }
                left--;
                right++;
            }
        }
        
        return s.substr(start, maxLength);
    }
};
```

---

### 2. String Manipulation

#### **LeetCode 49 - Group Anagrams**
```cpp
// Problem: Group anagrams together
// Input: ["eat","tea","tan","ate","nat","bat"]
// Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        
        for (string str : strs) {
            string sorted = str;
            sort(sorted.begin(), sorted.end());
            anagramMap[sorted].push_back(str);
        }
        
        vector<vector<string>> result;
        for (auto& pair : anagramMap) {
            result.push_back(pair.second);
        }
        return result;
    }
};
```

#### **LeetCode 151 - Reverse Words in a String**
```cpp
// Problem: Reverse words in string
// Input: "the sky is blue"
// Output: "blue is sky the"

class Solution {
public:
    string reverseWords(string s) {
        vector<string> words;
        string word;
        stringstream ss(s);
        
        // Extract words
        while (ss >> word) {
            words.push_back(word);
        }
        
        // Reverse and join
        string result;
        for (int i = words.size() - 1; i >= 0; i--) {
            result += words[i];
            if (i > 0) result += " ";
        }
        
        return result;
    }
};
```

#### **LeetCode 8 - String to Integer (atoi)**
```cpp
// Problem: Implement atoi
// Input: "42"
// Output: 42

class Solution {
public:
    int myAtoi(string s) {
        int i = 0, n = s.length();
        int sign = 1;
        long result = 0;
        
        // Skip whitespace
        while (i < n && s[i] == ' ') i++;
        
        // Check sign
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            sign = (s[i] == '-') ? -1 : 1;
            i++;
        }
        
        // Convert digits
        while (i < n && isdigit(s[i])) {
            result = result * 10 + (s[i] - '0');
            
            // Check overflow
            if (result * sign > INT_MAX) return INT_MAX;
            if (result * sign < INT_MIN) return INT_MIN;
            
            i++;
        }
        
        return result * sign;
    }
};
```

---

### 3. String Pattern Matching

#### **LeetCode 38 - Count and Say**
```cpp
// Problem: Generate count and say sequence
// Input: n = 4
// Output: "1211" (1 -> "11" -> "21" -> "1211")

class Solution {
public:
    string countAndSay(int n) {
        string result = "1";
        
        for (int i = 1; i < n; i++) {
            string temp;
            int count = 1;
            
            for (int j = 0; j < result.length(); j++) {
                if (j + 1 < result.length() && result[j] == result[j + 1]) {
                    count++;
                } else {
                    temp += to_string(count) + result[j];
                    count = 1;
                }
            }
            result = temp;
        }
        
        return result;
    }
};
```

#### **LeetCode 43 - Multiply Strings**
```cpp
// Problem: Multiply two string numbers
// Input: num1 = "123", num2 = "456"
// Output: "56088"

class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int m = num1.length(), n = num2.length();
        vector<int> result(m + n, 0);
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int sum = mul + result[i + j + 1];
                
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }
        
        string answer;
        int i = 0;
        while (i < result.size() && result[i] == 0) i++;
        while (i < result.size()) {
            answer += to_string(result[i]);
            i++;
        }
        
        return answer;
    }
};
```

---

## Hard Problems

### 1. Advanced String Algorithms

#### **LeetCode 76 - Minimum Window Substring**
```cpp
// Problem: Find minimum window substring
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(128, 0), have(128, 0);
        
        // Count characters needed
        for (char c : t) need[c]++;
        
        int required = 0;
        for (int count : need) {
            if (count > 0) required++;
        }
        
        int left = 0, right = 0;
        int formed = 0;
        int minLen = INT_MAX;
        int minLeft = 0;
        
        while (right < s.length()) {
            char c = s[right];
            have[c]++;
            
            if (need[c] > 0 && have[c] == need[c]) {
                formed++;
            }
            
            while (formed == required && left <= right) {
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                char leftChar = s[left];
                have[leftChar]--;
                
                if (need[leftChar] > 0 && have[leftChar] < need[leftChar]) {
                    formed--;
                }
                left++;
            }
            
            right++;
        }
        
        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};
```

#### **LeetCode 10 - Regular Expression Matching**
```cpp
// Problem: Implement regex matching
// Input: s = "aa", p = "a*"
// Output: true

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        
        dp[0][0] = true;
        
        // Handle patterns like a*, a*b*, etc.
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 2];
                    
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        dp[i][j] = dp[i][j] || dp[i - 1][j];
                    }
                }
            }
        }
        
        return dp[m][n];
    }
};
```

---

### 2. String Permutation Problems

#### **LeetCode 567 - Permutation in String**
```cpp
// Problem: Check if string contains permutation of another
// Input: s1 = "ab", s2 = "eidbaooo"
// Output: true

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Freq(26, 0), s2Freq(26, 0);
        
        // Count frequencies
        for (char c : s1) s1Freq[c - 'a']++;
        
        int windowSize = s1.length();
        
        // Initial window
        for (int i = 0; i < windowSize; i++) {
            s2Freq[s2[i] - 'a']++;
        }
        
        // Check initial window
        if (s1Freq == s2Freq) return true;
        
        // Slide window
        for (int i = windowSize; i < s2.length(); i++) {
            s2Freq[s2[i] - 'a']++;
            s2Freq[s2[i - windowSize] - 'a']--;
            
            if (s1Freq == s2Freq) return true;
        }
        
        return false;
    }
};
```

---

## Pattern-Based Categorization

### 1. Two Pointers Pattern

**Problems:**
- LeetCode 125 - Valid Palindrome
- LeetCode 344 - Reverse String
- LeetCode 345 - Reverse Vowels of a String
- LeetCode 680 - Valid Palindrome II

### 2. Sliding Window Pattern

**Problems:**
- LeetCode 3 - Longest Substring Without Repeating Characters
- LeetCode 76 - Minimum Window Substring
- LeetCode 438 - Find All Anagrams in a String
- LeetCode 567 - Permutation in String

### 3. Hash Map/Set Pattern

**Problems:**
- LeetCode 49 - Group Anagrams
- LeetCode 242 - Valid Anagram
- LeetCode 387 - First Unique Character
- LeetCode 409 - Longest Palindrome

### 4. Dynamic Programming Pattern

**Problems:**
- LeetCode 5 - Longest Palindromic Substring
- LeetCode 10 - Regular Expression Matching
- LeetCode 72 - Edit Distance
- LeetCode 1143 - Longest Common Subsequence

### 5. Stack Pattern

**Problems:**
- LeetCode 20 - Valid Parentheses
- LeetCode 71 - Simplify Path
- LeetCode 394 - Decode String
- LeetCode 1047 - Remove All Adjacent Duplicates

### 6. Backtracking Pattern

**Problems:**
- LeetCode 17 - Letter Combinations of Phone Number
- LeetCode 22 - Generate Parentheses
- LeetCode 131 - Palindrome Partitioning
- LeetCode 140 - Word Break II

---

## Topic-wise Practice Plan

### Week 1: Basic String Operations
```cpp
// Day 1-2: Basic Manipulation
- LeetCode 344: Reverse String
- LeetCode 541: Reverse String II
- LeetCode 557: Reverse Words in String III

// Day 3-4: String Comparison
- LeetCode 14: Longest Common Prefix
- LeetCode 242: Valid Anagram
- LeetCode 205: Isomorphic Strings

// Day 5-7: String Parsing
- LeetCode 13: Roman to Integer
- LeetCode 8: String to Integer (atoi)
- LeetCode 38: Count and Say
```

### Week 2: Intermediate Patterns
```cpp
// Day 1-2: Substring Problems
- LeetCode 3: Longest Substring Without Repeating Characters
- LeetCode 30: Substring with Concatenation of All Words

// Day 3-4: Palindrome Problems
- LeetCode 125: Valid Palindrome
- LeetCode 5: Longest Palindromic Substring
- LeetCode 647: Palindromic Substrings

// Day 5-7: Anagram and Permutation
- LeetCode 49: Group Anagrams
- LeetCode 438: Find All Anagrams
- LeetCode 567: Permutation in String
```

### Week 3: Advanced Topics
```cpp
// Day 1-2: Dynamic Programming
- LeetCode 72: Edit Distance
- LeetCode 97: Interleaving String

// Day 3-4: Complex Parsing
- LeetCode 10: Regular Expression Matching
- LeetCode 44: Wildcard Matching

// Day 5-7: Comprehensive Review
- LeetCode 76: Minimum Window Substring
- LeetCode 32: Longest Valid Parentheses
```

---

## Additional Platform Recommendations

### Codeforces String Problems
```
1. 1A - Theatre Square (String formatting)
2. 71A - Way Too Long Words
3. 118A - String Task
4. 112A - Petya and Strings
5. 236A - Boy or Girl
6. 281A - Word Capitalization
7. 266A - Stones on the Table
8. 791A - Bear and Big Brother (String comparison)
```

### HackerRank String Problems
```
1. Strings Introduction
2. StringStream
3. Attribute Parser
4. Strings - Making Anagrams
5. Sherlock and the Valid String
6. Common Child
7. Bear and Steady Gene
8. Morgan and a String
```

### GeeksforGeeks String Problems
```
1. Check if string is rotated by two places
2. Roman Number to Integer
3. Anagram
4. Remove Duplicates
5. Longest Distinct characters in string
6. Implement Atoi
7. Validate an IP Address
8. Longest Palindrome in a String
9. Permutations of a given string
10. Recursively remove all adjacent duplicates
```

---

## Tips for Building Strong String Logic

1. **Start with Easy Problems**: Build confidence with basic string operations before moving to complex algorithms.

2. **Understand Time/Space Complexity**: Always analyze your solution's complexity. Most string problems can be optimized to O(n) time.

3. **Master Common Patterns**:
   - Sliding window for substring problems
   - Two pointers for palindrome/reverse problems
   - Hash maps for frequency counting
   - Dynamic programming for optimization problems

4. **Practice Edge Cases**:
   - Empty strings
   - Single character strings
   - All same characters
   - Very long strings
   - Special characters and spaces

5. **Use Built-in Functions Wisely**: While C++ provides many string functions, understand their complexity:
   - `substr()` is O(n)
   - `find()` is O(n*m) in worst case
   - `+=` is amortized O(1)

6. **Debug Effectively**:
   - Print intermediate results
   - Test with small inputs first
   - Use assertions to validate assumptions

Remember: The key to mastering string problems is consistent practice and understanding the underlying patterns rather than memorizing solutions.