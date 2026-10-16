/*
 * 10 — Hash Tables in C
 * Demonstrates: a hash function, separate chaining for collision handling,
 * insert, get, remove, contains, and freeing the whole table.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

struct Entry {
    char key[50];
    int value;
    struct Entry *next;
};

struct HashTable {
    struct Entry *buckets[TABLE_SIZE];
};

/* ---------- Declarations ---------- */
unsigned int hash(const char *key);
void initTable(struct HashTable *table);
void insert(struct HashTable *table, const char *key, int value);
int get(struct HashTable *table, const char *key);
int contains(struct HashTable *table, const char *key);
void remove_key(struct HashTable *table, const char *key);
void printBucket(struct HashTable *table, unsigned int index);
void freeTable(struct HashTable *table);

int main(void) {

    struct HashTable table;
    initTable(&table);

    /* ---------- 1. The hash function ---------- */
    section("1. the hash function");
    printf("hash(\"cat\")       = %u\n", hash("cat"));
    printf("hash(\"dog\")       = %u\n", hash("dog"));
    printf("hash(\"afhamuche\") = %u\n", hash("afhamuche"));
    printf("hash(\"claude\")    = %u\n", hash("claude"));

    /* ---------- 2. Inserting key-value pairs ---------- */
    section("2. inserting key-value pairs");
    insert(&table, "afhamuche", 100);
    insert(&table, "claude", 200);
    insert(&table, "cat", 1);
    insert(&table, "dog", 2);   /* "cat" and "dog" both hash to the same index */
    printf("Inserted: afhamuche=100, claude=200, cat=1, dog=2\n");

    /* ---------- 3. Demonstrating the collision ---------- */
    section("3. demonstrating a collision");
    unsigned int catIndex = hash("cat");
    unsigned int claudeIndex = hash("claude");
    printf("\"cat\" hashes to index %u, \"claude\" hashes to index %u\n", catIndex, claudeIndex);
    if (catIndex == claudeIndex) {
        printf("Collision confirmed — both land in the same bucket.\n");
        printf("Bucket %u contents: ", catIndex);
        printBucket(&table, catIndex);
    } else {
        printf("No collision this time — different buckets.\n");
    }

    /* ---------- 4. Looking up values ---------- */
    section("4. looking up values with get()");
    printf("get(\"afhamuche\") = %d\n", get(&table, "afhamuche"));
    printf("get(\"claude\")    = %d\n", get(&table, "claude"));
    printf("get(\"cat\")       = %d\n", get(&table, "cat"));
    printf("get(\"dog\")       = %d\n", get(&table, "dog"));
    printf("get(\"missing\")   = %d  (not found, sentinel value)\n", get(&table, "missing"));

    /* ---------- 5. contains() ---------- */
    section("5. checking existence with contains()");
    printf("contains(\"claude\")  = %s\n", contains(&table, "claude") ? "true" : "false");
    printf("contains(\"unknown\") = %s\n", contains(&table, "unknown") ? "true" : "false");

    /* ---------- 6. Removing a key (claude, which collided with cat) ---------- */
    section("6. removing a key (claude)");
    printf("Before removal, bucket %u: ", claudeIndex);
    printBucket(&table, claudeIndex);

    remove_key(&table, "claude");

    printf("After removing \"claude\", bucket %u: ", claudeIndex);
    printBucket(&table, claudeIndex);
    printf("get(\"claude\") after removal = %d  (not found)\n", get(&table, "claude"));
    printf("get(\"cat\") still works      = %d  (cat untouched by claude's removal)\n", get(&table, "cat"));

    /* ---------- 7. Removing a key that doesn't exist ---------- */
    section("7. removing a key that does not exist");
    remove_key(&table, "nonexistent");   /* should do nothing, no crash */
    printf("Attempted to remove \"nonexistent\" — no effect, no crash.\n");

    /* ---------- 8. Freeing the entire table ---------- */
    section("8. freeing the entire table");
    freeTable(&table);
    printf("All entries freed.\n");

    printf("\nAll hash table concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

unsigned int hash(const char *key) {
    unsigned int sum = 0;
    while (*key != '\0') {
        sum += (unsigned int)(*key);
        key++;
    }
    return sum % TABLE_SIZE;
}

void initTable(struct HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

void insert(struct HashTable *table, const char *key, int value) {
    unsigned int index = hash(key);

    struct Entry *newEntry = malloc(sizeof(struct Entry));
    if (newEntry == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newEntry->key, key);
    newEntry->value = value;
    newEntry->next = table->buckets[index];
    table->buckets[index] = newEntry;
}

int get(struct HashTable *table, const char *key) {
    unsigned int index = hash(key);
    struct Entry *current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1;
}

int contains(struct HashTable *table, const char *key) {
    return get(table, key) != -1;
}

void remove_key(struct HashTable *table, const char *key) {
    unsigned int index = hash(key);
    struct Entry *current = table->buckets[index];
    struct Entry *previous = NULL;

    while (current != NULL && strcmp(current->key, key) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return;   /* key not found */
    }

    if (previous == NULL) {
        table->buckets[index] = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
}

void printBucket(struct HashTable *table, unsigned int index) {
    struct Entry *current = table->buckets[index];
    while (current != NULL) {
        printf("[%s:%d] -> ", current->key, current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void freeTable(struct HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct Entry *current = table->buckets[i];
        while (current != NULL) {
            struct Entry *next = current->next;
            free(current);
            current = next;
        }
        table->buckets[i] = NULL;
    }
}
