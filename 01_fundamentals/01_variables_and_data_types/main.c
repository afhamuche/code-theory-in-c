/*
 * ============================================================
 * Topic 01 — Variables & Data Types in C
 * File:    main.c
 * Repo:    code-theory-in-c
 * Author:  afhamuche
 *
 * Compile: gcc main.c -o main
 * Run:     ./main
 * ============================================================
 */

#include <stdio.h>
#include <stdbool.h>   /* for bool, true, false     */
#include <math.h>      /* for fabs() — float compare */

/* ── Separator helper (keeps output readable) ─────────────── */
void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void) {

    printf("Topic 01 — Variables & Data Types in C\n");

    /* ──────────────────────────────────────────────────────
     * 1. INTEGER TYPES
     * ────────────────────────────────────────────────────── */
    section("1. Integer Types");

    char            c  = 'A';           /* 1 byte: stores ASCII value    */
    unsigned char   uc = 200;           /* 1 byte: 0–255 (no sign bit)   */
    short           s  = -1500;         /* 2 bytes                        */
    int             i  = -2100000000;   /* 4 bytes: most common int type  */
    long            l  = 1234567890L;   /* 4 or 8 bytes (platform varies) */
    long long       ll = 9000000000LL;  /* 8 bytes: very large numbers    */

    printf("char:           %c  (ASCII %d)\n", c, c);
    printf("unsigned char:  %u\n", uc);
    printf("short:          %d\n", s);
    printf("int:            %d\n", i);
    printf("long:           %ld\n", l);
    printf("long long:      %lld\n", ll);

    /* ──────────────────────────────────────────────────────
     * 2. FLOATING POINT TYPES
     * ────────────────────────────────────────────────────── */
    section("2. Floating Point Types");

    float       f  = 3.14f;            /* ~6-7 digits precision          */
    double      d  = 3.141592653589;   /* ~15-16 digits precision        */
    long double ld = 3.14159265358979L;/* ~18-19 digits precision        */

    printf("float:          %f\n", f);
    printf("double:         %.12lf\n", d);
    printf("long double:    %.15Lf\n", ld);

    /* ──────────────────────────────────────────────────────
     * 3. BOOL TYPE
     * ────────────────────────────────────────────────────── */
    section("3. Bool Type (stdbool.h)");

    bool is_learning = true;
    bool is_done     = false;

    printf("is_learning:    %s\n", is_learning ? "true" : "false");
    printf("is_done:        %s\n", is_done     ? "true" : "false");

    /* ──────────────────────────────────────────────────────
     * 4. CHARACTERS & STRINGS
     * ────────────────────────────────────────────────────── */
    section("4. Characters & Strings");

    char letter      = 'Z';
    char name[]      = "afhamuche";    /* char array — null terminated   */

    printf("char letter:    %c\n", letter);
    printf("string name:    %s\n", name);
    printf("name[0]:        %c  (first character)\n", name[0]);
    printf("null terminator at name[9]: '\\0' = %d\n", name[9]);

    /* ──────────────────────────────────────────────────────
     * 5. VARIABLE DECLARATION STYLES
     * ────────────────────────────────────────────────────── */
    section("5. Declaration Styles");

    int score       = 100;             /* declare + initialize            */
    float temp      = 36.6f;
    char grade      = 'A';

    int x = 0, y = 0, z = 0;          /* multiple on one line            */

    int result;                        /* declare first                   */
    result = 42;                       /* assign later                    */

    printf("score:          %d\n", score);
    printf("temp:           %.1f\n", temp);
    printf("grade:          %c\n", grade);
    printf("x, y, z:        %d, %d, %d\n", x, y, z);
    printf("result:         %d\n", result);

    /* ──────────────────────────────────────────────────────
     * 6. TYPE QUALIFIERS
     * ────────────────────────────────────────────────────── */
    section("6. Type Qualifiers");

    const float     PI        = 3.14159f; /* cannot be changed after init */
    unsigned int    count     = 4000000000U;
    signed int      altitude  = -500;
    volatile int    sensor    = 42;       /* may change unexpectedly      */

    printf("const PI:       %.5f\n", PI);
    printf("unsigned int:   %u\n", count);
    printf("signed int:     %d\n", altitude);
    printf("volatile int:   %d\n", sensor);

    /* ──────────────────────────────────────────────────────
     * 7. TYPE CASTING
     * ────────────────────────────────────────────────────── */
    section("7. Type Casting");

    int a = 5;
    int b = 2;

    float correct = (float)a / b;   /* cast BEFORE division → 2.5        */
    float wrong   = a / b;          /* integer division first  → 2.0     */

    printf("(float)5 / 2:   %.1f  (correct cast)\n", correct);
    printf("5 / 2:          %.1f  (integer division — wrong!)\n", wrong);

    /* ──────────────────────────────────────────────────────
     * 8. sizeof() — MEMORY SIZES
     * ────────────────────────────────────────────────────── */
    section("8. sizeof() — Memory Sizes");

    printf("char:           %zu byte(s)\n",  sizeof(char));
    printf("short:          %zu byte(s)\n",  sizeof(short));
    printf("int:            %zu byte(s)\n",  sizeof(int));
    printf("long:           %zu byte(s)\n",  sizeof(long));
    printf("long long:      %zu byte(s)\n",  sizeof(long long));
    printf("float:          %zu byte(s)\n",  sizeof(float));
    printf("double:         %zu byte(s)\n",  sizeof(double));
    printf("long double:    %zu byte(s)\n",  sizeof(long double));
    printf("bool:           %zu byte(s)\n",  sizeof(bool));

    /* ──────────────────────────────────────────────────────
     * 9. COMMON PITFALLS DEMONSTRATED
     * ────────────────────────────────────────────────────── */
    section("9. Common Pitfalls");

    /* Pitfall 1: Integer overflow */
    unsigned char overflow_demo = 255;
    printf("unsigned char 255 + 1 = %d  (wraps to 0)\n", (unsigned char)(overflow_demo + 1));

    /* Pitfall 2: Wrong format specifier — printing int as float */
    int wrong_type = 42;
    printf("Correct %%d:     %d\n", wrong_type);
    /* printf("Wrong %%f:   %f\n", wrong_type); // <-- undefined behavior! */
    printf("Wrong %%f would be undefined behavior — skipped safely.\n");

    /* Pitfall 3: Float comparison — NEVER use == */
    float val = 0.1f + 0.2f;
    printf("\n0.1f + 0.2f = %.20f\n", val);
    printf("val == 0.3f?    %s  (never use == for floats!)\n",
           (val == 0.3f) ? "true" : "false");
    printf("fabs check?     %s  (use epsilon instead)\n",
           (fabs(val - 0.3f) < 1e-6) ? "true" : "false");

    /* ──────────────────────────────────────────────────────
     * 10. FORMAT SPECIFIERS SUMMARY
     * ────────────────────────────────────────────────────── */
    section("10. Format Specifiers");

    printf("%%d  (int):        %d\n",   42);
    printf("%%u  (uint):       %u\n",   42u);
    printf("%%f  (float):      %f\n",   3.14f);
    printf("%%lf (double):     %lf\n",  3.14);
    printf("%%c  (char):       %c\n",   'C');
    printf("%%s  (string):     %s\n",   "hello");
    printf("%%lld (long long): %lld\n", 9000000000LL);
    printf("%%zu (size_t):     %zu\n",  sizeof(int));
    printf("%%x  (hex):        %x\n",   255);
    printf("%%o  (octal):      %o\n",   8);

    /* ──────────────────────────────────────────────────────
     * Done
     * ────────────────────────────────────────────────────── */
    printf("\n========================================\n");
    printf("  Topic 01 complete. Next: 02_conditionals\n");
    printf("========================================\n\n");

    return 0;
}