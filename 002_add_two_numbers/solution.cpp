#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

struct ListNode {
public:
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}

    size_t size() const {
        size_t size = 1;
        ListNode* walker = next;
        while (walker) {
            ++size;
            walker = walker->next;
        }
        return size;
    }

    ~ListNode() {
        if (next) {
            delete next;
        }
    }

public:
    int val;
    ListNode* next;
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr;
        ListNode** current_node = &head;
        int current_sum = 0;

        while (l1 || l2 || current_sum) {
            if (l1) {
                current_sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                current_sum += l2->val;
                l2 = l2->next;
            }

            *current_node = new ListNode(current_sum % 10);
            current_node = &((*current_node)->next);
            current_sum /= 10;
        }
        return head;
    }
};

void PrintList(std::ostream& output, ListNode* list);
std::unique_ptr<ListNode> ParseList(std::istringstream& ss);
std::pair<std::unique_ptr<ListNode>, std::unique_ptr<ListNode>> ParseLine(
    const std::string& line);

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
        PrintList(std::cout, lists.first.get());
        PrintList(std::cout, lists.second.get());
        std::unique_ptr<ListNode> answer(
            solution.addTwoNumbers(lists.first.get(), lists.second.get()));
        PrintList(std::cout, answer.get());
    }

    return 0;
}

void PrintList(std::ostream& output, ListNode* list) {
    bool is_first = true;
    output << '[';
    while (list) {
        if (is_first) {
            is_first = false;
        } else {
            output << ", ";
        }
        output << list->val;
        list = list->next;
    }
    output << ']';
    output << std::endl;
}

std::unique_ptr<ListNode> ParseList(std::istringstream& ss) {
    std::unique_ptr<ListNode> result;
    ListNode* buffer = nullptr;
    int number;
    char ch;

    ss >> ch;
    while (ss >> number) {
        if (!result) {
            result = std::make_unique<ListNode>(number);
            buffer = result.get();
        } else {
            buffer->next = new ListNode(number);
            buffer = buffer->next;
        }
        ss >> ch;
        if (ch == ']') {
            break;
        }
    }

    return result;
}

std::pair<std::unique_ptr<ListNode>, std::unique_ptr<ListNode>> ParseLine(
    const std::string& line) {
    std::istringstream ss(line);
    char ch;

    std::unique_ptr<ListNode> first_list = ParseList(ss);
    ss >> ch;
    std::unique_ptr<ListNode> second_list = ParseList(ss);

    return {std::move(first_list), std::move(second_list)};
}