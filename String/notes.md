# Deep Dive into Strings in C++

## Table of Contents
1. [Introduction](#introduction)
2. [String Class Basics](#string-class-basics)
3. [Constructor and Initialization](#constructor-and-initialization)
4. [String Operations](#string-operations)
5. [Accessing Characters](#accessing-characters)
6. [String Modifiers](#string-modifiers)
7. [String Capacity Functions](#string-capacity-functions)
8. [String Comparison](#string-comparison)
9. [Searching and Finding](#searching-and-finding)
10. [Substrings](#substrings)
11. [String Conversion Functions](#string-conversion-functions)
12. [String Stream](#string-stream)
13. [C-Style Strings vs C++ Strings](#c-style-strings-vs-c-strings)
14. [String Iterators](#string-iterators)
15. [Competitive Programming Shortcuts](#competitive-programming-shortcuts)

---

## Introduction

In C++, strings are objects that represent sequences of characters. The `std::string` class is part of the Standard Template Library (STL) and provides a rich set of functions for string manipulation.

```cpp
#include <string>
using namespace std;
```

---

## String Class Basics

### What is std::string?
- A class template specialization of `std::basic_string`
- Stores characters as a contiguous sequence
- Automatically manages memory
- Null-terminated for compatibility with C-style strings

```cpp
string s1;                   // Empty string
string s2 = "Hello";         // Initialize with C-string
string s3("World");          // Constructor syntax
string s4(s2);               // Copy constructor
string s5(5, 'A');           // "AAAAA"
```

---

## Constructor and Initialization

```cpp
// Different ways to initialize strings
string str1;                           // Empty string
string str2 = "Hello";                 // Direct assignment
string str3("Hello World", 5);         // First 5 chars: "Hello"
string str4(str2, 2, 3);               // Substring from index 2, length 3: "llo"
string str5(10, '*');                  // Repeat character: "**********"
string str6 = {'H', 'e', 'l', 'l', 'o'}; // Initializer list
string str7(str6.begin(), str6.end());    // Iterator range
```

---

## String Operations

### Basic Operations

```cpp
string s1 = "Hello";
string s2 = " World";
string s3;

// Concatenation
s3 = s1 + s2;                    // "Hello World"
s1 += s2;                        // s1 becomes "Hello World"
s1.append("!");                  // Append at end

// Assignment
s3.assign("New string");
s3.assign("Hello World", 5);     // "Hello"
s3.assign(3, 'X');               // "XXX"
```

### String Length

```cpp
string str = "Hello";
int len1 = str.length();    // 5
int len2 = str.size();      // 5 (same as length)
```

---

## Accessing Characters

```cpp
string str = "Hello";

// Methods to access characters
char c1 = str[0];            // 'H' (no bounds checking)
char c2 = str.at(0);         // 'H' (with bounds checking)

// Front and back
char first = str.front();    // 'H'
char last = str.back();      // 'o'

// Modify characters
str[0] = 'J';                // "Jello"
str.at(1) = 'a';             // "Jallo"
```

---

## String Modifiers

### Insert Function

```cpp
string str = "Hello World";

// Insert at position
str.insert(5, " Beautiful");     // "Hello Beautiful World"
str.insert(0, "Say: ");          // Insert at beginning
str.insert(str.length(), "!");   // Insert at end
str.insert(5, 3, '*');           // Insert characters
str.insert(5, "##", 0, 2);       // Insert substring
```

### Erase Function

```cpp
string str = "Hello Beautiful World";

// Erase characters
str.erase(5, 10);                // Remove " Beautiful": "Hello World"
str.erase(str.begin());          // Remove first character
str.erase(str.begin() + 2, str.end() - 2); // Remove range
str.clear();                     // Remove all characters
```

### Replace Function

```cpp
string str = "Hello World";

// Replace characters
str.replace(6, 5, "C++");        // "Hello C++"
str.replace(0, 5, "Hi");         // "Hi C++"
str.replace(3, 2, 2, '*');       // Replace with characters
str.replace(str.begin(), str.end(), "New"); // Replace entire string
```

### Push and Pop

```cpp
string str = "Hello";

// Add/remove characters at end
str.push_back('!');              // "Hello!"
str.pop_back();                  // "Hello"
```

### Swap Function

```cpp
string s1 = "Hello";
string s2 = "World";

s1.swap(s2);                     // s1 = "World", s2 = "Hello"
swap(s1, s2);                    // Swap back
```

---

## String Capacity Functions

```cpp
string str = "Hello";

// Size and length
int size = str.size();           // 5
int length = str.length();       // 5

// Capacity
int capacity = str.capacity();   // Current allocated capacity

// Maximum size
int max_size = str.max_size();   // Maximum possible size

// Empty check
bool isEmpty = str.empty();      // false

// Resize
str.resize(10);                  // Extend to 10 characters
str.resize(3);                   // Reduce to "Hel"

// Reserve
str.reserve(100);                // Reserve space for 100 characters

// Shrink to fit
str.shrink_to_fit();             // Reduce capacity to size
```

---

## String Comparison

### Compare Function

```cpp
string s1 = "apple";
string s2 = "banana";

// Using compare
int result = s1.compare(s2);     // Negative (s1 < s2)
result = s2.compare(s1);         // Positive (s2 > s1)
result = s1.compare("apple");    // 0 (equal)

// Partial comparison
string str = "Hello World";
result = str.compare(0, 5, "Hello");  // Compare first 5 chars: 0
result = str.compare(6, 5, "World");  // Compare "World": 0

// Using operators
bool isEqual = (s1 == s2);
bool isLess = (s1 < s2);
bool isGreater = (s1 > s2);
bool isNotEqual = (s1 != s2);
bool isLessOrEqual = (s1 <= s2);
bool isGreaterOrEqual = (s1 >= s2);
```

---

## Searching and Finding

### Find Function

```cpp
string str = "Hello World, Hello C++";

// Find first occurrence
size_t pos = str.find("Hello");      // 0
pos = str.find("Hello", 5);          // 13 (search from index 5)
pos = str.find('W');                 // 6 (find character)
pos = str.find('X');                 // string::npos (not found)

// Find last occurrence
pos = str.rfind("Hello");            // 13 (search from end)
pos = str.rfind('l');                // 21 (last 'l')

// Find first of
string vowels = "aeiou";
pos = str.find_first_of(vowels);     // 1 ('e')

// Find last of
pos = str.find_last_of(vowels);      // 19 ('e' in "C++")

// Find first not of
pos = str.find_first_not_of("Hello"); // 5 (' ')

// Find last not of
pos = str.find_last_not_of("World");  // 12 (',')

// Check if not found
if (pos == string::npos) {
    cout << "Not found";
}
```

---

## Substrings

### Substr Function

```cpp
string str = "Hello World";

// Extract substring
string sub1 = str.substr(6);          // "World"
string sub2 = str.substr(0, 5);       // "Hello"
string sub3 = str.substr(6, 2);       // "Wo"

// Extract all possible substrings
for (int i = 0; i < str.length(); i++) {
    for (int j = 1; j <= str.length() - i; j++) {
        cout << str.substr(i, j) << endl;
    }
}
```

---

## String Conversion Functions

### Converting Numbers to Strings

```cpp
// Using to_string
string num1 = to_string(123);        // "123"
string num2 = to_string(3.14);       // "3.140000"
string num3 = to_string(3.14f);      // "3.140000"

// Using stringstream (older method)
#include <sstream>
stringstream ss;
ss << 123;
string str = ss.str();               // "123"
```

### Converting Strings to Numbers

```cpp
string str = "123";
string fstr = "3.14";

// String to integer
int num = stoi(str);                 // 123
int num2 = stoi("0x1A", nullptr, 16); // 26 (hexadecimal)

// String to long
long lnum = stol(str);               // 123

// String to long long
long long llnum = stoll(str);        // 123

// String to float
float fnum = stof(fstr);             // 3.14

// String to double
double dnum = stod(fstr);            // 3.14

// String to long double
long double ldnum = stold(fstr);     // 3.14
```

### Character Conversions

```cpp
#include <cctype>

char c = 'a';

// Convert to uppercase
char upper = toupper(c);             // 'A'
char upper2 = toupper('A');          // 'A'

// Convert to lowercase
char lower = tolower('A');           // 'a'

// Check character type
bool isAlpha = isalpha(c);           // true (letter)
bool isDigit = isdigit('5');         // true
bool isSpace = isspace(' ');         // true
bool isUpper = isupper('A');         // true
bool isLower = islower('a');         // true
bool isAlnum = isalnum('a');         // true (alphanumeric)
```

---

## String Stream

### Basic String Stream Operations

```cpp
#include <sstream>

// Output string stream
ostringstream oss;
oss << "Hello " << "World" << " " << 2024;
string result = oss.str();           // "Hello World 2024"

// Input string stream
string data = "Hello 123 3.14";
istringstream iss(data);
string word;
int num;
double dnum;
iss >> word >> num >> dnum;          // word="Hello", num=123, dnum=3.14

// String stream for parsing
string csv = "apple,banana,orange";
stringstream ss(csv);
string item;
while (getline(ss, item, ',')) {
    cout << item << endl;            // apple, banana, orange
}
```

### Common String Stream Use Cases

```cpp
// Convert any type to string
template<typename T>
string to_string_stream(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

// Convert string to any type
template<typename T>
T from_string(const string& str) {
    T value;
    istringstream iss(str);
    iss >> value;
    return value;
}

// Concatenate mixed types
stringstream ss;
ss << "Result: " << 42 << ", " << 3.14 << ", " << "text";
string combined = ss.str();
```

---

## C-Style Strings vs C++ Strings

### Converting Between Types

```cpp
// C++ string to C-style string
string cpp_str = "Hello";
const char* c_str = cpp_str.c_str();    // Null-terminated
const char* data = cpp_str.data();      // Not necessarily null-terminated

// C-style string to C++ string
const char* c_style = "World";
string str1 = c_style;                  // Implicit conversion
string str2(c_style);                   // Explicit conversion

// Character array to string
char arr[] = {'H', 'e', 'l', 'l', 'o', '\0'};
string str3(arr);                        // "Hello"
string str4(arr, 3);                     // First 3 chars: "Hel"
```

---

## String Iterators

### Iterator Types and Usage

```cpp
string str = "Hello World";

// Forward iteration
for (string::iterator it = str.begin(); it != str.end(); ++it) {
    cout << *it;
}

// Reverse iteration
for (string::reverse_iterator rit = str.rbegin(); rit != str.rend(); ++rit) {
    cout << *rit;
}

// Constant iterators (read-only)
for (string::const_iterator cit = str.cbegin(); cit != str.cend(); ++cit) {
    cout << *cit;
}

// Range-based for loop
for (char c : str) {
    cout << c;
}

// Auto with iterators
for (auto it = str.begin(); it != str.end(); ++it) {
    cout << *it;
}
```

### Iterator Functions

```cpp
string str = "Hello";

// Get iterators
string::iterator begin = str.begin();
string::iterator end = str.end();
string::reverse_iterator rbegin = str.rbegin();
string::reverse_iterator rend = str.rend();

// Using iterators with algorithms
#include <algorithm>
sort(str.begin(), str.end());           // Sort characters
reverse(str.begin(), str.end());        // Reverse string

// Find using iterators
auto it = find(str.begin(), str.end(), 'e');
if (it != str.end()) {
    cout << "Found at position: " << (it - str.begin());
}
```

---

## Competitive Programming Shortcuts

### Essential String Tricks

```cpp
// 1. Fast input/output
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);

// 2. String to lowercase/uppercase
string s = "Hello World";
transform(s.begin(), s.end(), s.begin(), ::tolower);  // "hello world"
transform(s.begin(), s.end(), s.begin(), ::toupper);  // "HELLO WORLD"

// 3. Check if string is palindrome
bool isPalindrome(const string& s) {
    string rev = s;
    reverse(rev.begin(), rev.end());
    return s == rev;
}

// Better palindrome check
bool isPalindrome(const string& s) {
    int n = s.length();
    for (int i = 0; i < n/2; i++) {
        if (s[i] != s[n-1-i]) return false;
    }
    return true;
}

// 4. Count occurrences of character
int count = count(s.begin(), s.end(), 'a');

// 5. Remove all occurrences of character
s.erase(remove(s.begin(), s.end(), 'a'), s.end());

// 6. Check if string contains only digits
bool isNumber = all_of(s.begin(), s.end(), ::isdigit);

// 7. Split string by delimiter
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 8. Join vector of strings
string join(const vector<string>& v, const string& delimiter) {
    string result;
    for (int i = 0; i < v.size(); i++) {
        result += v[i];
        if (i < v.size() - 1) result += delimiter;
    }
    return result;
}

// 9. Find all occurrences of substring
vector<int> findAllOccurrences(const string& s, const string& pattern) {
    vector<int> positions;
    size_t pos = s.find(pattern);
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = s.find(pattern, pos + 1);
    }
    return positions;
}
```

### Common Competitive Programming Patterns

```cpp
// 1. Check if string is substring
bool isSubstring(const string& sub, const string& str) {
    return str.find(sub) != string::npos;
}

// 2. Check if two strings are anagrams
bool areAnagrams(string s1, string s2) {
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
}

// 3. Remove duplicates from string
string removeDuplicates(string s) {
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    return s;
}

// 4. Count frequency of each character
map<char, int> getFrequency(const string& s) {
    map<char, int> freq;
    for (char c : s) {
        freq[c]++;
    }
    return freq;
}

// 5. Check if string is rotation of another
bool isRotation(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    string temp = s1 + s1;
    return temp.find(s2) != string::npos;
}

// 6. Longest common prefix
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

// 7. Generate all substrings
vector<string> getAllSubstrings(const string& s) {
    vector<string> substrings;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 1; j <= s.length() - i; j++) {
            substrings.push_back(s.substr(i, j));
        }
    }
    return substrings;
}

// 8. String compression (basic)
string compressString(const string& s) {
    string result;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i + 1 < n && s[i] == s[i+1]) {
            count++;
            i++;
        }
        result += s[i];
        if (count > 1) result += to_string(count);
    }
    return result;
}
```

### Memory Optimization Tips

```cpp
// Use references to avoid copying
void processString(const string& s) {
    // Process without copying
}

// Use string_view (C++17) for read-only
#include <string_view>
void processString(string_view sv) {
    // Lightweight string reference
}

// Reserve space to avoid reallocations
string result;
result.reserve(1000);  // Reserve expected size

// Use char array for fixed-size strings
char buffer[100];
snprintf(buffer, sizeof(buffer), "Value: %d", 42);
```

---

## Summary

The C++ `string` class is a powerful tool that provides:
- Dynamic memory management
- Rich set of manipulation functions
- Efficient operations for competitive programming
- Seamless integration with C-style strings
- STL algorithm compatibility

Mastering string operations is crucial for competitive programming and general C++ development, as strings are fundamental data structures used in numerous algorithms and problem-solving scenarios.