/*
 * ============================================================
 * Topic 02 — Conditionals in C
 * File:    main.c
 * Repo:    code-theory-in-c
 * Author:  afhamuche
 *
 * Compile: gcc main.c -o main -Wall -Wextra
 * Run:     ./main
 * ============================================================
 */

#include <stdio.h>
#include <stdbool.h>   /* for bool, true, false */

/* ── Separator helper ──────────────────────────────────────── */
void section(const char *title) {
    printf("\n========================================\n");
    printf("  %s\n", title);
    printf("========================================\n");
}

/* ============================================================
 * MAIN
 * ============================================================ */
int main(void) {

    printf("Topic 02 — Conditionals in C\n");

    /* ──────────────────────────────────────────────────────
     * 1. HOW C EVALUATES CONDITIONS
     * ────────────────────────────────────────────────────── */
    section("1. How C Evaluates Conditions");

    printf("if (1)  → ");
    if (1)  printf("runs   — non-zero is true\n");

    printf("if (0)  → ");
    if (0)  printf("runs\n");
    else    printf("skipped — zero is false\n");

    printf("if (-42)→ ");
    if (-42) printf("runs   — negative is also true\n");

    printf("if (0 == 0) → ");
    if (0 == 0) printf("runs   — comparison result is 1 (true)\n");

    /* ──────────────────────────────────────────────────────
     * 2. if STATEMENT
     * ────────────────────────────────────────────────────── */
    section("2. if Statement");

    int age = 20;
    printf("age = %d\n", age);
    if (age >= 18) {
        printf("Result: Adult — condition was true\n");
    }

    age = 15;
    printf("\nage = %d\n", age);
    if (age >= 18) {
        printf("Result: Adult\n");
    }
    printf("Result: (nothing — condition was false)\n");

    /* ──────────────────────────────────────────────────────
     * 3. if / else STATEMENT
     * ────────────────────────────────────────────────────── */
    section("3. if / else Statement");

    int temperature = 15;
    printf("temperature = %d\n", temperature);
    if (temperature >= 25) {
        printf("Result: It's warm\n");
    } else {
        printf("Result: It's cold\n");
    }

    temperature = 30;
    printf("\ntemperature = %d\n", temperature);
    if (temperature >= 25) {
        printf("Result: It's warm\n");
    } else {
        printf("Result: It's cold\n");
    }

    /* ──────────────────────────────────────────────────────
     * 4. if / else if / else CHAIN
     * ────────────────────────────────────────────────────── */
    section("4. if / else if / else Chain");

    int scores[] = {95, 83, 71, 65, 42};
    int num_scores = 5;

    for (int i = 0; i < num_scores; i++) {
        int score = scores[i];
        printf("score = %d → Grade: ", score);

        if (score >= 90) {
            printf("A\n");
        } else if (score >= 80) {
            printf("B\n");
        } else if (score >= 70) {
            printf("C\n");
        } else if (score >= 60) {
            printf("D\n");
        } else {
            printf("F\n");
        }
    }

    /* ──────────────────────────────────────────────────────
     * 5. NESTED if STATEMENTS
     * ────────────────────────────────────────────────────── */
    section("5. Nested if Statements");

    int person_age = 22;
    int has_id     = 1;
    int is_vip     = 0;

    printf("age=%d  has_id=%d  is_vip=%d\n", person_age, has_id, is_vip);
    if (person_age >= 18) {
        if (has_id) {
            printf("Result: Entry allowed\n");
        } else {
            printf("Result: No ID — entry denied\n");
        }
    } else {
        printf("Result: Too young — entry denied\n");
    }

    person_age = 16;
    printf("\nage=%d  has_id=%d\n", person_age, has_id);
    if (person_age >= 18) {
        if (has_id) {
            printf("Result: Entry allowed\n");
        } else {
            printf("Result: No ID — entry denied\n");
        }
    } else {
        printf("Result: Too young — entry denied\n");
    }

    /* ──────────────────────────────────────────────────────
     * 6. switch STATEMENT
     * ────────────────────────────────────────────────────── */
    section("6. switch Statement");

    int days[] = {1, 3, 5, 7};
    int num_days = 4;

    for (int i = 0; i < num_days; i++) {
        int day = days[i];
        printf("day %d → ", day);

        switch (day) {
            case 1:  printf("Monday\n");      break;
            case 2:  printf("Tuesday\n");     break;
            case 3:  printf("Wednesday\n");   break;
            case 4:  printf("Thursday\n");    break;
            case 5:  printf("Friday\n");      break;
            case 6:  printf("Saturday\n");    break;
            case 7:  printf("Sunday\n");      break;
            default: printf("Invalid day\n"); break;
        }
    }

    /* ──────────────────────────────────────────────────────
     * 7. switch FALL-THROUGH (intentional)
     * ────────────────────────────────────────────────────── */
    section("7. switch Fall-Through (intentional)");

    int months[]   = {1, 4, 2, 11};
    int num_months = 4;

    for (int i = 0; i < num_months; i++) {
        int month = months[i];
        int month_days;

        switch (month) {
            case 1: case 3: case 5: case 7:
            case 8: case 10: case 12:
                month_days = 31; break;
            case 4: case 6: case 9: case 11:
                month_days = 30; break;
            case 2:
                month_days = 28; break;
            default:
                month_days = -1; break;
        }
        printf("Month %2d → %d days\n", month, month_days);
    }

    /* ──────────────────────────────────────────────────────
     * 8. TERNARY OPERATOR ? :
     * ────────────────────────────────────────────────────── */
    section("8. Ternary Operator ? :");

    int x = 10;
    const char *size = (x > 5) ? "big" : "small";
    printf("x = %d → %s\n", x, size);

    x = 3;
    size = (x > 5) ? "big" : "small";
    printf("x = %d → %s\n", x, size);

    int num     = -42;
    int abs_val = (num < 0) ? -num : num;
    printf("abs(%d) = %d\n", num, abs_val);

    int n = 7;
    printf("%d is %s\n", n, (n % 2 == 0) ? "even" : "odd");

    /* ──────────────────────────────────────────────────────
     * 9. COMPARISON OPERATORS
     * ────────────────────────────────────────────────────── */
    section("9. Comparison Operators");

    int a = 5, b = 8;
    printf("a = %d, b = %d\n\n", a, b);
    printf("a == b  → %s\n", (a == b) ? "true" : "false");
    printf("a != b  → %s\n", (a != b) ? "true" : "false");
    printf("a >  b  → %s\n", (a >  b) ? "true" : "false");
    printf("a <  b  → %s\n", (a <  b) ? "true" : "false");
    printf("a >= b  → %s\n", (a >= b) ? "true" : "false");
    printf("a <= b  → %s\n", (a <= b) ? "true" : "false");

    /* ──────────────────────────────────────────────────────
     * 10. LOGICAL OPERATORS && || !
     * ────────────────────────────────────────────────────── */
    section("10. Logical Operators");

    int user_age = 22;
    int user_id  = 1;
    int admin    = 0;

    printf("age=%d  id=%d  admin=%d\n\n", user_age, user_id, admin);

    if (user_age >= 18 && user_id) {
        printf("&& (AND): Entry allowed — age OK and has ID\n");
    }
    if (user_age >= 18 || admin) {
        printf("|| (OR):  Access granted — age OK or is admin\n");
    }
    if (!admin) {
        printf("!  (NOT): Standard access — not an admin\n");
    }
    printf("\nCombined: age>=18 && (id || admin) → %s\n",
           (user_age >= 18 && (user_id || admin)) ? "true" : "false");

    /* ──────────────────────────────────────────────────────
     * 11. COMMON PITFALLS
     * ────────────────────────────────────────────────────── */
    section("11. Common Pitfalls");

    /* Pitfall 1: = vs == */
    int val = 0;
    if (val == 5) {
        printf("val is 5\n");
    } else {
        printf("Pitfall 1: val == 5 is false (val = %d)\n", val);
        printf("           Never use = inside if — use ==\n");
    }

    /* Pitfall 2: missing braces */
    int count = 3;
    printf("\nPitfall 2 — missing braces:\n");
    printf("  count = %d\n", count);
    if (count > 0)
        printf("  Line 1: this is inside the if\n");
    printf("  Line 2: this ALWAYS runs — not part of the if!\n");
    printf("  Fix: always wrap blocks in { }\n");

    /* Pitfall 3: switch fall-through (accidental) */
    printf("\nPitfall 3 — accidental fall-through:\n");
    int code = 1;
    printf("  code = %d, switch without break:\n", code);
    switch (code) {
        case 1: printf("  case 1 ran\n");
        case 2: printf("  case 2 ran\n");
        case 3: printf("  case 3 ran\n"); break;
    }
    printf("  All three ran! Add break to each case to fix.\n");

    /* ──────────────────────────────────────────────────────
     * Done
     * ────────────────────────────────────────────────────── */
    printf("\n========================================\n");
    printf("  Topic 02 complete. Next: 03_loops\n");
    printf("========================================\n\n");

    return 0;
}