# Longest Palindromic Substring

## Problem Statement

Given a string s, return the longest **palindromic substring** in s.

### Example 1:

    Input: s = "babad"
    Output: "bab"
    Explanation: "aba" is also a valid answer.

### Example 2:

    Input: s = "cbbd"
    Output: "bb"

### Constraints:

- 1 <= s.length <= 1000
- s consist of only digits and English letters.

## Approach

The solution uses Manacher's Algorithm, which finds the longest palindromic substring in linear time **O(n)**. The algorithm handles both even- and odd-length palindromes by transforming the input string into a new format with additional boundary characters (e.g., **#a#b#b#a#**), ensuring uniform treatment of palindromes of both lengths.

### Steps:

1. **Preprocessing (AddGrid):**

    The input string is transformed by inserting special characters (**#**) between each character and at the boundaries. This simplifies the palindrome-checking process by unifying odd- and even-length palindromes.

2. **Main Loop (Palindromic Radius Calculation):**

    The algorithm maintains the largest palindrome found so far using two pointers, **left** and **right**, representing the bounds of the current longest palindrome. For each position in the string:

    - If the current position lies within the bounds of the known palindrome, a mirrored position is calculated, and the palindrome size is initially set as the minimum of the mirrored value or the remaining space within the bounds.
    
    - The palindrome is expanded by comparing characters on both sides of the current center, adjusting the boundaries when necessary.

3. **Post-processing (RemoveGrid):**

    After calculating the palindrome radii, the algorithm removes the special characters from the result, returning the actual longest palindromic substring from the original input.

## Complexity

- Time Complexity: 

    The time complexity is O(n), where n is the length of the input string. Each character is processed at most twice — once when expanding the palindrome and once when updating the boundaries.

- Space Complexity: 

    The space complexity is **O(n)** due to the additional array **d** that stores the palindrome radii and the transformed string (**buffer**), which has twice the length of the original string plus one.