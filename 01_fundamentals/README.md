# 01 — Fundamentals

> The bedrock of C programming. Before data structures, algorithms, or systems — you need to master how C thinks.

---

## 🧭 Why Start Here?

C is a low-level language that gives you **direct control over memory and hardware**. Unlike Python or JavaScript, C does not hold your hand — it expects you to understand exactly what you are telling the machine to do.

The fundamentals in this section are not just syntax exercises. They are the **mental models** you will rely on for every topic that follows. A shaky foundation here leads to mysterious bugs later.

---

## 📁 Topics in This Section

| # | Topic | Description | Status |
|---|-------|-------------|--------|
| 01 | [Variables & Data Types](./01_variables_and_data_types/README.md) | How C stores and labels data in memory | ⬜ Not started |
| 02 | [Conditionals](./02_conditionals/README.md) | Decision making with if/else and switch | ⬜ Not started |
| 03 | [Loops](./03_loops/README.md) | Repeating logic with for, while, do-while | ⬜ Not started |
| 04 | [Functions & Recursion](./04_functions_and_recursion/README.md) | Reusable blocks of logic, functions calling themselves | ⬜ Not started |
| 05 | [Arrays & Strings](./05_arrays_and_strings/README.md) | Collections of data, and how C handles text | ⬜ Not started |
| 06 | [Pointers & References](./06_pointers_and_references/README.md) | The most powerful — and dangerous — feature of C | ⬜ Not started |

---

## 🔗 How These Topics Connect

```
Variables & Data Types
        ↓
    store values that flow into
        ↓
  Conditionals & Loops
        ↓
    control logic organized into
        ↓
      Functions
        ↓
    which operate on
        ↓
  Arrays & Strings
        ↓
    accessed efficiently through
        ↓
       Pointers
```

Each topic builds directly on the one before it. **Do not skip ahead.**

---

## ⚙️ C Concepts Unique to This Section

These are things that trip up beginners coming from other languages:

### No Boolean Type (by default)
```c
// C uses integers for true/false
if (1)  { /* true  */ }
if (0)  { /* false */ }

// Or include stdbool.h for readability
#include <stdbool.h>
bool flag = true;
```

### No String Type
```c
// Strings are just arrays of characters
char name[] = "afhamuche";  // ends with invisible '\0'
```

### Manual Memory Awareness
```c
int x;              // declared but NOT initialized
printf("%d", x);    // ⚠️ undefined behavior — garbage value
```

### Functions Must Be Declared Before Use
```c
// ✅ Prototype declared at top
int add(int a, int b);

int main() {
    printf("%d", add(3, 4));
}

int add(int a, int b) {
    return a + b;
}
```

---

## 🛠️ How to Compile & Run Any Topic

```bash
# Single file
gcc main.c -o main && ./main

# With a separate implementation file
gcc main.c topic.c -o main && ./main

# With all warnings enabled (recommended while learning)
gcc -Wall -Wextra main.c -o main && ./main
```

> 💡 Always compile with `-Wall -Wextra` while learning. These flags surface hidden bugs and bad practices.

---

## 📌 Fundamentals Checklist

Use this as a self-assessment before moving to Data Structures:

- [ ] I can declare and initialize all primitive C types
- [ ] I understand the difference between `float` and `double`
- [ ] I can write if/else, nested conditions, and switch statements
- [ ] I know when to use `for` vs `while` vs `do-while`
- [ ] I can write and call functions with parameters and return values
- [ ] I understand what recursion is and can trace a recursive call
- [ ] I can declare, index, and iterate over arrays
- [ ] I understand that C strings are `char` arrays with `'\0'`
- [ ] I can declare a pointer, assign an address to it, and dereference it
- [ ] I understand the relationship between arrays and pointers

---

## 📚 Recommended Order

Work through the topics **in order**. Each one is a prerequisite for the next:

```
01 → 02 → 03 → 04 → 05 → 06
```

Once all 6 are complete, you are ready for **[02 — Data Structures](../02_data_structures/README.md)**.

---

*Back to [Repository Root](../README.md)*
