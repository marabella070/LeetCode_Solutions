#include <array>
#include <cstdio>
#include <algorithm>
#include <random>
#include <cmath>

struct ChessSquare {
    int row;
    int column;
};


template <size_t N>
using QueenArrangement = std::array<int, N>;

template <size_t N>
QueenArrangement<N> GenerateRandomPermutation(const QueenArrangement<N>& queen_arrangement) {
    QueenArrangement<N> random_permutation(queen_arrangement.begin(), queen_arrangement.end());
    
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(random_permutation.begin(), random_permutation.end(), g);
    return random_permutation;
}

bool AreQueensAttacking(const ChessSquare& lhs, const ChessSquare& rhs) {
    return ((lhs.row == rhs.row) || (lhs.column == rhs.column) || 
                (std::abs(lhs.row - rhs.row) == std::abs(lhs.column - rhs.column)));
}

template <size_t N>
int CountCollisions(const QueenArrangement<N>& queen_arrangement) {
    int collisions_count = 0;

    for (int i = 0; i < N; ++i) {
        ChessSquare lhs{i + 1, queen_arrangement[i]};
        if (lhs.column == 0) {
            continue;
        }

        for (int j = i + 1; j < N; ++j) {
            ChessSquare rhs{j + 1, queen_arrangement[j]};
            if (rhs.column == 0) {
                continue;
            }

            if (AreQueensAttacking(lhs, rhs)) {
                ++collisions_count;
            }
        }
    }
    return collisions_count;
}

template <size_t N>
int CollisionSearchAndCorrection (QueenArrangement<N>& queen_arrangement, int collisions_count) {
    for (int row = 0; row < N; ++row) {
        ChessSquare lhs{row + 1, queen_arrangement[row]};
        if (lhs.column == 0) {
            continue;
        }

        for (int column = 0; column < N; ++column) {
            ChessSquare rhs{column + 1, queen_arrangement[column]};
            if (rhs.column == 0) {
                continue;
            }

            if (AreQueensAttacking(lhs, rhs)) {
                std::swap(queen_arrangement[lhs.row], queen_arrangement[rhs.row]);
                int new_collisions_count = CountCollisions(queen_arrangement);
                if (new_collisions_count < collisions_count) {
                    return CollisionSearchAndCorrection(queen_arrangement, new_collisions_count);
                }
                std::swap(queen_arrangement[lhs.row], queen_arrangement[rhs.row]);
            }
        }
    }
    return collisions_count;
}

template <size_t N>
QueenArrangement<N> QueenSearch(const QueenArrangement<N>& queen_arrangement) {
    QueenArrangement<N> random_permutation;
    do {
        random_permutation = GenerateRandomPermutation(queen_arrangement);
        int collisions_count = CountCollisions(random_permutation);
    } while (!CollisionSearchAndCorrection(random_permutation, collisions_count));
    return random_permutation;
}