# 05 — Arrays & Strings in C

> Collections of data, and how C handles text.

---

## 🧠 What is an Array?

An **array** is a fixed-size collection of elements, all of the **same type**, stored in **contiguous memory**. Instead of creating separate variables for related data, you group them under one name and access each by an **index**.

```c
/* Without an array — unscalable */
int score1 = 90;
int score2 = 85;
int score3 = 78;

/* With an array — clean and scalable */
int scores[3] = {90, 85, 78};
```

---

## 🔑 Anatomy of an Array

```c
type name[size] = {values};
```

| Part | Purpose | Example |
|------|---------|---------|
| **Type** | Type of every element in the array | `int`, `float`, `char` |
| **Name** | How you refer to the array | `scores`, `grades` |
| **Size** | Number of elements it can hold | `[5]` |
| **Index** | Position of an element, starting at **0** | `scores[0]` is the first element |

```c
int scores[5] = {90, 85, 78, 92, 88};

printf("%d\n", scores[0]);   /* 90 — first element */
printf("%d\n", scores[4]);   /* 88 — last element (size - 1) */
```

> ⚠️ C arrays are **zero-indexed**. An array of size `5` has valid indices `0` through `4` — there is no `scores[5]`.

---

## 🗂️ Declaring & Initializing Arrays

```c
/* Declare with a fixed size, no values yet (garbage values inside) */
int numbers[5];

/* Declare and initialize fully */
int numbers[5] = {1, 2, 3, 4, 5};

/* Let the compiler count the size from the values */
int numbers[] = {1, 2, 3, 4, 5};   /* size is automatically 5 */

/* Partial initialization — remaining elements default to 0 */
int numbers[5] = {1, 2};   /* → {1, 2, 0, 0, 0} */

/* All elements set to 0 */
int numbers[5] = {0};
```

---

## 📦 Accessing & Modifying Elements

```c
int numbers[5] = {10, 20, 30, 40, 50};

/* Read an element */
printf("%d\n", numbers[2]);   /* 30 */

/* Modify an element */
numbers[2] = 99;
printf("%d\n", numbers[2]);   /* 99 */

/* Get the size of an array (in elements) */
int length = sizeof(numbers) / sizeof(numbers[0]);
printf("Length: %d\n", length);   /* 5 */
```

> 💡 `sizeof(array)` gives the **total bytes**, not the element count. Dividing by `sizeof(array[0])` (the size of one element) gives you the actual number of elements.

---

## 🔂 Looping Through Arrays

Arrays and loops (topic 03) go hand in hand — a `for` loop is the standard way to visit every element.

```c
int numbers[5] = {10, 20, 30, 40, 50};

for (int i = 0; i < 5; i++) {
    printf("numbers[%d] = %d\n", i, numbers[i]);
}
```

---

## 🌐 Multidimensional Arrays

An array of arrays — commonly used for grids, tables, and matrices.

```c
/* 2D array: 3 rows, 4 columns */
int grid[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

printf("%d\n", grid[1][2]);   /* 7 — row 1, column 2 */

/* Looping through a 2D array needs nested loops */
for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 4; col++) {
        printf("%d ", grid[row][col]);
    }
    printf("\n");
}
```

---

## 🔤 Strings in C

C has **no built-in string type**. A string is simply a **`char` array** ending with a special **null terminator** `'\0'`, which marks where the string stops.

```c
char name1[] = "afhamuche";           /* compiler adds '\0' automatically */
char name2[] = {'C', 'l', 'a', 'u', 'd', 'e', '\0'};   /* same idea, manual */

printf("%s\n", name1);   /* "afhamuche" */
```

> ⚠️ Without the null terminator, C has no way of knowing where a string ends — functions like `printf("%s", ...)` will keep reading memory past the array until they happen to hit a `\0`, which is undefined behavior.

### String size vs string length

```c
char word[20] = "hello";

printf("%zu\n", sizeof(word));        /* 20  — total bytes reserved */
printf("%zu\n", strlen(word));        /* 5   — characters before '\0' */
```

---

## 🧰 Common String Functions (`<string.h>`)

| Function | Purpose | Example |
|----------|---------|---------|
| `strlen(s)` | Length of string (excludes `\0`) | `strlen("hi")` → `2` |
| `strcpy(dest, src)` | Copy a string | `strcpy(buf, "hello")` |
| `strcat(dest, src)` | Append a string | `strcat(buf, " world")` |
| `strcmp(a, b)` | Compare two strings (0 = equal) | `strcmp("cat", "cat")` → `0` |
| `strncpy` / `strncat` | Safer, length-limited versions | Prevents buffer overrun |

```c
#include <string.h>

char greeting[50] = "Hello";
strcat(greeting, ", afhamuche!");
printf("%s\n", greeting);   /* "Hello, afhamuche!" */

if (strcmp(greeting, "Hello, afhamuche!") == 0) {
    printf("Strings match!\n");
}
```

> ⚠️ Never compare strings with `==` — that compares memory addresses, not contents. Always use `strcmp`.

---

## 🔗 Arrays and Functions

Arrays are passed to functions as a **pointer to their first element** — not a full copy. This means a function *can* modify the caller's array directly, unlike ordinary variables (topic 04's pass-by-value rule doesn't apply the same way here).

```c
void doubleValues(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] * 2;
    }
}

int main(void) {
    int nums[3] = {1, 2, 3};
    doubleValues(nums, 3);
    printf("%d %d %d\n", nums[0], nums[1], nums[2]);  /* 2 4 6 — original changed! */
    return 0;
}
```

> 💡 Because only a pointer is passed, the function has no way to know the array's size on its own — you must always pass the size as a separate parameter, as shown above.

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Out-of-bounds access | `int arr[5]; arr[5] = 1;` | Valid indices are `0` to `size - 1` |
| Missing null terminator | Building a char array manually without `'\0'` | Always terminate strings with `'\0'` |
| Comparing strings with `==` | `if (str1 == str2)` | Use `strcmp(str1, str2) == 0` |
| Buffer overflow with `strcpy`/`strcat` | Copying a string longer than the destination array | Use `strncpy`/`strncat`, or size buffers generously |
| Confusing `sizeof` with `strlen` | Using `sizeof(str)` to get character count | `sizeof` = bytes reserved, `strlen` = characters before `\0` |
| Assuming array size inside a function | `sizeof(arr)` inside a function that received `arr[]` | Pass the size explicitly as a parameter |
| Uninitialized array elements | Reading `numbers[5]` from `int numbers[5];` before assigning it | Always initialize before reading |

---

## 💡 Key Takeaways

- An array is a fixed-size, same-type, contiguous block of memory, accessed by index
- Indices start at `0`; the last valid index is `size - 1`
- `sizeof(array) / sizeof(array[0])` gives the element count of a full array
- Multidimensional arrays are arrays of arrays, accessed with `arr[row][col]`
- C strings are `char` arrays terminated with `'\0'` — there is no built-in string type
- Use `<string.h>` functions (`strlen`, `strcpy`, `strcat`, `strcmp`) instead of manual loops for common string tasks
- Arrays passed to functions decay to a pointer — the function can modify the original, but doesn't know its size unless you pass it separately

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of arrays, multidimensional arrays, and string handling |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [04 — Functions & Recursion](../04_functions_and_recursion/README.md)*
*Next topic → [06 — Pointers](../06_pointers/README.md)*
