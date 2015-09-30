#include <stdio.h>

/**
 * @file Find max sub matrix sum in O(n^3) time
 * @author Zeno Zeng
 *
 * To build: gcc bonus1.c -std=c99
 */

// O(n) version of find max sub seq sum
int findMaxSubSeqSum(int n, int seq[n]) {
    int maxSum = 0;
    int tmpSum = 0;
    for (int i = 0; i < n; i++) {
        tmpSum += seq[i];
        if (tmpSum > maxSum) {
            maxSum = tmpSum;
        } else {
            // If the prev seq sum is less that 0
            // Then we simply drop it
            if (tmpSum < 0) {
                tmpSum = 0;
            }
        }
    }
    return maxSum;
}

int findMaxSubMatrixSum(int n, int matrix[n][n]) {

    // First we prepare flatten sequences in O(n^3) time

    int flatten[n][n][n]; // flatten [startRow][endRow] = {merged seq}
    for (int startRow = 0; startRow < n; startRow++) {
        for (int endRow = startRow; endRow < n; endRow++) {
            for (int cursor = 0; cursor < n; cursor++) {
                flatten[startRow][endRow][cursor] = matrix[endRow][cursor];
                if (endRow != startRow) {
                    flatten[startRow][endRow][cursor] += flatten[startRow][endRow - 1][cursor];
                }
            }
        }
    }

    int maxSum = 0;

    // We have O(n^2) sequences
    // then for each sequence we do findMaxSubSeqSum in O(n) time

    // So the max sub matrix is [startRow to endRow] * [maxSeqStart to maxSeqEnd]
    // And we can find it in O(n^3) time

    for (int startRow = 0; startRow < n; startRow++) {
        for (int endRow = startRow; endRow < n; endRow++) {
            int tmpSum = findMaxSubSeqSum(n, flatten[startRow][endRow]);
            maxSum = maxSum > tmpSum ? maxSum : tmpSum;
        }
    }

    return maxSum;
}
