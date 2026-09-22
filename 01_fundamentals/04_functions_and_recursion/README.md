# 04 — Functions & Recursion in C

> Breaking programs into reusable, self-contained blocks of logic.

---

## 🧠 What is a Function?

A **function** is a named block of code that performs a specific task. Instead of repeating logic throughout a program, you write it once and **call** it whenever needed.

```c
/* Without a function — repeated logic */
printf("Sum: %d\n", 3 + 4);
printf("Sum: %d\n", 10 + 20);

/* With a function — reusable logic */
int add(int a, int b) {
    return a + b;
}

printf("Sum: %d\n", add(3, 4));
printf("Sum: %d\n", add(10, 20));
```

Every C program already uses a function — `main()` is the entry point every program starts from.

---

## 🔑 Anatomy of a Function

```c
return_type function_name(parameter_list) {
    /* body */
    return value;   /* omitted if return_type is void */
}
```

| Part | Purpose | Example |
|------|---------|---------|
| **Return type** | Type of value sent back | `int`, `float`, `void` |
| **Name** | How you call the function | `add`, `calculateArea` |
| **Parameters** | Inputs the function receives | `(int a, int b)` |
| **Body** | The code that runs | `{ return a + b; }` |
| **return** | Sends a value back and exits the function | `return a + b;` |

---

## 🗂️ Declaring, Defining, and Calling

C separates a function's **declaration** (also called a *prototype*), its **definition**, and its **call**.

```c
#include <stdio.h>

/* Declaration (prototype) — tells the compiler this function exists */
int add(int a, int b);

int main(void) {
    int result = add(2, 3);   /* Call — actually runs the function */
    printf("%d\n", result);
    return 0;
}

/* Definition — the actual implementation */
int add(int a, int b) {
    return a + b;
}
```

> ⚠️ If you call a function **before** it's declared or defined, the compiler won't know its signature. Always declare functions above `main()`, or place their full definition before first use.

---

## 📦 Function Types by Signature

| Signature | Meaning | Example |
|-----------|---------|---------|
| Takes nothing, returns nothing | `void greet(void)` | Prints a message |
| Takes parameters, returns nothing | `void printSum(int a, int b)` | Prints but doesn't return |
| Takes nothing, returns a value | `int getRandomNumber(void)` | Generates and returns |
| Takes parameters, returns a value | `int add(int a, int b)` | Most common form |

```c
void greet(void) {
    printf("Hello!\n");
}

void printSum(int a, int b) {
    printf("Sum: %d\n", a + b);
}

int getFive(void) {
    return 5;
}

int add(int a, int b) {
    return a + b;
}
```

---

## 🔁 Parameters: Pass by Value

C passes arguments **by value** — the function receives a **copy** of the argument, not the original variable. Changing a parameter inside the function does **not** affect the caller's variable.

```c
void increment(int x) {
    x = x + 1;         /* modifies the local copy only */
}

int main(void) {
    int num = 5;
    increment(num);
    printf("%d\n", num);   /* still prints 5 — unchanged! */
    return 0;
}
```

> 💡 To actually modify the caller's variable, you must pass a **pointer** to it (covered in topic 06 — Pointers). This is one of the most important gotchas in C.

---

## 🌍 Scope: Local vs Global Variables

| Scope | Declared | Visible From |
|-------|----------|--------------|
| **Local** | Inside a function or block | Only within that function/block |
| **Global** | Outside all functions | Anywhere in the file, after declaration |

```c
int globalCount = 0;   /* global — visible everywhere below this line */

void increment(void) {
    int localStep = 1;      /* local — only exists inside this function */
    globalCount += localStep;
}
```

> ⚠️ Overusing global variables makes programs harder to debug and reason about. Prefer passing values through parameters and return values.

---

## 🔂 Recursion

A **recursive function** is a function that calls **itself** to solve a smaller version of the same problem, until it reaches a **base case** that stops the recursion.

```c
/* Factorial: n! = n * (n-1) * (n-2) * ... * 1 */
int factorial(int n) {
    if (n <= 1) {
        return 1;              /* base case — stops the recursion */
    }
    return n * factorial(n - 1);  /* recursive case — calls itself */
}
```

**Every recursive function needs:**
1. A **base case** — the condition that stops the recursion
2. A **recursive case** — where the function calls itself with a smaller/simpler input

Without a base case, recursion never stops and causes a **stack overflow**.

### How recursion executes (factorial(4))

```
factorial(4)
  → 4 * factorial(3)
       → 3 * factorial(2)
            → 2 * factorial(1)
                 → 1  (base case reached)
            → 2 * 1 = 2
       → 3 * 2 = 6
  → 4 * 6 = 24
```

Each call waits on the **call stack** until the call below it returns.

---

## 🔃 Recursion vs Loops

| Situation | Prefer |
|-----------|--------|
| Simple repetition, known iterations | Loop (`for`/`while`) |
| Naturally recursive structure (trees, nested data) | Recursion |
| Performance-critical code | Loop (recursion has function-call overhead) |
| Divide-and-conquer algorithms (topic 45) | Recursion |
| Deep recursion depth (thousands of calls) | Loop (avoid stack overflow) |

Any recursive function **can** be rewritten as a loop, and vice versa — recursion is a tool for readability on certain problems, not a requirement.

---

## 📐 Common Recursion Patterns

### Factorial
```c
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

### Fibonacci sequence
```c
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
```

### Sum of digits
```c
int sumDigits(int n) {
    if (n == 0) return 0;
    return (n % 10) + sumDigits(n / 10);
}
```

### Reversing a string (in place, index-based)
```c
void reverse(char str[], int start, int end) {
    if (start >= end) return;
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverse(str, start + 1, end - 1);
}
```

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Missing base case | Recursive function with no stopping condition | Always define a clear base case |
| Base case never reached | `factorial(-3)` never hits `n <= 1` going downward | Validate input or fix the recursive step |
| Assuming pass-by-reference | Expecting a function to modify the caller's variable | Use pointers to modify the original |
| Forgetting function prototypes | Calling a function defined later in the file | Declare a prototype above `main()` |
| Excessive global variables | Functions silently depending on shared state | Pass values as parameters instead |
| Unbounded recursion depth | Recursive function on very large input | Convert to an iterative loop |
| Ignoring return values | Calling `add(2, 3);` and discarding the result | Store or use the returned value |

---

## 💡 Key Takeaways

- Functions let you organize code into reusable, named blocks
- A function has a declaration, a definition, and is executed via a call
- C passes arguments **by value** — the function gets a copy, not the original
- Local variables live only inside their function; global variables live for the whole program
- Recursion solves a problem by calling itself on a smaller version, until a base case is hit
- Every recursive function must have a base case, or it will overflow the call stack
- Recursion and loops can often solve the same problem — choose based on readability and performance

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of functions and recursion |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [03 — Loops](../03_loops/README.md)*
*Next topic → [05 — Arrays & Strings](../05_arrays_and_strings/README.md)*
