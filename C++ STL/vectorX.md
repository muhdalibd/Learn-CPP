# Vector STL in C++ - Complete Guide

## 📌 What is Vector?

Vector is a **dynamic array** that can grow or shrink in size automatically. It's one of the most commonly used containers in C++ STL.

### Key Features
- ✅ Dynamic size (auto-resizing)
- ✅ Fast random access O(1)
- ✅ Efficient insertion/deletion at end O(1)
- ✅ Cache-friendly (contiguous memory)
- ✅ Rich set of member functions

---

## 🔨 Vector Creation Methods

### 1. Empty Vector
```cpp
vector<int> v;  // Creates empty vector
```

### 2. With Size and Default Value
```cpp
vector<int> v1(5, 10);  // {10, 10, 10, 10, 10}
vector<int> v2(3);      // {0, 0, 0} - default initialized
```

### 3. Using Initializer List (C++11)
```cpp
vector<int> v3 = {1, 2, 3, 4, 5};
vector<int> v4 {1, 2, 3, 4, 5};
```

### 4. From Array
```cpp
int arr[] = {1, 2, 3, 4, 5};
vector<int> v5(arr, arr + 5);
```

### 5. From Another Vector's Range
```cpp
vector<int> x = {1, 2, 3, 4, 5};
vector<int> v6(x.begin() + 1, x.end() - 1);  // {2, 3, 4}
```

### 6. Copy Constructor
```cpp
vector<int> y = {1, 2, 3, 4, 5};
vector<int> v7(y);   // Deep copy
vector<int> v8 = y;  // Deep copy
```

### 7. Move Semantics (C++11)
```cpp
vector<int> z = {1, 2, 3, 4, 5};
vector<int> v9(move(z));  // Transfers ownership, z becomes empty
```

### 8. Using assign() Method
```cpp
vector<int> v10;
v10.assign(5, 100);              // {100, 100, 100, 100, 100}
v10.assign(arr, arr + 3);        // From array range
v10.assign({10, 20, 30});        // From initializer list
```

---

## 📝 Important Member Functions

### Element Access

| Function | Description | Complexity |
|----------|-------------|------------|
| `v[i]` | Access element (no bounds check) | O(1) |
| `v.at(i)` | Access element (with bounds check) | O(1) |
| `v.front()` | First element | O(1) |
| `v.back()` | Last element | O(1) |
| `v.data()` | Pointer to underlying array | O(1) |

```cpp
vector<int> v = {10, 20, 30};
cout << v[0];      // 10 (no bounds checking)
cout << v.at(1);   // 20 (throws exception if out of range)
cout << v.front(); // 10
cout << v.back();  // 30
```

### Size and Capacity

| Function | Description |
|----------|-------------|
| `size()` | Number of elements |
| `capacity()` | Allocated storage size |
| `empty()` | Check if empty |
| `reserve(n)` | Reserve memory for n elements |
| `shrink_to_fit()` | Reduce capacity to size |
| `max_size()` | Maximum possible size |

```cpp
vector<int> v;
v.reserve(100);    // Pre-allocate memory
v.push_back(1);
cout << v.size();     // 1
cout << v.capacity(); // 100
v.shrink_to_fit();    // capacity = size
```

### Modifiers

| Function | Description | Complexity |
|----------|-------------|------------|
| `push_back(x)` | Add element at end | O(1) |
| `emplace_back(args...)` | Construct and add at end | O(1) |
| `pop_back()` | Remove last element | O(1) |
| `insert(pos, x)` | Insert at position | O(n) |
| `erase(pos)` | Remove at position | O(n) |
| `clear()` | Remove all elements | O(n) |
| `swap(other)` | Swap two vectors | O(1) |

```cpp
vector<int> v;
v.push_back(10);       // {10}
v.emplace_back(20);    // {10, 20} - constructs in-place
v.insert(v.begin(), 5); // {5, 10, 20}
v.erase(v.begin());    // {10, 20}
v.pop_back();          // {10}
v.clear();             // {}
```

### Iterators

```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Normal iterators
auto it = v.begin();     // Points to first element
auto end = v.end();      // Points past last element

// Reverse iterators
auto rit = v.rbegin();   // Points to last element
auto rend = v.rend();    // Points before first element

// Const iterators (read-only)
auto cit = v.cbegin();
auto cend = v.cend();
```

---

## 🚀 Competitive Programming Shortcuts

### 1. Quick Initialization
```cpp
// Size n with value 0
vector<int> dp(n, 0);

// Size n with value -1
vector<int> vis(n, -1);

// 2D vector (n x m) initialized to 0
vector<vector<int>> grid(n, vector<int>(m, 0));

// 3D vector
vector<vector<vector<int>>> dp3(n, vector<vector<int>>(m, vector<int>(k, -1)));
```

### 2. Common Operations
```cpp
// Sort vector
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>());  // Descending

// Reverse vector
reverse(v.begin(), v.end());

// Find element
auto it = find(v.begin(), v.end(), target);
if (it != v.end()) {
    int index = it - v.begin();
}

// Count occurrences
int cnt = count(v.begin(), v.end(), value);

// Sum of elements
int sum = accumulate(v.begin(), v.end(), 0);

// Max/Min element
auto max_it = max_element(v.begin(), v.end());
auto min_it = min_element(v.begin(), v.end());

// Remove duplicates
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

// Binary search
bool exists = binary_search(v.begin(), v.end(), target);
auto lb = lower_bound(v.begin(), v.end(), target);  // First >= target
auto ub = upper_bound(v.begin(), v.end(), target);  // First > target
```

### 3. Lambda Functions with STL
```cpp
// Custom sort
sort(v.begin(), v.end(), [](int a, int b) {
    return abs(a) < abs(b);  // Sort by absolute value
});

// Custom comparator for pairs
vector<pair<int,int>> vp;
sort(vp.begin(), vp.end(), [](auto& a, auto& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second > b.second;
});

// Find with condition
auto it = find_if(v.begin(), v.end(), [](int x) {
    return x > 50;
});

// Remove if condition
v.erase(remove_if(v.begin(), v.end(), [](int x) {
    return x % 2 == 0;  // Remove even numbers
}), v.end());
```

### 4. Memory Optimization
```cpp
// Reserve memory to avoid reallocation
vector<int> v;
v.reserve(1000000);  // Reserve for 1M elements

// Clear vector and free memory
vector<int>().swap(v);  // Free all memory
v.clear();  // Just clears elements, memory retained
v.shrink_to_fit();  // Reduce capacity

// Move instead of copy
vector<int> v2 = move(v1);  // Fast, v1 becomes empty
```

### 5. String to Vector Conversions
```cpp
// Split string by delimiter
string s = "Hello World CPP";
vector<string> tokens;
stringstream ss(s);
string token;
while (getline(ss, token, ' ')) {
    tokens.push_back(token);
}

// String to vector of chars
string str = "abc";
vector<char> vc(str.begin(), str.end());

// Vector of chars to string
string str2(vc.begin(), vc.end());
```

### 6. Common Patterns
```cpp
// Prefix sum
vector<int> prefix(n + 1, 0);
for (int i = 0; i < n; i++) {
    prefix[i + 1] = prefix[i] + arr[i];
}

// Difference array
vector<int> diff(n + 1, 0);
diff[l] += val;
diff[r + 1] -= val;

// Rotate vector
rotate(v.begin(), v.begin() + k, v.end());  // Left rotate by k
rotate(v.begin(), v.end() - k, v.end());    // Right rotate by k

// Next permutation
next_permutation(v.begin(), v.end());
prev_permutation(v.begin(), v.end());
```

### 7. Performance Tips
```cpp
// Use emplace_back instead of push_back for objects
vector<pair<int, int>> v;
v.emplace_back(1, 2);  // Better than v.push_back({1, 2});

// Use reference in range-based loops
for (auto& x : v) {  // Avoid copying
    x *= 2;
}
for (const auto& x : v) {  // Read-only
    cout << x;
}

// Pre-increment iterators
for (auto it = v.begin(); it != v.end(); ++it) {  // Not it++
    // ...
}
```

### 8. Debugging Helpers
```cpp
// Print vector
template<typename T>
void print(const vector<T>& v) {
    for (const auto& x : v) cout << x << " ";
    cout << endl;
}

// Print 2D vector
template<typename T>
void print2D(const vector<vector<T>>& v) {
    for (const auto& row : v) {
        for (const auto& x : row) cout << x << " ";
        cout << endl;
    }
}
```

---

## ⚡ Time Complexities Summary

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Access ([] / at) | O(1) | O(1) |
| push_back | O(1) | O(n) amortized |
| pop_back | O(1) | O(1) |
| insert | O(n) | O(n) |
| erase | O(n) | O(n) |
| sort | O(n log n) | O(n log n) |
| find | O(n) | O(n) |
| binary_search | O(log n) | O(log n) |

---

## 💡 Best Practices

1. **Use `reserve()`** when size is known in advance
2. **Use `emplace_back()`** instead of `push_back()` for objects
3. **Use `const auto&`** in range-based loops for read-only access
4. **Use `at()`** for safety-critical code (throws exceptions)
5. **Use `[]`** for performance-critical code (no bounds checking)
6. **Clear and free memory** with `vector<int>().swap(v)` when done
7. **Avoid `insert()`/`erase()`** in middle for large vectors (O(n))
8. **Prefer `vector`** over arrays for dynamic data in C++

This guide covers the essential vector operations and competitive programming shortcuts that will make your code more efficient and concise! 🎯