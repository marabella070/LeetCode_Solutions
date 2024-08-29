#pragma once

#include <cmath>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace chess {
using Board = std::vector<std::vector<bool>>;
using Combination = std::vector<int>;

struct Square {
    int row;
    int column;
};

}  // namespace chess

namespace std {
template <>
struct hash<chess::Combination> {
    std::size_t operator()(const chess::Combination& chess_combination) const {
        size_t result = 0;
        size_t combination_size = chess_combination.size();

        for (int row = 0; row < combination_size; ++row) {
            result +=
                std::pow(17, combination_size - row) * chess_combination[row];
        }
        return result;
    }
};
}  // namespace std

class Solution {
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        chess::Board posible_positions = InitializeBoard(n);
        chess::Combination current_combination(n);
        std::unordered_set<chess::Combination> found_combinations;

        Find(found_combinations, current_combination, posible_positions, 0, n);

        return PrintAnswers(found_combinations);
    }

    int totalNQueens(int n) {
        chess::Board posible_positions = InitializeBoard(n);
        chess::Combination current_combination(n);
        std::unordered_set<chess::Combination> found_combinations;

        Find(found_combinations, current_combination, posible_positions, 0, n);

        return static_cast<int>(found_combinations.size());
    }

private:
    std::vector<std::vector<std::string>> PrintAnswers(
        const std::unordered_set<chess::Combination>& queen_combinations) {
        std::vector<std::vector<std::string>> result;

        for (const chess::Combination& queen_combination : queen_combinations) {
            std::vector<std::string> string_combination;
            for (int column_number : queen_combination) {
                std::string string_row(queen_combination.size(), '.');
                string_row[column_number] = 'Q';
                string_combination.push_back(std::move(string_row));
            }
            result.push_back(std::move(string_combination));
        }
        return result;
    }

    chess::Board InitializeBoard(int n) {
        chess::Board board(n, std::vector<bool>(n, true));
        return board;
    }

    void MarkVertical(chess::Board& chess_board, chess::Square chess_square,
                      int N) {
        for (int row = 0; row < N; ++row) {
            chess_board[row][chess_square.column] = false;
        }
    }

    void MarkHorizontal(chess::Board& chess_board, chess::Square chess_square,
                        int N) {
        for (int column = 0; column < N; ++column) {
            chess_board[chess_square.row][column] = false;
        }
    }

    void MarkDiagonale(chess::Board& chess_board, chess::Square chess_square,
                       int N) {
        int delta = 0;

        auto within_board = [&](int row, int column) {
            return (0 <= row && row < N) && (0 <= column && column < N);
        };

        // Mark over part of diagonale
        while (within_board(chess_square.row + delta,
                            chess_square.column + delta)) {
            chess_board[chess_square.row + delta][chess_square.column + delta] =
                false;
            ++delta;
        }

        delta = 0;

        // Mark under part of diagonale
        while (within_board(chess_square.row - delta,
                            chess_square.column - delta)) {
            chess_board[chess_square.row - delta][chess_square.column - delta] =
                false;
            ++delta;
        }

        delta = 0;

        // Убираем верхнюю часть побочной диагонали
        while (within_board(chess_square.row + delta,
                            chess_square.column - delta)) {
            chess_board[chess_square.row + delta][chess_square.column - delta] =
                false;
            ++delta;
        }

        delta = 0;

        // Убираем нижнюю часть побочной диагонали
        while (within_board(chess_square.row - delta,
                            chess_square.column + delta)) {
            chess_board[chess_square.row - delta][chess_square.column + delta] =
                false;
            ++delta;
        }
    }

    chess::Board MarkQueenMoves(chess::Board chess_board,
                                chess::Square chess_square, int N) {
        MarkVertical(chess_board, chess_square, N);
        MarkHorizontal(chess_board, chess_square, N);
        MarkDiagonale(chess_board, chess_square, N);

        return chess_board;
    }

    void Find(std::unordered_set<chess::Combination>& raw_result,
              chess::Combination& current_combination,
              chess::Board posible_positions, int queen_number, int N) {
        if (queen_number >= N) {
            raw_result.insert(current_combination);
            return;
        }

        for (int column = 0; column < N; ++column) {
            if (posible_positions[queen_number][column]) {
                current_combination[queen_number] = column;
                Find(raw_result, current_combination,
                     MarkQueenMoves(posible_positions,
                                    chess::Square{queen_number, column}, N),
                     queen_number + 1, N);
            }
        }
    }
};