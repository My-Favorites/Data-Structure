#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mss.h"

int get_k(int n, int q)
{
    int k = (int)(4000000 / pow(n, q));

    if (k > 2000)
        k = 2000;
    if (k < 3)
        k = 3;

    return k;
}

void init(int a[MAXN][MAXN], int n)
{
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            a[i][j] = rand() % 10000000 - 5000000;
    }
}

void test(int a[MAXN][MAXN], int n, int k,
          int (*func)(int[MAXN][MAXN], int, int[2][2]))
{
    int ki;
    clock_t start, stop;
    double ticks, duration, average;
    int mss;
    int result[2][2];

    printf("(Using K = %d):\n", k);
    start = clock();
    for (ki = 1; ki <= k; ki++)
        mss = func(a, n, result);
    stop = clock();
    ticks = ((double)(stop - start));
    printf("Ticks: %.0f\n", ticks);
    duration = ticks / CLOCKS_PER_SEC * 1000;
    printf("Total time: %.3f ms\n", duration);
    average = duration / k;
    printf("Average time: %.5f ms\n", average);
}


int main()
{
    int n, k;
    int a[MAXN][MAXN];
    double t;

    srand(time(NULL));
    while (1) {
        printf("Input the N (-1 for exit): ");
        scanf("%d", &n);
        if (n == -1) 
            break;
        init(a, n);

        k = get_k(n, 6);
        printf("Testing the first algorithm...\n");
        test(a, n, k, &mss1);

        k = get_k(n, 4);
        printf("Testing the second algorithm...\n");
        test(a, n, k, &mss2);

        k = get_k(n, 3);
        printf("Testing the third algorithm...\n");
        test(a, n, k, &mss3);
    }

    printf("Bye bye.\n");    
    return 0;
}
