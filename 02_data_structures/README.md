# 02 — Data Structures

> Organizing data efficiently. Fundamentals taught you how C stores a single value — this section teaches you how to structure many of them together.

---

## 🧭 Why This Section?

Every real program manages collections of data — contacts, transactions, routes, connections. **How** that data is organized determines how fast your program runs and how much memory it uses.

In [01 — Fundamentals](../01_fundamentals/README.md) you learned arrays and pointers. Data structures are what you build **with** pointers: linked lists, trees, graphs, and hash tables are all just clever arrangements of nodes connected by addresses. If topic 06 (Pointers) felt abstract, this section is where it becomes concrete and load-bearing — almost everything here is built out of `struct` and pointers working together.

---

## 📁 Topics in This Section

| # | Topic | Description |
|---|-------|-------------|
| 07 | [Linked Lists](./07_linked_lists/README.md) | Nodes connected by pointers instead of fixed array slots |
| 08 | [Stacks](./08_stacks/README.md) | Last-in, first-out (LIFO) data access |
| 09 | [Queues](./09_queues/README.md) | First-in, first-out (FIFO) data access |
| 10 | [Hash Tables](./10_hash_tables/README.md) | Key-value lookup using hashing for near-instant access |
| 11 | [Binary Trees](./11_binary_trees/README.md) | Hierarchical data with parent and child nodes |
| 12 | [Binary Search Trees](./12_binary_search_trees/README.md) | Ordered trees that make searching fast |
| 13 | [Heaps](./13_heaps/README.md) | Trees that always keep the min or max element on top |
| 14 | [Graphs](./14_graphs/README.md) | Nodes connected by arbitrary relationships, not just hierarchy |
| 15 | [Tries](./15_tries/README.md) | Trees specialized for storing and searching strings |
| 16 | [Segment Trees](./16_segment_trees/README.md) | Trees built for fast range queries over arrays |

---

## 🔗 How These Topics Connect

```
Linked Lists
    ↓
  the building block reused to make
    ↓
Stacks & Queues
    ↓
  scale up to key-value lookup via
    ↓
  Hash Tables
    ↓
  or branch out into hierarchy as
    ↓
  Binary Trees
    ↓
  ordered for fast search →  Binary Search Trees
  ordered for min/max     →  Heaps
    ↓
Graphs (trees generalized — cycles and arbitrary connections allowed)
    ↓
Tries (trees specialized for strings)
    ↓
Segment Trees (trees specialized for fast range queries)
```

Linked lists come first because nearly every structure after them — stacks, queues, trees, graphs — is a **node-and-pointer** idea at its core, just arranged differently. Master the node/pointer pattern once here, and everything after is a variation on it.

---

## ⚙️ C Concepts Unique to This Section

Data structures introduce ideas that fundamentals only hinted at:

### struct — Grouping Related Data

```c
struct Node {
    int data;
    struct Node *next;   /* a struct can point to another struct of its own type */
};
```

Every structure in this section is built from `struct`s that hold data and pointers to other `struct`s.

### Dynamic Memory Allocation

Fundamentals used fixed-size arrays. Data structures need to **grow and shrink at runtime**, which means allocating memory on the heap:

```c
#include <stdlib.h>

struct Node *newNode = malloc(sizeof(struct Node));
if (newNode == NULL) {
    /* allocation failed — always check */
}

/* ... use newNode ... */

free(newNode);   /* release it when done, or leak memory */
```

> ⚠️ Every `malloc` needs a matching `free`. Forgetting this causes a **memory leak** — a bug fundamentals-only programs never have to worry about.

### Self-Referential Structs

```c
struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

A `struct` containing a pointer to its own type is how trees, linked lists, and graphs all represent their connections — there is no special "tree" or "list" keyword in C, just this pattern applied differently.

### Recursion Returns, With a Purpose

Topic 04 (Recursion) comes back here with real teeth: traversing a tree, searching a BST, or walking a graph is naturally recursive, because each node's subtree has the exact same shape as the whole structure.

---

## 🛠️ How to Compile & Run Any Topic

```bash
# Single file
gcc main.c -o main -Wall -Wextra && ./main

# With a separate implementation file (common once structs grow large)
gcc main.c structure.c -o main -Wall -Wextra && ./main
```

> 💡 Consider running data-structure exercises through a memory checker like **valgrind** (Linux/Mac) once you're comfortable, to catch leaks and invalid memory access from `malloc`/`free` mistakes.

---

## 📌 Data Structures Checklist

Use this as a self-assessment before moving to Algorithms:

- [ ] I can define a `struct` and a self-referential `struct`
- [ ] I understand `malloc` and `free`, and always pair them
- [ ] I can build, traverse, and free a singly linked list
- [ ] I understand the LIFO behavior of a stack and FIFO behavior of a queue
- [ ] I can explain how a hash table maps a key to an index
- [ ] I can traverse a binary tree (in-order, pre-order, post-order)
- [ ] I understand why a BST makes search faster than an unordered tree
- [ ] I can explain the min-heap / max-heap property
- [ ] I understand the difference between a tree and a graph
- [ ] I know when a trie or segment tree is the right tool over a simpler structure

---

## 📚 Recommended Order

Work through the topics **in order**. Each one either reuses the previous topic's pattern or builds directly on it:

```
07 → 08 → 09 → 10 → 11 → 12 → 13 → 14 → 15 → 16
```

Once all 10 are complete, you are ready for **[03 — Algorithms](../03_algorithms/README.md)**.

---

*Back to [Repository Root](../README.md)*
*Previous section → [01 — Fundamentals](../01_fundamentals/README.md)*
