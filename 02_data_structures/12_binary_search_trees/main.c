/*
 * 12 - Binary Search Trees in C
 * Demonstrates: insert (rule-based), search, in-order traversal
 * (producing sorted output), and delete covering all three cases
 * (no children, one child, two children).
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stdlib.h>

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* ---------- Declarations ---------- */
struct TreeNode *createNode(int value);
struct TreeNode *insert(struct TreeNode *node, int value);
int search(struct TreeNode *node, int target);
void inOrder(struct TreeNode *node);
struct TreeNode *findMin(struct TreeNode *node);
struct TreeNode *deleteNode(struct TreeNode *node, int value);
int countNodes(struct TreeNode *node);
void freeTree(struct TreeNode *node);

int main(void) {

    /* ---------- 1. Building the BST through insert() ---------- */
    section("1. building the BST through insert()");
    struct TreeNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 20);

    printf("Inserted: 10, 5, 15, 3, 7, 20\n");
    printf("In-order (should be sorted): ");
    inOrder(root);
    printf("\n");

    /* ---------- 2. Inserting a duplicate ---------- */
    section("2. inserting a duplicate (10)");
    int before = countNodes(root);
    root = insert(root, 10);
    int after = countNodes(root);
    printf("Node count before: %d, after inserting duplicate 10: %d\n", before, after);
    printf("%s\n", (before == after) ? "Duplicate correctly ignored." : "Unexpected change!");

    /* ---------- 3. Searching the BST ---------- */
    section("3. searching with search()");
    printf("search(root, 7)  = %s\n", search(root, 7) ? "found" : "not found");
    printf("search(root, 20) = %s\n", search(root, 20) ? "found" : "not found");
    printf("search(root, 99) = %s  (not in the tree)\n", search(root, 99) ? "found" : "not found");

    /* ---------- 4. findMin ---------- */
    section("4. finding the minimum value");
    struct TreeNode *min = findMin(root);
    printf("findMin(root) = %d  (leftmost node)\n", min->data);

    struct TreeNode *minOfRightSubtree = findMin(root->right);
    printf("findMin(root->right) = %d  (smallest value >= 10)\n", minOfRightSubtree->data);

    /* ---------- 5. Deleting a leaf (Case 1) ---------- */
    section("5. deleting a leaf node (3) - Case 1");
    printf("Before: ");
    inOrder(root);
    printf("\n");

    root = deleteNode(root, 3);

    printf("After deleting 3: ");
    inOrder(root);
    printf("\n");

    /* ---------- 6. Deleting a node with one child (Case 2) ---------- */
    section("6. deleting a node with one child (15, which only has right child 20) - Case 2");
    printf("Before: ");
    inOrder(root);
    printf("\n");

    root = deleteNode(root, 15);

    printf("After deleting 15: ");
    inOrder(root);
    printf("\n");
    printf("search(root, 15) = %s  (confirms it's gone)\n", search(root, 15) ? "found" : "not found");
    printf("search(root, 20) = %s  (confirms 20 survived the deletion)\n", search(root, 20) ? "found" : "not found");

    /* ---------- 7. Deleting a node with two children (Case 3) ---------- */
    section("7. deleting the root (10, has two children) - Case 3");
    printf("Before: ");
    inOrder(root);
    printf("\n");

    root = deleteNode(root, 10);

    printf("After deleting 10: ");
    inOrder(root);
    printf("\n");
    printf("search(root, 10) = %s  (confirms it's gone)\n", search(root, 10) ? "found" : "not found");

    /* ---------- 8. Deleting a value that doesn't exist ---------- */
    section("8. deleting a value that does not exist (999)");
    int countBefore = countNodes(root);
    root = deleteNode(root, 999);
    int countAfter = countNodes(root);
    printf("Node count before: %d, after: %d  (unchanged, no crash)\n", countBefore, countAfter);

    /* ---------- 9. Demonstrating worst-case shape ---------- */
    section("9. worst case: inserting already-sorted data");
    struct TreeNode *skewed = NULL;
    for (int i = 1; i <= 5; i++) {
        skewed = insert(skewed, i);
    }
    printf("Inserted 1,2,3,4,5 in order - tree degrades into a right-only chain.\n");
    printf("In-order (still sorted, but no branching left): ");
    inOrder(skewed);
    printf("\n");
    freeTree(skewed);

    /* ---------- 10. Freeing the remaining tree ---------- */
    section("10. freeing the tree");
    freeTree(root);
    root = NULL;
    printf("Tree freed. root is now: %p\n", (void *)root);

    printf("\nAll binary search tree concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

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

struct TreeNode *insert(struct TreeNode *node, int value) {
    if (node == NULL) {
        return createNode(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }
    /* if value == node->data, it's a duplicate - do nothing */

    return node;
}

int search(struct TreeNode *node, int target) {
    if (node == NULL) {
        return 0;
    }
    if (target == node->data) {
        return 1;
    }
    if (target < node->data) {
        return search(node->left, target);
    }
    return search(node->right, target);
}

void inOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

struct TreeNode *findMin(struct TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct TreeNode *deleteNode(struct TreeNode *node, int value) {
    if (node == NULL) {
        return NULL;
    }

    if (value < node->data) {
        node->left = deleteNode(node->left, value);
    } else if (value > node->data) {
        node->right = deleteNode(node->right, value);
    } else {
        /* found the node to delete */

        if (node->left == NULL) {
            struct TreeNode *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            struct TreeNode *temp = node->left;
            free(node);
            return temp;
        }

        /* two children: replace with the in-order successor */
        struct TreeNode *successor = findMin(node->right);
        node->data = successor->data;
        node->right = deleteNode(node->right, successor->data);
    }

    return node;
}

int countNodes(struct TreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void freeTree(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}
