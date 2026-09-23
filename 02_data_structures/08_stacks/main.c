/*
 * 08 — Stacks in C
 * Demonstrates: LIFO behavior using both an array-based stack and a
 * linked-list-based stack, including push, pop, peek, isEmpty,
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

/* ---------- Array-based stack ---------- */

struct Stack {
    int data[MAX_SIZE];
    int top;   /* -1 means empty */
};

void initStack(struct Stack *s);
void push(struct Stack *s, int value);
int pop(struct Stack *s);
int peek(struct Stack *s);
int isEmpty(struct Stack *s);
int isFull(struct Stack *s);

/* ---------- Linked-list-based stack ---------- */

struct StackNode {
    int data;
    struct StackNode *next;
};

void pushList(struct StackNode **top, int value);
int popList(struct StackNode **top);
int peekList(struct StackNode *top);
int isEmptyList(struct StackNode *top);
void freeStackList(struct StackNode *top);

int main(void) {

    /* ========== ARRAY-BASED STACK ========== */

    section("1. array-based stack: push");
    struct Stack arrStack;
    initStack(&arrStack);

    push(&arrStack, 10);
    push(&arrStack, 20);
    push(&arrStack, 30);
    printf("Pushed 10, 20, 30. Top is now: %d\n", peek(&arrStack));

    section("2. array-based stack: pop");
    printf("pop() -> %d\n", pop(&arrStack));
    printf("peek() -> %d  (unchanged by peek, top after pop)\n", peek(&arrStack));
    printf("pop() -> %d\n", pop(&arrStack));
    printf("pop() -> %d\n", pop(&arrStack));

    section("3. array-based stack: underflow");
    printf("Stack is empty? %s\n", isEmpty(&arrStack) ? "yes" : "no");
    printf("pop() -> %d  (underflow, sentinel value)\n", pop(&arrStack));

    section("4. array-based stack: overflow");
    for (int i = 1; i <= MAX_SIZE; i++) {
        push(&arrStack, i * 100);
    }
    printf("Stack full? %s\n", isFull(&arrStack) ? "yes" : "no");
    push(&arrStack, 999);   /* triggers overflow message */

    /* ========== LINKED-LIST-BASED STACK ========== */

    section("5. linked-list stack: push");
    struct StackNode *listStack = NULL;   /* an empty stack */

    pushList(&listStack, 10);
    pushList(&listStack, 20);
    pushList(&listStack, 30);
    printf("Pushed 10, 20, 30. Top is now: %d\n", peekList(listStack));

    section("6. linked-list stack: pop");
    printf("pop() -> %d\n", popList(&listStack));
    printf("peek() -> %d\n", peekList(listStack));
    printf("pop() -> %d\n", popList(&listStack));
    printf("pop() -> %d\n", popList(&listStack));

    section("7. linked-list stack: underflow");
    printf("Stack is empty? %s\n", isEmptyList(listStack) ? "yes" : "no");
    printf("pop() -> %d  (underflow, sentinel value)\n", popList(&listStack));

    section("8. linked-list stack: no fixed limit");
    for (int i = 1; i <= 10; i++) {
        pushList(&listStack, i);
    }
    printf("Pushed 10 values with no overflow check needed.\n");
    printf("Top is now: %d\n", peekList(listStack));

    /* clean up remaining nodes */
    freeStackList(listStack);
    listStack = NULL;

    printf("\nAll stack concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Array-based stack definitions ---------- */

void initStack(struct Stack *s) {
    s->top = -1;
}

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
        return -1;
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

int isFull(struct Stack *s) {
    return s->top == MAX_SIZE - 1;
}

/* ---------- Linked-list-based stack definitions ---------- */

void pushList(struct StackNode **top, int value) {
    struct StackNode *newNode = malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
}

int popList(struct StackNode **top) {
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

int peekList(struct StackNode *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return top->data;
}

int isEmptyList(struct StackNode *top) {
    return top == NULL;
}

void freeStackList(struct StackNode *top) {
    struct StackNode *current = top;
    while (current != NULL) {
        struct StackNode *next = current->next;
        free(current);
        current = next;
    }
}
