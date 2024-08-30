# Add Two Numbers

## Problem Statement

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. The task is to add the two numbers and return the sum as a linked list. The returned linked list should also be in reverse order, with each node representing a single digit.

## Approach

To solve the problem, we traverse both linked lists while simultaneously adding the corresponding digits. We manage the carry from the addition of two digits and continue this process until we have processed all digits in both linked lists.

## Complexity

### Complexity
Time Complexity:
The time complexity of this solution is O(max(n, m)), where n and m are the lengths of the two input linked lists. This is because we traverse each list once.


### Space Complexity:
The space complexity is O(max(n, m)). This is due to the creation of a new linked list that stores the result, which, in the worst case, is as long as the longest input list plus one additional node for a possible carry.