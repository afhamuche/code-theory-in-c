/*
 * 03 — Loops in C
 * Demonstrates: for, while, do-while, break, continue, nested loops,
 * infinite loops, common patterns, and common pitfalls.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stdbool.h>

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

int main(void) {

    /* ---------- 1. for loop ---------- */
    section("1. for loop");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }

    /* ---------- 2. while loop ---------- */
    section("2. while loop");
    int count = 5;
    while (count > 0) {
        printf("%d\n", count);
        count--;
    }

    /* ---------- 3. do-while loop ---------- */
    section("3. do-while loop (simulated input)");
    int number = 0;
    int attempts[] = {15, 20, 7};   /* fake "user input" so it runs without scanf */
    int idx = 0;
    do {
        number = attempts[idx];
        printf("Attempt: %d\n", number);
        idx++;
    } while ((number < 1 || number > 10) && idx < 3);

    if (number >= 1 && number <= 10) {
        printf("Valid number: %d\n", number);
    } else {
        printf("No valid number entered in simulated attempts.\n");
    }

    /* ---------- 4. break ---------- */
    section("4. break");
    for (int i = 0; i < 10; i++) {
        if (i == 5) {
            break;
        }
        printf("%d\n", i);
    }

    /* ---------- 5. continue ---------- */
    section("5. continue (skip even numbers)");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            continue;
        }
        printf("%d\n", i);
    }

    /* ---------- 6. nested loops ---------- */
    section("6. nested loops (multiplication table)");
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("%d x %d = %d\n", i, j, i * j);
        }
    }

    /* ---------- 7. infinite loop (with manual break) ---------- */
    section("7. infinite loop pattern");
    int ticks = 0;
    while (1) {
        printf("tick %d\n", ticks);
        ticks++;
        if (ticks >= 3) {
            break;  /* required, or this would run forever */
        }
    }

    /* ---------- 8. iterating over an array ---------- */
    section("8. pattern: iterating over an array");
    int arr[] = {10, 20, 30, 40, 50};
    int len = 5;
    for (int i = 0; i < len; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    /* ---------- 9. summing an array ---------- */
    section("9. pattern: summing an array");
    int nums[] = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += nums[i];
    }
    printf("Sum = %d\n", sum);

    /* ---------- 10. reverse iteration ---------- */
    section("10. pattern: reverse iteration");
    for (int i = 4; i >= 0; i--) {
        printf("%d\n", i);
    }

    /* ---------- 11. stepping by more than 1 ---------- */
    section("11. pattern: stepping by 2");
    for (int i = 0; i <= 10; i += 2) {
        printf("%d\n", i);
    }

    /* ---------- 12. finding an element ---------- */
    section("12. pattern: finding an element");
    int haystack[] = {3, 7, 2, 9, 5};
    int target = 9;
    int found = -1;
    for (int i = 0; i < 5; i++) {
        if (haystack[i] == target) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        printf("Found %d at index %d\n", target, found);
    } else {
        printf("%d not found\n", target);
    }

    /* ---------- 13. common pitfalls (safe demonstrations) ---------- */
    section("13. common pitfalls");

    /* Off-by-one: correct version shown (the buggy version would read out of bounds) */
    printf("-- Off-by-one fix: use i < len, not i <= len --\n");
    int demo[] = {1, 2, 3};
    int demoLen = 3;
    for (int i = 0; i < demoLen; i++) {   /* correct: i < demoLen */
        printf("demo[%d] = %d\n", i, demo[i]);
    }

    /* Empty for body pitfall — shown as a comment only, never executed */
    printf("-- Empty for-body pitfall (do NOT do this): --\n");
    printf("   for (i = 0; i < 10; i++);   // <-- stray semicolon = empty body\n");

    /* Forgetting break in search */
    printf("-- Forgetting break in search wastes iterations --\n");
    int seen = 0;
    for (int i = 0; i < 5; i++) {
        if (haystack[i] == target) {
            seen++;
            break;   /* correct: stop once found */
        }
    }
    printf("Search stopped after finding target (seen=%d)\n", seen);

    printf("\nAll loop concepts demonstrated successfully.\n");

    return 0;
}
