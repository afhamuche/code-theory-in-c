# 01 — Variables & Data Types in C

> Understanding how C stores, labels, and manages data in memory.

---

## 🧠 What is a Variable?

A **variable** is a named location in memory that holds a value. In C, every variable must be:

1. **Declared** — you tell C what type and name it has
2. **Initialized** — you give it a starting value
3. **Used** — you read or modify it in your program

```c
int age = 25;   // declared, initialized, ready to use
```

---

## 📦 Why Data Types Matter in C

Unlike higher-level languages, **C does not manage memory for you**. When you declare a variable, you are directly telling the computer:

- How many **bytes** to reserve in memory
- How to **interpret** the bits stored there

Choosing the wrong type wastes memory or causes **overflow** (values wrapping around unexpectedly).

---

## 🗂️ Core Data Types in C

### Integer Types (whole numbers)

| Type | Size | Range | Use Case |
|------|------|-------|----------|
| `char` | 1 byte | -128 to 127 | Single characters, small numbers |
| `unsigned char` | 1 byte | 0 to 255 | Pixel values, byte data |
| `short` | 2 bytes | -32,768 to 32,767 | Small integers |
| `int` | 4 bytes | -2,147,483,648 to 2,147,483,647 | General purpose integers |
| `long` | 4 or 8 bytes | Platform dependent | Large integers |
| `long long` | 8 bytes | -9.2 × 10¹⁸ to 9.2 × 10¹⁸ | Very large integers |

> ⚠️ Sizes can vary by platform and compiler. Use `sizeof()` to check.

---

### Floating Point Types (decimal numbers)

| Type | Size | Precision | Use Case |
|------|------|-----------|----------|
| `float` | 4 bytes | ~6–7 digits | Basic decimals, graphics |
| `double` | 8 bytes | ~15–16 digits | Scientific calculations |
| `long double` | 10–16 bytes | ~18–19 digits | High precision math |

> ⚠️ Never use `==` to compare floats — use a small tolerance (epsilon) instead.

---

### Other Types

| Type | Description |
|------|-------------|
| `_Bool` / `bool` | Boolean — 0 (false) or 1 (true). Requires `<stdbool.h>` |
| `void` | Represents no value — used in functions and pointers |

---

## 🔠 Characters & Strings

```c
char letter = 'A';          // single character — stored as ASCII integer 65
char name[] = "afhamuche";  // string — an array of chars ending with '\0'
```

C has **no native string type**. Strings are just arrays of `char` ending with a null terminator `'\0'`.

---

## 🏷️ Variable Declaration Rules

```c
// Syntax: type name = value;
int score = 100;
float temperature = 36.6;
char grade = 'A';

// Multiple declarations on one line
int x = 0, y = 0, z = 0;

// Declare first, assign later
int result;
result = 42;
```

### Naming Rules
- Can contain letters, digits, and underscores `_`
- Must **start with a letter or underscore** (not a digit)
- **Case-sensitive** (`age` and `Age` are different variables)
- Cannot use reserved keywords (`int`, `return`, `while`, etc.)

---

## 🔒 Type Qualifiers

Qualifiers add extra rules to how a variable behaves:

| Qualifier | Meaning | Example |
|-----------|---------|---------|
| `const` | Value cannot change after assignment | `const float PI = 3.14159;` |
| `unsigned` | Only positive values (doubles max range) | `unsigned int count = 0;` |
| `signed` | Positive and negative (default for most types) | `signed int temp = -5;` |
| `volatile` | Value may change unexpectedly (e.g. hardware) | `volatile int sensor;` |

---

## 🔄 Type Casting

Converting a value from one type to another:

```c
int a = 5;
int b = 2;

float result = (float)a / b;  // → 2.5  (explicit cast)
float bad    = a / b;         // → 2.0  (integer division first, then stored as float)
```

> ⚠️ Always cast **before** the operation, not after.

---

## 📐 Checking Sizes with sizeof()

```c
#include <stdio.h>

int main() {
    printf("char:      %zu bytes\n", sizeof(char));
    printf("int:       %zu bytes\n", sizeof(int));
    printf("float:     %zu bytes\n", sizeof(float));
    printf("double:    %zu bytes\n", sizeof(double));
    printf("long long: %zu bytes\n", sizeof(long long));
    return 0;
}
```

---

## ⚠️ Common Pitfalls in C

| Pitfall | Example | Fix |
|---------|---------|-----|
| Integer overflow | `char x = 200;` (max is 127) | Use `unsigned char` or `int` |
| Uninitialized variable | `int x; printf("%d", x);` | Always initialize before use |
| Float comparison | `if (x == 0.1)` | Use `fabs(x - 0.1) < 1e-9` |
| Wrong format specifier | `printf("%d", 3.14)` | Use `%f` for floats |
| Signed/unsigned mismatch | Comparing `int` with `unsigned int` | Be consistent with types |

---

## 🖨️ Format Specifiers (printf / scanf)

| Type | Specifier |
|------|-----------|
| `int` | `%d` or `%i` |
| `unsigned int` | `%u` |
| `float` | `%f` |
| `double` | `%lf` |
| `char` | `%c` |
| `string (char[])` | `%s` |
| `long long` | `%lld` |
| `size_t` | `%zu` |
| Hexadecimal | `%x` |
| Octal | `%o` |

---

## 💡 Key Takeaways

- Every variable in C has a **type**, a **name**, and a **value**
- Data types directly control **memory allocation**
- C is **strongly typed** — you must declare types explicitly
- Always **initialize** variables before using them
- Use `sizeof()` to verify sizes on your platform
- C strings are `char` arrays — not a built-in type

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of all data types |

---

## ▶️ How to Run

```bash
gcc main.c -o main && ./main
```

---

*Next topic → [02 — Conditionals](../../01_fundamentals/02_conditionals/README.md)*
