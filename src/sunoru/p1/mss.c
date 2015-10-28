#include "mss.h"

/*
 * O(N^6).
 * first , find the top left corner and the lower right corner of submatrix.
 * second , add all number in submatrix.
 * then , compare sum and max , choose the better and record.
 * finally , return the answer.
 * return the max value. return i, m, j, n in "result".
 */
int mss1(int a[MAXN][MAXN], int n, int result[2][2])
{
    int x1, x2, y1, y2, i, j, sum;
    int max = -1;

    for (x1 = 0; x1 < n; x1++)
        for (y1 = 0; y1 < n; y1++)
            for (x2 = x1; x2 < n; x2++)
                for (y2 = y1; y2 < n; y2++) {
                    sum = 0;
                    for (i = x1; i <= x2; i++)
                        for (j = y1; j <= y2; j++)
                            sum = sum + a[i][j];
                    if (sum > max) {
                        max = sum;
                        result[0][0] = x1;
                        result[0][1] = x2;
                        result[1][0] = y1;
                        result[1][1] = y2;
                    }
                }

    return max;
}


/*
 * O(N^4).
 * first , let b[x][y1][y2] equal to sum of the a[x][y] (y1<=y<=y2).
 * second , find the first line of submatrix y1 and the last line of submatrix y2.
 * then , find the first row of submatrix x1 and the last row of submatrix x2.
 * add the whole b[x][y1][y2] (x1<=x<=x2).
 * then , compare sum and max , choose the better and record.
 * finally , return the answer.
 * return the max value. return i, m, j, n in "result".
 */
int mss2(int a[MAXN][MAXN], int n, int result[2][2])
{
    int x1, x2, y1, y2, sum;
    int max = -1;
    int b[MAXN][MAXN][MAXN];

    for (x1 = 0; x1 < n; x1++) {
        for (y1 = 0; y1 < n; y1++) {
            b[x1][y1][y1] = a[x1][y1];
            for (y2 = y1 + 1; y2 < n; y2++)
                b[x1][y1][y2] = b[x1][y1][y2 - 1] + a[x1][y2];
        }
    }
    for (y1 = 0; y1 < n; y1++)
        for (y2 = y1; y2 < n; y2++)
            for (x1 = 0; x1 < n; x1++) {
                sum = 0;
                for (x2 = x1; x2 < n; x2++) {
                    sum = sum + b[x2][y1][y2];
                    if(sum > max) {
                        max = sum;
                        result[0][0] = x1;
                        result[0][1] = x2;
                        result[1][0] = y1;
                        result[1][1] = y2;
                    }
                }
            }

    return max;
}

/*
 * O(N^3).
 * first , let b[x][y1][y2] equal to sum of the a[x][y] (y1<=y<=y2).
 * second , find the first line of submatrix y1 and the last line of submatrix y2.
 * then , use greedy algorithm to find the max and x1 , x2.
 * finally , return the answer.
 * return the max value. return i, m, j, n in "result".
 */
int mss3(int a[MAXN][MAXN], int n, int result[2][2])
{
	int x1, x2, y1, y2, sum;
	int max = -1; 	
    int b[MAXN][MAXN][MAXN];

    for (x1 = 0; x1 < n; x1++) {
        for (y1 = 0; y1 < n; y1++) {
            b[x1][y1][y1] = a[x1][y1];
            for (y2 = y1 + 1; y2 < n; y2++)
                b[x1][y1][y2] = b[x1][y1][y2 - 1] + a[x1][y2];
        }
    }
    for (y1 = 0; y1 < n; y1++)
        for (y2 = y1; y2 < n; y2++) {
        	sum = 0;
        	x1 = 0;
            for (x2 = 0; x2 < n; x2++) {
                sum = sum + b[x2][y1][y2];
                if(sum > max) {
                    max = sum;
                    result[0][0] = x1;
                    result[0][1] = x2;
                    result[1][0] = y1;
                    result[1][1] = y2;
                }
                if (sum < 0) {
                	x1 = x2 + 1;
					sum = 0; 
                }
            }
        }  
	return max;
}



