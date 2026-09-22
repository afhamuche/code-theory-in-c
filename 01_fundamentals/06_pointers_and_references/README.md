# 06 — Pointers & References in C

> The most powerful — and dangerous — feature of C.

---

## 🧠 What is a Pointer?

A **pointer** is a variable that stores a **memory address** instead of an ordinary value. Where a normal variable holds data directly, a pointer holds the *location* of where that data lives in memory.

```c
int age = 25;      /* an ordinary variable — holds the value 25 */
int *p = &age;      /* a pointer — holds the ADDRESS of age */
```

This is the concept both topic 04 (Functions & Recursion) and topic 05 (Arrays & Strings) kept pointing toward: pass-by-value couldn't modify a caller's variable, but arrays somehow could. The reason is pointers — arrays were secretly using them all along.

---

## 🔑 The Two Core Operators

| Operator | Name | Meaning |
|----------|------|---------|
| `&` | Address-of | Gets the memory address of a variable |
| `*` | Dereference | Gets (or sets) the value **at** an address |

```c
int age = 25;
int *p = &age;    /* p now holds the address of age */

printf("%d\n", age);    /* 25 — the value */
printf("%p\n", &age);   /* e.g. 0x7ffee3a1b45c — the address */
printf("%p\n", p);      /* same address — p stores it */
printf("%d\n", *p);     /* 25 — dereferencing p gets the value at that address */

*p = 30;                 /* dereferencing to WRITE — changes age itself */
printf("%d\n", age);    /* 30 — age was modified through the pointer! */
```

> ⚠️ `*` means two different things depending on context: in a **declaration** (`int *p`), it means "p is a pointer." In an **expression** (`*p`), it means "the value at the address p holds."

---

## 🗂️ Declaring Pointers

```c
int *p;        /* pointer to an int    */
float *fp;     /* pointer to a float   */
char *cp;      /* pointer to a char    */

int age = 25;
int *p = &age;  /* declare and initialize in one line */
```

### Pointer type must match

A pointer's type tells C how many bytes to read/write at that address, and how to interpret them. You generally can't point an `int *` at a `float`, or vice versa, without an explicit (and usually wrong) cast.

```c
int number = 10;
int *ptr = &number;   /* correct: int* points to an int */

float value = 3.14;
float *fptr = &value; /* correct: float* points to a float */
```

---

## 🕳️ NULL Pointers

A pointer that isn't pointing at anything valid should be set to `NULL` — a special value meaning "points to nothing."

```c
#include <stddef.h>   /* defines NULL */

int *p = NULL;

if (p == NULL) {
    printf("p is not pointing to anything.\n");
}
```

> ⚠️ Dereferencing a `NULL` pointer (`*p` when `p` is `NULL`) crashes the program (a **segmentation fault**). Always check a pointer isn't `NULL` before dereferencing it if there's any doubt.

---

## 🔁 Pointers and Functions: Fixing Pass-by-Value

Recall topic 04's `increment` function, which failed to modify the caller's variable:

```c
void increment(int x) {
    x = x + 1;   /* only changes the local copy */
}
```

With a pointer, the function receives the **address** of the caller's variable, and can modify it directly:

```c
void increment(int *x) {
    *x = *x + 1;   /* dereference — modifies the ORIGINAL variable */
}

int main(void) {
    int num = 5;
    increment(&num);          /* pass the ADDRESS of num */
    printf("%d\n", num);      /* 6 — actually changed! */
    return 0;
}
```

This is the standard C pattern for letting a function modify a caller's variable: **pass a pointer to it**.

---

## 📦 Pointers and Arrays

Topic 05 showed that arrays passed to functions can be modified by the function — this is because an array's name **decays into a pointer to its first element**.

```c
int numbers[3] = {10, 20, 30};
int *p = numbers;        /* no & needed — array name already IS an address */

printf("%d\n", *p);       /* 10 — first element */
printf("%d\n", *(p + 1)); /* 20 — pointer arithmetic: move 1 int forward */
printf("%d\n", *(p + 2)); /* 30 */

/* Array indexing is just pointer arithmetic in disguise */
printf("%d\n", numbers[1]);  /* 20 */
printf("%d\n", *(numbers + 1)); /* 20 — identical to numbers[1] */
```

> 💡 `arr[i]` and `*(arr + i)` are **exactly the same operation** in C. Array indexing is syntactic sugar over pointer arithmetic.

### Pointer arithmetic moves by element size, not by byte

```c
int nums[3] = {1, 2, 3};
int *p = nums;

p = p + 1;   /* moves forward by sizeof(int) bytes (4), not 1 byte */
printf("%d\n", *p);   /* 2 */
```

---

## 🔤 Pointers and Strings

Since a C string is a `char` array, a `char *` can point at one and be used to walk through it character by character.

```c
char word[] = "hello";
char *p = word;

while (*p != '\0') {
    printf("%c\n", *p);
    p++;              /* move to the next character */
}
```

---

## 🌐 Pointer to Pointer

A pointer can itself be pointed to — useful for functions that need to modify what a pointer points at (common in dynamic memory, topic 08).

```c
int age = 25;
int *p = &age;
int **pp = &p;    /* pointer to a pointer */

printf("%d\n", **pp);   /* 25 — dereference twice to reach the value */
```

---

## 🔃 Pointers vs Arrays — Similar, Not Identical

| Aspect | Array | Pointer |
|--------|-------|---------|
| Memory | Fixed block, allocated once | Just an address — can be reassigned |
| `sizeof` | Total size of the array | Size of the pointer itself (usually 8 bytes) |
| Reassignment | `arr = otherArr;` — **not allowed** | `p = otherPtr;` — allowed |
| Knows its own size? | Yes, at compile time | No — must be tracked separately |

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;

printf("%zu\n", sizeof(arr));   /* 20 — 5 ints × 4 bytes */
printf("%zu\n", sizeof(p));     /* 8  — just the pointer's own size */
```

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Dereferencing an uninitialized pointer | `int *p; printf("%d", *p);` | Always initialize pointers (`NULL` or a valid address) |
| Dereferencing `NULL` | `int *p = NULL; *p = 5;` | Check `if (p != NULL)` before dereferencing |
| Dangling pointer | Pointer still used after its target is freed/out of scope | Set pointer to `NULL` after freeing; don't return addresses of local variables |
| Mismatched pointer types | Pointing an `int *` at a `float` | Match the pointer's type to the data it points to |
| Confusing `&` and `*` | Mixing up "address of" with "value at" | `&` gets an address, `*` gets the value stored there |
| Pointer arithmetic out of bounds | Walking a pointer past the end of an array | Track array bounds carefully; stop at the correct size |
| Forgetting arrays decay to pointers | Assuming `sizeof(arr)` works the same inside a function | Pass array size explicitly as a parameter (topic 05) |

---

## 💡 Key Takeaways

- A pointer stores a memory address, not a value directly
- `&` gets an address; `*` dereferences an address to read or write the value there
- Pointers let functions modify a caller's variable — the fix for topic 04's pass-by-value limitation
- Arrays and pointers are closely related: an array's name decays into a pointer to its first element
- `arr[i]` and `*(arr + i)` are the same operation in C
- Always initialize pointers, and never dereference a `NULL` or uninitialized pointer
- Pointers are the foundation for dynamic memory allocation (topic 08) and data structures like linked lists (topic 20+)

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of pointers, addresses, dereferencing, and pointer/array relationships |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [05 — Arrays & Strings](../05_arrays_and_strings/README.md)*
*Next topic → [07 — Structs](../07_structs/README.md)*
