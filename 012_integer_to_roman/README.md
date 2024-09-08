# Integer to Roman

## Problem Statement

Seven different symbols represent Roman numerals with the following values:

| Symbol | Value |
|--------|-------|
|I       |1      |
|V       |5      |
|X       |10     |
|L       |50     |
|C       |100    |
|D       |500    |
|M       |1000   |

Roman numerals are formed by appending the conversions of decimal place values from highest to lowest. Converting a decimal place value into a Roman numeral has the following rules:

- If the value does not start with 4 or 9, select the symbol of the maximal value that can be subtracted from the input, append that symbol to the result, subtract its value, and convert the remainder to a Roman numeral.

- If the value starts with 4 or 9 use the subtractive form representing one symbol subtracted from the following symbol, for example, 4 is 1 (I) less than 5 (V): IV and 9 is 1 (I) less than 10 (X): IX. Only the following subtractive forms are used: 4 (IV), 9 (IX), 40 (XL), 90 (XC), 400 (CD) and 900 (CM).

- Only powers of 10 (I, X, C, M) can be appended consecutively at most 3 times to represent multiples of 10. You cannot append 5 (V), 50 (L), or 500 (D) multiple times. If you need to append a symbol 4 times use the subtractive form.

Given an integer, convert it to a Roman numeral.

### Example 1:

    Input: num = 3749

    Output: "MMMDCCXLIX"

    Explanation:

    3000 = MMM as 1000 (M) + 1000 (M) + 1000 (M)
    700 = DCC as 500 (D) + 100 (C) + 100 (C)
    40 = XL as 10 (X) less of 50 (L)
    9 = IX as 1 (I) less of 10 (X)
    Note: 49 is not 1 (I) less of 50 (L) because the conversion is based on decimal places

### Example 2:

    Input: num = 58

    Output: "LVIII"

    Explanation:

    50 = L
    8 = VIII

### Example 3

    Input: num = 1994

    Output: "MCMXCIV"

    Explanation:

    1000 = M
    900 = CM
    90 = XC
    4 = IV

### Constraints:

- 1 <= num <= 3999

## Approach

The solution to the **Integer to Roman** problem relies on a **greedy algorithm**. We map the largest Roman numeral symbols to their corresponding integer values using a static lookup table (**std::array<std::pair<int, std::string>, 13>**). This table is sorted in descending order based on the integer values.

For each symbol in the table, we perform the following steps:

1. **Iterate through the symbols**: Starting from the largest value (1000), we repeatedly subtract the value from the input integer (num) as long as the integer is greater than or equal to the value.

2. **Append the corresponding Roman numeral**: For each subtraction, we append the associated Roman numeral symbol to the result string.

3. **Move to the next symbol**: Once the integer becomes smaller than the current value, we move on to the next value and repeat the process.

4. **Stop when the integer is zero**: The process terminates when the integer has been fully converted to its Roman numeral representation.

This method ensures that the Roman numeral is built from the largest possible symbols first, producing the correct representation.

## Complexity

- Time Complexity: O(1)

    The time complexity is effectively constant because the Roman numeral system is limited to a fixed set of numerals. The solution iterates through at most 13 values (the number of entries in the lookup table), and each integer division and string concatenation operation is bounded. Even for the largest input (3999), the number of operations remains constant and small.

- Space Complexity: O(1)

    The space complexity is also constant, as the only additional space used is for storing the lookup table and the result string. No extra space is required that scales with the size of the input integer.