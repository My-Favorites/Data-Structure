#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

/* Your function will be put here */

void merge_pass(ElementType list[], ElementType sorted[], int N, int length)
{
    int i, j, k, l;

    for (i = 0; i < N; i += length << 1) {
        j = 0;
        k = 0;
        while (i + j < N && i + length + k < N && j < length && k < length)
            if (list[i + j] < list[i + length + k]) {
                sorted[i + j + k] = list[i + j];
                j++;
            } else {
                sorted[i + j + k] = list[i + length + k];
                k++;
            }
        for (; i + j < N && j < length; j++)
            sorted[i + j + k] = list[i + j];
        for (; i + length + k < N && k < length; k++)
            sorted[i + j + k] = list[i + length + k];
    }
    for (; i < N; i++)
            sorted[i] = list[i];
}
