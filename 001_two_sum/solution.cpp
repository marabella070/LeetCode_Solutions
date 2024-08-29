#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public: 
    std::vector<int> twoSum(std::vector<int>&nums, int target) {
        std::unordered_map<int, int> storage;
        storage.reserve(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            if (auto it = storage.find(target - nums[i]); it != storage.end()) {
                return {it->second, i};
            } 
            storage.emplace(nums[i], i);
        }
        return {};
    }
};

struct InputParameters {
    std::vector<int> nums;
    int target;
};

int main() {
    using namespace std::string_literals;

    InputParameters example_first{ {2, 7, 11, 15}, 9 };
    InputParameters example_second{ {3, 2, 4}, 6 }; 
    InputParameters example_third{ {3, 3}, 6 };

    Solution solution;

    auto PrintAnswer = [] (std::vector<int>& storage) {
        bool is_first = true;
        std::cout << '[';
        for (int element : storage) {
            if (is_first) {
                is_first = false;
            } else {
                std::cout << ',';
            }
            std::cout << element;
        }
        std::cout << ']' << std::endl;
    };

    std::vector<int> answer_first = solution.twoSum(example_first.nums, example_first.target);
    PrintAnswer(answer_first);
    
    std::vector<int> answer_second = solution.twoSum(example_second.nums, example_second.target);
    PrintAnswer(answer_second);
    
    std::vector<int> answer_third = solution.twoSum(example_third.nums, example_third.target);
    PrintAnswer(answer_third);

    return 0;
}