# Longest Substring Without Repeating Characters

## Problem Statement

Given a string s, find the length of the longest substring without repeating characters.

## Approach

To solve the problem efficiently, we can use the sliding window technique with a two-pointer approach. We maintain a window that tracks characters from the string and adjust the window to remove repeating characters. A data structure like an array (for ASCII characters) or a hash map is used to store the most recent index of each character.

## Complexity

- Time Complexity: O(n), where n is the length of the string. Each character is visited at most twice (once by the end pointer and once by the start pointer).

- Space Complexity: O(1) if considering the array for ASCII characters (fixed size), or O(min(n, m)) where m is the number of possible unique characters, if using a dynamic data structure like a hash map.