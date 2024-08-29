# Two Sum

## Problem Statement
Given an array of integers `nums` and an integer `target`, return indices of the two numbers such that they add up to `target`.

## Approach
I used a hash map to store the difference between the target and each element, along with its index. This allows for O(1) lookup time for each complement, resulting in an O(n) time complexity overall.

## Complexity
- Time: O(n)
- Space: O(n)
