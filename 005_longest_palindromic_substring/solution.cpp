#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*O(n^3)*/
// class Solution {
// public:
//     std::string longestPalindrome(std::string s) {
//         if (!s.size()) {
//             return "";
//         }
//         std::string result(1, s[0]);

//         for (int i= 0; i < s.size(); ++i) {
//             for (int j = i + 1; j < s.size(); ++j) {
//                 bool is_polindrome = true;
//                 int low = i;
//                 int high = j;
//                 while (low < high) {
//                     if (s[low] != s[high]) {
//                         is_polindrome = false;
//                         break;
//                     }
//                     ++low;
//                     --high;
//                 }
//                 if (is_polindrome && ((j - i + 1) > result.size())) {
//                     result = s.substr(i, (j - i + 1));
//                 }
//             }
//         }
//         return result;
//     }
// };

/*O(n^2)*/
// class Solution {
// public:
//     std::string longestPalindrome(std::string s) {
//         std::string result;
//         int low;
//         int high;

//         for (int i = 0; i < s.size(); ++i) {
//             //odd polindrome
//             low = i;
//             high = i;
//             while ((0 <= low && high < s.size()) && s[low] == s[high]) {
//                 if ((high - low + 1) > result.size()) {
//                     result = s.substr(low, high - low + 1);
//                 }
//                 --low;
//                 ++high;
//             }

//             //even polindrome
//             low = i;
//             high = i + 1;
//             while ((0 <= low && high < s.size()) && s[low] == s[high]) {
//                 if ((high - low + 1) > result.size()) {
//                     result = s.substr(low, high - low + 1);
//                 }
//                 --low;
//                 ++high;
//             }
//         }

//         return result;
//     }
// };

/*O(n)*/
class Solution {
public:
    std::string AddGrid(const std::string& str) {
        std::string result;
        result.reserve((2 * str.size()) + 1);
        result.push_back('#');
        for (char element : str) {
            result.push_back(element);
            result.push_back('#');
        }
        return result;
    }

    std::string RemoveGrid(const std::string& str) {
        std::string result;
        result.reserve(str.size() / 2);
        for (char element : str) {
            if (element != '#') {
                result.push_back(element);
            }
        }
        return result;
    }

    std::string longestPalindrome(std::string s) {
        if (s.size() <= 1) return s;
        if (s.size() == 2) {
            return (s[0] == s[1]) ? s : std::string(1, s[0]);
        }

        std::string result;
        std::vector<int> d((2 * s.size()) + 1, 0);
        std::string buffer = AddGrid(s);

        int left = -1;
        int right = -1;
        for (int i = 0; i < buffer.size(); ++i) {
            if (i <= right) {
                int mirror_i = (right - i) + left;
                d[i] = std::min(d[mirror_i], right - i + 1);
            }

            int low = i - d[i];
            int high = i + d[i];
            while ((0 <= low && high < buffer.size()) &&
                   buffer[low] == buffer[high]) {
                --low;
                ++high;
                ++d[i];
            }

            if ((high - 1) > right) {
                left = low + 1;
                right = high - 1;
            }
        }

        int start = 0;
        int max_len = 1;

        for (int i = 0; i < d.size(); ++i) {
            if (d[i] > max_len) {
                start = i - d[i] + 1;
                max_len = d[i];
            }
        }

        return RemoveGrid(buffer.substr(start, (max_len * 2) - 1));
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
        std::cout << "For string - "s << example
                  << ", longest palindromic substring is - "s
                  << solution.longestPalindrome(example) << std::endl;
    }

    return 0;
}