/*
 * 06 — Pointers & References in C
 * Demonstrates: address-of (&) and dereference (*), pointer declaration,
 * NULL pointers, pointers fixing pass-by-value, pointers and arrays,
 * pointer arithmetic, pointers and strings, pointer to pointer, and
 * pointers vs arrays with sizeof.
 *
 * Compile: gcc main.c -o main -Wall -Wextra && ./main
 */

#include <stdio.h>
#include <stddef.h>   /* NULL */

void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ---------- Declarations ---------- */
void badIncrement(int x);
void increment(int *x);

int main(void) {

    /* ---------- 1. What is a pointer? ---------- */
    section("1. what is a pointer?");
    int age = 25;
    int *p = &age;

    printf("age        = %d\n", age);
    printf("&age       = %p\n", (void *)&age);
    printf("p          = %p\n", (void *)p);
    printf("*p         = %d\n", *p);

    /* ---------- 2. Dereferencing to write ---------- */
    section("2. dereferencing to write");
    printf("Before: age = %d\n", age);
    *p = 30;
    printf("After:  age = %d  (changed through the pointer!)\n", age);

    /* ---------- 3. Declaring pointers of different types ---------- */
    section("3. declaring pointers of different types");
    int number = 10;
    int *ptr = &number;

    float value = 3.14f;
    float *fptr = &value;

    printf("number = %d, *ptr  = %d\n", number, *ptr);
    printf("value  = %.2f, *fptr = %.2f\n", value, *fptr);

    /* ---------- 4. NULL pointers ---------- */
    section("4. NULL pointers");
    int *nullPtr = NULL;

    if (nullPtr == NULL) {
        printf("nullPtr is not pointing to anything.\n");
    }
    /* NOTE: *nullPtr would crash the program (segfault) — never dereference NULL */

    /* ---------- 5. Pointers fixing pass-by-value ---------- */
    section("5. pointers fixing pass-by-value");
    int num = 5;

    printf("Before badIncrement: num = %d\n", num);
    badIncrement(num);
    printf("After badIncrement:  num = %d  (unchanged — pass by value)\n", num);

    printf("Before increment (pointer): num = %d\n", num);
    increment(&num);
    printf("After increment (pointer):  num = %d  (changed!)\n", num);

    /* ---------- 6. Pointers and arrays ---------- */
    section("6. pointers and arrays");
    int numbers[3] = {10, 20, 30};
    int *arrPtr = numbers;   /* no & needed — array name already IS an address */

    printf("*arrPtr       = %d\n", *arrPtr);
    printf("*(arrPtr + 1) = %d\n", *(arrPtr + 1));
    printf("*(arrPtr + 2) = %d\n", *(arrPtr + 2));

    printf("numbers[1]       = %d\n", numbers[1]);
    printf("*(numbers + 1)   = %d  (identical to numbers[1])\n", *(numbers + 1));

    /* ---------- 7. Pointer arithmetic ---------- */
    section("7. pointer arithmetic");
    int nums[3] = {1, 2, 3};
    int *np = nums;

    printf("*np before: %d\n", *np);
    np = np + 1;   /* moves forward by sizeof(int) bytes, not 1 byte */
    printf("*np after np + 1: %d\n", *np);

    /* ---------- 8. Pointers and strings ---------- */
    section("8. pointers and strings");
    char word[] = "hello";
    char *cp = word;

    printf("Walking through \"%s\" character by character:\n", word);
    while (*cp != '\0') {
        printf("%c\n", *cp);
        cp++;
    }

    /* ---------- 9. Pointer to pointer ---------- */
    section("9. pointer to pointer");
    int age2 = 25;
    int *p2 = &age2;
    int **pp = &p2;

    printf("age2 = %d\n", age2);
    printf("*p2  = %d\n", *p2);
    printf("**pp = %d  (dereferenced twice)\n", **pp);

    /* ---------- 10. Pointers vs arrays: sizeof ---------- */
    section("10. pointers vs arrays: sizeof");
    int arr[5] = {1, 2, 3, 4, 5};
    int *arrp = arr;

    printf("sizeof(arr)  = %zu  (5 ints x 4 bytes = total array size)\n", sizeof(arr));
    printf("sizeof(arrp) = %zu  (just the pointer's own size)\n", sizeof(arrp));

    printf("\nAll pointer concepts demonstrated successfully.\n");

    return 0;
}

/* ---------- Definitions ---------- */

/* Pass by value — cannot modify the caller's variable (see topic 04) */
void badIncrement(int x) {
    x = x + 1;
}

/* Pass by pointer — CAN modify the caller's variable */
void increment(int *x) {
    *x = *x + 1;
}
