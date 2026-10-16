# 11 — Binary Trees in C

> Hierarchical data with parent and child nodes.

---

## 🧠 What is a Binary Tree?

A **binary tree** is a hierarchical structure where each **node** holds a value and points to at most **two children** — conventionally called **left** and **right**. It's the first data structure in this repository that branches instead of just chaining in a line.

```
        10
       /  \
      5    15
     / \     \
    3   7     20
```

Compare the shapes so far: a linked list (topic 07) is a single chain — each node has exactly one `next`. A binary tree is that same self-referential-struct idea, but each node now has **two** outgoing pointers instead of one, which is what creates the branching shape.

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

---

## 🔑 Tree Vocabulary

| Term | Meaning |
|------|---------|
| **Root** | The topmost node (has no parent) |
| **Parent** | A node with one or more children |
| **Child** | A node pointed to by a parent |
| **Leaf** | A node with no children (`left` and `right` are both `NULL`) |
| **Subtree** | Any node and everything beneath it — itself a complete smaller tree |
| **Height** | The number of edges on the longest path from a node down to a leaf |
| **Depth** | The number of edges from the root down to a given node |

Every subtree is itself a valid binary tree — this self-similarity is exactly why tree algorithms are almost always written **recursively** (topic 04).

---

## 🗂️ Building a Tree Manually

Unlike a linked list, there isn't usually one single "insert" operation for a plain binary tree — you build it by explicitly connecting nodes. (Topic 12 — Binary Search Trees introduces a rule-based insert.)

```c
#include <stdlib.h>

struct TreeNode *createNode(int value) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Manually wiring up the tree from the diagram above */
struct TreeNode *root = createNode(10);
root->left = createNode(5);
root->right = createNode(15);
root->left->left = createNode(3);
root->left->right = createNode(7);
root->right->right = createNode(20);
```

> 💡 `createNode` is the same pattern as topic 07's node creation with `malloc` — the only difference is a tree node needs *two* pointers initialized to `NULL` instead of one.

---

## 🔁 Traversal: Visiting Every Node

"Traversal" means visiting every node in the tree exactly once. Because a tree branches, there's more than one sensible order to do that in — three classic ones, all built from the same recursive shape.

### In-order (Left, Node, Right)

```c
void inOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;   /* base case — topic 04's recursion lesson applies directly */
    }
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}
```

### Pre-order (Node, Left, Right)

```c
void preOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}
```

### Post-order (Left, Right, Node)

```c
void postOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->data);
}
```

Using the tree from the diagram above:

| Traversal | Order Visited | Output |
|-----------|-----------------|--------|
| In-order | left, node, right | `3 5 7 10 15 20` |
| Pre-order | node, left, right | `10 5 3 7 15 20` |
| Post-order | left, right, node | `3 7 5 20 15 10` |

> 💡 Notice all three functions have the exact base case (`if (node == NULL) return;`) and the exact same recursive calls (`inOrder(node->left)` / `inOrder(node->right)`) — only the **position** of the `printf` line changes. That one-line difference is the entire distinction between the three traversal orders.

---

## 📏 Measuring a Tree

```c
int height(struct TreeNode *node) {
    if (node == NULL) {
        return -1;   /* an empty tree has height -1; a single leaf has height 0 */
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int countNodes(struct TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}
```

Both functions follow the same shape as traversal: handle the `NULL` base case, recurse into both children, then combine the results. This "ask my children, then combine their answers" pattern is the core idea behind almost every tree algorithm you'll meet later (including topic 41 — Divide & Conquer).

---

## 🔍 Searching a Plain Binary Tree

A plain binary tree has **no ordering rule**, so finding a value means checking every node — there's no shortcut like topic 12's BST will give you.

```c
int contains(struct TreeNode *node, int target) {
    if (node == NULL) {
        return 0;   /* not found */
    }
    if (node->data == target) {
        return 1;   /* found */
    }
    return contains(node->left, target) || contains(node->right, target);
}
```

This is **O(n)** — same as searching an unsorted linked list — because the tree's shape alone gives no information about where a value might be.

---

## 🧹 Freeing a Tree

Just like topic 07's `freeList`, every `malloc`'d node must eventually be `free`'d. For a tree, the natural way to visit every node once is post-order: free the children before freeing the parent that points to them.

```c
void freeTree(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);   /* free the node only after both children are gone */
}
```

> ⚠️ Freeing a node *before* its children would lose the only pointers that let you reach them — exactly the same "save before you free" lesson from topic 07, just applied recursively.

---

## 🌍 Real-World Uses of Binary Trees

| Use Case | How Trees Apply |
|----------|-------------------|
| File systems | Folders containing folders — naturally hierarchical |
| Expression parsing | Compilers represent expressions as trees (operators as parent nodes) |
| Binary Search Trees (topic 12) | Ordered trees for fast search, insert, delete |
| Heaps (topic 13) | Specialized trees for fast min/max access |
| Decision trees | Branching logic, as in simple AI/ML models |

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Missing base case | A tree function with no `NULL` check | Every recursive tree function needs `if (node == NULL) return ...;` |
| Freeing in the wrong order | Freeing a node before its children | Free children first (post-order), same as topic 07's linked list rule |
| Forgetting to initialize `left`/`right` | A new node with garbage pointers instead of `NULL` | Always set both to `NULL` in `createNode` |
| Assuming a tree is sorted | Searching a plain binary tree expecting BST-style shortcuts | A plain binary tree has no ordering rule — that's topic 12 |
| Confusing height and depth | Using them interchangeably | Height measures down from a node; depth measures down from the root to a node |
| Stack overflow on very deep trees | Recursion depth exceeding the call stack | Recognize that very unbalanced trees can make recursion expensive (ties into topic 44 — Big O) |

---

## 💡 Key Takeaways

- A binary tree is a node with up to two children (`left` and `right`), built from the same self-referential struct pattern as topic 07's linked list
- Every subtree is itself a valid tree — this self-similarity is why tree code is almost always recursive
- The three traversal orders (in-order, pre-order, post-order) differ only in *where* you print relative to the two recursive calls
- Searching a plain (unordered) binary tree is O(n) — no shortcuts without an ordering rule
- Freeing a tree must happen post-order: children before parent, same logic as topic 07's node-freeing rule
- This topic lays the foundation for topic 12 (Binary Search Trees) and topic 13 (Heaps), which both add a rule on top of this same shape

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo: building a tree, all three traversals, height, node count, search, and freeing |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [10 — Hash Tables](../10_hash_tables/README.md)*
*Next topic → [12 — Binary Search Trees](../12_binary_search_trees/README.md)*
