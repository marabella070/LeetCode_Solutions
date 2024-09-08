#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
public:
    int romanToInt(std::string s) {
        std::unordered_map<char, int> roman = {
            {'I', 1},   {'V', 5},   {'X', 10},  {'L', 50},
            {'C', 100}, {'D', 500}, {'M', 1000}};

        int result = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (i < n - 1 && roman[s[i]] < roman[s[i + 1]]) {
                result -= roman[s[i]];
            } else {
                result += roman[s[i]];
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

    std::string example;
    while (std::getline(input, example)) {
        std::cout << "Roman number - "s << example << ", in integer equals: "s
                  << solution.romanToInt(example) << std::endl;
    }

    return 0;
}