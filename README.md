# Marble Cutting Optimization

This repository contains a C++ implementation of an algorithm to optimize the cutting of marble sheets, along with a version (`marble-chrono.cpp`) that measures the execution time for each input.
The problem given aims to maximize the value obtained by cutting a rectangle into smaller pieces, adhering to constraints on dimensions and associated values for each piece. Our proposed solution employs dynamic programming, tabulation, to efficiently calculate the maximum achievable value, considering both horizontal and vertical cuts.
For a better understanding of our problem, we did research on the classic Knapsack problem with guillotine cuts, as this problem is a variant of it. 
Initially, the pieces and their rotations are organized into a matrix, representing potential cutting configurations. Following this organization, dynamic programming is applied to explore all possible combinations of cuts, thus obtaining the maximum values of subproblems until reaching a global solution.

## Getting Started

Clone the repository to your local machine using the following command in your terminal or command prompt:

```bash
git clone https://github.com/mariamfmr/marble-cutting-knapsack/
```

### Prerequisites

- C++ compiler (g++)
- Make

### Build and Run

To build the executable for the main algorithm and execute it for each input file in the `testsTime` folder, run the following commands:

```bash
make
```

To clean the generated output files from the testsTime folder, use:

```bash
make clean
```
### Test Data

The repository includes a total of 54 tests located in the testsTime folder. The folder tests/ include 4 tests that were given to us along with their expected output, ranging from 2 very simply tests to 2 hard tests.
Each test  in testsTime/ include 200 randomized pieces with random sizes and values with 5 tests for every 1000 of the sum of rows and columns of the main rectangle.

To generate additional tests, use the following command:

```bash
./gen_supermarble (rows) (cols) (number of pieces) (number of test files)
```

### Contents

    - marble.cpp: Main algorithm implementation in c++ language.
    - marble.rs: Main algorithm implementation in rust language.
    - marble-chrono.cpp: Algorithm version that measures execution time.
    - gen_supermarble.cpp: Auxiliar tool to generate additional test inputs.
    - relatorio.pdf: Document explaining the main problem, summarizing the solution, and drawing conclusions from both practical and theoretical analyses.
    - complexity-comparison.html: Graph plotting the time-wise behavior of the algorithm for each X+Y input, comparing it to O(n^3) and O(n^3 / 2).
    - complexity-linear.html: Graph plotting x^3 and x^3 / 2 into the x-axis with the data.

### Conclusion

Theoretical analysis suggests that the algorithm has a complexity of O(n^3 / 2) due to considering only half of the sub-problems. 
Despite this reduction in the number of subproblems, the overall complexity remains cubic O(n^3) due to the constant factor in the big-O notation. Therefore, even though our algorithm exhibits improved efficiency by tackling a reduced set of subproblems, the cubic nature of the problem dominates the overall complexity.
Practical analysis is further detailed in the relatorio.pdf.

