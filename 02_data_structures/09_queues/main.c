/*
 * 09 — Queues in C
 * Demonstrates: FIFO behavior using both a circular-array-based queue and
 * a linked-list-based queue, including enqueue, dequeue, peek, isEmpty,
 * overflow, and underflow handling.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5   /* small on purpose, so we can actually trigger overflow */

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ---------- Array-based queue (circular buffer) ---------- */

struct ArrayQueue {
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;
};

void initArrayQueue(struct ArrayQueue *q);
int isFullArray(struct ArrayQueue *q);
int isEmptyArray(struct ArrayQueue *q);
void enqueueArray(struct ArrayQueue *q, int value);
int dequeueArray(struct ArrayQueue *q);
int peekArray(struct ArrayQueue *q);

/* ---------- Linked-list-based queue ---------- */

struct QueueNode {
    int data;
    struct QueueNode *next;
};

struct Queue {
    struct QueueNode *front;
    struct QueueNode *rear;
};

void initQueue(struct Queue *q);
void enqueue(struct Queue *q, int value);
int dequeue(struct Queue *q);
int peek(struct Queue *q);
int isEmptyList(struct Queue *q);
void freeQueue(struct Queue *q);

int main(void) {

    /* ========== ARRAY-BASED QUEUE (CIRCULAR BUFFER) ========== */

    section("1. array-based queue: enqueue");
    struct ArrayQueue arrQueue;
    initArrayQueue(&arrQueue);

    enqueueArray(&arrQueue, 10);
    enqueueArray(&arrQueue, 20);
    enqueueArray(&arrQueue, 30);
    printf("Enqueued 10, 20, 30. Front is now: %d\n", peekArray(&arrQueue));

    section("2. array-based queue: dequeue");
    printf("dequeue() -> %d\n", dequeueArray(&arrQueue));
    printf("peek() -> %d  (unchanged by peek, new front after dequeue)\n", peekArray(&arrQueue));
    printf("dequeue() -> %d\n", dequeueArray(&arrQueue));

    section("3. array-based queue: circular wraparound");
    /* front/rear will wrap around the fixed-size array here */
    enqueueArray(&arrQueue, 40);
    enqueueArray(&arrQueue, 50);
    enqueueArray(&arrQueue, 60);   /* rear wraps back to index 0 */
    printf("Enqueued 40, 50, 60 after two dequeues — rear wrapped around.\n");
    printf("Current front: %d\n", peekArray(&arrQueue));

    section("4. array-based queue: overflow");
    enqueueArray(&arrQueue, 999);   /* fills the queue to exactly MAX_SIZE */
    printf("Queue full? %s\n", isFullArray(&arrQueue) ? "yes" : "no");
    enqueueArray(&arrQueue, 111);   /* now genuinely triggers overflow */

    section("5. array-based queue: draining and underflow");
    while (!isEmptyArray(&arrQueue)) {
        printf("dequeue() -> %d\n", dequeueArray(&arrQueue));
    }
    printf("Queue is empty? %s\n", isEmptyArray(&arrQueue) ? "yes" : "no");
    printf("dequeue() -> %d  (underflow, sentinel value)\n", dequeueArray(&arrQueue));

    /* ========== LINKED-LIST-BASED QUEUE ========== */

    section("6. linked-list queue: enqueue");
    struct Queue listQueue;
    initQueue(&listQueue);

    enqueue(&listQueue, 10);
    enqueue(&listQueue, 20);
    enqueue(&listQueue, 30);
    printf("Enqueued 10, 20, 30. Front is now: %d\n", peek(&listQueue));

    section("7. linked-list queue: dequeue");
    printf("dequeue() -> %d\n", dequeue(&listQueue));
    printf("peek() -> %d\n", peek(&listQueue));
    printf("dequeue() -> %d\n", dequeue(&listQueue));
    printf("dequeue() -> %d\n", dequeue(&listQueue));

    section("8. linked-list queue: underflow");
    printf("Queue is empty? %s\n", isEmptyList(&listQueue) ? "yes" : "no");
    printf("dequeue() -> %d  (underflow, sentinel value)\n", dequeue(&listQueue));

    section("9. linked-list queue: no fixed limit");
    for (int i = 1; i <= 10; i++) {
        enqueue(&listQueue, i * 100);
    }
    printf("Enqueued 10 values with no overflow check needed.\n");
    printf("Front is now: %d\n", peek(&listQueue));

    /* clean up remaining nodes */
    freeQueue(&listQueue);

    printf("\nAll queue concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Array-based queue definitions ---------- */

void initArrayQueue(struct ArrayQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFullArray(struct ArrayQueue *q) {
    return q->count == MAX_SIZE;
}

int isEmptyArray(struct ArrayQueue *q) {
    return q->count == 0;
}

void enqueueArray(struct ArrayQueue *q, int value) {
    if (isFullArray(q)) {
        printf("Queue overflow — cannot enqueue %d\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;   /* wrap around when reaching the end */
    q->data[q->rear] = value;
    q->count++;
}

int dequeueArray(struct ArrayQueue *q) {
    if (isEmptyArray(q)) {
        printf("Queue underflow — nothing to dequeue\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;   /* wrap around when reaching the end */
    q->count--;
    return value;
}

int peekArray(struct ArrayQueue *q) {
    if (isEmptyArray(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->data[q->front];
}

/* ---------- Linked-list-based queue definitions ---------- */

void initQueue(struct Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

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

int peek(struct Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->front->data;
}

int isEmptyList(struct Queue *q) {
    return q->front == NULL;
}

void freeQueue(struct Queue *q) {
    struct QueueNode *current = q->front;
    while (current != NULL) {
        struct QueueNode *next = current->next;
        free(current);
        current = next;
    }
    q->front = NULL;
    q->rear = NULL;
}
