#include "solution.h"

int main() {
    Solution solution;
    std::vector<std::vector<std::string>> result = solution.solveNQueens(5);

    for (const auto& queen_permutation : result) {
        bool is_first_row = true;
        std::cout << "[";
        for (const std::string& row : queen_permutation) {
            if (!is_first_row) {
                std::cout << ',';
            } else {
                is_first_row = false;
            }
            std::cout << "\"" << row << "\"";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}