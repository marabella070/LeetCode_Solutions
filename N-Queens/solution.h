#pragma once

#include "domain.h"

#include <string>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <set>
#include <fstream>


template <size_t N>
using ChessCombination = std::array<chess::ChessSquare, N>;


namespace std {
    template <size_t N>
    struct hash<ChessCombination<N>> {
        std::size_t operator()(const ChessCombination<N>& chess_combination) const {
            size_t combination_size = chess_combination.size();
            size_t result = 0;
            for (const chess::ChessSquare& queen_position : chess_combination) {
                result += std::pow(17, combination_size--) * queen_position.hash();
            }

            return result;
        }
    };

    template <size_t N>
    struct equal_to<ChessCombination<N>> {
        bool operator()(const ChessCombination<N>& lhs, const ChessCombination<N>& rhs) const {
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        }
    };

} // std namespace 



class Solution {
public:
    template <size_t N>
    void solveNQueens() {
        chess::ChessBoard<N> posible_positions = InitializeBoard<N>();
        ChessCombination<N> current_combination;
        std::unordered_set<ChessCombination<N>> raw_result;

        Find(raw_result, current_combination, posible_positions, 0);

        PrintAnswers(raw_result);
    }

private:
    template <size_t N>
    void PrintAnswers(const std::unordered_set<ChessCombination<N>>& raw_result) {
        using namespace std::string_literals;
        
        std::ofstream out("solution.txt");

        size_t count = 0;
        for (const ChessCombination<N>& queen_combination : raw_result) {
            chess::ChessBoard<N> chess_board = InitializeBoard<N>();

            for (const chess::ChessSquare& chess_square : queen_combination) {
                chess_board[chess_square.row_][chess_square.column_] = false;
            }

            out << "Number#"s << (count++) << std::endl;
            out << '|' << std::string(N, '-') << '|' << std::endl;
            for (int row = 0; row < N; ++row) {
                out << '|';
                for (int column = 0; column < N; ++column) {
                    out << ((chess_board[row][column]) ? '\'' : '*');
                }
                out << '|' << std::endl;
            }
            out << '|' << std::string(N, '-') << '|' << std::endl << std::endl;
        }
    }

    template <size_t N>
    chess::ChessBoard<N> InitializeBoard() {
        chess::ChessBoard<N> board;
        for (std::array<bool, N>& line : board) {
            std::fill(line.begin(), line.end(), true);
        }
        return board;
    }

    template <size_t N>
    void MarkVertical(chess::ChessBoard<N>& chess_board, chess::ChessSquare chess_square) {
        for (chess::Row row = 0; row < N; ++row) {
            chess_board[row][chess_square.column_] = false;
        }
    }

    template <size_t N>
    void MarkHorizontal(chess::ChessBoard<N>& chess_board, chess::ChessSquare chess_square) {
        for (chess::Column column = 0; column < N; ++column) {
            chess_board[chess_square.row_][column] = false;
        }
    }

    template <size_t N>
    void MarkDiagonale(chess::ChessBoard<N>& chess_board, chess::ChessSquare chess_square) {
        int delta = 0;

        auto within_board = [&] (int row, int column) {
            return (0 <= row && row < N) && (0 <= column && column < N);
        };

        //Mark over part of diagonale
        while (within_board(chess_square.row_ + delta, chess_square.column_ + delta)) {
            chess_board[chess_square.row_ + delta][chess_square.column_ + delta] = false;
            ++delta;
        }

        delta = 0;

        //Mark under part of diagonale
        while (within_board(chess_square.row_ - delta, chess_square.column_ - delta)) {
            chess_board[chess_square.row_ - delta][chess_square.column_ - delta] = false;
            ++delta;
        }

        delta = 0;

        // Убираем верхнюю часть побочной диагонали
        while (within_board(chess_square.row_ + delta, chess_square.column_ - delta)) {
            chess_board[chess_square.row_ + delta][chess_square.column_ - delta] = false;
            ++delta;
        }

        delta = 0;

        // Убираем нижнюю часть побочной диагонали
        while (within_board(chess_square.row_ - delta, chess_square.column_ + delta)) {
            chess_board[chess_square.row_ - delta][chess_square.column_ + delta] = false;
            ++delta;
        }
    } 

    template <size_t N>
    chess::ChessBoard<N> MarkQueenMoves(chess::ChessBoard<N> chess_board, chess::ChessSquare chess_square) {
        MarkVertical(chess_board, chess_square);
        MarkHorizontal(chess_board, chess_square);
        MarkDiagonale(chess_board, chess_square);

        return chess_board;
    } 

    template <size_t N>
    void Find(std::unordered_set<ChessCombination<N>>& raw_result, ChessCombination<N>& current_combination, 
                chess::ChessBoard<N> posible_positions, int queen_number) {

        if (queen_number >= N) {
            ChessCombination<N> sorted_combination = current_combination;
            std::sort(sorted_combination.begin(), sorted_combination.end());
            raw_result.insert(std::move(sorted_combination));
            return;
        }

        for (chess::Row row = queen_number; row < N; ++row) {
            for (chess::Column column = 0; column < N; ++column) {
                if (posible_positions[row][column]) {
                    chess::ChessSquare next_queen(row, column);
                    current_combination[queen_number] = next_queen;
                    Find (raw_result, current_combination, MarkQueenMoves(posible_positions, next_queen), queen_number + 1);
                }
            }
        }
    }
};