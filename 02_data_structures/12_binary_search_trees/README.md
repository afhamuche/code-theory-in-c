# 12 — Binary Search Trees in C

> Ordered trees that make searching fast.

---

## 🧠 What is a Binary Search Tree?

A **Binary Search Tree (BST)** is a binary tree (topic 11) with exactly one extra rule added on top: for every node, **everything in its left subtree is smaller**, and **everything in its right subtree is larger**.

```
        10
       /  \
      5    15
     / \     \
    3   7     20
```

This is the same tree shape from topic 11 — but now it isn't arbitrary. Check any node: `5`'s left child (`3`) is smaller, its right child (`7`) is larger. `10`'s left subtree (`5, 3, 7`) are all smaller than `10`, and its right subtree (`15, 20`) are all larger. That one consistent rule is what turns a plain tree into a BST.

> 💡 Notice: an **in-order traversal** of a BST always visits nodes in sorted order. Run `inOrder` from topic 11 on the tree above and you'll get `3 5 7 10 15 20` — perfectly sorted, for free, just from the ordering rule.

---

## 🔑 Why the Ordering Rule Matters

Topic 11 said searching a plain binary tree is **O(n)** — you have to check every node, because the shape alone tells you nothing about where a value might be.

A BST's ordering rule changes that completely. At every node, you can **eliminate half the remaining tree** with a single comparison:

```
Looking for 7 in the tree above:

10 → 7 < 10, go left
5  → 7 > 5, go right
7  → found!
```

Three comparisons found a value in a tree of six nodes — you never even looked at `15` or `20`. This is **O(log n)** on a reasonably balanced tree, the same logarithmic speedup behind topic 17's Binary Search, applied to a dynamic, growable structure instead of a sorted array.

---

## 📦 Inserting into a BST

Insertion follows the ordering rule: compare, go left or right, repeat until you find an empty spot.

```c
struct TreeNode *insert(struct TreeNode *node, int value) {
    if (node == NULL) {
        return createNode(value);   /* found the empty spot — insert here */
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    /* if value == node->data, it's a duplicate — do nothing */

    return node;
}
```

> 💡 Notice the pattern `node->left = insert(node->left, value);` — this is a common and slightly tricky idiom: the recursive call either returns the unchanged subtree, or returns a brand-new node when it hits `NULL`. Reassigning the result back onto `node->left` is what actually attaches the new node into the tree.

```c
struct TreeNode *root = NULL;
root = insert(root, 10);
root = insert(root, 5);
root = insert(root, 15);
root = insert(root, 3);
root = insert(root, 7);
root = insert(root, 20);
/* builds the exact same tree as topic 11 — but now by RULE, not by hand */
```

---

## 🔍 Searching a BST

This is where the payoff shows up directly — compare `search` here to `contains` from topic 11.

```c
int search(struct TreeNode *node, int target) {
    if (node == NULL) {
        return 0;   /* not found */
    }
    if (target == node->data) {
        return 1;   /* found */
    }
    if (target < node->data) {
        return search(node->left, target);    /* only go ONE direction */
    }
    return search(node->right, target);
}
```

Topic 11's `contains` had to check **both** `node->left` and `node->right` on every call (`contains(left) || contains(right)`), because a plain tree gives no hints. A BST's `search` only ever recurses into **one** side — the ordering rule tells you exactly which half to discard.

---

## 🗑️ Deleting from a BST

Deletion is the trickiest BST operation, because removing a node must preserve the ordering rule for everything left behind. There are three cases:

```c
struct TreeNode *findMin(struct TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;   /* leftmost node = smallest value */
    }
    return node;
}

struct TreeNode *deleteNode(struct TreeNode *node, int value) {
    if (node == NULL) {
        return NULL;   /* value not found */
    }

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        /* found the node to delete */

        if (node->left == NULL) {          /* Case 1: no children, or only a right child */
            struct TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {   /* Case 2: only a left child */
            struct TreeNode *temp = node->left;
            free(node);
            return temp;
        }

        /* Case 3: two children — replace with the smallest value in the right subtree */
        struct TreeNode *successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }

    return node;
}
```

| Case | Situation | Strategy |
|------|-----------|----------|
| 1 | Node has no left child (0 or 1 children) | Replace the node with its right child (or `NULL`) |
| 2 | Node has no right child (1 child) | Replace the node with its left child |
| 3 | Node has two children | Replace its value with its **in-order successor** (smallest value in the right subtree), then delete that successor instead |

> ⚠️ Case 3 is the one that trips people up: you don't just unlink the node — you copy a value up from elsewhere, then recursively delete the *original location* of that value, which is now guaranteed to fall into Case 1 or 2.

---

## 📈 Why "On Average" — BST Performance

| Scenario | Search / Insert / Delete |
|----------|-----------------------------|
| Balanced tree (left/right subtrees roughly equal size) | O(log n) |
| Unbalanced tree (e.g., inserting sorted data: 1, 2, 3, 4, 5...) | O(n) — degrades into a linked list |

Inserting already-sorted values into a plain BST produces a tree that only ever grows to one side:

```
insert(1), insert(2), insert(3), insert(4) →

1
 \
  2
   \
    3
     \
      4
```

This is a valid BST (the ordering rule still holds), but it has no branching left — every operation becomes O(n), identical to topic 07's linked list. **Self-balancing trees** (AVL trees, red-black trees) solve this by automatically restructuring during insertion, but implementing one is beyond this topic — it's worth knowing the name and the problem it solves, the same way topic 10 flagged open addressing without implementing it.

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Forgetting to reassign on insert | Calling `insert(node->left, value);` without `node->left =` | The reassignment is what actually attaches the new node |
| Breaking the ordering rule | Inserting without comparing, or comparing with the wrong operator | Always route left for smaller, right for larger |
| Searching like a plain tree | Recursing into both `left` and `right` in `search` | A BST only needs to recurse into one side per comparison |
| Mishandling two-child deletion | Just removing the node and orphaning its children | Replace with the in-order successor (or predecessor), then delete that |
| Assuming O(log n) always | Inserting sorted data and expecting fast operations | A BST degrades to O(n) when unbalanced — sorted insertion is the worst case |
| Confusing BST property with heap property | Expecting the root to always be the min or max | A BST orders left-vs-right; a heap (topic 13) orders parent-vs-child instead |

---

## 💡 Key Takeaways

- A BST is a binary tree (topic 11) with one added rule: left subtree smaller, right subtree larger
- That single rule turns O(n) search (topic 11's `contains`) into O(log n) search, by letting you discard half the tree at every step
- In-order traversal of a BST always produces sorted output
- Insertion and search both follow the same "compare, then go exactly one direction" pattern
- Deletion has three cases, with the two-children case (replace with the in-order successor) being the one to study carefully
- A BST's speed is only guaranteed when it stays reasonably balanced — sorted-order insertion is the worst case, degrading to O(n)

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo: insert, search, in-order traversal (sorted output), and delete covering all three cases |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [11 — Binary Trees](../11_binary_trees/README.md)*
*Next topic → [13 — Heaps](../13_heaps/README.md)*
