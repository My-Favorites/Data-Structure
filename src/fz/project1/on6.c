#include <stdio.h>

int calculateSubMatrixSum(int n, int matrix[n][n], int x, int y, int w, int h) {
    int sum = 0;
    for (int i = x; i < (x + w); i++) {
        for (int j = y; j < (y + h); j++) {
            sum += matrix[j][i];
        }
    }
    return sum;
}

int findMaxSubMatrixSum(int n, int matrix[n][n]) {
    int max = 0; // note the maximum sum is 0 if all the integers are negative.
    int tmp;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            for (int w = 1; (x + w) <= n; w++) {
                for (int h = 1; (y + h) <= n; h++) {
                    tmp = calculateSubMatrixSum(n, matrix, x, y, w, h);
                    max = tmp > max ? tmp : max;
                }
            }
        }
    }
    return max;
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
