#include <stdio.h>

/**
 * O(n) version of find max sub seq sum
 */
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

    for (int startRow = 0; startRow < n; startRow++) {
        for (int endRow = startRow; endRow < n; endRow++) {
            int tmpSum = findMaxSubSeqSum(n, flatten[startRow][endRow]);
            maxSum = maxSum > tmpSum ? maxSum : tmpSum;
        }
    }

    return maxSum;
}

void main() {
    int matrix[4][4] = {
        {0, -2, -7, 0},
        {9, 2, -6, 2},
        {-4, 1, -4, 1},
        {-1, 8, 0, -2}
    };
    int max = findMaxSubMatrixSum(4, matrix);
    printf("Max sub matrix sum: %d", max);
}
