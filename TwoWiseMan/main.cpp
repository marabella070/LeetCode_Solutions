#include <iostream>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

const int UPPER_BOUND = 99;
const int LOWER_BOUND = 2;

bool isPrime(int number) {
    if (number <= 1)
        return false;
    if (number <= 3) // 2 and 3 prime
        return true;
    if ((number % 2 == 0) || (number % 3 == 0))
        return false;

    for (int i = 5; i <= std::sqrt(number); i += 6) {
        if ((number % i == 0) || (number % (i + 2) == 0)) 
            return false;
    }
    return true;
}

std::vector<std::pair<int, int>> FindFactors(int n) {
    std::vector<std::pair<int, int>> factors;
    for (int i = LOWER_BOUND; i <= std::sqrt(n); ++i) {
        if (n % i == 0) {
            factors.push_back({i, n / i});
        }
    }
    return factors;
}

std::vector<std::pair<int, int>> FindSums(int n) {
    std::vector<std::pair<int, int>> sums;
    for (int i = LOWER_BOUND; i <= (n / 2); ++i) {
        int j = n - i;
        sums.push_back({i, j});
    }
    return sums;
}

std::set<int> GeneratePossibleAliNumbers() {
    std::set<int> ali_numbers;
    for (int i = LOWER_BOUND; i <= UPPER_BOUND; ++i) {
        for (int j = i; j <= UPPER_BOUND; ++j) {
            if (isPrime(i) && isPrime(j)) {
                continue;
            }
            ali_numbers.insert(i * j);
        } 
    } 
    return ali_numbers;
}

std::set<int> GeneratePossibleValiNumbers() {
    std::set<int> all_possible_amounts;
    for (int i = LOWER_BOUND; i <= UPPER_BOUND; ++i) {
        for (int j = i; j <= UPPER_BOUND; ++j) {
            all_possible_amounts.insert(i + j);
        } 
    } 
    std::set<int> vali_numbers;

    for (int possible_amount : all_possible_amounts) {
        bool is_vali_number = true;
        for (int i = LOWER_BOUND; i <= (possible_amount / 2); ++i) {
            int j = possible_amount - i;
            if (isPrime(i) && isPrime(j)) {
                is_vali_number = false;
                break;
            }
        }
        if (is_vali_number) {
            vali_numbers.insert(possible_amount);
        }
    }
    return vali_numbers;
}

int main() {
    std::set<int> vali_numbers = GeneratePossibleValiNumbers();
    std::set<int> raw_ali_numbers = GeneratePossibleAliNumbers();

    std::vector<int> clear_ali_numbers;

    for (int ali_number : raw_ali_numbers) {
        std::vector<std::pair<int, int>> factors = FindFactors(ali_number);

        int intersection_number = 0;
        std::pair<int, int> possible_answer;
        for (std::pair<int, int> factor : factors) {
            auto it = std::find(vali_numbers.begin(), vali_numbers.end(), factor.first + factor.second);
            if (it != vali_numbers.end()) {
                ++intersection_number;
                possible_answer = {factor.first, factor.second};
            }
            if (intersection_number > 1) {
                break;
            }
        }
        if (intersection_number == 1) {
            clear_ali_numbers.push_back(possible_answer.first * possible_answer.second);
        }
    }

    std::vector<std::pair<int, int>> answer;

    for (int vali_number : vali_numbers) {
        std::vector<std::pair<int, int>> all_sums = FindSums(vali_number);
        for (std::pair<int, int> sum : all_sums) {
            auto it = std::find(clear_ali_numbers.begin(), clear_ali_numbers.end(), sum.first * sum.second);
            if (it != clear_ali_numbers.end()) {
                answer.push_back(sum);
            }
        }
    }

    for (std::pair<int, int> element : answer) {
        std::cout << element.first << ", " << element.second << std::endl;
    }

    return 0;
}