#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

// Helper function to find and remove an element from a vector
void deleteElement(std::vector<std::string>& vec, const std::string& elem) {
    vec.erase(std::remove(vec.begin(), vec.end(), elem), vec.end());
}

// Function to print the current possible values (for debugging purposes)
void printState(const std::string& prefix, 
                const std::map<int, std::vector<std::string>>& muls, 
                const std::map<int, std::vector<std::string>>& sums) {
    std::cout << prefix << "\nPossible muls:\n";
    for (const auto& [key, value] : muls) {
        std::cout << key << " (" << value.size() << "): ";
        for (const auto& pair : value) {
            std::cout << pair << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nPossible sums:\n";
    for (const auto& [key, value] : sums) {
        std::cout << key << " (" << value.size() << "): ";
        for (const auto& pair : value) {
            std::cout << pair << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    using namespace std::string_literals;

    int max_num = (argc > 1) ? std::stoi(argv[1]) : 99;
    bool DEBUG = false;

    // Possible values for sums and muls
    std::map<int, std::vector<std::string>> sums;
    std::map<int, std::vector<std::string>> muls;

    // Initially, no information - all pairs are possible
    for (int i = 2; i <= max_num; ++i) {
        for (int j = i; j <= max_num; ++j) {
            sums[i + j].push_back(std::to_string(i) + "+" + std::to_string(j));
            muls[i * j].push_back(std::to_string(i) + "*" + std::to_string(j));
        }
    }

    std::cout << "Stage #1"s << std::endl;

    // Stage 1: Ali does not know x, y => mul is not a unique multiplication
    // And Vali knows this beforehand => sum is not sum of such a pair
    std::vector<std::string> del_muls_from_sum;
    for (int i = 2; i <= max_num; ++i) {
        for (int j = i; j <= max_num; ++j) {
            if (muls[i * j].size() == 1) { //Delete all multiplication with one factor's pair(because it's mulitiplication of prime numbers)
                muls.erase(i * j);
                if (sums.find(i + j) != sums.end()) {
                    del_muls_from_sum.insert(del_muls_from_sum.end(), sums[i + j].begin(), sums[i + j].end());
                    sums.erase(i + j);
                }
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Stage #2"s << std::endl;

    // Remove corresponding muls for deleted sums
    for (const auto& sum : del_muls_from_sum) {
        int a, b;
        sscanf(sum.c_str(), "%d+%d", &a, &b);
        if (muls.find(a * b) != muls.end()) {
            deleteElement(muls[a * b], std::to_string(a) + "*" + std::to_string(b));
            if (muls[a * b].empty()) {
                muls.erase(a * b);
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Stage #3"s << std::endl;

    // Stage 3: Ali now knows the numbers => mul is unique
    std::map<int, std::vector<std::string>> rest_sums;
    for (int i = 2; i <= max_num; ++i) {
        for (int j = i; j <= max_num; ++j) {
            if (muls.find(i * j) != muls.end()) {
                if (muls[i * j].size() > 1) {
                    muls.erase(i * j);
                } else if (muls[i * j].size() == 1 && sums.find(i + j) != sums.end()) {
                    rest_sums[i + j].push_back(std::to_string(i) + "+" + std::to_string(j));
                }
            }
        }
    }
    sums = rest_sums;

    std::cout << std::endl;
    std::cout << "Stage #4"s << std::endl;

    // Stage 4: Vali now knows the numbers => sum is unique
    std::map<int, std::vector<std::string>> rest_muls;
    for (int i = 2; i <= max_num; ++i) {
        for (int j = i; j <= max_num; ++j) {
            if (sums.find(i + j) != sums.end()) {
                if (sums[i + j].size() > 1) {
                    sums.erase(i + j);
                } else if (sums[i + j].size() == 1 && muls.find(i * j) != muls.end()) {
                    rest_muls[i * j].push_back(std::to_string(i) + "*" + std::to_string(j));
                }
            }
        }
    }
    muls = rest_muls;

    printState("Final solutions:", muls, sums);

    return 0;
}