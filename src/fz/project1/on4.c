#include <stdio.h>

int findMaxSubMatrixSum(int n, int matrix[n][n]) {
    int max = 0; // note the maximum sum is 0 if all the integers are negative.
    int tmp;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            tmp = 0;
            for (int offsetX = 0; (x + offsetX) < n; offsetX++) {
                for (int offsetY = 0; (y + offsetY) < n; offsetY++) {
                    tmp += matrix[y+offsetY][x+offsetX];
                    max = max > tmp ? max : tmp;
                }
            }
        }
    }
    return max;
}
