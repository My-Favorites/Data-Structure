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
