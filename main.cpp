
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Sudoku.h"

using std::cerr;
using std::cout;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Must pass file name to read board from as argument.\n";
        return -1;
    }

    std::ifstream board_file(argv[1]);
    if (!board_file.is_open()) {
        cerr << "Unable to open file " << argv[1] << '\n';
        return -1;
    }

    Sudoku sudoku;

    try {
        sudoku = Sudoku(board_file);
    } catch (const std::runtime_error &err) {
        cerr << err.what() << '\n';
        return -1;
    }

    const auto size = sudoku.board_size();
    cout << "Successfully read board of size " << size << '\n';

    cout << "\nBoard:\n\n"
         << sudoku;

    cout << "\nSolving...\n";

    auto start = high_resolution_clock::now();
    sudoku.solve();
    auto stop = high_resolution_clock::now();

    auto us = duration_cast<microseconds>(stop - start);
    auto ms = us / 1000;
    us %= 1000;
    auto sec = ms / 1000;
    ms %= 1000;

    cout << "Duration: " << sec.count() << " s "
         << ms.count() << " ms "
         << us.count() << " us.\n";

    cout << "\nBoard:\n\n"
         << sudoku;

    return 0;
}
