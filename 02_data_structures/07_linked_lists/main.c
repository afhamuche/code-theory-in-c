/*
 * 07 — Linked Lists in C
 * Demonstrates: defining a node, creating nodes with malloc, inserting
 * at head and tail, traversal, deleting a node, freeing the whole list,
 * and checking malloc's return value.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ---------- Declarations ---------- */
void insertAtHead(struct Node **head, int value);
void insertAtTail(struct Node **head, int value);
void printList(struct Node *head);
void deleteValue(struct Node **head, int value);
void freeList(struct Node *head);
int countNodes(struct Node *head);

int main(void) {

    struct Node *head = NULL;   /* an empty list */

    /* ---------- 1. Creating a single node manually ---------- */
    section("1. creating a node with malloc");
    struct Node *firstNode = malloc(sizeof(struct Node));
    if (firstNode == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    firstNode->data = 10;
    firstNode->next = NULL;
    head = firstNode;

    printf("head->data = %d\n", head->data);
    printf("head->next = %p (NULL — only one node so far)\n", (void *)head->next);

    /* ---------- 2. Inserting at the head ---------- */
    section("2. inserting at the head");
    insertAtHead(&head, 5);
    printf("After inserting 5 at head: ");
    printList(head);

    /* ---------- 3. Inserting at the tail ---------- */
    section("3. inserting at the tail");
    insertAtTail(&head, 20);
    insertAtTail(&head, 30);
    printf("After inserting 20, 30 at tail: ");
    printList(head);

    /* ---------- 4. Traversal ---------- */
    section("4. traversing the list");
    printList(head);
    printf("Node count: %d\n", countNodes(head));

    /* ---------- 5. Deleting a node ---------- */
    section("5. deleting a node (value 20)");
    deleteValue(&head, 20);
    printf("After deleting 20: ");
    printList(head);

    section("5b. deleting the head node (value 5)");
    deleteValue(&head, 5);
    printf("After deleting 5 (was head): ");
    printList(head);

    section("5c. deleting a value that does not exist (999)");
    deleteValue(&head, 999);
    printf("After attempting to delete 999: ");
    printList(head);

    /* ---------- 6. Freeing the entire list ---------- */
    section("6. freeing the entire list");
    freeList(head);
    head = NULL;   /* good practice: avoid a dangling pointer */
    printf("List freed. head is now: %p\n", (void *)head);

    printf("\nAll linked list concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

void insertAtHead(struct Node **head, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void insertAtTail(struct Node **head, int value) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void printList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void deleteValue(struct Node **head, int value) {
    struct Node *current = *head;
    struct Node *previous = NULL;

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value %d not found — nothing deleted.\n", value);
        return;
    }

    if (previous == NULL) {
        *head = current->next;   /* deleting the head node */
    } else {
        previous->next = current->next;   /* skip over the found node */
    }

    free(current);
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;   /* save next before freeing current */
        free(current);
        current = next;
    }
}

int countNodes(struct Node *head) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}
