#include "Sudoku.h"

Sudoku::Sudoku(std::istream &is)
{
    std::string in_line;
    while (getline(is, in_line)) {
        std::istringstream line_stream(in_line);
        std::istream_iterator<int> start(line_stream), eof;
        board.push_back(std::vector<int>(start, eof));
    }

    for (const auto &row : board) {
        if (row.size() != board.size()) {
            throw std::runtime_error("Board must be square.");
        }
    }

    const auto size = static_cast<int>(board.size());
    if (size != 4 && size != 9 && size != 16) {
        throw std::runtime_error("Board must have size 4, 9, or 16.");
    }

    line = std::string(board.size() * (size > 10 ? 5 : 4) + 1, '-');
    box_size = size == 16 ? 4 : (size == 9 ? 3 : 2);

    for (int i = size - 1; i >= 0; --i) {
        auto row = board[i];
        for (int j = size - 1; j >= 0; --j) {
            if (row[j] == 0) {
                blanks.emplace_back(i, j);
            } else if (row[j] < 0 || row[j] > size) {
                throw std::runtime_error("Board must consist of numbers within the appropriate range.");
            }
        }
    }
}

bool Sudoku::solve()
{
    if (blanks.empty())
        return true;
    auto row_col = blanks.back();
    int row = row_col.first;
    int col = row_col.second;

    for (std::size_t num = 1; num <= board.size(); ++num) {
        if (is_safe(row, col, num)) {
            board[row][col] = num;
            blanks.pop_back();
            if (solve())
                return true;

            board[row][col] = 0;
            blanks.push_back(row_col);
        }
    }
    return false;
}

bool Sudoku::in_row(int row, int num) const
{
    return std::find(board[row].cbegin(), board[row].cend(), num) != board[row].cend();
}

bool Sudoku::in_col(int col, int num) const
{
    for (const auto &row : board) {
        if (row[col] == num)
            return true;
    }
    return false;
}

bool Sudoku::in_box(int br, int bc, int num) const
{
    for (int i = br * box_size, iend = i + box_size; i < iend; ++i) {
        for (int j = bc * box_size, jend = j + box_size; j < jend; ++j) {
            if (board[i][j] == num)
                return true;
        }
    }
    return false;
}

bool Sudoku::is_safe(int row, int col, int num) const
{
    return !(in_row(row, num) ||
             in_col(col, num) ||
             in_box(row / box_size, col / box_size, num));
}

std::ostream &operator<<(std::ostream &os, const Sudoku &sudoku)
{
    os << sudoku.line << '\n';
    if (sudoku.board.size() > 10) {
        for (const auto &row : sudoku.board) {
            os << '|';
            for (auto i : row) {
                if (i)
                    os << " " << std::setw(2) << i << " |";
                else
                    os << " __ |";
            }
            os << '\n'
               << sudoku.line << '\n';
        }
    } else {
        for (const auto &row : sudoku.board) {
            os << '|';
            for (auto i : row) {
                if (i)
                    os << " " << i << " |";
                else
                    os << " _ |";
            }
            os << '\n'
               << sudoku.line << '\n';
        }
    }

    return os;
}
