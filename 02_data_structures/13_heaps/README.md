# 13 — Heaps in C

> Trees that always keep the min or max element on top.

---

## 🧠 What is a Heap?

A **heap** is a binary tree (topic 11) with a different ordering rule than a BST (topic 12). Where a BST orders **left vs. right** (smaller left, larger right), a heap orders **parent vs. child**:

- **Min-heap**: every parent is **smaller** than its children — the smallest value is always at the root
- **Max-heap**: every parent is **larger** than its children — the largest value is always at the root

```
Min-heap example:

        3
       / \
      5   8
     / \
    10  7
```

Notice `3` (the root) is smaller than both `5` and `8`. `5` is smaller than both `10` and `7`. There's **no rule at all between siblings** — `10` and `7` aren't ordered relative to each other, and `5` isn't necessarily smaller than `8`. This is a much weaker rule than a BST's, and that weaker rule is exactly what makes heaps fast at the one thing they're built for: **always knowing the min (or max) instantly**.

---

## 🔑 Why Not Just Use a BST?

| | BST | Heap |
|---|-----|------|
| Finding the min/max | O(log n) — walk down one side | O(1) — it's always the root |
| Finding an arbitrary value | O(log n) | O(n) — no left/right ordering to search by |
| Shape | Can become unbalanced (topic 12) | Always a **complete** tree — no unbalancing possible |

A heap trades away "can search for anything" to gain "min/max is always instant." That trade is exactly what you want for priority queues, scheduling, and the `*Sort` and graph algorithms coming later (topics 21, 24, 25).

---

## 🗂️ The Complete Tree Rule — and Why Heaps Use an Array

A heap must always be a **complete binary tree**: every level is fully filled, except possibly the last, which fills **left to right** with no gaps.

```
        3
       / \
      5   8
     / \
    10  7

Complete: yes - last level (10, 7) fills left to right, no gaps.
```

Because the shape is always this predictable, a heap doesn't need `malloc`'d nodes and `left`/`right` pointers at all — the whole tree fits neatly into a plain **array**, with parent/child relationships computed by index arithmetic instead of followed through pointers:

```c
#define MAX_SIZE 100

struct MinHeap {
    int data[MAX_SIZE];
    int size;
};
```

For a node at index `i`:

| Relationship | Formula |
|--------------|---------|
| Left child | `2 * i + 1` |
| Right child | `2 * i + 2` |
| Parent | `(i - 1) / 2` (integer division) |

```
Array: [3, 5, 8, 10, 7]
Index:  0  1  2  3   4

index 0 (value 3): left child = index 1 (5), right child = index 2 (8)
index 1 (value 5): left child = index 3 (10), right child = index 4 (7)
```

Same tree as the diagram above — just stored flat. This is a direct callback to topic 05's array fundamentals: no pointers, no self-referential structs, just arithmetic on indices.

---

## ⬆️ Inserting: Bubble Up (Sift Up)

To insert, add the new value at the **next open spot** (the end of the array, keeping it complete), then **swap it upward** with its parent until the ordering rule is satisfied again.

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(struct MinHeap *heap, int value) {
    if (heap->size == MAX_SIZE) {
        printf("Heap overflow - cannot insert %d\n", value);
        return;
    }

    int i = heap->size;
    heap->data[i] = value;   /* place at the next open spot */
    heap->size++;

    /* bubble up while smaller than parent */
    while (i > 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
```

---

## ⬇️ Removing the Min: Bubble Down (Sift Down / Heapify)

The only element you ever remove from a heap is the **root** (the min or max). To do it without breaking the complete-tree shape:

1. Save the root's value to return
2. Move the **last** element into the root position
3. Shrink the array by one
4. **Bubble that element down**, repeatedly swapping with its smaller child, until the ordering rule holds again

```c
void heapifyDown(struct MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapifyDown(heap, smallest);   /* recurse down the path we just swapped into */
    }
}

int extractMin(struct MinHeap *heap) {
    if (heap->size == 0) {
        printf("Heap underflow - nothing to extract\n");
        return -1;
    }

    int min = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];   /* move last element to root */
    heapifyDown(heap, 0);

    return min;
}
```

> 💡 `heapifyDown` is recursive, following the same shape you've seen since topic 11: check a base case (no swap needed), then recurse — here, recursing *down the specific branch* the swap just moved into, rather than into both children like topic 11's traversals did.

---

## 🔃 Tracing an Example

```
insert(5)  -> [5]
insert(3)  -> [3, 5]              (3 bubbles above 5)
insert(8)  -> [3, 5, 8]
insert(1)  -> [1, 3, 8, 5]        (1 bubbles all the way to the root)

extractMin() -> returns 1
  last element (5) moves to root: [5, 3, 8]
  5 bubbles down below 3:        [3, 5, 8]
  returns 1
```

---

## 👀 peek() — Looking at the Min Without Removing

```c
int peek(struct MinHeap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty\n");
        return -1;
    }
    return heap->data[0];   /* the min is always the root */
}
```

This is **O(1)** — no traversal needed at all, which is the entire reason heaps exist.

---

## 🌍 Real-World Uses of Heaps

| Use Case | Why a Heap Fits |
|----------|-------------------|
| Priority queues | Always process the highest-priority (min or max) item next |
| Heap Sort (topic 21) | Repeatedly extract the min/max to produce sorted output |
| Dijkstra's Algorithm (topic 24) | Always expand the closest unvisited node next |
| A* Search (topic 25) | Always expand the most promising node next |
| Task scheduling | Run the most urgent task first |
| Finding the k largest/smallest elements | A heap of size k tracks the answer without sorting everything |

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Confusing heap property with BST property | Expecting `data[left] < data[i] < data[right]` ordering | A heap only orders parent-vs-child, never left-vs-right or between siblings |
| Breaking the complete-tree shape | Removing from the middle of the array instead of the root | Only ever remove the root; always refill from the last element |
| Wrong index arithmetic | Using `2*i` instead of `2*i + 1` for the left child | Left = `2i+1`, right = `2i+2`, parent = `(i-1)/2` |
| Forgetting to bubble after insert/extract | Placing a value without sifting up or down | Every insert needs `heapifyUp`; every extract needs `heapifyDown` |
| Mixing up min-heap and max-heap comparisons | Using `<` where `>` was intended | Decide min-heap or max-heap up front, and keep every comparison consistent with it |
| Heap overflow (array-based, fixed size) | Inserting past `MAX_SIZE` | Always check capacity before inserting, same as topic 08's array stack |

---

## 💡 Key Takeaways

- A heap orders parent-vs-child (min-heap: parent smaller; max-heap: parent larger) — a much looser rule than a BST's left-vs-right ordering
- A heap is always a **complete** binary tree, which lets it be stored in a plain array using index math instead of pointers
- Left child = `2i+1`, right child = `2i+2`, parent = `(i-1)/2`
- Insert places at the end and bubbles up; extract replaces the root with the last element and bubbles down
- `peek()` (reading the min/max) is O(1) — the entire point of a heap
- Heaps power priority queues, Heap Sort, and the shortest-path algorithms coming in topics 21, 24, and 25

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of an array-based min-heap: insert, extractMin, peek, and tracing the heap's contents at each step |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [12 — Binary Search Trees](../12_binary_search_trees/README.md)*
*Next topic → [14 — Graphs](../14_graphs/README.md)*
