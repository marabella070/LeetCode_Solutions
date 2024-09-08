#include <array>
#include <fstream>
#include <iostream>
#include <string>

class Solution {
public:
    std::string intToRoman(int num) {
        std::array<std::pair<int, std::string>, 13> roman = {{{1000, "M"},
                                                              {900, "CM"},
                                                              {500, "D"},
                                                              {400, "CD"},
                                                              {100, "C"},
                                                              {90, "XC"},
                                                              {50, "L"},
                                                              {40, "XL"},
                                                              {10, "X"},
                                                              {9, "IX"},
                                                              {5, "V"},
                                                              {4, "IV"},
                                                              {1, "I"}}};

        std::string result;
        for (const auto& [value, symbol] : roman) {
            while (num >= value) {
                result += symbol;
                num -= value;
            }
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    using namespace std::string_literals;

    if (argc != 2) {
        std::cout << "Wrong format of input data"s << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        std::cout << "Couldn't open \"" << argv[1] << "\" file"s << std::endl;
        return 1;
    }

    Solution solution;

    int example;
    while (input >> example) {
        std::cout << "Roman representation of the number - "s << example
                  << " is: "s << solution.intToRoman(example) << std::endl;
    }

    return 0;
}