# 07 — Linked Lists in C

> Nodes connected by pointers instead of fixed array slots.

---

## 🧠 What is a Linked List?

A **linked list** is a chain of separate memory blocks called **nodes**, where each node holds some data and a **pointer to the next node**. Unlike an array, the elements don't have to sit next to each other in memory — they're connected purely by address, using exactly the pointer skills from topic 06.

```
[ 10 | next ] → [ 20 | next ] → [ 30 | next ] → NULL
```

```c
/* Array — fixed size, contiguous memory */
int arr[3] = {10, 20, 30};

/* Linked list — grows dynamically, scattered in memory */
struct Node {
    int data;
    struct Node *next;
};
```

---

## 🔑 Why Not Just Use an Array?

| | Array | Linked List |
|---|-------|-------------|
| Size | Fixed at declaration | Grows/shrinks at runtime |
| Memory layout | Contiguous | Scattered, connected by pointers |
| Insert/delete at front | Requires shifting every element | O(1) — just repoint a pointer |
| Random access (`arr[i]`) | O(1) — instant | O(n) — must walk from the head |
| Extra memory per element | None | One pointer per node |

Linked lists trade fast indexed access for cheap insertion and deletion — a tradeoff you'll see repeated throughout data structures.

---

## 🗂️ Defining a Node

```c
struct Node {
    int data;              /* the value stored in this node */
    struct Node *next;     /* pointer to the next node, or NULL if this is the last one */
};
```

This is a **self-referential struct** — a `struct Node` containing a pointer to another `struct Node`. It's the pattern topic 02's category README called out as the foundation for nearly everything in this section.

A linked list itself is usually just a single pointer, called the **head**, pointing at the first node:

```c
struct Node *head = NULL;   /* an empty list */
```

---

## 📦 Creating a Node with malloc

Nodes live on the **heap**, so they persist beyond the function that created them, and so the list can grow to any size at runtime.

```c
#include <stdlib.h>

struct Node *newNode = malloc(sizeof(struct Node));
if (newNode == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
}

newNode->data = 10;
newNode->next = NULL;
```

> 💡 `newNode->data` is shorthand for `(*newNode).data` — "dereference the pointer, then access the `data` field." The arrow operator `->` exists specifically because this pattern is so common with pointers to structs.

---

## 🔂 Inserting at the Head

```c
void insertAtHead(struct Node **head, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = *head;   /* new node points to the old first node */
    *head = newNode;         /* head now points to the new node */
}
```

> ⚠️ Notice the parameter is `struct Node **head` — a **pointer to a pointer**. The function needs to modify what `head` itself points at (topic 06), not just the node it currently points to. Passing `struct Node *head` here would only change a local copy of the head pointer, exactly like `badIncrement` in topic 06.

---

## ➕ Inserting at the Tail

```c
void insertAtTail(struct Node **head, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;   /* walk to the last node */
    }
    current->next = newNode;
}
```

---

## 🔍 Traversing a Linked List

```c
void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
```

Traversal always follows the same shape: start at `head`, follow `->next` until you hit `NULL`.

---

## 🗑️ Deleting a Node

```c
void deleteValue(struct Node **head, int value) {
    struct Node *current = *head;
    struct Node *previous = NULL;

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;   /* value not found */
    }

    if (previous == NULL) {
        *head = current->next;   /* deleting the head node */
    } else {
        previous->next = current->next;   /* skip over the found node */
    }

    free(current);   /* release its memory */
}
```

> ⚠️ Every node created with `malloc` must eventually be freed. A linked list that's never cleaned up leaks memory for as long as the program runs.

---

## 🧹 Freeing an Entire List

```c
void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;   /* save next before freeing current */
        free(current);
        current = next;
    }
}
```

> ⚠️ You must save `current->next` **before** calling `free(current)` — once a node is freed, reading any of its fields (including `->next`) is undefined behavior.

---

## 🔃 Singly vs Doubly Linked Lists

| Type | Structure | Tradeoff |
|------|-----------|----------|
| **Singly linked** | Each node points only `next` | Simple, less memory, can only walk forward |
| **Doubly linked** | Each node points `next` AND `prev` | Can walk backward, easier deletion, costs an extra pointer per node |

```c
struct DoublyNode {
    int data;
    struct DoublyNode *next;
    struct DoublyNode *prev;
};
```

This topic focuses on singly linked lists — the doubly linked variant is the same idea with one more pointer to maintain.

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Not checking `malloc`'s return value | Assuming allocation always succeeds | Always check `if (newNode == NULL)` |
| Memory leak | Losing the only pointer to a node without freeing it | Always `free()` nodes you're done with |
| Using freed memory | Reading `current->data` after `free(current)` | Save any needed data/pointers before freeing |
| Losing the head | Reassigning `head` without updating every reference to the list | Pass `struct Node **head` when a function must change the head |
| Forgetting to set `next = NULL` | A new tail node still pointing at garbage memory | Always initialize `next` explicitly |
| Dereferencing NULL | Calling `head->data` on an empty list | Check `if (head == NULL)` before accessing |

---

## 💡 Key Takeaways

- A linked list is a chain of nodes connected by pointers, not laid out contiguously like an array
- Each node is a self-referential `struct` holding data and a pointer to the next node
- Nodes are allocated on the heap with `malloc`, and must be released with `free`
- Modifying the head pointer itself requires a pointer-to-pointer (`struct Node **`), just like topic 06's fix for pass-by-value
- Traversal, insertion, and deletion are all built from the same "walk with a pointer until you hit `NULL`" pattern
- Linked lists trade array's fast indexing for cheap insertion/deletion at arbitrary positions

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of a singly linked list: insert, traverse, delete, and free |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [06 — Pointers & References](../../01_fundamentals/06_pointers_and_references/README.md)*
*Next topic → [08 — Stacks](../08_stacks/README.md)*
