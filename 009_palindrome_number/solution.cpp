#include <fstream>
#include <iostream>
#include <vector>

class Solution {
public:
    bool isPalindrome(int x) {
        // Негативные числа и числа, заканчивающиеся на 0, не могут быть
        // палиндромами, за исключением 0.
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;

        int reverse_x = 0;
        while (x > reverse_x) {
            reverse_x = reverse_x * 10 + x % 10;
            x /= 10;
        }

        // Для четного количества цифр x == reverse_x,
        // Для нечетного - мы отбрасываем среднюю цифру reverse_x / 10
        return x == reverse_x || x == reverse_x / 10;
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
        std::cout << example << std::endl;
        std::cout << std::boolalpha << solution.isPalindrome(example)
                  << std::endl;
    }

    return 0;
}

005longest_palindromic_substring