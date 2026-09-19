# All Pointer Concepts Used in OOP in C++

Pointers are deeply intertwined with Object-Oriented Programming in C++. Below is a comprehensive coverage of every pointer-related concept used in OOP.

---

## 1. **Pointer to Object (Basic)**

A pointer that stores the address of an object.

```cpp
class Student {
public:
    string name;
    int age;
    void display() { cout << name << ", " << age << endl; }
};

int main() {
    Student s{"Alice", 20};
    Student *ptr = &s;          // pointer to object
    ptr->display();             // Alice, 20
    (*ptr).display();           // same thing
    return 0;
}
```

**Key Rule:** `ptr->member` ≡ `(*ptr).member`

---

## 2. **`this` Pointer**

Every non-static member function has an implicit `this` pointer that points to the invoking object.

```cpp
class Counter {
    int count;
public:
    Counter(int c) : count(c) {}

    Counter& increment() {
        this->count++;          // explicit use of this
        return *this;           // returns current object
    }

    void show() { cout << count << endl; }
};

int main() {
    Counter c(0);
    c.increment().increment().increment();   // method chaining
    c.show();   // 3
}
```

**Uses of `this`:**
- Resolve name conflicts (`this->x = x;`)
- Return `*this` for chaining
- Pass current object to other functions
- Delete current object (`delete this;` — rare, dangerous)

---

## 3. **Dynamic Object Creation (`new` / `delete`)**

```cpp
class Rectangle {
public:
    double l, w;
    Rectangle(double a, double b) : l(a), w(b) {}
    ~Rectangle() { cout << "Destroyed\n"; }
};

int main() {
    Rectangle *r = new Rectangle(5, 3);   // heap allocation
    cout << r->l * r->w << endl;

    delete r;      // calls destructor + frees memory
    r = nullptr;   // avoid dangling pointer
}
```

**Rules:**
- `new` → allocates on heap + calls constructor
- `delete` → calls destructor + frees memory
- `new[]` / `delete[]` for arrays
- **Never** mix `new` with `free()` or `malloc` with `delete`

---

## 4. **Array of Object Pointers**

```cpp
class Item {
public:
    int id;
    Item(int i) : id(i) {}
};

int main() {
    Item *items[3];                    // array of pointers
    for (int i = 0; i < 3; i++)
        items[i] = new Item(i + 1);

    // use items[i]->id

    for (int i = 0; i < 3; i++)
        delete items[i];
}
```

Also: **pointer to array of objects**

```cpp
Item *arr = new Item[3]{Item(1), Item(2), Item(3)};
delete[] arr;
```

---

## 5. **Pointer to Base Class (Polymorphism)**

The single most important OOP use of pointers: a base-class pointer can point to derived-class objects.

```cpp
class Shape {
public:
    virtual void draw() { cout << "Shape\n"; }
    virtual ~Shape() {}                // virtual destructor!
};

class Circle : public Shape {
public:
    void draw() override { cout << "Circle\n"; }
};

class Square : public Shape {
public:
    void draw() override { cout << "Square\n"; }
};

int main() {
    Shape *s1 = new Circle();
    Shape *s2 = new Square();

    s1->draw();     // Circle  (dynamic dispatch)
    s2->draw();     // Square

    delete s1;
    delete s2;
}
```

**Why virtual destructor matters:**

```cpp
Shape *s = new Circle();
delete s;    // if ~Shape is not virtual → UB (Circle's destructor not called)
```

---

## 6. **Pointer to Derived Class**

```cpp
Circle *c = new Circle();
c->draw();                   // fine

Shape *s = c;                // implicit upcast (safe)
// Circle *c2 = s;           // ❌ error — needs explicit cast
Circle *c2 = dynamic_cast<Circle*>(s);   // safe downcast
if (c2) c2->draw();
```

---

## 7. **Pointer to Member Function**

Pointers that point to member functions (not data). Used in callbacks, frameworks, and design patterns.

```cpp
class Calculator {
public:
    int add(int a, int b) { return a + b; }
    int sub(int a, int b) { return a - b; }
};

int main() {
    Calculator calc;
    int (Calculator::*op)(int, int);   // declare pointer-to-member-function

    op = &Calculator::add;
    cout << (calc.*op)(3, 4) << endl;   // 7

    op = &Calculator::sub;
    cout << (calc.*op)(10, 4) << endl;  // 6

    // with pointer to object
    Calculator *p = &calc;
    cout << (p->*op)(5, 2) << endl;     // 3
}
```

---

## 8. **Pointer to Member Data**

```cpp
class Point {
public:
    int x, y;
};

int main() {
    int Point::*pm = &Point::x;    // pointer-to-member-data

    Point p{10, 20};
    cout << p.*pm << endl;         // 10
    pm = &Point::y;
    cout << p.*pm << endl;         // 20
}
```

---

## 9. **`this` + Constructor Chaining / Self-Reference**

```cpp
class Node {
public:
    int data;
    Node *next;
    Node(int d) : data(d), next(nullptr) {}

    Node* setNext(Node *n) {
        this->next = n;
        return this;
    }
};
```

---

## 10. **Self-Referential Classes (Linked Structures)**

Foundation of linked lists, trees, graphs.

```cpp
class Node {
public:
    int data;
    Node *next;               // pointer to same class
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
    Node *head;
public:
    LinkedList() : head(nullptr) {}

    void push(int d) {
        Node *n = new Node(d);
        n->next = head;
        head = n;
    }

    ~LinkedList() {
        while (head) {
            Node *t = head;
            head = head->next;
            delete t;
        }
    }
};
```

Binary tree node:

```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
```

---

## 11. **Pointer to Pointer (Double Pointer) in OOP**

Used for modifying pointer itself, 2D dynamic arrays, or passing objects that need pointer reassignment.

```cpp
class Matrix {
    int **data;
    int rows, cols;
public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; i++)
            data[i] = new int[cols]{};
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++) delete[] data[i];
        delete[] data;
    }
    int& at(int i, int j) { return data[i][j]; }
};
```

Modifying a pointer inside a function:

```cpp
void createStudent(Student **s) {
    *s = new Student("Bob", 22);
}

int main() {
    Student *s = nullptr;
    createStudent(&s);
    // use s
    delete s;
}
```

---

## 12. **`void*` Pointer in OOP**

Generic pointer — used in low-level containers and callbacks.

```cpp
class AnyHolder {
    void *data;
public:
    template<typename T>
    void set(T *obj) { data = obj; }

    template<typename T>
    T* get() { return static_cast<T*>(data); }
};
```

---

## 13. **Smart Pointers (Modern C++) — RAII**

The modern replacement for raw pointers in OOP.

### `unique_ptr` — exclusive ownership

```cpp
#include <memory>

class Engine {
public:
    void start() { cout << "Engine started\n"; }
};

class Car {
    std::unique_ptr<Engine> engine;
public:
    Car() : engine(std::make_unique<Engine>()) {}
    void drive() { engine->start(); }
};
```

### `shared_ptr` — shared ownership

```cpp
std::shared_ptr<Shape> s1 = std::make_shared<Circle>();
std::shared_ptr<Shape> s2 = s1;     // refcount = 2
// destroyed when last reference goes away
```

### `weak_ptr` — non-owning reference (breaks cycles)

```cpp
class B;
class A {
public:
    std::shared_ptr<B> b;
};
class B {
public:
    std::weak_ptr<A> a;   // avoids circular reference
};
```

---

## 14. **Conversion Between Pointers (Casting)**

| Cast | Purpose | Example |
|------|---------|---------|
| `static_cast` | Compile-time up/down cast | `static_cast<Circle*>(s)` |
| `dynamic_cast` | Runtime-checked downcast (needs virtual) | `dynamic_cast<Circle*>(s)` |
| `const_cast` | Add/remove const | `const_cast<int*>(p)` |
| `reinterpret_cast` | Bit-level reinterpret | `reinterpret_cast<char*>(obj)` |

```cpp
Shape *s = new Circle();

// Safe downcast
if (Circle *c = dynamic_cast<Circle*>(s)) {
    c->draw();
} else {
    cout << "Not a Circle\n";
}
```

---

## 15. **`const` Pointer Variants in OOP**

```cpp
class Data { public: int x; };

Data d{10};

const Data *p1 = &d;        // pointer to const → cannot modify *p1
Data *const p2 = &d;        // const pointer → cannot reassign p2
const Data *const p3 = &d;  // both

// Const member functions and pointers
class Example {
    int v;
public:
    int get() const { return v; }   // this is const Data* inside
};
```

---

## 16. **Pointer to Object as Function Parameter**

```cpp
void modify(Student *s) { s->age = 25; }         // pass by pointer
void modifyRef(Student &s) { s.age = 25; }       // pass by reference

void noModify(const Student *s) { /* s->age = 1; ❌ */ }
```

**Comparison:**

| Method | Overhead | Can be null | Reassignable |
|--------|----------|-------------|--------------|
| By value | copy | N/A | No |
| By reference | none | No | No |
| By pointer | none | Yes | Yes |

---

## 17. **Returning Objects as Pointers**

```cpp
class Factory {
public:
    static Shape* createShape(int type) {
        if (type == 1) return new Circle();
        if (type == 2) return new Square();
        return nullptr;
    }
};

// Modern version
static std::unique_ptr<Shape> createShape(int type) {
    if (type == 1) return std::make_unique<Circle>();
    return std::make_unique<Square>();
}
```

---

## 18. **Pointer to Object and Operator Overloading**

```cpp
class Complex {
public:
    double r, i;
    Complex(double r, double i) : r(r), i(i) {}

    Complex operator+(const Complex &c) {
        return Complex(r + c.r, i + c.i);
    }
};

int main() {
    Complex *a = new Complex(1, 2);
    Complex b(3, 4);
    Complex c = *a + b;    // dereference to use operator
    delete a;
}
```

---

## 19. **`nullptr` and Null Checks in OOP**

```cpp
Shape *s = nullptr;
if (s != nullptr) s->draw();     // always check before dereferencing
```

Use `nullptr` (C++11) — never `NULL` or `0` for pointers.

---

## 20. **Dangling Pointers, Memory Leaks, Double Delete**

```cpp
// Dangling
Shape *s = new Circle();
delete s;
// s->draw();   ❌ UB

// Leak
Shape *s2 = new Circle();
// forgot delete

// Double delete
Shape *s3 = new Circle();
delete s3;
delete s3;      // ❌ UB
```

**Best practice:** Set pointer to `nullptr` after delete.

```cpp
delete s;
s = nullptr;
```

---

## 21. **Pointers in Design Patterns**

| Pattern | Pointer Usage |
|---------|---------------|
| **Singleton** | Static pointer to single instance |
| **Factory** | Returns pointer to base class |
| **Observer** | Array/list of pointers to observers |
| **Strategy** | Pointer to abstract strategy object |
| **Decorator** | Pointer to wrapped component |
| **Composite** | Vector of pointers to children |
| **Prototype** | `clone()` returns pointer |
| **Iterator** | Pointer to current node |
| **Flyweight** | Pointers to shared objects |
| **Chain of Responsibility** | `next` pointer to next handler |

**Example — Strategy pattern:**

```cpp
class SortStrategy {
public:
    virtual void sort(vector<int>&) = 0;
    virtual ~SortStrategy() {}
};

class Context {
    SortStrategy *strategy;
public:
    Context(SortStrategy *s) : strategy(s) {}
    void execute(vector<int>& v) { strategy->sort(v); }
};
```

---

## 22. **Pointers and Inheritance Layout**

- Base-class pointer → derived object: safe upcast
- Multiple inheritance: pointer adjustment happens automatically
- Virtual inheritance: pointer resolution handled by compiler

```cpp
class A { public: int a; };
class B { public: int b; };
class C : public A, public B { public: int c; };

C obj;
A *pa = &obj;   // adjusted pointer
B *pb = &obj;   // different adjusted pointer
```

---

## 23. **Reference vs Pointer in OOP**

| Aspect | Pointer | Reference |
|--------|---------|-----------|
| Null | Yes | No |
| Reassignable | Yes | No |
| Arithmetic | Yes | No |
| Syntax | `p->x` | `r.x` |
| Polymorphism | Yes | Yes |
| Ownership | Explicit | None |

---

## 24. **Smart Pointer in OOP — Ownership Semantics**

| Pointer | Ownership | Copyable | Use Case |
|---------|-----------|----------|----------|
| `unique_ptr` | Exclusive | No | Default choice |
| `shared_ptr` | Shared | Yes | Shared resources |
| `weak_ptr` | None | Yes | Break cycles, cache |
| Raw `*` | None | Yes | Non-owning observer |

---

## 25. **Complete Example — Putting It All Together**

```cpp
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    void draw() const override { cout << "Circle\n"; }
    double area() const override { return 3.14159 * r * r; }
};

class Rectangle : public Shape {
    double w, h;
public:
    Rectangle(double w, double h) : w(w), h(h) {}
    void draw() const override { cout << "Rectangle\n"; }
    double area() const override { return w * h; }
};

class Canvas {
    vector<unique_ptr<Shape>> shapes;   // owning pointers
public:
    void add(unique_ptr<Shape> s) {
        shapes.push_back(move(s));
    }

    void render() const {
        for (const auto &s : shapes) {   // const reference to unique_ptr
            s->draw();                    // pointer to base → polymorphism
            cout << "  area = " << s->area() << endl;
        }
    }
};

int main() {
    Canvas c;
    c.add(make_unique<Circle>(5));
    c.add(make_unique<Rectangle>(4, 6));
    c.render();
    // No delete needed — unique_ptr handles cleanup
}
```

---

## Summary Table

| Concept | Syntax |
|---------|--------|
| Pointer to object | `Class *p = &obj;` |
| Dynamic allocation | `Class *p = new Class(args);` |
| Delete | `delete p;` / `delete[] p;` |
| Member access | `p->member`, `(*p).member` |
| `this` | implicit pointer in member functions |
| Pointer to member fn | `int (Class::*fp)() = &Class::fn;` |
| Pointer to member data | `int Class::*dp = &Class::x;` |
| Base pointer | `Base *b = new Derived();` |
| Cast | `dynamic_cast<Derived*>(b)` |
| Array of pointers | `Class *arr[N];` |
| Pointer to pointer | `Class **pp = &p;` |
| Smart pointers | `unique_ptr`, `shared_ptr`, `weak_ptr` |
| Const variants | `const T*`, `T* const`, `const T* const` |
| null | `nullptr` |

These concepts form the complete pointer toolkit for OOP in C++ — from raw pointers and polymorphism to modern RAII-based smart pointers.