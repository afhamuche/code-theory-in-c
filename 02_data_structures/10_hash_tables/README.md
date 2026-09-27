# 10 — Hash Tables in C

> Key-value lookup using hashing for near-instant access.

---

## 🧠 What is a Hash Table?

A **hash table** stores data as **key-value pairs** and gives you near-instant lookup, insertion, and deletion — on average, all three run in **O(1)** time, regardless of how much data is stored. Compare that to a linked list (topic 07), where finding a value means walking the whole chain — O(n).

The trick is a **hash function**: a function that converts a key (like a string) into a number, which becomes an index into an array.

```
key "afhamuche"  →  hash function  →  index 3
key "claude"     →  hash function  →  index 7

table[3] = "afhamuche"'s value
table[7] = "claude"'s value
```

Instead of searching for a key, you compute where it *should* be, and go straight there.

---

## 🔑 Core Hash Table Operations

| Operation | Purpose |
|-----------|---------|
| `insert(key, value)` | Store a value under a key |
| `get(key)` | Retrieve the value stored under a key |
| `remove(key)` | Delete a key-value pair |
| `contains(key)` | Check whether a key exists |

Unlike an array (indexed by position) or a linked list (indexed by traversal order), a hash table is indexed by **meaning** — you look things up by a name, not a position.

---

## 🗂️ The Hash Function

A hash function takes a key and produces an index within the bounds of your underlying array. For string keys, a common simple approach sums character codes and reduces with modulo:

```c
#define TABLE_SIZE 10

unsigned int hash(const char *key) {
    unsigned int sum = 0;
    while (*key != '\0') {
        sum += (unsigned int)(*key);   /* add each character's ASCII value */
        key++;
    }
    return sum % TABLE_SIZE;   /* keep the index within bounds */
}
```

```
hash("cat") = ('c' + 'a' + 't') % TABLE_SIZE = (99 + 97 + 116) % 10 = 312 % 10 = 2
```

> 💡 A good hash function should be **fast** to compute and **spread keys evenly** across the table. A poor one clusters too many keys into the same few indices, which hurts performance (see collisions below).

---

## 💥 Collisions

Two different keys can hash to the **same index** — this is called a **collision**, and it's unavoidable once you have more possible keys than table slots (the **pigeonhole principle**). A hash table isn't complete without a collision-handling strategy.

```
hash("cat") = 2
hash("dog") = 2   ← collision! both want index 2
```

### Strategy: Separate Chaining

Each slot in the table isn't a single value — it's the **head of a linked list** (topic 07 returns here). Colliding keys just get appended to that slot's list.

```c
struct Entry {
    char key[50];
    int value;
    struct Entry *next;   /* self-referential — same pattern as topic 07 */
};

struct HashTable {
    struct Entry *buckets[TABLE_SIZE];   /* array of linked list heads */
};
```

```
Index 2 → [ "cat" | 1 ] → [ "dog" | 2 ] → NULL
```

This is the approach this topic implements — it's the most common in practice and directly reuses everything you already know about linked lists.

### Strategy: Open Addressing (mentioned, not implemented here)

Instead of chaining, if a slot is taken, probe forward to the next available slot (`index + 1`, `index + 2`, ...). Simpler memory layout, but more sensitive to a table filling up. Worth knowing the name — it comes up often in interviews and other languages' hash table implementations.

---

## 📦 Inserting with Separate Chaining

```c
void insert(struct HashTable *table, const char *key, int value) {
    unsigned int index = hash(key);

    struct Entry *newEntry = malloc(sizeof(struct Entry));
    if (newEntry == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    strcpy(newEntry->key, key);
    newEntry->value = value;
    newEntry->next = table->buckets[index];   /* insert at head of that bucket's list */
    table->buckets[index] = newEntry;
}
```

> 💡 This is the exact same "insert at head" pattern from topic 07's `insertAtHead` — a hash table bucket is just a linked list, so everything you learned there applies directly here.

---

## 🔍 Looking Up a Value

```c
int get(struct HashTable *table, const char *key) {
    unsigned int index = hash(key);
    struct Entry *current = table->buckets[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;   /* found it */
        }
        current = current->next;
    }

    return -1;   /* not found */
}
```

Notice the two-step lookup: first the hash function jumps you to the right **bucket** in O(1), then (if there was a collision) you walk that bucket's short list — which is only slow if many keys collided into the same bucket.

---

## 🗑️ Removing a Key

```c
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
        table->buckets[index] = current->next;   /* removing the bucket's head */
    } else {
        previous->next = current->next;
    }

    free(current);
}
```

This is nearly identical to `deleteValue` from topic 07 — a hash table's deletion is just linked-list deletion, scoped to one bucket.

---

## ⏱️ Why O(1) — and When It Isn't

| Scenario | Average Case | Worst Case |
|----------|---------------|------------|
| Good hash function, low load | O(1) | O(1) |
| Many collisions (poor hash function, or table too small) | O(1) | O(n) — degrades to a linked list search |

The "near-instant" access hash tables are known for is an **average-case** guarantee, not a strict one. If every key collided into a single bucket, you'd be doing a full linked-list traversal — no better than topic 07 by itself. Choosing a good hash function and keeping the table appropriately sized (a good **load factor**) is what keeps performance close to O(1) in practice.

---

## 🌍 Real-World Uses of Hash Tables

| Use Case | Why a Hash Table Fits |
|----------|-------------------------|
| Dictionaries / maps in other languages | Python's `dict`, JavaScript's `Object`, Java's `HashMap` |
| Caching | Fast key lookup for previously computed results |
| Database indexing | Quickly locating a record by a unique key (topic 49) |
| Compilers | Symbol tables mapping variable names to memory locations |
| Counting frequencies | Word counts, duplicate detection |

---

## ⚠️ Common Pitfalls

| Pitfall | Example | Fix |
|---------|---------|-----|
| Ignoring collisions | Assuming each key gets its own slot | Always implement a collision strategy (chaining or open addressing) |
| Poor hash function | A function that clusters most keys into a few indices | Choose a function that distributes keys evenly |
| Using `==` on string keys | `if (current->key == key)` | Use `strcmp(current->key, key) == 0` (topic 05) |
| Forgetting to free entries | Removing or destroying the table without `free()`-ing each `Entry` | Free every node in every bucket, not just the table itself |
| Fixed-size key buffers | `char key[50]` truncating a longer key | Size buffers generously, or use dynamic allocation for keys |
| Confusing hash table with array | Expecting an index-based lookup like `arr[i]` | A hash table looks up by key value, computed through the hash function |

---

## 💡 Key Takeaways

- A hash table stores key-value pairs and offers average O(1) insert, lookup, and delete
- A hash function converts a key into an array index — fast and evenly distributed is the goal
- Collisions are unavoidable and must be handled — separate chaining (linked lists per bucket) is the most common approach
- Chaining directly reuses topic 07's linked list operations: insert-at-head, traverse-and-compare, and delete
- Hash table performance is an average-case guarantee — a bad hash function degrades it toward O(n)
- Real languages' built-in maps/dictionaries are hash tables under the hood

---

## 📄 Files in This Topic

| File | Description |
|------|-------------|
| `README.md` | This file — concept explanation |
| `main.c` | Runnable demo of a hash table using separate chaining: insert, get, remove, and collision handling |

---

## ▶️ How to Run

```bash
gcc main.c -o main -Wall -Wextra && ./main
```

---

*Previous topic → [09 — Queues](../09_queues/README.md)*
*Next topic → [11 — Binary Trees](../11_binary_trees/README.md)*
