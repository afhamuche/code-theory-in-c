# 08 — Stacks in C

> Last-in, first-out (LIFO) data access.

---

## 🧠 What is a Stack?

A **stack** is a data structure where the **last** element added is the **first** one removed — Last-In, First-Out (**LIFO**). Picture a stack of plates: you place new plates on top, and you always take the top plate off first. You can't grab a plate from the middle without removing everything above it.

```
Push 10 → Push 20 → Push 30

   Top → [ 30 ]
         [ 20 ]
         [ 10 ]

Pop() → removes 30, returns it. Top is now 20.
```

Real examples of LIFO behavior: your browser's "back" button, the undo feature in a text editor, and — critically — **function calls themselves**, which are tracked on a **call stack** (the exact mechanism that made recursion in topic 04 work).

---

## 🔑 Core Stack Operations

| Operation | Purpose | Typical Return |
|-----------|---------|-----------------|
| `push(value)` | Add an element to the top | nothing (or success/failure) |
| `pop()` | Remove and return the top element | the removed value |
| `peek()` / `top()` | Look at the top element without removing it | the top value |
| `isEmpty()` | Check whether the stack has any elements | `true`/`false` |
| `isFull()` | (Array-based only) Check whether the stack has room | `true`/`false` |

A stack only ever exposes its **top** — there's no way to reach into the middle without popping everything above it first.

---

## 🗂️ Two Ways to Build a Stack in C

A stack is a *behavior* (LIFO access), not a specific memory layout — you can implement it with either an array or a linked list.

### Option A: Array-based stack

```c
#define MAX_SIZE 100

struct Stack {
    int data[MAX_SIZE];
    int top;   /* index of the current top element, -1 means empty */
};

void initStack(struct Stack *s) {
    s->top = -1;
}
```

| | Pros | Cons |
|---|------|------|
| Array-based | Simple, fast, no `malloc` overhead per element | Fixed maximum size, must check `isFull()` |

### Option B: Linked-list-based stack

```c
struct StackNode {
    int data;
    struct StackNode *next;
};

struct StackNode *top = NULL;   /* an empty stack */
```

| | Pros | Cons |
|---|------|------|
| Linked-list-based | Grows dynamically, no fixed limit | Slight overhead per node (pointer + malloc) |

This topic implements both, since the tradeoff between "fixed-size but simple" and "dynamic but pointer-based" is one you'll weigh constantly in later topics.

---

## 📦 Array-Based Stack: push, pop, peek

```c
void push(struct Stack *s, int value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack overflow — cannot push %d\n", value);
        return;
    }
    s->top++;
    s->data[s->top] = value;
}

int pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow — nothing to pop\n");
        return -1;   /* sentinel value indicating failure */
    }
    int value = s->data[s->top];
    s->top--;
    return value;
}

int peek(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack is empty\n");
        return -1;
    }
    return s->data[s->top];
}

int isEmpty(struct Stack *s) {
    return s->top == -1;
}
```

> ⚠️ Pushing onto a full array-based stack is called a **stack overflow**; popping an empty stack is a **stack underflow**. Both must be checked explicitly — C won't stop you from reading or writing out of bounds.

---

## 🔗 Linked-List-Based Stack: push, pop, peek

Pushing and popping both happen at the **head** — the same O(1) operation as `insertAtHead` from topic 07.

```c
void push(struct StackNode **top, int value) {
    struct StackNode *newNode = malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct StackNode **top) {
    if (*top == NULL) {
        printf("Stack underflow — nothing to pop\n");
        return -1;
    }
    struct StackNode *temp = *top;
    int value = temp->data;
    *top = temp->next;
    free(temp);
    return value;
}

int peek(struct StackNode *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}
```

> 💡 Notice `push` takes `struct StackNode **top` — a pointer to a pointer — for the same reason `insertAtHead` did in topic 07: the function must change what `top` itself points at.

---

## 🔃 Tracing an Example

```
push(10)  →  [10]
push(20)  →  [10, 20]
push(30)  →  [10, 20, 30]
pop()     →  returns 30   →  [10, 20]
peek()    →  returns 20   →  [10, 20]  (unchanged — peek doesn't remove)
pop()     →  returns 20   →  [10]
pop()     →  returns 10   →  []
pop()     →  underflow    →  []
```

---

## 🌍 Real-World Uses of Stacks

| Use Case | How LIFO Applies |
|----------|-------------------|
| Function call stack | Each function call is "pushed"; returning "pops" it |
| Undo/redo in editors | Each action pushed; undo pops the most recent |
| Browser back button | Each visited page pushed; back pops the most recent |
| Expression evaluation | Parentheses matching, converting infix to postfix |
| Backtracking algorithms | Explore a path, push state, pop to backtrack (topic 42) |

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Stack overflow (array-based) | Pushing past `MAX_SIZE` | Always check `isFull()` before pushing |
| Stack underflow | Popping or peeking an empty stack | Always check `isEmpty()` first |
| Forgetting `free()` (linked-list-based) | `pop()` without freeing the removed node | Free the popped node after extracting its value |
| Confusing stack with queue | Expecting FIFO behavior from a stack | Stacks are LIFO — the last thing in is the first thing out |
| Not initializing `top` | Using a `struct Stack` with garbage `top` value | Always call `initStack()` (or set `top = -1` / `top = NULL`) first |
| Returning a sentinel without checking it | Treating `pop()`'s `-1` as a real value | Check `isEmpty()` before trusting the returned value |

---

## 💡 Key Takeaways

- A stack is LIFO: the last element pushed is the first one popped
- Core operations are `push`, `pop`, `peek`, and `isEmpty`
- A stack can be implemented with a fixed-size array or a linked list — same behavior, different tradeoffs
- Array-based stacks must check for overflow; both implementations must check for underflow
- The linked-list version reuses topic 07's head-insertion pattern and its `struct Node **` requirement
- Function calls, undo/redo, and backtracking all rely on stack (LIFO) behavior under the hood

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of both an array-based and a linked-list-based stack |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [07 — Linked Lists](../07_linked_lists/README.md)*
*Next topic → [09 — Queues](../09_queues/README.md)*
