# 02 — Conditionals in C

> Teaching your program to make decisions based on conditions.

---

## 🧠 What is a Conditional?

A **conditional** is a statement that runs a block of code **only if a certain condition is true**. Without conditionals, every program would execute the same way every time — no decisions, no branching, no logic.

```c
if (score >= 50) {
    printf("You passed!\n");
} else {
    printf("You failed.\n");
}
```

---

## 🔑 How C Evaluates Conditions

In C, every condition evaluates to either:

| Result | Value | Meaning |
|--------|-------|---------|
| True   | Any non-zero integer | Condition is met |
| False  | `0` | Condition is not met |

```c
if (1)   { /* always runs    */ }
if (0)   { /* never runs     */ }
if (-42) { /* runs — non-zero */ }
```

> ⚠️ C has no native `true`/`false` — it uses integers. Include `<stdbool.h>` if you want readable `true` and `false`.

---

## 🗂️ Types of Conditionals in C

### 1. if statement

The simplest form — runs a block only when the condition is true.

```c
int age = 20;

if (age >= 18) {
    printf("Adult\n");
}
```

---

### 2. if / else statement

Runs one block if true, another if false.

```c
int temperature = 15;

if (temperature >= 25) {
    printf("It's warm\n");
} else {
    printf("It's cold\n");
}
```

---

### 3. if / else if / else chain

Checks multiple conditions in order — stops at the first true one.

```c
int score = 72;

if (score >= 90) {
    printf("Grade: A\n");
} else if (score >= 80) {
    printf("Grade: B\n");
} else if (score >= 70) {
    printf("Grade: C\n");
} else if (score >= 60) {
    printf("Grade: D\n");
} else {
    printf("Grade: F\n");
}
```

> ⚠️ Only the **first** matching block runs — even if multiple conditions are true.

---

### 4. Nested if statements

An `if` inside another `if`. Use carefully — deep nesting gets hard to read.

```c
int age = 20;
int has_id = 1;

if (age >= 18) {
    if (has_id) {
        printf("Entry allowed\n");
    } else {
        printf("No ID — entry denied\n");
    }
} else {
    printf("Too young — entry denied\n");
}
```

---

### 5. switch statement

Tests a single variable against multiple fixed values. Cleaner than a long `if/else if` chain when checking one variable.

```c
int day = 3;

switch (day) {
    case 1:
        printf("Monday\n");
        break;
    case 2:
        printf("Tuesday\n");
        break;
    case 3:
        printf("Wednesday\n");
        break;
    case 4:
        printf("Thursday\n");
        break;
    case 5:
        printf("Friday\n");
        break;
    default:
        printf("Weekend\n");
        break;
}
```

> ⚠️ Always include `break` — without it, execution **falls through** to the next case.

---

### 6. Ternary operator `? :`

A compact one-line conditional. Best for simple assignments — avoid for complex logic.

```c
// Syntax: condition ? value_if_true : value_if_false

int x = 10;
char *result = (x > 5) ? "big" : "small";
printf("%s\n", result);  /* → big */

/* Equivalent if/else: */
if (x > 5) {
    result = "big";
} else {
    result = "small";
}
```

---

## ⚖️ Comparison Operators

Used inside conditions to compare values:

| Operator | Meaning | Example | Result |
|----------|---------|---------|--------|
| `==` | Equal to | `5 == 5` | true |
| `!=` | Not equal to | `5 != 3` | true |
| `>`  | Greater than | `7 > 3` | true |
| `<`  | Less than | `2 < 9` | true |
| `>=` | Greater than or equal | `5 >= 5` | true |
| `<=` | Less than or equal | `4 <= 6` | true |

---

## 🔗 Logical Operators

Combine multiple conditions together:

| Operator | Meaning | Example | Result |
|----------|---------|---------|--------|
| `&&` | AND — both must be true | `age > 18 && has_id` | true only if both |
| `\|\|` | OR — at least one must be true | `isAdmin \|\| isOwner` | true if either |
| `!`  | NOT — flips true/false | `!is_done` | true if false |

```c
int age     = 22;
int has_id  = 1;
int is_vip  = 0;

if (age >= 18 && has_id) {
    printf("Entry allowed\n");
}

if (age >= 18 || is_vip) {
    printf("Special access\n");
}

if (!is_vip) {
    printf("Standard access only\n");
}
```

---

## 🔄 switch vs if/else — When to Use Which

| Situation | Use |
|-----------|-----|
| Comparing one variable to fixed values | `switch` |
| Ranges (`score >= 90`) | `if/else if` |
| Complex conditions with `&&` / `\|\|` | `if/else if` |
| Floating point comparisons | `if/else if` (switch doesn't support floats) |
| Simple two-way decision | `if/else` |
| One-liner assignment | ternary `? :` |

---

## 💥 switch Fall-Through

Without `break`, execution continues into the next case — sometimes intentional:

```c
int month = 4;
int days;

switch (month) {
    case 1: case 3: case 5: case 7:
    case 8: case 10: case 12:
        days = 31;
        break;
    case 4: case 6: case 9: case 11:
        days = 30;
        break;
    case 2:
        days = 28;
        break;
    default:
        days = -1;
}

printf("Days in month %d: %d\n", month, days);
```

> Here fall-through is **intentional** — multiple cases share the same result.

---

## ⚠️ Common Pitfalls

| Pitfall | Wrong | Right |
|---------|-------|-------|
| Assignment in condition | `if (x = 5)` — always true! | `if (x == 5)` |
| Missing braces | `if (x > 0) doA(); doB();` — doB always runs | Always use `{ }` |
| Missing `break` in switch | Falls through unintentionally | Add `break` to every case |
| Float in switch | `switch (3.14)` — not allowed | Use `if/else if` for floats |
| Comparing chars wrong | `if (c = 'A')` | `if (c == 'A')` |

---

## 💡 Key Takeaways

- `if/else` is the most fundamental decision tool in C
- C treats `0` as false and any non-zero as true
- `switch` is cleaner than long `if/else if` chains for fixed values
- Always use `break` in `switch` unless fall-through is intentional
- Never use `=` (assignment) where you mean `==` (comparison) — C won't warn you
- Use the ternary operator `? :` for simple, readable one-liners only

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of all conditional types |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [01 — Variables & Data Types](../01_variables_and_data_types/README.md)*
*Next topic → [03 — Loops](../03_loops/README.md)*