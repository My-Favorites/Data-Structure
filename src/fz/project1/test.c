#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "share.h"

#ifndef CLK_TCK
#define CLK_TCK CLOCKS_PER_SEC
#endif

clock_t start;
clock_t end;
double seconds;
int numbers[6] = {5, 10, 30, 50, 80, 100};

int main() {
    for (int i = 0; i < 6; i++) {
        // Generate data
        int N = numbers[i];
        int matrix[N][N];
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                matrix[j][k] = rand() % 200 - 100;
            }
        }
        // Test
        start = clock();
        int iterations = 0;
        int ticks = 0;
        while (ticks < 100 * 1000) {
            findMaxSubMatrixSum(N, matrix);
            ticks = clock() - start;
            iterations++;
        }
        seconds = (double) ticks / CLK_TCK;
        printf("\n\n  N: %d \n  Iterations: %d \n  Ticks: %d \n  Total Time: %lf \n  Duration: %lf", N, iterations, ticks, seconds, seconds / iterations);
    }
    return 0;
}
