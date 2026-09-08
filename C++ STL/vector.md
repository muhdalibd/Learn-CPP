# 🚀 Deep Dive into Vectors in C++

A `std::vector` in C++ is a sequence container representing an array that can change in size. Unlike static arrays in C (e.g., `int arr[5]`) where the memory allocation is strictly defined at compile-time, vectors are **dynamic arrays**. They abstract away low-level memory management, allowing you to grow or shrink the list at runtime without manually handling `malloc` or `realloc`.

---

## 🧠 Memory Under the Hood: Size vs. Capacity

Understanding how a vector manages memory is critical for writing efficient C++ code. A vector maintains its elements in a contiguous block of memory on the heap.

When you push a new element to a vector that is already full, it cannot simply "append" it if there is no adjacent free memory. Instead, it performs a **reallocation**:

1. Allocates a brand new, larger block of memory (usually double the current capacity).
2. Copies (or moves) all existing elements to the new block.
3. Destroys the old elements and frees the old memory.
4. Adds the new element.

| Concept | Definition | Function |
| --- | --- | --- |
| **Size** | The actual number of elements currently stored in the vector. | `.size()` |
| **Capacity** | The total number of elements the vector can hold before it must allocate more memory. | `.capacity()` |

> **Pro Tip:** If you know roughly how many elements you will need ahead of time, use `.reserve(n)`. This allocates the memory upfront, preventing costly runtime reallocations!

---

## 🛠️ Creating and Initializing Vectors

C++ provides high flexibility for instantiating vectors, from empty declarations to deep copies of other containers.

```cpp
#include <vector>
using namespace std;

// 1. Empty and Pre-filled Vectors
vector<int> v;                // Empty vector
vector<int> v1(5, 10);        // 5 elements, all initialized to 10: {10, 10, 10, 10, 10}
vector<int> v2(3);            // 3 elements, default-initialized to 0: {0, 0, 0}

// 2. Initializer Lists (Modern C++)
vector<int> v3 = {1, 2, 3, 4, 5};
vector<int> v4{1, 2, 3, 4, 5};

// 3. From Existing Arrays or Containers
int arr[] = {1, 2, 3, 4, 5};
vector<int> v5(arr, arr + 5); 

// 4. Copying and Moving
vector<int> y = {1, 2, 3};
vector<int> v7(y);            // Deep copy of y
vector<int> v9(move(y));      // Transfers ownership (y is now empty, O(1) operation)

```

---

## ⚙️ Core Member Functions

### Accessing Elements

* **`front()` / `back()`:** Returns a reference to the first / last element.
* **`operator[n]`:** Fast access to the element at index `n` *(No bounds checking—risky if you go out of bounds)*.
* **`at(n)`:** Accesses element at index `n` *(Includes bounds checking, throws `out_of_range` exception if invalid)*.

### Iterators

* **`begin()`:** Returns an iterator pointing to the first element.
* **`end()`:** Returns an iterator pointing to the theoretical element *just after* the last element.

### Modifying the Vector

```cpp
vector<int> vec = {1, 2, 3};

// Addition
vec.push_back(4);             // Appends 4 to the end
vec.emplace_back(5);          // Constructs 5 directly in place at the end (faster for complex objects)

// Insertion (Costly if not at the end!)
vec.insert(vec.begin() + 1, 99);   // Inserts 99 at index 1: {1, 99, 2, 3, 4, 5}

// Removal
vec.pop_back();               // Removes the last element
vec.erase(vec.begin());       // Removes the first element
vec.clear();                  // Destroys all elements, size becomes 0

```

---

## ⏱️ Big-O Time Complexity

Just like dynamic arrays in other languages, the position where you insert or remove elements drastically impacts performance. Because elements are stored in contiguous memory, inserting at the beginning forces all subsequent elements to shift right.

| Operation | Time Complexity | Explanation |
| --- | --- | --- |
| **Access / Read** | `O(1)` Constant | Direct access via index mathematically calculates the memory address instantly. |
| **Insert / Delete at End** | `O(1)` Amortized | Usually instant. Occasionally `O(n)` if the capacity is reached and a reallocation is triggered. |
| **Insert / Delete at Beginning** | `O(n)` Linear | Requires shifting every single element in the vector to the right (or left) to make room. |
| **Search (Unsorted)** | `O(n)` Linear | Must check each element one by one. |