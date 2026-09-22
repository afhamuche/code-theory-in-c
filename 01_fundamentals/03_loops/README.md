# 03 — Loops in C

> Repeating logic with `for`, `while`, and `do-while`.

---

## 🧠 What is a Loop?

A **loop** is a control structure that repeats a block of code multiple times until a condition is no longer true. Without loops, you would have to write the same code over and over manually.

```c
/* Without a loop — tedious and unscalable */
printf("Hello\n");
printf("Hello\n");
printf("Hello\n");

/* With a loop — clean and scalable */
for (int i = 0; i < 3; i++) {
    printf("Hello\n");
}
```

---

## 🔑 Anatomy of a Loop

Every loop in C has three key parts:

| Part | Purpose | Example |
|------|---------|---------|
| **Initialization** | Set the starting state | `int i = 0` |
| **Condition** | Keep looping while true | `i < 10` |
| **Update** | Change state each iteration | `i++` |

---

## 🗂️ Types of Loops in C

### 1. for loop

Best when you know **exactly how many times** to repeat.

```c
/* Syntax */
for (initialization; condition; update) {
    /* body */
}

/* Example: print 0 to 4 */
for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
```

**How it executes:**
1. `int i = 0` — runs once at the start
2. `i < 5` — checked before every iteration
3. Body runs if condition is true
4. `i++` — runs after every iteration
5. Repeat from step 2

---

### 2. while loop

Best when you **don't know in advance** how many iterations are needed — loop continues while a condition holds.

```c
/* Syntax */
while (condition) {
    /* body */
}

/* Example: count down from 5 */
int count = 5;
while (count > 0) {
    printf("%d\n", count);
    count--;
}
```

> ⚠️ If the condition is never false, the loop runs forever — an **infinite loop**. Always make sure the condition can become false.

---

### 3. do-while loop

Like `while`, but the body runs **at least once** — the condition is checked *after* the first iteration.

```c
/* Syntax */
do {
    /* body */
} while (condition);

/* Example: ask for input until valid */
int number;
do {
    printf("Enter a number between 1 and 10: ");
    scanf("%d", &number);
} while (number < 1 || number > 10);

printf("Valid number: %d\n", number);
```

> 💡 Use `do-while` when the action must happen **before** you can check whether to continue — user input is the classic case.

---

## 🔁 Loop Control Statements

### break

Exits the loop immediately, regardless of the condition.

```c
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break;          /* stop the loop when i reaches 5 */
    }
    printf("%d\n", i);  /* prints 0 1 2 3 4 */
}
```

---

### continue

Skips the **rest of the current iteration** and jumps to the next one.

```c
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue;       /* skip even numbers */
    }
    printf("%d\n", i);  /* prints 1 3 5 7 9 */
}
```

---

### goto (avoid in practice)

Jumps to a labeled line in the code. Available in C but considered bad practice — breaks code readability. Use `break` or `continue` instead.

---

## 🔂 Nested Loops

A loop inside another loop. The inner loop completes fully for each iteration of the outer loop.

```c
/* Print a multiplication table */
for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
        printf("%d x %d = %d\n", i, j, i * j);
    }
}
```

Output:
```
1 x 1 = 1
1 x 2 = 2
1 x 3 = 3
2 x 1 = 2
...
```

> ⚠️ Be careful with nested loops — two nested loops of size `n` run `n²` times. Three nested loops run `n³` times. This matters for performance (Big O — topic 44).

---

## ♾️ Infinite Loops

A loop with a condition that never becomes false. Sometimes intentional (e.g. a server waiting for connections), but usually a bug.

```c
/* Intentional infinite loop — must break out manually */
while (1) {
    /* do something */
    if (done) break;
}

/* Common infinite loop patterns */
for (;;) { }        /* for loop with no condition */
while (1) { }       /* while with constant true   */
while (true) { }    /* same, with stdbool.h       */
```

---

## 🔃 for vs while vs do-while — When to Use Which

| Situation | Use |
|-----------|-----|
| Known number of iterations | `for` |
| Iterating over an array | `for` |
| Unknown iterations, check first | `while` |
| Reading until a condition | `while` |
| Must run at least once | `do-while` |
| User input validation | `do-while` |
| Event / game loop | `while (1)` or `for (;;)` |

---

## 📐 Common Loop Patterns

### Iterating over an array
```c
int arr[] = {10, 20, 30, 40, 50};
int len = 5;

for (int i = 0; i < len; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
}
```

### Summing an array
```c
int nums[] = {1, 2, 3, 4, 5};
int sum = 0;

for (int i = 0; i < 5; i++) {
    sum += nums[i];
}
printf("Sum = %d\n", sum);   /* → 15 */
```

### Iterating in reverse
```c
for (int i = 4; i >= 0; i--) {
    printf("%d\n", i);   /* → 4 3 2 1 0 */
}
```

### Stepping by more than 1
```c
for (int i = 0; i <= 10; i += 2) {
    printf("%d\n", i);   /* → 0 2 4 6 8 10 */
}
```

### Finding an element
```c
int arr[]  = {3, 7, 2, 9, 5};
int target = 9;
int found  = -1;

for (int i = 0; i < 5; i++) {
    if (arr[i] == target) {
        found = i;
        break;
    }
}

if (found != -1) {
    printf("Found %d at index %d\n", target, found);
} else {
    printf("%d not found\n", target);
}
```

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Off-by-one error | `for (i = 0; i <= 5; i++)` on array of 5 | Use `i < 5` not `i <= 5` |
| Infinite loop | `while (i < 10)` with no `i++` | Always update the loop variable |
| Modifying index inside loop | Changing `i` inside the body | Use a separate variable instead |
| Uninitialized loop variable | `int i; while (i < 10)` | Always initialize loop variables |
| Forgetting `break` in search | Loop keeps going after finding result | Use `break` once found |
| Empty `for` with semicolon | `for (i = 0; i < 10; i++);` — body is empty! | Never put `;` right after `for(...)` |

---

## 💡 Key Takeaways

- `for` is best when the number of iterations is known upfront
- `while` is best when the stop condition depends on runtime values
- `do-while` guarantees the body runs at least once
- `break` exits the loop immediately; `continue` skips to the next iteration
- Nested loops multiply execution time — be mindful of performance
- Always ensure your loop condition will eventually become false
- Off-by-one errors (`<` vs `<=`) are among the most common bugs in C

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of all loop types and patterns |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [02 — Conditionals](../02_conditionals/README.md)*
*Next topic → [04 — Functions & Recursion](../04_functions_and_recursion/README.md)*
