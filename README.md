# Sudoku Solver

A simple program to solve [Sudoku](https://en.wikipedia.org/wiki/Sudoku) puzzles of any size (4, 9, or 16).

## Compilation

```
g++ -O3 -Wall -o sudoku main.cpp Sudoku.cpp
```

## Usage

The binary takes one argument that specifies a file to read a board from. Sample boards are in the `boards` folder.

```
./sudoku boards/board9.txt
./sudoku boards/board4.txt
etc.
```

Each row consist of whitespace separated numbers, with a blank represented by `0`. The board must be square and have dimensions 4x4, 9x9, or 16x16. Every number (other than the blanks `0`) must be in the range `[1, size]`.
