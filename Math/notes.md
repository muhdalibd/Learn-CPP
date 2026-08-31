

## Maths and Number Theory in Competitive Programming

## 1. Overview

Number theory in competitive programming is not about advanced algebra, trigonometry, or calculus. It mainly involves applying basic mathematical concepts efficiently in code.

Important topics include:

- [Prime numbers](#prime-numbers)
- [Prime factorization](#factors-of-a-number)
- [Factors and divisors](#factors-of-a-number)
- [Sieve of Eratosthenes](#sieve-of-eratosthenes)
- [GCD](#gcd) and [LCM](#lcm).
- [Modular arithmetic](#modular-arithmetic)
- [Binary exponentiation](#binary-exponentiation)
- [Modular exponentiation](#modular-exponentiation)
- [Factorials](#factorial)
- [Combinations ${}^nC_r$](#combinations)

The key goal is to convert mathematical observations into efficient algorithms.

______________________________________________________________________

## Prime Numbers

### Concept

A prime number is a natural number greater than $1$ that has exactly two factors:

- $1$.
- The number itself.

Examples:

- $2$: factors are $1, 2$.
- $3$: factors are $1, 3$.
- $5$: factors are $1, 5$.
- $12$: not prime because it has factors $1, 2, 3, 4, 6, 12$.

Numbers $0$ and $1$ are not prime.

### Basic Prime Check

A number $n$ is prime if no number between $2$ and $n-1$ divides it.

### C++ Implementation — $O(n)$

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isPrimeBasic(long long n) {
    if (n < 2) {
        return false;
    }

    for (long long i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}
```


### Optimized Prime Check

If $n$ is composite, it must have at least one factor less than or equal to $\sqrt n$.

Therefore, we only need to check divisors up to $\sqrt n$.

### C++ Implementation — $O(\sqrt n)$

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}
```


______________________________________________________________________

## Factors of a Number

### Concept

A factor or divisor of $n$ is a number that divides $n$ completely.

For example, the factors of $12$ are:

$$
1, 2, 3, 4, 6, 12
$$

If $i$ divides $n$, then $\frac{n}{i}$ is also a factor. This allows us to find all factors in $O(\sqrt n)$.

### C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<long long> getFactors(long long n) {
    vector<long long> factors;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);

            if (i != n / i) {
                factors.push_back(n / i);
            }
        }
    }

    sort(factors.begin(), factors.end());
    return factors;
}
```


### Example

For $n = 36$, the function returns:

```text
1 2 3 4 6 9 12 18 36
```

The condition `i != n / i` prevents duplicate factors for perfect squares such as $36$.

______________________________________________________________________

## Sieve of Eratosthenes

### Concept

The Sieve of Eratosthenes finds all prime numbers from $1$ to $n$.

Instead of individually checking every number for primality, we:

1. Assume every number is prime.
2. Mark $0$ and $1$ as non-prime.
3. Start from $2$.
4. If a number is still prime, mark all of its multiples as non-prime.
5. Continue up to $\sqrt n$.

For a prime $p$, marking starts from $p^2$, because smaller multiples have already been marked by smaller prime numbers.

### C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);

    if (n >= 0) {
        isPrime[^1_0] = false;
    }

    if (n >= 1) {
        isPrime[^1_1] = false;
    }

    for (long long i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (long long multiple = i * i;
                 multiple <= n;
                 multiple += i) {
                isPrime[multiple] = false;
            }
        }
    }

    return isPrime;
}
```


### Printing Primes

```cpp
int main() {
    int n;
    cin >> n;

    vector<bool> isPrime = sieve(n);

    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            cout << i << " ";
        }
    }

    return 0;
}
```


### Complexity

- Time: $O(n \log \log n)$.
- Space: $O(n)$.

The sieve is useful when many prime queries are required within a fixed range.

______________________________________________________________________

## Modular Arithmetic

### Concept

When numbers become very large, problems often ask for an answer modulo $m$.

Useful identities:

$$
(a+b)\bmod m =
((a\bmod m)+(b\bmod m))\bmod m
$$

$$
(a-b)\bmod m =
((a\bmod m)-(b\bmod m)+m)\bmod m
$$

$$
(a \times b)\bmod m =
((a\bmod m)(b\bmod m))\bmod m
$$

### C++ Example

```cpp
long long modularAddition(long long a, long long b, long long mod) {
    return ((a % mod) + (b % mod)) % mod;
}

long long modularSubtraction(long long a, long long b, long long mod) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

long long modularMultiplication(long long a, long long b, long long mod) {
    return ((a % mod) * (b % mod)) % mod;
}
```

Adding `mod` in subtraction prevents a negative result.

______________________________________________________________________

## Binary Exponentiation

### Concept

The naive way to calculate $a^b$ is to multiply $a$, $b$ times. Its complexity is $O(b)$.

Binary exponentiation reduces the complexity to $O(\log b)$ by repeatedly halving the exponent.

Mathematical identities:

For even $b$:

$$
a^b = a^{b/2} \times a^{b/2}
$$

For odd $b$:

$$
a^b = a^{b/2} \times a^{b/2} \times a
$$

### Recursive C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

long long binaryPower(long long a, long long b) {
    if (b == 0) {
        return 1;
    }

    long long half = binaryPower(a, b / 2);

    if (b % 2 == 0) {
        return half * half;
    }

    return half * half * a;
}
```


### Iterative C++ Implementation

```cpp
long long binaryPower(long long a, long long b) {
    long long result = 1;

    while (b > 0) {
        if (b & 1) {
            result *= a;
        }

        a *= a;
        b >>= 1;
    }

    return result;
}
```


### Complexity

- Naive exponentiation: $O(b)$.
- Binary exponentiation: $O(\log b)$.

______________________________________________________________________

## Modular Exponentiation

### Concept

Sometimes we need to calculate:

$$
a^b \bmod m
$$

Calculating $a^b$ first may cause integer overflow. Instead, apply modulo during every multiplication.

### C++ Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

long long modularPower(long long a, long long b, long long mod) {
    a %= mod;
    long long result = 1 % mod;

    while (b > 0) {
        if (b & 1) {
            result = (result * a) % mod;
        }

        a = (a * a) % mod;
        b >>= 1;
    }

    return result;
}
```


### Complexity

- Time: $O(\log b)$.
- Space: $O(1)$.


### Example

```cpp
int main() {
    long long a, b, mod;
    cin >> a >> b >> mod;

    cout << modularPower(a, b, mod);
    return 0;
}
```


______________________________________________________________________

## GCD

### Concept

The GCD, or Greatest Common Divisor, of two numbers is the largest number that divides both numbers.

For example:

$$
\gcd(60,45)=15
$$

The factors common to $60$ and $45$ are $1,3,5,15$, and the greatest is $15$.

### Euclidean Algorithm

The Euclidean algorithm uses:

$$
\gcd(a,b)=\gcd(b,a\bmod b)
$$

The base case is:

$$
\gcd(a,0)=a
$$

### Recursive C++ Implementation

```cpp
long long gcdRecursive(long long a, long long b) {
    if (b == 0) {
        return a;
    }

    return gcdRecursive(b, a % b);
}
```


### Iterative C++ Implementation

```cpp
long long gcdIterative(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}
```

C++ also provides a standard implementation:

```cpp
#include <numeric>

long long answer = gcd(60LL, 45LL);
```


### Complexity

The Euclidean algorithm runs in:

$$
O(\log(\min(a,b)))
$$

______________________________________________________________________

## LCM

### Concept

The LCM, or Least Common Multiple, is the smallest positive number divisible by both numbers.

For $60$ and $45$:

$$
\operatorname{lcm}(60,45)=180
$$

The relationship between GCD and LCM is:

$$
a \times b = \gcd(a,b) \times \operatorname{lcm}(a,b)
$$

Therefore:

$$
\operatorname{lcm}(a,b)=\frac{a}{\gcd(a,b)}\times b
$$

Dividing before multiplying helps reduce overflow risk.

### C++ Implementation

```cpp
long long lcm(long long a, long long b) {
    return (a / gcd(a, b)) * b;
}
```


______________________________________________________________________

## Factorial

### Concept

The factorial of $n$, written as $n!$, is:

$$
n! = 1 \times 2 \times 3 \times \cdots \times n
$$

Examples:

$$
5! = 1 \times 2 \times 3 \times 4 \times 5 = 120
$$

Special cases:

$$
0! = 1
$$

$$
1! = 1
$$

### C++ Implementation

```cpp
long long factorial(int n) {
    long long result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}
```

The result grows very quickly, so `long long` can only store factorials up to a relatively small value.

______________________________________________________________________

## Combinations ${}^nC_r$

### Concept

The number of ways to choose $r$ objects from $n$ objects is:

$$
{}^nC_r = \frac{n!}{r!(n-r)!}
$$

Important cases:

$$
{}^nC_0 = 1
$$

$$
{}^nC_n = 1
$$

$$
{}^nC_r = 0 \quad \text{when } r>n
$$

### C++ Implementation Using Factorials

```cpp
long long combinationUsingFactorial(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }

    long long numerator = factorial(n);
    long long denominator = factorial(r) * factorial(n - r);

    return numerator / denominator;
}
```

This method is simple but can overflow quickly.

### Pascal Identity

Combinations also follow:

$$
{}^nC_r = {}^{n-1}C_{r-1} + {}^{n-1}C_r
$$

This leads to a recursive implementation.

```cpp
long long combinationRecursive(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }

    if (r == 0 || r == n) {
        return 1;
    }

    return combinationRecursive(n - 1, r - 1)
         + combinationRecursive(n - 1, r);
}
```

This recursive version demonstrates the formula but is inefficient because it recalculates many states.

### Practical Iterative Implementation

```cpp
long long combination(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }

    r = min(r, n - r);

    long long result = 1;

    for (int i = 1; i <= r; i++) {
        result = result * (n - r + i) / i;
    }

    return result;
}
```


______________________________________________________________________

## Key Problem-Solving Observations

### Prime Sum

If $n$ is an odd prime greater than $2$, and we need two prime numbers whose sum is $n$:

- One number must be the only even prime, $2$.
- The other number must be $n-2$.
- Check whether $n-2$ is prime.

```cpp
if (isPrime(n - 2)) {
    cout << 2 << " " << n - 2 << '\n';
} else {
    cout << -1 << '\n';
}
```


### Prime Addition Observation

For any prime number $p$, choosing $7$ ensures:

- If $p=2$, then $p+7=9$, which is not prime.
- If $p>2$, both $p$ and $7$ are odd, so $p+7$ is even and greater than $2$, hence not prime.

Therefore, $7$ is always a valid answer in problems requiring a prime number to be added so that the result is non-prime.

### GCD and LCM Construction

To make:

$$
\gcd(a,b)=\operatorname{lcm}(c,d)
$$

choose:

```text
b = 1
c = 1
d = 1
a = n - 3
```

Then:

$$
a+b+c+d = n
$$

and:

$$
\gcd(a,1)=1
$$

$$
\operatorname{lcm}(1,1)=1
$$

This is an example of solving a complex-looking problem through mathematical construction.

______________________________________________________________________

### Complete Utility Template

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }

    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

vector<bool> sieve(int n) {
    vector<bool> prime(n + 1, true);

    if (n >= 0) {
        prime[^1_0] = false;
    }

    if (n >= 1) {
        prime[^1_1] = false;
    }

    for (long long i = 2; i * i <= n; i++) {
        if (prime[i]) {
            for (long long j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }

    return prime;
}

vector<long long> getFactors(long long n) {
    vector<long long> factors;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);

            if (i != n / i) {
                factors.push_back(n / i);
            }
        }
    }

    sort(factors.begin(), factors.end());
    return factors;
}

long long gcdValue(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

long long lcmValue(long long a, long long b) {
    return (a / gcdValue(a, b)) * b;
}

long long modularPower(long long a, long long b, long long mod) {
    a %= mod;
    long long result = 1 % mod;

    while (b > 0) {
        if (b & 1) {
            result = (result * a) % mod;
        }

        a = (a * a) % mod;
        b >>= 1;
    }

    return result;
}

long long factorial(int n) {
    long long result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }

    return result;
}

long long combination(int n, int r) {
    if (r < 0 || r > n) {
        return 0;
    }

    r = min(r, n - r);

    long long result = 1;

    for (int i = 1; i <= r; i++) {
        result = result * (n - r + i) / i;
    }

    return result;
}

int main() {
    cout << boolalpha;
    cout << isPrime(17) << endl;
    cout << gcdValue(60, 45) << endl;
    cout << lcmValue(60, 45) << endl;
    cout << modularPower(7, 100, 10) << endl;
    cout << factorial(5) << endl;
    cout << combination(5, 2) << endl;

    return 0;
}
```


## Complexity Reference

| Technique | Time Complexity |
| :-- | --: |
| Basic prime check | $O(n)$ |
| Optimized prime check | $O(\sqrt n)$ |
| Factors using all numbers | $O(n)$ |
| Factors using pairs | $O(\sqrt n)$ |
| Sieve of Eratosthenes | $O(n\log\log n)$ |
| Binary exponentiation | $O(\log b)$ |
| Modular exponentiation | $O(\log b)$ |
| Euclidean GCD | $O(\log(\min(a,b)))$ |
| Factorial loop | $O(n)$ |
| Direct combination using factorials | $O(n)$ |


<div style="text-align: center; color: #09ed2c;">⁂ Thank You ⁂</div>
