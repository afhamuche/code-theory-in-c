/*
 * 11 - Binary Trees in C
 * Demonstrates: building a tree manually, in-order/pre-order/post-order
 * traversal, measuring height and node count, searching an unordered
 * tree, and freeing the whole tree.
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
void inOrder(struct TreeNode *node);
void preOrder(struct TreeNode *node);
void postOrder(struct TreeNode *node);
int height(struct TreeNode *node);
int countNodes(struct TreeNode *node);
int contains(struct TreeNode *node, int target);
void freeTree(struct TreeNode *node);

int main(void) {

    /* ---------- 1. Building the tree manually ---------- */
    section("1. building the tree manually");
    /*
     *         10
     *        /  \
     *       5    15
     *      / \     \
     *     3   7     20
     */
    struct TreeNode *root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->right = createNode(20);

    if (root == NULL || root->left == NULL || root->right == NULL) {
        printf("Memory allocation failed while building the tree.\n");
        return 1;
    }
    printf("Tree built: root=10, left subtree={5,3,7}, right subtree={15,20}\n");

    /* ---------- 2. In-order traversal ---------- */
    section("2. in-order traversal (left, node, right)");
    printf("Expected: 3 5 7 10 15 20\n");
    printf("Actual:   ");
    inOrder(root);
    printf("\n");

    /* ---------- 3. Pre-order traversal ---------- */
    section("3. pre-order traversal (node, left, right)");
    printf("Expected: 10 5 3 7 15 20\n");
    printf("Actual:   ");
    preOrder(root);
    printf("\n");

    /* ---------- 4. Post-order traversal ---------- */
    section("4. post-order traversal (left, right, node)");
    printf("Expected: 3 7 5 20 15 10\n");
    printf("Actual:   ");
    postOrder(root);
    printf("\n");

    /* ---------- 5. Measuring the tree ---------- */
    section("5. measuring the tree");
    printf("height(root)     = %d\n", height(root));
    printf("countNodes(root) = %d\n", countNodes(root));

    /* ---------- 6. Height and count of a subtree ---------- */
    section("6. height and count of a subtree (root->left)");
    printf("height(root->left)     = %d  (subtree {5,3,7})\n", height(root->left));
    printf("countNodes(root->left) = %d\n", countNodes(root->left));

    /* ---------- 7. Searching the tree ---------- */
    section("7. searching with contains()");
    printf("contains(root, 7)   = %s\n", contains(root, 7) ? "true" : "false");
    printf("contains(root, 20)  = %s\n", contains(root, 20) ? "true" : "false");
    printf("contains(root, 99)  = %s  (not in the tree)\n", contains(root, 99) ? "true" : "false");

    /* ---------- 8. Leaf check ---------- */
    section("8. identifying a leaf node");
    struct TreeNode *leaf = root->left->left;   /* node holding 3 */
    printf("Node %d is a leaf? %s\n", leaf->data,
           (leaf->left == NULL && leaf->right == NULL) ? "yes" : "no");
    printf("Node %d is a leaf? %s\n", root->data,
           (root->left == NULL && root->right == NULL) ? "yes" : "no");

    /* ---------- 9. Freeing the entire tree ---------- */
    section("9. freeing the entire tree");
    freeTree(root);
    root = NULL;
    printf("Tree freed. root is now: %p\n", (void *)root);

    printf("\nAll binary tree concepts demonstrated successfully.\n");

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

void inOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

void preOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

void postOrder(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->data);
}

int height(struct TreeNode *node) {
    if (node == NULL) {
        return -1;
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

int contains(struct TreeNode *node, int target) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == target) {
        return 1;
    }
    return contains(node->left, target) || contains(node->right, target);
}

void freeTree(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}
