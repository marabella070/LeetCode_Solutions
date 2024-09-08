# Median of Two Sorted Arrays

## Problem Statement

Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

### Example 1:

    Input: nums1 = [1,3], nums2 = [2]
    Output: 2.00000
    Explanation: merged array = [1,2,3] and median is 2.

### Example 2:

    Input: nums1 = [1,2], nums2 = [3,4]
    Output: 2.50000
    Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

### Constraints:

    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106

## Approach

The problem requires finding the median of two sorted arrays, which can be solved using a binary search approach. Instead of merging the arrays, which would take **O(m+n)** time, we can find the median by dividing both arrays in such a way that half of the elements are on the left side of the median and half are on the right.

### Steps:

1. Swap the arrays if necessary to ensure that nums1 is the smaller array. This allows us to minimize the range for binary search.
2. Perform binary search on the smaller array, partitioning both arrays at indices that together sum up to half of the total number of elements.
3. Check if the partitions are correct by comparing the maximum elements of the left halves to the minimum elements of the right halves.
4. If the partitions are correct, calculate the median based on the parity (odd or even) of the total number of elements.

## Complexity

- Time Complexity: O(logmin(m,n))

The binary search is performed on the smaller array, which has m elements. The time complexity is therefore O(logm), where m is the size of the smaller array.

- Space Complexity: O(1)

The algorithm only uses a constant amount of extra space for variables like low, high, partition1, partition2, and a few others. No additional space proportional to the input size is required, so the space complexity is O(1).