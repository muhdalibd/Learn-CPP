# Deep Dive into HashMap in C++

## Table of Contents
1. [Introduction](#introduction)
2. [Underlying Implementation](#underlying-implementation)
3. [Basic Operations](#basic-operations)
4. [Advanced Functions](#advanced-functions)
5. [Custom Hash Functions](#custom-hash-functions)
6. [Handling Collisions](#handling-collisions)
7. [Performance Analysis](#performance-analysis)
8. [Competitive Programming Shortcuts](#competitive-programming-shortcuts)
9. [Common Pitfalls](#common-pitfalls)
10. [Best Practices](#best-practices)

---

## Introduction

### What is HashMap?
- **HashMap** in C++ is implemented as `unordered_map` in STL
- Stores key-value pairs in **average O(1)** time complexity
- Uses **hash table** internally
- Part of `<unordered_map>` header

### Two Types Available:
1. **`unordered_map`**: Stores unique keys
2. **`unordered_multimap`**: Allows duplicate keys

---

## Underlying Implementation

### Hash Table Structure
```
[Hash Function] → Key → Hash Value → Bucket Index
```

### Internal Components:
- **Buckets**: Array of linked lists (or trees in newer implementations)
- **Hash Function**: Converts key to hash value
- **Load Factor**: Average elements per bucket (default max: 1.0)

### Key Characteristics:
- Keys are **hashed** into bucket indices
- Elements with same hash stored in same bucket (collision)
- C++11 onwards: buckets use **forward lists**
- When load factor exceeds max, **rehashing** occurs

---

## Basic Operations

### 1. Declaration & Initialization
```cpp
#include <unordered_map>

// Empty map
unordered_map<string, int> mp;

// With initial capacity
unordered_map<string, int> mp(100);

// Initializer list
unordered_map<string, int> mp = {
    {"apple", 1},
    {"banana", 2},
    {"orange", 3}
};

// Copy constructor
unordered_map<string, int> mp2(mp);

// Range constructor
unordered_map<string, int> mp3(mp.begin(), mp.end());
```

### 2. Insertion Methods
```cpp
unordered_map<string, int> mp;

// Method 1: Using []
mp["key"] = 10;  // Creates if not exists

// Method 2: Using insert()
mp.insert({"key2", 20});
mp.insert(make_pair("key3", 30));
mp.insert(pair<string, int>("key4", 40));

// Method 3: Using emplace() - More efficient
mp.emplace("key5", 50);

// Method 4: Insert with hint
mp.insert(mp.begin(), {"key6", 60});
```

### 3. Accessing Elements
```cpp
// Using [] - Creates if not exists (dangerous for const maps)
int val = mp["key"];

// Using at() - Throws exception if not found
int val2 = mp.at("key");  // Throws out_of_range if missing

// Find - Returns iterator
auto it = mp.find("key");
if (it != mp.end()) {
    cout << it->second;
}

// Count - Returns 0 or 1 for unordered_map
if (mp.count("key") > 0) {
    // Key exists
}

// Contains (C++20)
if (mp.contains("key")) {
    // Key exists
}
```

### 4. Deletion Methods
```cpp
// Erase by key
mp.erase("key");

// Erase by iterator
auto it = mp.find("key");
if (it != mp.end()) {
    mp.erase(it);
}

// Erase range
mp.erase(mp.begin(), mp.end());

// Clear all elements
mp.clear();
```

---

## Advanced Functions

### 1. Bucket Interface
```cpp
unordered_map<string, int> mp;

// Number of buckets
size_t bucket_count = mp.bucket_count();

// Maximum possible buckets
size_t max_buckets = mp.max_bucket_count();

// Bucket size (elements in specific bucket)
size_t bucket_size = mp.bucket_size(0);

// Get bucket index for key
size_t bucket_index = mp.bucket("key");
```

### 2. Hash Policy
```cpp
// Load factor
float load = mp.load_factor();  // Current load factor
float max_load = mp.max_load_factor();  // Max load factor

// Set max load factor
mp.max_load_factor(0.75);

// Rehash to specific bucket count
mp.rehash(100);

// Reserve buckets for expected elements
mp.reserve(1000);  // Prevents rehashing
```

### 3. Iterators
```cpp
// Begin/End
for (auto it = mp.begin(); it != mp.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
}

// Cbegin/Cend (const iterators)
for (auto it = mp.cbegin(); it != mp.cend(); ++it) {
    // Cannot modify elements
}

// Range-based for loop
for (const auto& pair : mp) {
    cout << pair.first << ": " << pair.second << endl;
}

// Structured bindings (C++17)
for (const auto& [key, value] : mp) {
    cout << key << ": " << value << endl;
}
```

### 4. Capacity Functions
```cpp
// Size - Number of elements
size_t size = mp.size();

// Max size
size_t max_size = mp.max_size();

// Empty check
bool isEmpty = mp.empty();
```

### 5. Other Useful Functions
```cpp
// Swap two maps
unordered_map<string, int> mp1, mp2;
mp1.swap(mp2);

// Extract node (C++17)
auto node = mp.extract("key");
if (node) {
    node.key() = "new_key";  // Modify key
    mp.insert(move(node));
}

// Merge two maps (C++17)
mp1.merge(mp2);

// Equal range
auto range = mp.equal_range("key");
for (auto it = range.first; it != range.second; ++it) {
    // Process elements
}
```

---

## Custom Hash Functions

### 1. For Custom Types
```cpp
struct Person {
    string name;
    int age;
    
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// Custom hash function
struct PersonHash {
    size_t operator()(const Person& p) const {
        size_t h1 = hash<string>()(p.name);
        size_t h2 = hash<int>()(p.age);
        return h1 ^ (h2 << 1);
    }
};

unordered_map<Person, string, PersonHash> personMap;
```

### 2. For Pairs
```cpp
struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

unordered_map<pair<int, int>, int, PairHash> mp;
```

### 3. For Tuples
```cpp
struct TupleHash {
    template <typename... Ts>
    size_t operator()(const tuple<Ts...>& t) const {
        return hash_tuple(t, index_sequence_for<Ts...>{});
    }
    
private:
    template <typename Tuple, size_t... Is>
    size_t hash_tuple(const Tuple& t, index_sequence<Is...>) const {
        size_t seed = 0;
        ((seed ^= hash<tuple_element_t<Is, Tuple>>{}(
            get<Is>(t)) + 0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
        return seed;
    }
};

unordered_map<tuple<int, int, int>, string, TupleHash> mp;
```

---

## Handling Collisions

### 1. Separate Chaining (Default in C++)
```cpp
// Multiple elements in same bucket stored in linked list
// Automatically handled by STL
```

### 2. Open Addressing (Not in STL, but good to know)
- Linear Probing
- Quadratic Probing
- Double Hashing

### 3. Load Factor Management
```cpp
unordered_map<int, int> mp;

// Set custom max load factor
mp.max_load_factor(0.5);  // Lower = less collisions, more memory

// Reserve space to prevent rehashing
mp.reserve(10000);
```

---

## Performance Analysis

### Time Complexity
| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert    | O(1)    | O(n)       |
| Delete    | O(1)    | O(n)       |
| Search    | O(1)    | O(n)       |
| Access [] | O(1)    | O(n)       |

### Space Complexity
- **O(n)** for n elements
- Extra space for buckets and overhead
- Each element stored in a node with pointer overhead

### Performance Tips
```cpp
// 1. Reserve space in advance
unordered_map<int, int> mp;
mp.reserve(1000000);  // Avoid rehashing

// 2. Use emplace instead of insert
mp.emplace(key, value);  // Constructs in-place

// 3. Use references to avoid copies
for (const auto& [key, value] : mp) {
    // No copying
}

// 4. Consider custom hash for better distribution
struct BetterHash {
    size_t operator()(int x) const {
        x ^= x >> 16;
        x *= 0x7feb352d;
        x ^= x >> 15;
        x *= 0x846ca68b;
        x ^= x >> 16;
        return x;
    }
};
```

---

## Competitive Programming Shortcuts

### 1. Quick Initialization
```cpp
// Method 1: Simple
unordered_map<int, int> mp;
mp[1] = 100;
mp[2] = 200;

// Method 2: Initializer list
unordered_map<int, int> mp = {{1, 100}, {2, 200}, {3, 300}};

// Method 3: From vector
vector<int> v = {1, 2, 3, 4};
unordered_map<int, int> mp;
for (int i = 0; i < v.size(); i++) mp[v[i]] = i;
```

### 2. Frequency Counting
```cpp
// Count frequency of elements
vector<int> arr = {1, 2, 3, 1, 2, 1};
unordered_map<int, int> freq;
for (int x : arr) freq[x]++;

// Print frequencies
for (auto& [num, count] : freq) {
    cout << num << " appears " << count << " times\n";
}
```

### 3. Character Frequency
```cpp
string s = "hello world";
unordered_map<char, int> freq;
for (char c : s) freq[c]++;
```

### 4. Two Sum Problem
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> mp;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (mp.count(complement)) {
            return {mp[complement], i};
        }
        mp[nums[i]] = i;
    }
    return {};
}
```

### 5. Check for Duplicates
```cpp
bool hasDuplicate(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (int x : nums) {
        if (mp[x]++ > 0) return true;
    }
    return false;
}
```

### 6. First Non-Repeating Character
```cpp
char firstNonRepeating(string s) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;
    
    for (char c : s) {
        if (freq[c] == 1) return c;
    }
    return '\0';
}
```

### 7. Group Anagrams
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    for (string s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        mp[key].push_back(s);
    }
    
    vector<vector<string>> result;
    for (auto& [key, group] : mp) {
        result.push_back(group);
    }
    return result;
}
```

### 8. Subarray Sum Equals K
```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    int sum = 0, count = 0;
    
    for (int x : nums) {
        sum += x;
        if (prefixSum.count(sum - k)) {
            count += prefixSum[sum - k];
        }
        prefixSum[sum]++;
    }
    return count;
}
```

### 9. Longest Substring Without Repeating Characters
```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> mp;
    int maxLen = 0, left = 0;
    
    for (int right = 0; right < s.length(); right++) {
        if (mp.count(s[right])) {
            left = max(left, mp[s[right]] + 1);
        }
        mp[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

### 10. Common CP Macros
```cpp
// Define macros for faster coding
#define umap unordered_map
#define umapi unordered_map<int, int>
#define umaps unordered_map<string, int>

// Usage
umapi freq;
umaps mp;
```

### 11. Fast I/O Setup
```cpp
// Add at start of main()
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
```

### 12. Custom Hash for Pairs (Common in CP)
```cpp
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

unordered_map<pair<int, int>, int, hash_pair> mp;
```

### 13. Pre-reserve for Performance
```cpp
// Always reserve if you know approximate size
unordered_map<int, int> mp;
mp.reserve(100000);  // Reserve space for 100K elements
mp.max_load_factor(0.7);  // Lower load factor for speed
```

### 14. Quick Check and Update
```cpp
// Check if key exists and update
if (mp.find(key) != mp.end()) {
    mp[key]++;  // Key exists
} else {
    mp[key] = 1;  // First occurrence
}

// Shorter version
mp[key]++;
```

---

## Common Pitfalls

### 1. Using [] on Const Maps
```cpp
void printMap(const unordered_map<int, int>& mp) {
    // cout << mp[1];  // ERROR! [] is non-const
    cout << mp.at(1);  // Correct way
}
```

### 2. Assuming Order
```cpp
// unordered_map has NO guaranteed order
// Don't rely on iteration order
// Use map for sorted order
```

### 3. Iterator Invalidation
```cpp
unordered_map<int, int> mp;
auto it = mp.begin();
mp.insert({1, 2});  // May invalidate iterators if rehash occurs
// Solution: Use reserve() if you know you'll insert
```

### 4. Performance Degradation
```cpp
// Bad: Frequent rehashing
unordered_map<int, int> mp;
for (int i = 0; i < 1000000; i++) {
    mp[i] = i;  // Multiple rehashes occur
}

// Good: Pre-reserve
unordered_map<int, int> mp;
mp.reserve(1000000);
for (int i = 0; i < 1000000; i++) {
    mp[i] = i;  // No rehashing
}
```

### 5. Hash Collision Attacks
```cpp
// Malicious input can cause many collisions
// Use custom hash for security-sensitive applications
struct SecureHash {
    size_t operator()(int x) const {
        // Use random seed to prevent attacks
        static const uint64_t seed = chrono::steady_clock::now()
            .time_since_epoch().count();
        x ^= seed;
        x ^= x >> 16;
        x *= 0x7feb352d;
        return x;
    }
};
```

---

## Best Practices

### 1. Choose the Right Container
```cpp
// Use unordered_map when:
// - Need O(1) average lookup
// - Order doesn't matter
// - Keys are hashable

// Use map when:
// - Need sorted order
// - Need range queries
// - Worst-case O(log n) required

// Use vector<pair> when:
// - Small number of elements (< 100)
// - Linear search is fine
```

### 2. Memory Management
```cpp
// Clear and shrink
mp.clear();
mp.rehash(0);  // Reduces bucket count to minimum

// Move instead of copy
unordered_map<int, int> newMap = std::move(oldMap);
```

### 3. Type Choices
```cpp
// Use const references in loops
for (const auto& pair : mp) {  // Avoid copying
    // Process pair
}

// Use structured bindings (C++17)
for (const auto& [key, value] : mp) {
    // Cleaner code
}
```

### 4. Exception Safety
```cpp
try {
    mp.at(key) = value;  // Throws if key not found
} catch (const out_of_range& e) {
    cout << "Key not found: " << e.what() << endl;
}
```

### 5. Performance Guidelines
```cpp
// 1. Reserve space when possible
mp.reserve(expected_size);

// 2. Use emplace for complex objects
mp.emplace(key, value);

// 3. Avoid unnecessary copies
mp.insert(move(tempPair));

// 4. Use find() instead of [] for lookup
auto it = mp.find(key);
if (it != mp.end()) {
    // Key exists
}
```

---

## Complete Example

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Student {
    string name;
    int id;
    
    bool operator==(const Student& other) const {
        return name == other.name && id == other.id;
    }
};

struct StudentHash {
    size_t operator()(const Student& s) const {
        return hash<string>()(s.name) ^ (hash<int>()(s.id) << 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Basic usage
    unordered_map<string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores.emplace("Charlie", 92);
    
    // Access and modify
    scores["Alice"] += 5;
    
    // Check existence
    if (scores.count("Bob")) {
        cout << "Bob's score: " << scores["Bob"] << endl;
    }
    
    // Iterate
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
    
    // Custom type
    unordered_map<Student, double, StudentHash> gpa;
    Student s1{"Alice", 1};
    gpa[s1] = 3.8;
    
    // Advanced operations
    scores.reserve(100);  // Reserve space
    float load = scores.load_factor();
    scores.max_load_factor(0.7);
    scores.rehash(50);
    
    return 0;
}
```

---

## Summary Table

| Function | Purpose | Complexity |
|----------|---------|------------|
| `operator[]` | Access/insert element | O(1) avg |
| `at()` | Access with bounds check | O(1) avg |
| `insert()` | Insert element | O(1) avg |
| `emplace()` | Construct in-place | O(1) avg |
| `erase()` | Remove element | O(1) avg |
| `find()` | Find element | O(1) avg |
| `count()` | Count elements with key | O(1) avg |
| `contains()` | Check existence (C++20) | O(1) avg |
| `clear()` | Remove all elements | O(n) |
| `size()` | Number of elements | O(1) |
| `empty()` | Check if empty | O(1) |
| `reserve()` | Reserve buckets | O(n) |
| `rehash()` | Set bucket count | O(n) |
| `load_factor()` | Current load factor | O(1) |
| `max_load_factor()` | Get/set max load factor | O(1) |
| `bucket_count()` | Number of buckets | O(1) |
| `bucket_size()` | Elements in bucket | O(bucket size) |
| `bucket()` | Bucket index for key | O(1) |

---

## Quick Reference Card

```cpp
// Essential includes
#include <unordered_map>

// Declaration
unordered_map<KeyType, ValueType> mp;

// Essential operations
mp[key] = value;           // Insert/update
mp.at(key);                // Access (throws if missing)
mp.find(key);              // Returns iterator
mp.count(key);             // 0 or 1
mp.erase(key);             // Remove
mp.clear();                // Remove all
mp.size();                 // Element count
mp.empty();                // Check empty

// Iteration
for (auto& [k, v] : mp)    // C++17
for (auto& p : mp)         // C++11

// Performance
mp.reserve(n);             // Reserve space
mp.max_load_factor(0.7);   // Set load factor
```

This comprehensive guide covers all essential aspects of HashMap in C++ with focus on practical usage and competitive programming applications.