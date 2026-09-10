# Hashing in C++ — A Complete Deep Dive

> A beginner-friendly but thorough set of notes covering hashing theory, hash functions, collision handling, load factor & rehashing, complexity analysis, C++ STL hashing, and real-world applications — with original C++ implementations for every technique.

---

## Table of Contents

1. [What Is Hashing?](#1-what-is-hashing)
2. [Why Do We Need Hashing?](#2-why-do-we-need-hashing)
3. [Key Terminology](#3-key-terminology)
4. [How Hashing Works — A Worked Example](#4-how-hashing-works--a-worked-example)
5. [Hash Functions](#5-hash-functions)
6. [Collisions and Collision Resolution](#6-collisions-and-collision-resolution)
7. [Technique 1: Separate Chaining](#7-technique-1-separate-chaining)
8. [Technique 2: Open Addressing](#8-technique-2-open-addressing)
9. [Load Factor and Rehashing](#9-load-factor-and-rehashing)
10. [Complexity Cheat Sheet](#10-complexity-cheat-sheet)
11. [Hashing in the C++ STL](#11-hashing-in-the-c-stl)
12. [Applications of Hashing](#12-applications-of-hashing)
13. [When NOT to Use Hashing](#13-when-not-to-use-hashing)
14. [Quick Revision Summary](#14-quick-revision-summary)

---

## 1. What Is Hashing?

**Hashing** is a technique that takes data (of any size — a number, a string, an object) and maps it to a fixed-size value, called a **hash value** or **hash code**, using a mathematical formula called a **hash function**. This hash value is then used as an **index** into an array-like structure called a **hash table**, so that data can be stored and found almost instantly.

In simple words:

> Hashing converts a "key" into an array index so we can jump straight to where the data lives, instead of searching for it.

A simple example: the hash function `H(x) = x % 10` converts *any* number into a value between 0 and 9. So no matter how large `x` is, we always land inside a table of size 10.

The beauty of hashing is that **search, insert, and delete can all be done in O(1) time on average** — much better than the O(n) search time of an unsorted array/linked list, or the O(log n) of a balanced BST.

Hashing is mainly used to implement:
- **Sets** — a collection of distinct keys (no duplicates).
- **Maps / Dictionaries** — a collection of key–value pairs, where each key is unique.

---

## 2. Why Do We Need Hashing?

Consider how other data structures perform search/insert/delete:

| Data Structure          | Search   | Insert   | Delete   |
|--------------------------|----------|----------|----------|
| Unsorted Array/List      | O(n)     | O(1)     | O(n)     |
| Sorted Array              | O(log n) | O(n)     | O(n)     |
| Balanced BST (AVL/Red-Black) | O(log n) | O(log n) | O(log n) |
| **Hash Table**            | **O(1) avg** | **O(1) avg** | **O(1) avg** |

Hashing wins when we only care about **exact key lookups** — "does this key exist?", "give me the value for this key?" — and don't need the data to stay sorted.

### When hashing is *not* the right tool

- You need **sorted order** along with search/insert/delete → use a **self-balancing BST**.
- Keys are strings and you need **prefix search** (autocomplete-like features) → use a **Trie**.
- You need **floor/ceiling** type queries (nearest smaller/larger key) → use a **self-balancing BST**.

---

## 3. Key Terminology

Understanding hashing means understanding these five building blocks:

| Term | Meaning |
|------|---------|
| **Key** | The input we want to store or look up (an integer, a string, an object, etc.) |
| **Hash Function** | A formula that converts a key into an index (the "hash value") |
| **Hash Value / Hash Index** | The output of the hash function — a number that tells us *where* in the table to look |
| **Hash Table** | The underlying array where data is actually stored |
| **Bucket / Slot** | One "cell" of the hash table, addressed by a hash index |
| **Collision** | When two *different* keys produce the *same* hash index |
| **Load Factor (α)** | `α = (number of stored elements) / (table size)` — a measure of how "full" the table is |
| **Rehashing** | Growing the table and re-inserting everything when the load factor gets too high |

Visually:

```
Key ──► Hash Function ──► Hash Index ──► Hash Table[Index] ──► stored value
"cat"        H(x)              3          table[3] = "cat"
```

---

## 4. How Hashing Works — A Worked Example

Let's manually hash the strings `{"ab", "cd", "efg"}` into a table of size 7.

**Step 1 — Assign numeric values to letters:** a = 1, b = 2, c = 3 … z = 26.

**Step 2 — Sum up the letters in each string:**
- "ab" → 1 + 2 = 3
- "cd" → 3 + 4 = 7
- "efg" → 5 + 6 + 7 = 18

**Step 3 — Apply the hash function `H(key) = sum(key) % tableSize`** (table size = 7):
- "ab" → 3 % 7 = **3**
- "cd" → 7 % 7 = **0**
- "efg" → 18 % 7 = **4**

**Step 4 — Place each string at its computed index:**

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|-------|---|---|---|---|---|---|---|
| Value | "cd" | | | "ab" | "efg" | | |

Now, to look up `"cd"`, we don't scan the whole table — we recompute `H("cd") = 0` and go **directly** to index 0. That's the entire magic of hashing: turning a search problem into an arithmetic problem.

---

## 5. Hash Functions

A **hash function** takes an input key of arbitrary size and converts it to a fixed-size output. Formally: `h: Key → [0, m-1]`, where `m` is the table size.

### 5.1 Properties of a Good Hash Function

| Property | What it means |
|----------|----------------|
| **Deterministic** | Same input always produces the same output |
| **Fixed output size** | Output always fits the table (e.g., always between 0 and m−1) |
| **Efficient** | Should be fast to compute — ideally O(1) or close to it |
| **Uniformity** | Keys should be spread evenly across all slots, minimizing clustering |
| **Pre-image resistance** | Hard to reconstruct the original key from just the hash value |
| **Collision resistance** | Hard to find two different keys with the same hash value |
| **Avalanche effect** | A tiny change in input should drastically change the output |

The last three matter mostly for **cryptographic** hash functions (security); for a normal DSA hash table, **uniformity and speed** matter most.

### 5.2 Examples That Illustrate Good vs. Bad Design

**Phone numbers as keys:** `h(k) = k % 100` (table size 100).
- Using the **last two digits** is a good choice — they vary a lot between numbers.
- Using the **first two digits** is a bad choice — many numbers share the same area code, so most keys would collide in a few buckets.

**Lowercase strings as keys:** assign a=1, b=2 … z=26, and sum the letters.
- `"ad"` → 1+4 = 5
- `"bc"` → 2+3 = 5

Both strings collide even though they're completely different words — a plain sum ignores **position**. A better design uses **weighted positions**, e.g. `h(s) = (Σ value(s[i]) × weight[i]) mod 100`, so that character order affects the result and collisions become rarer.

### 5.3 Types of Hash Functions

**1. Division Method**
```
h(k) = k mod m        (m is usually chosen to be a prime number)
```
Simple and fast, but distribution quality strongly depends on picking a good `m` (prime numbers, avoiding powers of 2, help spread keys evenly).

**2. Multiplication Method**
```
h(k) = floor( m * ( (k * A) mod 1 ) )      where 0 < A < 1
```
Multiply the key by a constant `A`, keep only the **fractional part**, then scale by `m`. Less sensitive to the exact value of `m` than the division method.

**3. Mid-Square Method**
- Square the key.
- Extract the **middle digits** of the squared value as the hash.

Squaring tends to spread out digits, which improves distribution, at the cost of extra computation.

**4. Folding Method**
- Split the key into equal-sized chunks.
- Add the chunks together (optionally reversing alternate chunks first).
- Apply modulo to fit the table size.

Works well for very large keys (e.g., long numeric IDs).

**5. Cryptographic Hash Functions** (SHA-256, SHA-3, MD5, etc.)
Designed for **security**, not speed — they provide strong collision resistance and pre-image resistance, used for password hashing, digital signatures, and blockchains. They are *much* slower than simple arithmetic hash functions and are overkill for ordinary hash tables.

**6. Universal Hashing**
```
h(k) = ((a*k + b) mod p) mod m
```
Here `a` and `b` are randomly chosen, and `p` is a prime larger than `m`. Because the function is chosen **randomly at runtime** from a family of functions, an adversary cannot craft inputs in advance that are guaranteed to collide — useful for security-sensitive or adversarial environments.

**7. Perfect Hashing**
A hash function built for a **known, fixed set of keys** so that there are **zero collisions**.
- **Minimal Perfect Hashing** — the output range exactly equals the number of keys.
- **Non-minimal Perfect Hashing** — the output range can be larger.

Great when the key set never changes (e.g., reserved keyword lookup in a compiler), but expensive to construct and unsuitable for dynamic data.

---

## 6. Collisions and Collision Resolution

Because a hash function maps a (potentially infinite) set of keys onto a (finite) set of table indices, **two different keys can end up with the same index**. This is called a **collision**, and it is *unavoidable* in general (pigeonhole principle) — so every hash table implementation needs a strategy to deal with it.

There are two major families of collision-resolution techniques:

```
Collision Resolution
├── 1. Separate Chaining      (store colliding keys in a list at that index)
└── 2. Open Addressing        (find another empty slot inside the same table)
        ├── Linear Probing
        ├── Quadratic Probing
        └── Double Hashing
```

---

## 7. Technique 1: Separate Chaining

### 7.1 The Idea

Instead of storing one key per slot, each slot holds a **linked list (or dynamic array)** of all the keys that hashed to it. When a collision occurs, the new key is simply appended to that slot's list — nothing gets overwritten or displaced.

**Example:** hash function `key % 5`, inserting keys `12, 15, 22, 25, 37`:

| Index | Chain |
|-------|-------|
| 0 | 15 → 25 |
| 1 | — |
| 2 | 12 → 22 → 37 |
| 3 | — |
| 4 | — |

To search for `22`, compute `22 % 5 = 2`, then walk the chain at index 2 until we find it (or reach the end).

### 7.2 Advantages

- Very simple to implement.
- The table **never "fills up"** — a chain can always grow.
- Performance degrades gracefully; not very sensitive to a poorly-tuned load factor.
- Ideal when you don't know in advance how many keys will be inserted/deleted.

### 7.3 Disadvantages

- Poor **cache locality** — traversing a linked list means jumping around memory, which is unfriendly to the CPU cache.
- Wastes space on empty buckets and on pointer/link overhead.
- If many keys collide into one chain, that chain's search degrades toward O(n).

### 7.4 What Can You Use for the "Chain"?

| Structure | Search | Insert | Delete | Notes |
|-----------|--------|--------|--------|-------|
| Linked List | O(len) | O(1) | O(len) | Not cache-friendly |
| Dynamic Array (`vector`) | O(len) | O(1)* | O(len) | Cache-friendly |
| Self-Balancing BST | O(log len) | O(log len) | O(log len) | Used by Java 8+ `HashMap` when a chain gets very long |

*(amortized; occasional resize costs more)*

### 7.5 Performance Analysis

Assuming keys are uniformly distributed (simple uniform hashing):
```
m = number of buckets
n = number of keys
Load Factor α = n / m

Expected search time = O(1 + α)
Expected insert time = O(1)
Expected delete time = O(1 + α)
```
If `α` is kept `O(1)` (i.e., roughly constant, achieved by rehashing), all operations run in **O(1) average time**.

### 7.6 C++ Implementation — Separate Chaining Hash Table

```cpp
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class ChainedHashTable {
    int bucketCount;                 // number of buckets
    int elementCount;                // number of stored keys
    vector<list<int>> buckets;       // each bucket is a chain (linked list)

    // Maps a key to a bucket index
    int hashOf(int key) const {
        return key % bucketCount;
    }

public:
    explicit ChainedHashTable(int buckets_ = 8)
        : bucketCount(buckets_), elementCount(0), buckets(buckets_) {}

    double loadFactor() const {
        return static_cast<double>(elementCount) / bucketCount;
    }

    // Doubles the table size and re-distributes every key
    void growAndRehash() {
        vector<list<int>> oldBuckets = move(buckets);
        bucketCount *= 2;
        buckets.assign(bucketCount, {});
        elementCount = 0;
        for (auto &chain : oldBuckets)
            for (int key : chain)
                insert(key);
    }

    void insert(int key) {
        if (contains(key)) return;              // no duplicate keys
        if (loadFactor() >= 0.75) growAndRehash();
        buckets[hashOf(key)].push_back(key);
        elementCount++;
    }

    bool contains(int key) const {
        const auto &chain = buckets[hashOf(key)];
        for (int k : chain)
            if (k == key) return true;
        return false;
    }

    void remove(int key) {
        auto &chain = buckets[hashOf(key)];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (*it == key) {
                chain.erase(it);
                elementCount--;
                return;
            }
        }
    }

    void display() const {
        for (int i = 0; i < bucketCount; i++) {
            cout << i << ":";
            for (int key : buckets[i]) cout << " -> " << key;
            cout << "\n";
        }
    }
};

int main() {
    ChainedHashTable table(5);

    for (int key : {12, 15, 22, 25, 37})
        table.insert(key);

    cout << "Hash table contents:\n";
    table.display();

    cout << "\nContains 22? " << (table.contains(22) ? "yes" : "no") << "\n";

    table.remove(22);
    cout << "After removing 22:\n";
    table.display();

    return 0;
}
```

**What this code does differently from a "toy" version:** it tracks `elementCount`, computes the **load factor** on every insert, and automatically doubles the bucket count (**rehashing**, explained in Section 9) once the load factor crosses `0.75`, so performance stays close to O(1) as the table grows.

---

## 8. Technique 2: Open Addressing

### 8.1 The Idea

In open addressing (a.k.a. **closed hashing**), there are **no chains** — every key lives directly inside the table array. When a collision happens, we **probe** (search) for the next available slot according to some fixed rule, until we find an empty one.

Because everything lives in one contiguous array, the table size **must always be ≥** the number of keys, and performance depends heavily on the **load factor** staying low (usually kept below ~0.7).

The three fundamental operations, at a conceptual level:

- **Insert(k):** Probe slots in sequence until an empty (or "deleted") slot is found; place `k` there.
- **Search(k):** Probe slots in the same sequence until the key is found, or an empty slot (never occupied) is reached — meaning the key does not exist.
- **Delete(k):** You **cannot** just empty the slot — that would break the probe chain for other keys and make `Search` stop too early. Instead, the slot is marked as **"deleted"** (a tombstone). Future inserts may reuse a deleted slot, but a search must keep going past it.

Open addressing comes in three popular flavors, each differing only in **how the next probe index is computed**.

---

### 8.2 Linear Probing

**Idea:** If the computed slot is full, just try the *very next* slot, wrapping around at the end of the table.

```
probe(i) = (h(key) + i) % tableSize     for i = 0, 1, 2, 3, ...
```

**Example:** hash function `key % 5`, inserting `50, 70, 76, 85, 93`:
- `50 % 5 = 0` → placed at 0
- `70 % 5 = 0` → collision, try 1 → placed at 1
- `76 % 5 = 1` → collision, try 2 → placed at 2
- `85 % 5 = 0` → collision → try 1 (full) → try 2 (full) → try 3 → placed at 3
- `93 % 5 = 3` → collision → try 4 → placed at 4

**Advantages:** simplest to compute; excellent **cache performance**, because probes touch consecutive memory addresses.

**Disadvantage — Primary Clustering:** once a run of consecutive filled slots forms, it tends to grow even longer, because *any* key hashing anywhere inside that run will probe through the whole thing before finding space. This can degrade performance significantly at high load factors.

#### C++ Implementation — Linear Probing

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Slot {
    int key;
    int value;
    bool occupied = false;   // is this slot currently holding live data?
    bool tombstone = false;  // was a key deleted from here?
};

class LinearProbingTable {
    vector<Slot> table;
    int capacity;
    int filledCount;          // occupied + tombstoned slots (for load factor)

    int hashOf(int key) const { return key % capacity; }

    void resizeAndRehash() {
        vector<Slot> old = move(table);
        capacity *= 2;
        table.assign(capacity, Slot{});
        filledCount = 0;
        for (auto &slot : old)
            if (slot.occupied) insert(slot.key, slot.value);
    }

public:
    explicit LinearProbingTable(int cap = 8) : capacity(cap), filledCount(0) {
        table.assign(capacity, Slot{});
    }

    void insert(int key, int value) {
        if (static_cast<double>(filledCount + 1) / capacity >= 0.7)
            resizeAndRehash();

        int idx = hashOf(key);
        int firstTombstone = -1;

        for (int probes = 0; probes < capacity; probes++) {
            Slot &s = table[idx];
            if (!s.occupied && !s.tombstone) {           // empty slot found
                int target = (firstTombstone != -1) ? firstTombstone : idx;
                table[target] = {key, value, true, false};
                filledCount++;
                return;
            }
            if (s.occupied && s.key == key) {             // key already exists -> update
                s.value = value;
                return;
            }
            if (s.tombstone && firstTombstone == -1)
                firstTombstone = idx;                      // remember first deleted slot

            idx = (idx + 1) % capacity;
        }
    }

    bool search(int key, int &valueOut) const {
        int idx = hashOf(key);
        for (int probes = 0; probes < capacity; probes++) {
            const Slot &s = table[idx];
            if (!s.occupied && !s.tombstone) return false;  // hit truly empty slot -> not found
            if (s.occupied && s.key == key) { valueOut = s.value; return true; }
            idx = (idx + 1) % capacity;
        }
        return false;
    }

    bool remove(int key) {
        int idx = hashOf(key);
        for (int probes = 0; probes < capacity; probes++) {
            Slot &s = table[idx];
            if (!s.occupied && !s.tombstone) return false;
            if (s.occupied && s.key == key) {
                s.occupied = false;
                s.tombstone = true;     // leave a tombstone, don't just clear the slot
                return true;
            }
            idx = (idx + 1) % capacity;
        }
        return false;
    }

    void display() const {
        for (int i = 0; i < capacity; i++)
            if (table[i].occupied)
                cout << "[" << i << "] " << table[i].key << " -> " << table[i].value << "\n";
    }
};

int main() {
    LinearProbingTable ht;
    ht.insert(1, 10);
    ht.insert(2, 20);
    ht.insert(3, 30);
    ht.insert(22, 220);   // collides with key 2 in a small table
    ht.insert(42, 420);

    cout << "Table contents:\n";
    ht.display();

    int val;
    if (ht.search(22, val)) cout << "\nFound 22 -> " << val << "\n";

    ht.remove(2);
    cout << "\nAfter deleting key 2, search for 2: "
         << (ht.search(2, val) ? "found" : "not found") << "\n";

    return 0;
}
```

**Complexity:** best case O(1); average case O(1) with a good hash function and reasonable load factor; worst case O(n) if the table is nearly full or badly clustered.

---

### 8.3 Quadratic Probing

**Idea:** Instead of moving one step at a time, jump by **increasing square numbers**: 1², 2², 3², … This spreads probes out more, reducing (but not eliminating) clustering.

```
probe(i) = (h(key) + i²) % tableSize     for i = 0, 1, 2, 3, ...
```

**Example:** table size = 7, `h(x) = x % 7`, inserting `22, 30, 50`:
- `22 % 7 = 1` → empty → placed at 1
- `30 % 7 = 2` → empty → placed at 2
- `50 % 7 = 1` → occupied → try `(1 + 1²) % 7 = 2` → occupied → try `(1 + 2²) % 7 = 5` → empty → placed at 5

**Advantage:** avoids the "long run" problem of linear probing (this is sometimes called avoiding *primary clustering*), giving noticeably better distribution.

**Disadvantage — Secondary Clustering:** keys that hash to the *same* initial index will always follow the *exact same* probe sequence, so they still cluster together (just less severely than linear probing). There is also a subtler problem:

> ⚠️ **Not every slot is guaranteed to be probed.** For certain table sizes, quadratic probing can fail to find an empty slot even though one exists, because the sequence of `(h + i²) % m` values doesn't cover all residues modulo `m`. This is fixed by choosing `m` to be **prime**, keeping the load factor **below 0.5**, or using a table size that's a **power of two** together with a specially adjusted probing formula (shown below).

#### C++ Implementation — Quadratic Probing

```cpp
#include <iostream>
#include <vector>
using namespace std;

class QuadraticProbingTable {
    vector<int> table;   // stores keys directly; -1 means empty
    int size;

public:
    explicit QuadraticProbingTable(int tableSize) : size(tableSize) {
        table.assign(size, -1);
    }

    bool insert(int key) {
        int home = key % size;
        if (table[home] == -1) {
            table[home] = key;
            return true;
        }
        // Probe using i^2 offsets
        for (int i = 1; i < size; i++) {
            int idx = (home + i * i) % size;
            if (table[idx] == -1) {
                table[idx] = key;
                return true;
            }
        }
        return false;   // table too full / no free slot found within the probe sequence
    }

    bool search(int key) const {
        int home = key % size;
        if (table[home] == key) return true;
        for (int i = 1; i < size; i++) {
            int idx = (home + i * i) % size;
            if (table[idx] == key) return true;
            if (table[idx] == -1) return false;   // hit empty slot: key can't be further along
        }
        return false;
    }

    void display() const {
        for (int i = 0; i < size; i++)
            cout << (table[i] == -1 ? -1 : table[i]) << " ";
        cout << "\n";
    }
};

int main() {
    QuadraticProbingTable ht(7);

    for (int key : {22, 30, 50})
        ht.insert(key);

    cout << "Table after inserts: ";
    ht.display();

    cout << "Search 50: " << (ht.search(50) ? "found" : "not found") << "\n";
    cout << "Search 15: " << (ht.search(15) ? "found" : "not found") << "\n";

    return 0;
}
```

**Complexity:** O(1) average with a good hash function and moderate load factor; worst case can approach O(n) as the table fills up, and — as noted above — some keys may fail to be placed at all unless the table size and load factor are chosen carefully.

---

### 8.4 Double Hashing

**Idea:** Use a **second, independent hash function** to decide the probing step size. Different keys that collide at the same home slot will now follow **different** probe sequences (unlike linear/quadratic probing), which essentially eliminates clustering.

```
probe(i) = (h1(key) + i * h2(key)) % tableSize     for i = 0, 1, 2, 3, ...
```

A common, well-tested pair of hash functions:
```
h1(key) = key % tableSize
h2(key) = PRIME - (key % PRIME)        where PRIME is a prime smaller than tableSize
```
`h2` must **never evaluate to 0** (otherwise probing would never move), and ideally it should be able to reach every slot eventually — choosing `PRIME` carefully (and keeping `tableSize` itself prime) helps guarantee this.

**Example:** table size = 7, `h1(k) = k % 7`, `h2(k) = 1 + (k % 5)`, inserting `27, 43, 692, 72`:
- `27 % 7 = 6` → empty → placed at 6
- `43 % 7 = 1` → empty → placed at 1
- `692 % 7 = 6` → collision → step = `1 + (692 % 5) = 3` → try `(6+3)%7 = 2` → empty → placed at 2
- `72 % 7 = 2` → collision → step = `1 + (72 % 5) = 3` → try `(2+3)%7 = 5` → empty → placed at 5

**Advantages:** best distribution of the three probing methods; virtually no clustering.

**Disadvantages:** more expensive per probe (two hash functions instead of one); worse cache locality than linear probing, since consecutive probes jump around the table rather than moving to adjacent memory.

#### C++ Implementation — Double Hashing

```cpp
#include <iostream>
#include <vector>
using namespace std;

const int EMPTY = -1;
const int DELETED = -2;

class DoubleHashTable {
    vector<int> table;
    int capacity;
    int keyCount;
    int stepPrime;   // a prime smaller than capacity, used by the second hash function

    static bool isPrime(int n) {
        if (n < 2) return false;
        for (int d = 2; d * d <= n; d++)
            if (n % d == 0) return false;
        return true;
    }

    int largestPrimeBelow(int n) const {
        for (int p = n - 1; p >= 2; p--)
            if (isPrime(p)) return p;
        return 2;
    }

    int hash1(int key) const { return key % capacity; }
    int hash2(int key) const { return stepPrime - (key % stepPrime); }  // never returns 0

public:
    explicit DoubleHashTable(int cap)
        : table(cap, EMPTY), capacity(cap), keyCount(0) {
        stepPrime = largestPrimeBelow(capacity);
    }

    bool isFull() const { return keyCount == capacity; }

    bool insert(int key) {
        if (isFull()) return false;
        int probe = hash1(key), step = hash2(key);
        while (table[probe] != EMPTY && table[probe] != DELETED)
            probe = (probe + step) % capacity;
        table[probe] = key;
        keyCount++;
        return true;
    }

    bool search(int key) const {
        int probe = hash1(key), step = hash2(key), start = probe;
        bool firstPass = true;
        while (true) {
            if (table[probe] == EMPTY) return false;
            if (table[probe] == key) return true;
            probe = (probe + step) % capacity;
            if (probe == start && !firstPass) return false;   // came full circle
            firstPass = false;
        }
    }

    bool remove(int key) {
        if (!search(key)) return false;
        int probe = hash1(key), step = hash2(key);
        while (table[probe] != EMPTY) {
            if (table[probe] == key) {
                table[probe] = DELETED;
                keyCount--;
                return true;
            }
            probe = (probe + step) % capacity;
        }
        return false;
    }

    void display() const {
        for (int v : table) cout << v << " ";
        cout << "\n";
    }
};

int main() {
    DoubleHashTable ht(13);

    for (int key : {27, 43, 692, 72})
        ht.insert(key);

    cout << "Table after inserts: ";
    ht.display();

    cout << "Search 692: " << (ht.search(692) ? "found" : "not found") << "\n";

    ht.remove(43);
    cout << "After deleting 43: ";
    ht.display();

    return 0;
}
```

**Complexity:** search/insert/delete take O(1) on average with a good pair of hash functions and reasonable load factor; O(n) worst case (rare in practice with double hashing since clustering is minimized).

---

### 8.5 Chaining vs. Open Addressing — Side-by-Side

| # | Separate Chaining | Open Addressing |
|---|--------------------|------------------|
| 1 | Simpler to implement | Requires more careful implementation (probing, tombstones) |
| 2 | Table never "fills up" | Table size must be ≥ number of keys; can become full |
| 3 | Less sensitive to load factor | Needs load factor to be kept low (≤ ~0.7) to avoid clustering |
| 4 | Good when insert/delete frequency is unpredictable | Good when the approximate number of keys is known ahead of time |
| 5 | Poor cache performance (linked-list traversal) | Better cache performance (data lives in one contiguous array) |
| 6 | Wastes space on unused buckets | Slots can be reused regardless of which key originally hashed there |
| 7 | Extra memory for links/pointers | No extra memory for links |

### 8.6 Comparing the Three Probing Strategies

| Aspect | Linear Probing | Quadratic Probing | Double Hashing |
|--------|-----------------|--------------------|-----------------|
| Probe sequence | `+1, +2, +3, ...` | `+1², +2², +3², ...` | `+step, +2·step, +3·step, ...` |
| Cache performance | **Best** (sequential access) | Medium | **Worst** (scattered access) |
| Clustering | Primary clustering (worst) | Secondary clustering (better) | Virtually none (best) |
| Computation cost | **Lowest** | Medium | **Highest** (two hash functions) |
| Guarantee of finding a free slot | Yes (if any slot is free) | Not always (depends on table size) | Yes, with a well-chosen second hash function |

### 8.7 Performance of Open Addressing (General Formula)

```
m = number of slots
n = number of keys
Load Factor α = n / m     (must stay < 1)

Expected time for search/insert/delete ≈ 1 / (1 - α)
```
Notice how this blows up as `α → 1`: at `α = 0.9`, expected time is `1/0.1 = 10` probes; at `α = 0.99`, it becomes `100` probes! This is exactly why open addressing implementations aggressively rehash once the load factor crosses a threshold like 0.7.

---

## 9. Load Factor and Rehashing

### 9.1 What Is Load Factor?

```
Load Factor (α) = Number of elements stored / Size of the hash table
```

It tells us **how "crowded"** the table is, and it directly predicts how many collisions we should expect:

- **Low α** (e.g., 0.2) → few collisions, fast operations, but wasted memory.
- **High α** (e.g., close to 1, or above 1 for chaining) → many collisions, slower operations.

Keeping the load factor within a healthy range is the single most important tuning knob for a hash table's performance.

### 9.2 What Is Rehashing, and Why Do We Need It?

**Rehashing** is the process of:
1. Creating a **new, larger** underlying array (commonly **double** the old size).
2. Recomputing the hash index for **every existing key**, since the hash function depends on table size (`key % capacity`).
3. Re-inserting every key into the new array.

We rehash because as more keys are inserted, the load factor keeps rising. If we never resized the table, collisions would keep piling up and every operation would slowly degrade from O(1) toward O(n). Rehashing periodically "resets" the load factor back to a low, healthy value — the classic **space-time tradeoff**: we spend a little extra memory (and one expensive O(n) rehash operation) to keep future operations fast.

### 9.3 How Rehashing Works, Step by Step

1. On every insertion, compute the new load factor.
2. If it exceeds a threshold (commonly **0.75** for chaining, or **0.7** for open addressing), trigger a rehash.
3. Allocate a new array of (typically) **2× the size**.
4. Walk through every slot/chain of the old array and re-insert each key into the new array using the hash function recalculated for the *new* capacity.
5. Discard the old array.

### 9.4 C++ Implementation — A Map with Automatic Rehashing

This example builds a simple key–value map (using chaining internally) that automatically rehashes once its load factor crosses `0.75`.

```cpp
#include <iostream>
#include <vector>
using namespace std;

class AutoRehashMap {
    struct Node {
        int key, value;
        Node* next;
        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> buckets;
    int numBuckets;
    int numPairs;
    static constexpr double LOAD_FACTOR_LIMIT = 0.75;

    int bucketIndex(int key) const { return key % numBuckets; }

    void rehash() {
        vector<Node*> oldBuckets = buckets;
        int oldCount = numBuckets;

        numBuckets *= 2;
        buckets.assign(numBuckets, nullptr);
        numPairs = 0;

        for (int i = 0; i < oldCount; i++) {
            Node* cur = oldBuckets[i];
            while (cur) {
                Node* nxt = cur->next;
                insert(cur->key, cur->value);   // re-insert into the resized table
                delete cur;
                cur = nxt;
            }
        }
    }

public:
    explicit AutoRehashMap(int initialBuckets = 5)
        : buckets(initialBuckets, nullptr), numBuckets(initialBuckets), numPairs(0) {}

    void insert(int key, int value) {
        int idx = bucketIndex(key);

        // Update value if key already exists
        for (Node* cur = buckets[idx]; cur; cur = cur->next) {
            if (cur->key == key) { cur->value = value; return; }
        }

        Node* fresh = new Node(key, value);
        fresh->next = buckets[idx];
        buckets[idx] = fresh;
        numPairs++;

        double loadFactor = static_cast<double>(numPairs) / numBuckets;
        if (loadFactor > LOAD_FACTOR_LIMIT) {
            cout << "Load factor " << loadFactor << " exceeded "
                 << LOAD_FACTOR_LIMIT << " -> rehashing to " << numBuckets * 2 << " buckets\n";
            rehash();
        }
    }

    bool get(int key, int &valueOut) const {
        for (Node* cur = buckets[bucketIndex(key)]; cur; cur = cur->next)
            if (cur->key == key) { valueOut = cur->value; return true; }
        return false;
    }

    void printState() const {
        cout << "Buckets: " << numBuckets << ", pairs: " << numPairs
             << ", load factor: " << (double)numPairs / numBuckets << "\n";
    }
};

int main() {
    AutoRehashMap map(5);

    for (int i = 1; i <= 6; i++) {
        map.insert(i, i * 100);
        map.printState();
    }

    int val;
    if (map.get(4, val)) cout << "\nValue for key 4: " << val << "\n";

    return 0;
}
```

### 9.5 Complexity of Rehashing

| Operation | Time Complexity | Notes |
|-----------|-------------------|-------|
| A single insert (no rehash triggered) | O(1) average | Normal case |
| A single insert **that triggers rehash** | O(n) | Every existing key must be moved once |
| **Amortized** cost per insert over many operations | O(1) | Because rehashing (doubling) happens exponentially less often as `n` grows |

This last row is the key insight: even though *one* insert can occasionally cost O(n), doubling the table size means rehashing happens at `n = 2, 4, 8, 16, …` — so if you sum up the total rehashing work over `n` inserts, it comes out to O(n) total, or **O(1) amortized per insert**.

---

## 10. Complexity Cheat Sheet

| Technique | Search (avg) | Insert (avg) | Delete (avg) | Search (worst) | Space Overhead |
|-----------|:---:|:---:|:---:|:---:|---|
| Separate Chaining | O(1 + α) | O(1) | O(1 + α) | O(n) | Extra pointers/links |
| Linear Probing | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) | O(n) | None (in-place) |
| Quadratic Probing | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) | O(n) | None (in-place) |
| Double Hashing | O(1/(1-α)) | O(1/(1-α)) | O(1/(1-α)) | O(n) | None (in-place) |

`α` is the load factor. In every case, keeping `α` bounded by regular rehashing is what keeps average-case behavior close to O(1).

---

## 11. Hashing in the C++ STL

You rarely need to hand-roll a hash table for everyday coding — C++'s Standard Template Library already implements one, heavily optimized, via **separate chaining** internally.

| STL Container | Equivalent Hashing Concept | Header |
|----------------|-----------------------------|--------|
| `std::unordered_set<T>` | Hash **Set** — stores unique keys only | `<unordered_set>` |
| `std::unordered_map<K, V>` | Hash **Map** — stores unique key → value pairs | `<unordered_map>` |
| `std::unordered_multiset<T>` | Hash set that allows duplicate keys | `<unordered_set>` |
| `std::unordered_multimap<K, V>` | Hash map that allows duplicate keys | `<unordered_map>` |

### 11.1 Quick Example

```cpp
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main() {
    // Hash Map: word -> frequency
    unordered_map<string, int> freq;
    for (string word : {"cat", "dog", "cat", "bird", "dog", "cat"})
        freq[word]++;

    for (auto &[word, count] : freq)
        cout << word << " -> " << count << "\n";

    // Hash Set: distinct elements
    unordered_set<int> seen;
    for (int x : {4, 2, 4, 7, 2, 9})
        seen.insert(x);

    cout << "\nDistinct elements: ";
    for (int x : seen) cout << x << " ";
    cout << "\n";

    return 0;
}
```

### 11.2 Custom Hash Function for Your Own Types

If you want to use a custom `struct` as a key in `unordered_map`/`unordered_set`, you must supply your own hash function and equality check:

```cpp
#include <unordered_map>
using namespace std;

struct Point {
    int x, y;
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash {
    size_t operator()(const Point &p) const {
        // Combine the two int hashes into one — a common idiom
        return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
    }
};

int main() {
    unordered_map<Point, string, PointHash> labels;
    labels[{0, 0}] = "origin";
    labels[{1, 1}] = "diagonal";
    return 0;
}
```

### 11.3 `unordered_map` vs `map`

| Feature | `unordered_map` (hash table) | `map` (self-balancing BST, usually Red-Black tree) |
|---------|-------------------------------|------------------------------------------------------|
| Average time complexity | O(1) | O(log n) |
| Worst-case time complexity | O(n) | O(log n) — guaranteed |
| Order of elements | Unordered | Sorted by key |
| Extra operations | None built-in | `lower_bound`, `upper_bound`, range queries |
| Memory overhead | Buckets + chains | Tree node pointers |

**Rule of thumb:** use `unordered_map` when you only need fast lookups and don't care about order; use `map` when you need sorted traversal or range queries.

### 11.4 Useful `unordered_map`/`unordered_set` Members

| Member | Purpose |
|--------|---------|
| `load_factor()` | Returns current load factor |
| `max_load_factor()` | Get/set the threshold that triggers a rehash |
| `rehash(n)` | Manually request at least `n` buckets |
| `reserve(n)` | Pre-allocate enough buckets for `n` elements (avoids repeated rehashing) |
| `bucket_count()` | Number of buckets currently allocated |
| `bucket(key)` | Which bucket a given key falls into |

If you know roughly how many elements you'll insert, calling `reserve()` upfront avoids multiple expensive rehashes during a loop of insertions — a handy performance trick in competitive programming and production code alike.

---

## 12. Applications of Hashing

Hashing shows up everywhere in real systems, not just in DSA problems. Broadly:

### 12.1 Data Integrity & Security
- **Password Storage** — store a one-way hash of a password instead of the plain text, so even a data breach doesn't expose actual passwords.
- **File Comparison / Message Digests** — a file's hash acts as a fingerprint; if even one bit changes, the hash changes completely, instantly revealing corruption or tampering.
- **Blockchain** — each block stores the hash of the previous block, so altering any historical block breaks the entire chain and is immediately detectable.
- **Fraud/Malware Detection** — known-malicious files are matched by comparing hashes against a database of malicious hashes.

### 12.2 Database & Search Optimization
- **Database Indexing** — hashing lets a database jump directly to a record instead of scanning the whole table.
- **Counting Distinct Elements / Frequencies** — using a hash set/map is the standard trick for problems like "count distinct elements" or "find the most frequent element."
- **Dictionaries / Associative Arrays** — the underlying mechanism behind Python `dict`, JavaScript `Map`, Java `HashMap`, and C++ `unordered_map`.
- **Rabin–Karp Algorithm** — a string-matching algorithm that hashes substrings to quickly rule out non-matches before doing an expensive character-by-character comparison.

### 12.3 Network & System Infrastructure
- **Load Balancing (Consistent Hashing)** — distributes requests evenly across servers, and — crucially — minimizes how much data needs to move when a server is added or removed.
- **Bloom Filters** — a compact, probabilistic structure that can quickly answer "definitely not present" or "possibly present" for huge datasets, using very little memory.
- **Network Routing** — hashing packet attributes helps route traffic efficiently.
- **Caching** — cache keys (e.g., URLs) are hashed to quickly check "do we already have this cached?"

### 12.4 Specialized Processing
- **Perceptual Image Hashing** — finds near-duplicate images (even after resizing/compression) by hashing structural features rather than raw bytes.
- **Symbol Tables in Compilers** — maps variable/function names to their memory locations or metadata during compilation.
- **Spatial Grids in Graphics** — hashing spatial coordinates helps organize objects in 3D scenes for faster rendering and collision detection.

---

## 13. When NOT to Use Hashing

Hashing is powerful but not universal. Reach for something else when you need:

| Requirement | Better Choice |
|---|---|
| Sorted traversal / range queries | Self-balancing BST (`std::map`) |
| Prefix search (autocomplete) | Trie |
| Floor/ceiling queries | Self-balancing BST |
| Guaranteed worst-case O(log n) (no O(n) spikes) | Self-balancing BST |
| A fixed, known key set with zero collisions needed | Perfect Hashing |

---

## 14. Quick Revision Summary

- **Hashing** maps keys to array indices via a **hash function**, enabling average **O(1)** search/insert/delete.
- A good hash function is **deterministic, fast, and uniform** — spreading keys evenly to minimize collisions.
- **Collisions are inevitable**; the two main resolution families are **Separate Chaining** (lists at each slot) and **Open Addressing** (probe for another slot in the same table).
- Within open addressing: **Linear Probing** (best cache, worst clustering) → **Quadratic Probing** (middle ground) → **Double Hashing** (best distribution, most computation).
- **Load Factor = n / m** measures how full the table is; when it crosses a threshold (commonly 0.7–0.75), the table **rehashes** — doubling in size and reinserting everything — to keep operations fast. Amortized, rehashing costs only O(1) extra per insert.
- In real C++ code, reach for **`unordered_map`/`unordered_set`** rather than hand-rolling a hash table — but understanding the internals (this document!) helps you reason about performance, write a custom hash function when needed, and answer interview questions confidently.
- Hashing powers an enormous range of real systems: password storage, blockchains, database indexes, caches, load balancers, and more.

---