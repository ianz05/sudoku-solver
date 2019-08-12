#pragma once

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class Sudoku
{
public:
    Sudoku() = default;
    explicit Sudoku(std::istream &is);

    auto board_size() const { return board.size(); }

    bool solve();

private:
    std::vector<std::vector<int>> board;
    std::string line;
    int box_size;
    std::vector<std::pair<int, int>> blanks;

    bool in_row(int row, int num) const;
    bool in_col(int col, int num) const;
    bool in_box(int bx, int by, int num) const;
    bool is_safe(int row, int col, int num) const;

    friend std::ostream &operator<<(std::ostream &out, const Sudoku &sudoku);
};
