/*
 * 04 — Functions & Recursion in C
 * Demonstrates: function anatomy, declaration vs definition vs call,
 * function signatures, pass-by-value, local vs global scope,
 * recursion (base case + recursive case), and common recursion patterns.
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

/* ---------- Declarations (prototypes) ---------- */

int add(int a, int b);
void greet(void);
void printSum(int a, int b);
int getFive(void);
void increment(int x);
void incrementGlobal(void);
int factorial(int n);
int fibonacci(int n);
int sumDigits(int n);
void reverseString(char str[], int start, int end);

/* ---------- Global variable (for scope demo) ---------- */
int globalCount = 0;

int main(void) {

    /* ---------- 1. Basic function call ---------- */
    section("1. basic function: add(a, b)");
    printf("add(3, 4) = %d\n", add(3, 4));
    printf("add(10, 20) = %d\n", add(10, 20));

    /* ---------- 2. Function signature variations ---------- */
    section("2. function signatures");
    greet();                      /* no params, no return */
    printSum(5, 7);               /* params, no return */
    printf("getFive() = %d\n", getFive());   /* no params, returns value */
    printf("add(2, 3) = %d\n", add(2, 3));   /* params, returns value */

    /* ---------- 3. Pass by value ---------- */
    section("3. pass by value");
    int num = 5;
    printf("Before increment(num): num = %d\n", num);
    increment(num);
    printf("After increment(num):  num = %d  (unchanged — copy was modified)\n", num);

    /* ---------- 4. Local vs global scope ---------- */
    section("4. local vs global scope");
    printf("globalCount before: %d\n", globalCount);
    incrementGlobal();
    incrementGlobal();
    incrementGlobal();
    printf("globalCount after 3 calls: %d\n", globalCount);

    /* ---------- 5. Recursion: factorial ---------- */
    section("5. recursion: factorial(4)");
    printf("factorial(4) = %d\n", factorial(4));
    printf("factorial(0) = %d  (base case directly)\n", factorial(0));

    /* ---------- 6. Recursion: fibonacci ---------- */
    section("6. recursion: fibonacci sequence (0..9)");
    for (int i = 0; i < 10; i++) {
        printf("fibonacci(%d) = %d\n", i, fibonacci(i));
    }

    /* ---------- 7. Recursion: sum of digits ---------- */
    section("7. recursion: sum of digits");
    int value = 12345;
    printf("sumDigits(%d) = %d\n", value, sumDigits(value));

    /* ---------- 8. Recursion: reverse a string in place ---------- */
    section("8. recursion: reverse a string");
    char word[] = "afhamuche";
    printf("Before: %s\n", word);
    reverseString(word, 0, (int)strlen(word) - 1);
    printf("After:  %s\n", word);

    /* ---------- 9. Recursion vs loop (same result, two approaches) ---------- */
    section("9. recursion vs loop: factorial(5)");
    printf("Recursive factorial(5) = %d\n", factorial(5));

    int iterative = 1;
    for (int i = 5; i >= 1; i--) {
        iterative *= i;
    }
    printf("Iterative factorial(5) = %d\n", iterative);

    printf("\nAll function and recursion concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

int add(int a, int b) {
    return a + b;
}

void greet(void) {
    printf("Hello!\n");
}

void printSum(int a, int b) {
    printf("Sum: %d\n", a + b);
}

int getFive(void) {
    return 5;
}

/* Pass by value — modifying x here does NOT affect the caller's variable */
void increment(int x) {
    x = x + 1;
}

/* Modifies the global variable directly — no pointer needed for globals */
void incrementGlobal(void) {
    int localStep = 1;   /* local — only exists during this call */
    globalCount += localStep;
}

/* Recursion: base case n <= 1, recursive case n * factorial(n-1) */
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

/* Recursion: base case n <= 1, recursive case fib(n-1) + fib(n-2) */
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/* Recursion: base case n == 0, recursive case (n % 10) + sumDigits(n / 10) */
int sumDigits(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) + sumDigits(n / 10);
}

/* Recursion: swaps outer characters, then recurses inward */
void reverseString(char str[], int start, int end) {
    if (start >= end) {
        return;   /* base case — pointers have met or crossed */
    }
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    reverseString(str, start + 1, end - 1);
}
