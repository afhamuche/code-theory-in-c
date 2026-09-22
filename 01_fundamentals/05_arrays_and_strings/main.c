/*
 * 05 — Arrays & Strings in C
 * Demonstrates: array declaration/initialization, accessing and modifying
 * elements, looping through arrays, multidimensional arrays, C strings
 * (null terminator), sizeof vs strlen, common string.h functions, and
 * passing arrays to functions.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <string.h>

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ---------- Declarations ---------- */
void doubleValues(int arr[], int size);
void printArray(const int arr[], int size);

int main(void) {

    /* ---------- 1. Declaring & initializing arrays ---------- */
    section("1. declaring & initializing arrays");
    int scores[5] = {90, 85, 78, 92, 88};
    printf("scores[0] = %d (first)\n", scores[0]);
    printf("scores[4] = %d (last)\n", scores[4]);

    int autoSized[] = {1, 2, 3, 4, 5};   /* compiler counts the size */
    int partial[5] = {1, 2};             /* remaining default to 0 */
    int zeroed[5] = {0};

    printf("autoSized has %zu elements\n", sizeof(autoSized) / sizeof(autoSized[0]));
    printf("partial:  ");
    printArray(partial, 5);
    printf("zeroed:   ");
    printArray(zeroed, 5);

    /* ---------- 2. Accessing & modifying elements ---------- */
    section("2. accessing & modifying elements");
    int numbers[5] = {10, 20, 30, 40, 50};
    printf("Before: numbers[2] = %d\n", numbers[2]);
    numbers[2] = 99;
    printf("After:  numbers[2] = %d\n", numbers[2]);

    int length = sizeof(numbers) / sizeof(numbers[0]);
    printf("Length of numbers[] = %d\n", length);

    /* ---------- 3. Looping through arrays ---------- */
    section("3. looping through arrays");
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }

    /* ---------- 4. Multidimensional arrays ---------- */
    section("4. multidimensional arrays (2D grid)");
    int grid[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("grid[1][2] = %d\n", grid[1][2]);
    printf("Full grid:\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }

    /* ---------- 5. Strings & the null terminator ---------- */
    section("5. strings & the null terminator");
    char name1[] = "afhamuche";
    char name2[] = {'C', 'l', 'a', 'u', 'd', 'e', '\0'};

    printf("name1 = %s\n", name1);
    printf("name2 = %s\n", name2);

    /* ---------- 6. sizeof vs strlen ---------- */
    section("6. sizeof vs strlen");
    char word[20] = "hello";
    printf("sizeof(word) = %zu  (total bytes reserved)\n", sizeof(word));
    printf("strlen(word) = %zu  (characters before '\\0')\n", strlen(word));

    /* ---------- 7. common string.h functions ---------- */
    section("7. common string.h functions");
    char greeting[50] = "Hello";
    strcat(greeting, ", afhamuche!");
    printf("After strcat: %s\n", greeting);

    if (strcmp(greeting, "Hello, afhamuche!") == 0) {
        printf("Strings match!\n");
    } else {
        printf("Strings do not match.\n");
    }

    char copy[50];
    strcpy(copy, greeting);
    printf("Copied string: %s\n", copy);
    printf("strlen(copy) = %zu\n", strlen(copy));

    /* ---------- 8. arrays and functions (pointer decay) ---------- */
    section("8. arrays and functions");
    int nums[3] = {1, 2, 3};
    printf("Before doubleValues: ");
    printArray(nums, 3);

    doubleValues(nums, 3);
    printf("After doubleValues:  ");
    printArray(nums, 3);

    printf("\nAll array and string concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

/* Arrays are passed as a pointer to the first element — modifies the caller's array */
void doubleValues(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = arr[i] * 2;
    }
}

void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
