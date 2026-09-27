# Deep Dive into Arrays, Vectors & Matrices in C++

## Table of Contents
1. [Arrays (Static)](#arrays-static)
2. [Vectors (Dynamic Arrays)](#vectors-dynamic-arrays)
3. [Matrices (2D Arrays & Vectors)](#matrices-2d-arrays--vectors)
4. [STL Algorithms for Arrays/Vectors](#stl-algorithms-for-arraysvectors)
5. [Competitive Programming Shortcuts](#competitive-programming-shortcuts)

---

## Arrays (Static)

### Declaration & Initialization
```cpp
// Basic declaration
int arr[5];                    // Uninitialized (garbage values)
int arr[5] = {1, 2, 3, 4, 5}; // Full initialization
int arr[5] = {1, 2};           // Partial: rest become 0
int arr[] = {1, 2, 3, 4, 5};  // Size auto-deduced
int arr[5] = {0};              // All zeros
int arr[5] = {};               // All zeros (C++11+)

// Using fill
fill(arr, arr + 5, 10);        // Fill entire array with 10

// Character arrays (strings)
char str[] = "Hello";          // Includes null terminator
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

### Accessing Elements
```cpp
int arr[] = {10, 20, 30, 40, 50};

// Index-based access
arr[0] = 100;                  // Modify element
cout << arr[2];                // Access element (no bounds checking)

// Pointer arithmetic
int* ptr = arr;                // Points to first element
cout << *(ptr + 2);            // Same as arr[2]
cout << *(arr + 1);            // Same as arr[1]

// Using at() - bounds checked (only for std::array)
std::array<int, 5> stdArr = {1, 2, 3, 4, 5};
stdArr.at(10);                 // Throws out_of_range exception
```

### Array Size
```cpp
int arr[] = {1, 2, 3, 4, 5};

// Size calculation
int size = sizeof(arr) / sizeof(arr[0]);  // 5
int bytes = sizeof(arr);                  // 20 (5 * 4 bytes for int)

// Using std::size (C++17+)
int size2 = std::size(arr);    // 5

// For std::array
std::array<int, 5> stdArr;
stdArr.size();                  // 5
```

### Passing Arrays to Functions
```cpp
// Array decays to pointer
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

// Using pointer
void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++)
        cout << *(arr + i) << " ";
}

// Reference to array (preserves size)
template <size_t N>
void printArray(int (&arr)[N]) {
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
}
```

### Multi-dimensional Arrays
```cpp
// 2D Array declaration
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Accessing
matrix[0][1] = 20;              // Row 0, Column 1
cout << matrix[2][2];           // 9

// Partial initialization
int matrix[3][3] = {{1}, {2}, {3}};  // Rest become 0
int matrix[3][3] = {0};              // All zeros

// 3D Array
int cube[2][2][2] = {
    {{1, 2}, {3, 4}},
    {{5, 6}, {7, 8}}
};
```

### Array Limitations
```cpp
// Fixed size - cannot be changed at runtime
int size = 10;
int arr[size];                  // Error (unless using VLA extension)

// No built-in size tracking
// No automatic bounds checking
// Cannot be copied with assignment operator
// int arr2[] = arr;            // Error
```

---

## Vectors (Dynamic Arrays)

### Declaration & Initialization
```cpp
#include <vector>

// Empty vector
vector<int> v1;

// Vector with size
vector<int> v2(5);              // 5 elements, all 0
vector<int> v3(5, 10);          // 5 elements, all 10
vector<int> v4 = {1, 2, 3, 4, 5};  // Initializer list

// Copy vector
vector<int> v5(v4);             // Copy constructor
vector<int> v6 = v4;            // Assignment copy

// Vector of vectors
vector<vector<int>> v7;         // 2D vector
vector<vector<int>> v8(3, vector<int>(4, 0));  // 3x4 matrix of zeros

// Fill constructor
vector<int> v9(10);             // 10 zeros
iota(v9.begin(), v9.end(), 1);  // 1, 2, 3, ..., 10
```

### Common Vector Operations
```cpp
vector<int> v = {3, 1, 4, 1, 5};

// Size & Capacity
v.size();                       // Number of elements (5)
v.capacity();                   // Allocated capacity
v.empty();                      // Check if empty
v.max_size();                   // Maximum possible size

// Accessing elements
v[0];                           // No bounds checking
v.at(0);                        // Bounds checked
v.front();                      // First element
v.back();                       // Last element
v.data();                       // Pointer to underlying array

// Adding elements
v.push_back(9);                 // Add to end
v.emplace_back(10);             // Construct in-place (faster)
v.insert(v.begin(), 0);         // Insert at position
v.insert(v.begin(), 3, 7);      // Insert 3 sevens at beginning
v.insert(v.begin(), {1, 2, 3}); // Insert initializer list

// Removing elements
v.pop_back();                   // Remove last element
v.erase(v.begin());             // Remove first element
v.erase(v.begin(), v.begin()+2);// Remove range
v.clear();                      // Remove all elements

// Resizing
v.resize(10);                   // Resize to 10 (new elements = 0)
v.resize(10, 5);                // Resize with fill value
v.reserve(100);                 // Reserve capacity (no size change)
v.shrink_to_fit();              // Reduce capacity to size
```

### Vector Iterators
```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Iterator types
vector<int>::iterator it;           // Mutable iterator
vector<int>::const_iterator cit;    // Read-only iterator
vector<int>::reverse_iterator rit;  // Reverse iterator

// Getting iterators
v.begin();                      // Iterator to first element
v.end();                        // Iterator past last element
v.rbegin();                     // Reverse iterator to last element
v.rend();                       // Reverse iterator before first element
v.cbegin();                     // Const iterator (C++11)
v.cend();                       // Const iterator (C++11)

// Iterating
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << " ";

// Reverse iteration
for (auto rit = v.rbegin(); rit != v.rend(); ++rit)
    cout << *rit << " ";
```

### Vector Memory Management
```cpp
vector<int> v;

// Capacity growth (typically doubles)
for (int i = 0; i < 10; i++) {
    v.push_back(i);
    cout << "Size: " << v.size() 
         << " Capacity: " << v.capacity() << endl;
}

// Manual memory management
v.reserve(1000);                // Pre-allocate (avoid reallocation)
v.clear();                      // Clear but keep capacity
v.shrink_to_fit();              // Free unused capacity

// Swap trick (C++98/03)
vector<int>().swap(v);          // Clear and free memory
```

### Advanced Vector Operations
```cpp
vector<int> v1 = {1, 2, 3};
vector<int> v2 = {4, 5, 6};

// Swap contents
v1.swap(v2);                    // O(1) swap

// Assignment
v1 = v2;                        // Copy assignment
v1 = move(v2);                  // Move assignment

// Comparison
if (v1 == v2) {}                // Element-wise comparison
if (v1 < v2) {}                 // Lexicographical comparison

// Vector<bool> specialization
vector<bool> flags(10);
flags[0] = true;
flags.flip();                   // Flip all bits
```

---

## Matrices (2D Arrays & Vectors)

### Static 2D Arrays
```cpp
// Fixed size 2D array
int matrix[3][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Accessing elements
matrix[0][0] = 10;
cout << matrix[1][2];           // 6

// Traversing
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}

// Diagonal traversal
for (int i = 0; i < 3; i++)
    cout << matrix[i][i] << " ";       // Main diagonal
for (int i = 0; i < 3; i++)
    cout << matrix[i][2-i] << " ";     // Anti-diagonal
```

### Dynamic 2D Arrays (Using Pointers)
```cpp
// Method 1: Array of pointers
int rows = 3, cols = 3;
int** matrix = new int*[rows];
for (int i = 0; i < rows; i++)
    matrix[i] = new int[cols];

// Initialize
for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
        matrix[i][j] = i * cols + j;

// Cleanup
for (int i = 0; i < rows; i++)
    delete[] matrix[i];
delete[] matrix;

// Method 2: Single contiguous block
int* matrix = new int[rows * cols];
// Access: matrix[i * cols + j] instead of matrix[i][j]
matrix[1 * cols + 2] = 10;
delete[] matrix;
```

### Vector of Vectors (2D Vector)
```cpp
// Declaration
vector<vector<int>> matrix;

// Initialization with size
int rows = 3, cols = 4;
vector<vector<int>> matrix2(rows, vector<int>(cols, 0));

// Initialization with values
vector<vector<int>> matrix3 = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

// Accessing
matrix3[0][1] = 20;
cout << matrix3[2][2];

// Adding rows dynamically
matrix.push_back(vector<int>());          // Add empty row
matrix[0].push_back(1);                   // Add element to row
matrix.push_back({1, 2, 3});              // Add row with values

// Traversing
for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}

// Range-based for loop
for (const auto& row : matrix) {
    for (int val : row) {
        cout << val << " ";
    }
    cout << endl;
}
```

### Matrix Operations
```cpp
// Matrix multiplication
vector<vector<int>> multiply(const vector<vector<int>>& A,
                              const vector<vector<int>>& B) {
    int n = A.size(), m = A[0].size(), p = B[0].size();
    vector<vector<int>> C(n, vector<int>(p, 0));
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            for (int k = 0; k < m; k++)
                C[i][j] += A[i][k] * B[k][j];
    
    return C;
}

// Matrix transpose
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> result(cols, vector<int>(rows));
    
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[j][i] = matrix[i][j];
    
    return result;
}

// In-place transpose (square matrix)
void transposeInPlace(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);
}

// Rotate matrix 90 degrees clockwise
void rotate90(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);
    // Reverse each row
    for (int i = 0; i < n; i++)
        reverse(matrix[i].begin(), matrix[i].end());
}
```

### Matrix Traversal Patterns
```cpp
// Spiral traversal
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> result;
    if (matrix.empty()) return result;
    
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    
    while (top <= bottom && left <= right) {
        // Traverse right
        for (int j = left; j <= right; j++)
            result.push_back(matrix[top][j]);
        top++;
        
        // Traverse down
        for (int i = top; i <= bottom; i++)
            result.push_back(matrix[i][right]);
        right--;
        
        if (top <= bottom) {
            // Traverse left
            for (int j = right; j >= left; j--)
                result.push_back(matrix[bottom][j]);
            bottom--;
        }
        
        if (left <= right) {
            // Traverse up
            for (int i = bottom; i >= top; i--)
                result.push_back(matrix[i][left]);
            left++;
        }
    }
    return result;
}

// Diagonal traversal (anti-diagonal)
vector<vector<int>> diagonalTraversal(vector<vector<int>>& matrix) {
    vector<vector<int>> result;
    int rows = matrix.size(), cols = matrix[0].size();
    
    for (int sum = 0; sum < rows + cols - 1; sum++) {
        vector<int> diagonal;
        int startRow = max(0, sum - cols + 1);
        int endRow = min(rows - 1, sum);
        
        for (int i = startRow; i <= endRow; i++) {
            int j = sum - i;
            diagonal.push_back(matrix[i][j]);
        }
        result.push_back(diagonal);
    }
    return result;
}
```

---

## STL Algorithms for Arrays/Vectors

### Sorting
```cpp
#include <algorithm>

int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
int n = sizeof(arr) / sizeof(arr[0]);

// Sort ascending
sort(arr, arr + n);

// Sort descending
sort(arr, arr + n, greater<int>());

// Custom comparator
sort(arr, arr + n, [](int a, int b) { return a > b; });

// Vector sorting
vector<int> v = {3, 1, 4, 1, 5};
sort(v.begin(), v.end());
sort(v.rbegin(), v.rend());     // Reverse sort

// Partial sort
partial_sort(v.begin(), v.begin() + 3, v.end());  // Sort first 3 elements

// Stable sort
stable_sort(v.begin(), v.end());

// Check if sorted
if (is_sorted(v.begin(), v.end())) {}
```

### Searching
```cpp
int arr[] = {1, 3, 5, 7, 9, 11};
int n = 6;

// Binary search (requires sorted array)
if (binary_search(arr, arr + n, 5)) {}
if (binary_search(arr, arr + n, 4)) {}  // Returns false

// Lower bound - first element >= value
auto it = lower_bound(arr, arr + n, 5);    // Points to 5
int idx = it - arr;                         // Index = 2

// Upper bound - first element > value
it = upper_bound(arr, arr + n, 5);          // Points to 7

// Equal range
auto range = equal_range(arr, arr + n, 5);

// Find
it = find(arr, arr + n, 5);
it = find_if(arr, arr + n, [](int x) { return x > 4; });

// Count
int count = count(arr, arr + n, 5);
int count_if = count_if(arr, arr + n, [](int x) { return x % 2 == 0; });
```

### Modifying Algorithms
```cpp
vector<int> v = {1, 2, 3, 4, 5};

// Reverse
reverse(v.begin(), v.end());            // {5, 4, 3, 2, 1}

// Rotate
rotate(v.begin(), v.begin() + 2, v.end());  // Rotate left by 2

// Shuffle
random_shuffle(v.begin(), v.end());     // Deprecated in C++14
shuffle(v.begin(), v.end(), mt19937(random_device()()));

// Fill
fill(v.begin(), v.end(), 10);           // {10, 10, 10, 10, 10}
fill_n(v.begin(), 3, 7);                // Fill first 3 with 7

// Generate
generate(v.begin(), v.end(), rand);     // Fill with random values

// Unique (requires sorted)
sort(v.begin(), v.end());
auto last = unique(v.begin(), v.end());
v.erase(last, v.end());                 // Remove duplicates

// Transform
transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
transform(v.begin(), v.end(), v.begin(), v.begin(), plus<int>());

// Replace
replace(v.begin(), v.end(), 2, 20);     // Replace 2 with 20
replace_if(v.begin(), v.end(), [](int x) { return x < 0; }, 0);

// Remove
remove(v.begin(), v.end(), 2);          // Move 2's to end
v.erase(remove(v.begin(), v.end(), 2), v.end());  // Erase-remove idiom

// Swap
iter_swap(v.begin(), v.end() - 1);      // Swap first and last
```

### Numeric Algorithms
```cpp
#include <numeric>

vector<int> v = {1, 2, 3, 4, 5};

// Sum
int sum = accumulate(v.begin(), v.end(), 0);
int sum_offset = accumulate(v.begin(), v.end(), 10);  // Sum + 10

// Product
int product = accumulate(v.begin(), v.end(), 1, multiplies<int>());

// Inner product (dot product)
vector<int> v2 = {1, 2, 3, 4, 5};
int dot = inner_product(v.begin(), v.end(), v2.begin(), 0);

// Partial sums
vector<int> prefix(v.size());
partial_sum(v.begin(), v.end(), prefix.begin());  // Prefix sums

// Adjacent difference
vector<int> diff(v.size());
adjacent_difference(v.begin(), v.end(), diff.begin());

// Iota (fill with sequential values)
int arr[5];
iota(arr, arr + 5, 1);                  // {1, 2, 3, 4, 5}

// GCD (C++17)
int gcd_val = gcd(12, 18);              // 6
int lcm_val = lcm(12, 18);              // 36
```

### Min/Max Operations
```cpp
vector<int> v = {3, 1, 4, 1, 5};

// Maximum
auto max_it = max_element(v.begin(), v.end());
int max_val = *max_it;
int max_idx = max_it - v.begin();

// Minimum
auto min_it = min_element(v.begin(), v.end());
int min_val = *min_it;
int min_idx = min_it - v.begin();

// Both min and max
auto [min_it2, max_it2] = minmax_element(v.begin(), v.end());

// Simple min/max
int a = 5, b = 10;
int mini = min(a, b);
int maxi = max(a, b);
int mini3 = min({1, 2, 3});             // Initializer list
```

---

## Competitive Programming Shortcuts

### Macros & Typedefs
```cpp
// Essential macros
#define ll long long
#define ull unsigned long long
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < b; i++)
#define per(i, a, b) for(int i = b - 1; i >= a; i--)
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL);

// Common constants
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
const double PI = acos(-1.0);
```

### Fast I/O Setup
```cpp
// Speed up I/O operations
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

// Custom fast input function
template<typename T>
void read(T &x) {
    x = 0;
    char c = getchar();
    T sign = 1;
    while(c < '0' || c > '9') {
        if(c == '-') sign = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        x = x*10 + c - '0';
        c = getchar();
    }
    x *= sign;
}
```

### Common Array Operations
```cpp
// Initialize array with value
int arr[100];
memset(arr, 0, sizeof(arr));        // Fill with 0
memset(arr, -1, sizeof(arr));       // Fill with -1
// Note: memset works for 0 and -1 only for int

// Dynamic size array
int n;
cin >> n;
vector<int> arr(n);
for(int i = 0; i < n; i++) cin >> arr[i];

// 1-based indexing
vector<int> arr(n + 1);
for(int i = 1; i <= n; i++) cin >> arr[i];

// Sort with index tracking
vector<int> idx(n);
iota(all(idx), 0);
sort(all(idx), [&](int i, int j) { return arr[i] < arr[j]; });
```

### 2D Matrix Shortcuts
```cpp
// Fast matrix input
int n, m;
cin >> n >> m;
vvi matrix(n, vi(m));
for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
        cin >> matrix[i][j];

// Matrix as single vector (better cache performance)
vector<int> matrix(n * m);
// Access: matrix[i * m + j]

// Direction arrays
int dx[] = {0, 0, 1, -1};          // 4-directional
int dy[] = {1, -1, 0, 0};

int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};  // 8-directional
int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Knight moves
int kx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int ky[] = {-1, 1, -2, 2, -2, 2, -1, 1};
```

### Useful One-Liners
```cpp
// Sum of array
int sum = accumulate(all(v), 0);
ll sum = accumulate(all(v), 0LL);  // Long long sum

// Max element with index
int mx = *max_element(all(v));
int mx_idx = max_element(all(v)) - v.begin();

// Min element with index  
int mn = *min_element(all(v));
int mn_idx = min_element(all(v)) - v.begin();

// Count occurrences
int cnt = count(all(v), x);

// Check if element exists
bool found = binary_search(all(v), x);

// Unique elements
sort(all(v));
v.erase(unique(all(v)), v.end());

// Reverse
reverse(all(v));

// Rotate left by k
rotate(v.begin(), v.begin() + k, v.end());

// Partial sort (k smallest)
partial_sort(v.begin(), v.begin() + k, v.end());

// Nth element
nth_element(v.begin(), v.begin() + k, v.end());  // k-th smallest

// Prefix sum
vector<int> pref(n + 1);
partial_sum(all(v), pref.begin() + 1);

// Check palindrome
bool isPal = equal(v.begin(), v.begin() + n/2, v.rbegin());
```

### Debug Macros
```cpp
// Debug printing
#define debug(x) cerr << #x << " = " << x << endl;
#define debug2(x, y) cerr << #x << " = " << x << ", " << #y << " = " << y << endl;

// Debug vector
template<typename T>
void debugVector(const vector<T>& v) {
    cerr << "[";
    for(int i = 0; i < v.size(); i++) {
        if(i) cerr << ", ";
        cerr << v[i];
    }
    cerr << "]" << endl;
}

// Debug matrix
template<typename T>
void debugMatrix(const vector<vector<T>>& mat) {
    cerr << "Matrix " << mat.size() << "x" << (mat.empty() ? 0 : mat[0].size()) << ":\n";
    for(const auto& row : mat) {
        for(const auto& val : row)
            cerr << val << " ";
        cerr << endl;
    }
}
```

### Common Algorithms Implemented
```cpp
// Binary search (custom)
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Kadane's algorithm (maximum subarray sum)
int kadane(vector<int>& arr) {
    int max_so_far = arr[0], max_ending_here = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        max_ending_here = max(arr[i], max_ending_here + arr[i]);
        max_so_far = max(max_so_far, max_ending_here);
    }
    return max_so_far;
}

// Two pointers technique
int twoPointer(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return 1;
        else if (sum < target) left++;
        else right--;
    }
    return 0;
}

// Sliding window
int slidingWindow(vector<int>& arr, int k) {
    int window_sum = 0, max_sum = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        window_sum += arr[i];
        if (i >= k - 1) {
            max_sum = max(max_sum, window_sum);
            window_sum -= arr[i - k + 1];
        }
    }
    return max_sum;
}
```

### Memory Optimization Tips
```cpp
// Use vector<int> instead of vector<bool> for speed
// Reserve space to avoid reallocation
vector<int> v;
v.reserve(1000000);

// Use emplace_back instead of push_back
vector<pair<int, int>> vp;
vp.emplace_back(1, 2);  // vs vp.push_back({1, 2});

// Use array instead of vector for small fixed sizes
array<int, 100> arr;  // Stack allocated

// Use static arrays for very large data
static int dp[100001][101];  // Avoid stack overflow

// Use int instead of long long when possible
// Use unordered_map for O(1) average lookup
unordered_map<int, int> mp;
mp.reserve(1000000);  // Pre-reserve for better performance
```

### Time Complexity Cheat Sheet
```
Operation           Array   Vector   Unordered Map   Set/Map
-------------      -------  -------  --------------  --------
Access (front)      O(1)     O(1)     O(1) avg        O(log n)
Access (middle)     O(1)     O(1)     -               -
Insert (front)      O(n)     O(n)     O(1) avg        O(log n)
Insert (back)       -        O(1)*    O(1) avg        O(log n)
Delete (front)      O(n)     O(n)     O(1) avg        O(log n)
Delete (back)       -        O(1)     O(1) avg        O(log n)
Search              O(n)     O(n)     O(1) avg        O(log n)
Sort                O(n log n) O(n log n) -           -
* Amortized
```

This comprehensive guide covers all essential aspects of arrays, vectors, and matrices in C++ with a focus on competitive programming applications.