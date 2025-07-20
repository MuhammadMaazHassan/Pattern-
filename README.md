# Pattern-
This C++ program, crafted during my first semester at COMSATS University Islamabad, Abbottabad Campus, generates a symmetric diamond pattern of 'x' characters in an n x n grid, where n is a user-provided positive integer. It reflects my early exploration of nested loops, user input handling, and console-based pattern generation.

The program generates a pattern of 'x' characters in the shape of a diamond or cross within a square grid of size n x n, where n is a user-provided positive integer. The pattern is symmetric, with 'x' characters placed in positions where the column index j satisfies j <= x && j <= n - x + 1, and spaces elsewhere. The variable x is calculated as n/2 + 1, determining the width of the pattern.

# Functionality:

- The program prompts the user to input a positive integer n, representing the size of the square grid.
- It calculates x as n/2 + 1 (using integer division), which controls the number of 'x' characters in each row.
- It uses nested loops to iterate over each cell in the n x n grid:
- The outer loop iterates over rows (i from 1 to n).
- The inner loop iterates over columns (j from 1 to n).
- For each cell, if the column index j satisfies j <= x && j <= n - x + 1, an 'x' is printed; otherwise, a space is printed.
