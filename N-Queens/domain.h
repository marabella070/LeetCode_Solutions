#pragma once

#include <vector>
#include <set>
#include <cstdio>
#include <cmath>

#include <array>

namespace chess {

template <size_t N>
using ChessBoard = std::array<std::array<bool, N>, N>;


// using ChessBoard = std::vector<std::vector<bool>>;
using Column = int;
using Row = int;

struct ChessSquare {
    ChessSquare() = default;

    explicit ChessSquare (Row row, Column column) 
        : row_(row), column_(column) {}

    bool operator==(const ChessSquare& other) const {
        return (row_ == other.row_) && (column_ == other.column_);
    }

    bool operator!=(const ChessSquare& other) const {
        return !(*this == other);
    }

    bool operator<(const ChessSquare& other) const {
        if (row_ < other.row_) {
            return true;
        } else if (row_ > other.row_) {
            return false;
        }

        return column_ < other.column_;
    }

    bool operator<= (const ChessSquare& other) const {
        return (*this == other) || (*this < other);
    }

    bool operator>(const ChessSquare& other) const {
        return !(*this <= other);
    }

    bool operator>=(const ChessSquare& other) const {
        return !(*this < other);
    }

    size_t hash() const {
        size_t hash_row = std::hash<size_t>{}(row_);
        size_t hash_column = std::hash<size_t>{}(column_);
        return hash_row ^ (hash_column << 1);
    }

    Row row_ = 0;
    Column column_ = 0;
};

} // chess namespace