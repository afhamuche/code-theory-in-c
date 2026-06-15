# 📚 code-theory-in-c

> A structured repository for learning and implementing 50 core coding theory concepts in the C programming language — from fundamentals to systems programming.

---

## 👤 Author

**afhamuche** — learning C, one concept at a time.

---

## 🎯 Purpose

This repository serves as a personal reference and learning journal for mastering coding theory through practical C implementations. Each topic includes a concept explanation and working C code.

---

## 🛠️ How to Compile & Run

All examples use GCC. To compile and run any `main.c` file:

```bash
gcc main.c -o main && ./main
```

For topics with separate header and implementation files:

```bash
gcc main.c <topic>.c -o main && ./main
```

For topics using threads (concurrency):

```bash
gcc main.c -o main -lpthread && ./main
```

---

## 📁 Repository Structure

```
code-theory-in-c/
│
├── README.md
├── .gitignore
│
├── 01_fundamentals/
├── 02_data_structures/
├── 03_algorithms/
├── 04_design_patterns/
├── 05_paradigms/
└── 06_systems/
```

Each topic folder contains:
- `README.md` — concept explanation and notes
- `main.c` — runnable demo/example
- `<topic>.h` / `<topic>.c` — header and implementation (where applicable)

---

## 📋 Topics & Progress

### 01 — Fundamentals

| # | Topic | Status |
|---|-------|--------|
| 01 | Variables & Data Types | ⬜ Not started |
| 02 | Conditionals | ⬜ Not started |
| 03 | Loops | ⬜ Not started |
| 04 | Functions & Recursion | ⬜ Not started |
| 05 | Arrays & Strings | ⬜ Not started |
| 06 | Pointers & References | ⬜ Not started |

### 02 — Data Structures

| # | Topic | Status |
|---|-------|--------|
| 07 | Linked Lists | ⬜ Not started |
| 08 | Stacks | ⬜ Not started |
| 09 | Queues | ⬜ Not started |
| 10 | Hash Tables | ⬜ Not started |
| 11 | Binary Trees | ⬜ Not started |
| 12 | Binary Search Trees (BST) | ⬜ Not started |
| 13 | Heaps / Priority Queues | ⬜ Not started |
| 14 | Graphs | ⬜ Not started |
| 15 | Tries | ⬜ Not started |
| 16 | Segment Trees | ⬜ Not started |

### 03 — Algorithms

| # | Topic | Status |
|---|-------|--------|
| 17 | Binary Search | ⬜ Not started |
| 18 | Bubble / Selection / Insertion Sort | ⬜ Not started |
| 19 | Merge Sort | ⬜ Not started |
| 20 | Quick Sort | ⬜ Not started |
| 21 | Heap Sort | ⬜ Not started |
| 22 | Depth-First Search (DFS) | ⬜ Not started |
| 23 | Breadth-First Search (BFS) | ⬜ Not started |
| 24 | Dijkstra's Algorithm | ⬜ Not started |
| 25 | A* Search Algorithm | ⬜ Not started |
| 26 | Bellman-Ford Algorithm | ⬜ Not started |
| 27 | Floyd-Warshall Algorithm | ⬜ Not started |
| 28 | Kadane's Algorithm | ⬜ Not started |
| 29 | Two Pointer Technique | ⬜ Not started |
| 30 | Sliding Window | ⬜ Not started |

### 04 — Design Patterns

| # | Topic | Status |
|---|-------|--------|
| 31 | Singleton Pattern | ⬜ Not started |
| 32 | Factory Pattern | ⬜ Not started |
| 33 | Observer Pattern | ⬜ Not started |
| 34 | Strategy Pattern | ⬜ Not started |
| 35 | Decorator Pattern | ⬜ Not started |
| 36 | MVC (Model-View-Controller) | ⬜ Not started |

### 05 — Paradigms

| # | Topic | Status |
|---|-------|--------|
| 37 | Object-Oriented Programming (OOP) in C | ⬜ Not started |
| 38 | Functional Programming | ⬜ Not started |
| 39 | Dynamic Programming (DP) | ⬜ Not started |
| 40 | Greedy Algorithms | ⬜ Not started |
| 41 | Divide & Conquer | ⬜ Not started |
| 42 | Backtracking | ⬜ Not started |
| 43 | Memoization & Caching | ⬜ Not started |

### 06 — Systems & Advanced

| # | Topic | Status |
|---|-------|--------|
| 44 | Big O Notation | ⬜ Not started |
| 45 | Bit Manipulation | ⬜ Not started |
| 46 | Concurrency & Multithreading | ⬜ Not started |
| 47 | Memory Management | ⬜ Not started |
| 48 | RESTful API Design | ⬜ Not started |
| 49 | Database Indexing & Query Optimization | ⬜ Not started |
| 50 | Compiler Design Basics | ⬜ Not started |

---

## 📊 Overall Progress

![Progress](https://img.shields.io/badge/Topics%20Completed-0%2F50-red?style=flat-square)

> Update the badge URL as you complete topics:
> - 0/50 → `red`
> - 25/50 → `yellow`  
> - 50/50 → `brightgreen`

---

## 📌 Legend

| Symbol | Meaning |
|--------|---------|
| ⬜ | Not started |
| 🔄 | In progress |
| ✅ | Completed |

---

## 📜 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

> *"The only way to learn a new programming language is by writing programs in it."* — Dennis Ritchie, creator of C
