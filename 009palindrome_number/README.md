# Palindrome Number

## Problem Statement

Given an integer x, return true if x is a palindrome, and false otherwise.

### Example 1:

    Input: x = 121
    Output: true
    Explanation: 121 reads as 121 from left to right and from right to left.

### Example 2:

    Input: x = -121
    Output: false
    Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

### Example 3:

    Input: x = 10
    Output: false
    Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

### Constraints:

    -2^31 <= x <= 2^31 - 1

## Approach

To determine if a number is a palindrome, we need to compare the number with its reverse. However, reversing the entire number might lead to integer overflow for large values, so instead, the approach reverses only the second half of the number.

## Complexity

- Time Complexity: O(length of number)

- Space Complexity: O(1)