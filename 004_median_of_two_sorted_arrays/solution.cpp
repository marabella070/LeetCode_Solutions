#include <array>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void PrintList(std::ostream& output, const std::vector<int>& storage);
std::vector<int> ParseList(std::istringstream& ss);
std::pair<std::vector<int>, std::vector<int>> ParseLine(
    const std::string& line);

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1,
                                  std::vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            std::swap(nums1, nums2);
        }

        int m = nums1.size();
        int n = nums2.size();
        int totalLength = m + n;
        int low = 0;
        int high = m;

        while (low <= high) {
            int partition1 = (low + high) / 2;
            int partition2 = (totalLength + 1) / 2 - partition1;

            int max_left1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
            int min_right1 = (partition1 == m) ? INT_MAX : nums1[partition1];

            int max_left2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
            int min_right2 = (partition2 == n) ? INT_MAX : nums2[partition2];

            if (max_left1 <= min_right2 && max_left2 <= min_right1) {
                if (totalLength % 2 == 0) {
                    return (std::max(max_left1, max_left2) +
                            std::min(min_right1, min_right2)) /
                           2.0;
                } else {
                    return std::max(max_left1, max_left2);
                }
            } else if (max_left1 > min_right2) {
                high = partition1 - 1;
            } else {
                low = partition1 + 1;
            }
        }
        throw std::invalid_argument("Input arrays are not sorted.");
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
        auto lists = ParseLine(buffer);
        PrintList(std::cout, lists.first);
        PrintList(std::cout, lists.second);
        std::cout << solution.findMedianSortedArrays(lists.first, lists.second)
                  << std::endl;
    }

    return 0;
}

void PrintList(std::ostream& output, const std::vector<int>& storage) {
    bool is_first = true;
    output << '[';
    for (auto element : storage) {
        if (is_first) {
            is_first = false;
        } else {
            output << ", ";
        }
        std::cout << element;
    }
    output << ']';
    output << std::endl;
}

std::vector<int> ParseList(std::istringstream& ss) {
    std::vector<int> result;
    int number;
    char ch;
    ss >> ch;
    while (ss >> number) {
        result.push_back(number);
        ss >> ch;
        if (ch == ']') {
            break;
        }
    }
    return result;
}

std::pair<std::vector<int>, std::vector<int>> ParseLine(
    const std::string& line) {
    std::istringstream ss(line);
    char ch;

    std::vector<int> first_list = ParseList(ss);
    ss >> ch;
    std::vector<int> second_list = ParseList(ss);

    return {std::move(first_list), std::move(second_list)};
}