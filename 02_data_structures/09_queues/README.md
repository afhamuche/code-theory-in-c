# 09 — Queues in C

> First-in, first-out (FIFO) data access.

---

## 🧠 What is a Queue?

A **queue** is a data structure where the **first** element added is the **first** one removed — First-In, First-Out (**FIFO**). Picture a checkout line: whoever joined first gets served first, and new people join at the back.

```
Enqueue 10 → Enqueue 20 → Enqueue 30

Front → [ 10 ] [ 20 ] [ 30 ] ← Rear

Dequeue() → removes 10, returns it. Front is now 20.
```

This is the direct opposite of topic 08's stack (LIFO). Where a stack always removes the item added *most recently*, a queue always removes the item added *least recently*.

| | Stack | Queue |
|---|-------|-------|
| Order | LIFO | FIFO |
| Add | `push` (top) | `enqueue` (rear) |
| Remove | `pop` (top) | `dequeue` (front) |
| Real-world analogy | Stack of plates | Checkout line |

---

## 🔑 Core Queue Operations

| Operation | Purpose | Typical Return |
|-----------|---------|-----------------|
| `enqueue(value)` | Add an element to the **rear** | nothing (or success/failure) |
| `dequeue()` | Remove and return the element at the **front** | the removed value |
| `peek()` / `front()` | Look at the front element without removing it | the front value |
| `isEmpty()` | Check whether the queue has any elements | `true`/`false` |
| `isFull()` | (Array-based only) Check whether the queue has room | `true`/`false` |

A queue exposes **two** ends — insertion happens at the rear, removal happens at the front — unlike a stack, which only ever touches one end.

---

## 🗂️ Two Ways to Build a Queue in C

Just like stacks in topic 08, a queue is a *behavior*, not a fixed memory layout — it can be built on an array or a linked list.

### Option A: Array-based queue (circular buffer)

A naive array queue that just shifts every element forward after each `dequeue` is wasteful — O(n) per removal. The standard fix is a **circular buffer**, where the front and rear indices wrap around using modulo arithmetic instead of shifting data.

```c
#define MAX_SIZE 5

struct Queue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;   /* how many elements are currently in the queue */
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}
```

### Option B: Linked-list-based queue

```c
struct QueueNode {
    int data;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front;
    struct QueueNode *rear;
};
```

| | Pros | Cons |
|---|------|------|
| Array-based (circular) | Fast, no `malloc` overhead per element | Fixed maximum size |
| Linked-list-based | Grows dynamically, no fixed limit | Must track both `front` and `rear` pointers |

---

## 📦 Array-Based Queue (Circular Buffer): enqueue, dequeue, peek

```c
int isFull(struct Queue *q) {
    return q->count == MAX_SIZE;
}

int isEmpty(struct Queue *q) {
    return q->count == 0;
}

void enqueue(struct Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue overflow — cannot enqueue %d\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;   /* wrap around when reaching the end */
    q->data[q->rear] = value;
    q->count++;
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue underflow — nothing to dequeue\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;   /* wrap around when reaching the end */
    q->count--;
    return value;
}
```

> 💡 The `% MAX_SIZE` (modulo) is what makes the buffer "circular" — once `front` or `rear` reaches the last index, the next increment wraps back to `0` instead of running off the array. Without this, a naive array queue would either need to shift elements on every dequeue, or waste space it can never reuse.

---

## 🔗 Linked-List-Based Queue: enqueue, dequeue, peek

Enqueue adds at the **rear**; dequeue removes from the **front** — the opposite ends of the list, which is why this implementation needs to track both pointers.

```c
void enqueue(struct Queue *q, int value) {
    struct QueueNode *newNode = malloc(sizeof(struct QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        /* empty queue — new node is both front and rear */
        q->front = newNode;
        q->rear = newNode;
        return;
    }

    q->rear->next = newNode;   /* attach after the current rear */
    q->rear = newNode;          /* new node becomes the rear */
}

int dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("Queue underflow — nothing to dequeue\n");
        return -1;
    }

    struct QueueNode *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;   /* queue is now empty — reset rear too */
    }

    free(temp);
    return value;
}
```

> ⚠️ When the last node is dequeued, `q->front` becomes `NULL` — but `q->rear` would still be pointing at the freed node unless you explicitly reset it too. Forgetting this leaves a **dangling pointer**.

---

## 🔃 Tracing an Example

```
enqueue(10)  →  [10]
enqueue(20)  →  [10, 20]
enqueue(30)  →  [10, 20, 30]
dequeue()    →  returns 10   →  [20, 30]
peek()       →  returns 20   →  [20, 30]  (unchanged — peek doesn't remove)
dequeue()    →  returns 20   →  [30]
dequeue()    →  returns 30   →  []
dequeue()    →  underflow    →  []
```

---

## 🌍 Real-World Uses of Queues

| Use Case | How FIFO Applies |
|----------|-------------------|
| Print job spooling | Documents print in the order they were sent |
| CPU task scheduling | Processes handled in arrival order (or priority variants) |
| Breadth-First Search (BFS, topic 23) | Nodes explored level-by-level, in the order they're discovered |
| Message queues / event handling | Events processed in the order they occurred |
| Customer service / call centers | Callers served in the order they called |

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Queue overflow (array-based) | Enqueuing past `MAX_SIZE` | Always check `isFull()` before enqueuing |
| Queue underflow | Dequeuing or peeking an empty queue | Always check `isEmpty()` first |
| Forgetting circular wraparound | Using `rear + 1` instead of `(rear + 1) % MAX_SIZE` | Always apply modulo when advancing front/rear |
| Not resetting `rear` on empty (linked-list) | Dequeuing the last node without clearing `rear` | Set `rear = NULL` when `front` becomes `NULL` |
| Forgetting `free()` (linked-list-based) | `dequeue()` without freeing the removed node | Free the dequeued node after extracting its value |
| Confusing queue with stack | Expecting LIFO behavior from a queue | Queues are FIFO — the first thing in is the first thing out |

---

## 💡 Key Takeaways

- A queue is FIFO: the first element enqueued is the first one dequeued
- Core operations are `enqueue` (rear), `dequeue` (front), `peek`, and `isEmpty`
- An array-based queue needs a **circular buffer** (modulo arithmetic) to avoid wasteful shifting
- A linked-list-based queue must track both `front` and `rear` pointers, since insertion and removal happen at opposite ends
- Stacks and queues share the same core shape (add/remove/peek/isEmpty) but differ entirely in *which end* is used
- BFS, task scheduling, and print spooling all rely on FIFO (queue) behavior under the hood

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of both a circular-array-based and a linked-list-based queue |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [08 — Stacks](../08_stacks/README.md)*
*Next topic → [10 — Hash Tables](../10_hash_tables/README.md)*
