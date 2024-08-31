#include <array>
#include <fstream>
#include <iostream>
#include <string>

class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::array<int, 128> contained_symbols;
        contained_symbols.fill(-1);
        int max_length = 0;
        int start = 0;

        for (int end = 0; end < s.size(); ++end) {
            if (contained_symbols[s[end]] >= start) {
                start = contained_symbols[s[end]] + 1;
            }
            contained_symbols[s[end]] = end;
            max_length = std::max(max_length, end - start + 1);
        }
        return max_length;
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

    std::string buffer;

    while (std::getline(input, buffer)) {
        std::cout << buffer << " - ";
        std::cout << solution.lengthOfLongestSubstring(buffer) << std::endl;
    }

    return 0;
}