#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize( int MaxElements ); /* details omitted */

void PercolateUp( int p, PriorityQueue H );
void PercolateDown( int p, PriorityQueue H );

void Insert( ElementType X, PriorityQueue H ) 
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp( p, H );
}

ElementType DeleteMin( PriorityQueue H ) 
{ 
    ElementType MinElement; 
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown( 1, H );
    return MinElement; 
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for ( i=0; i<n; i++ ) {
        scanf("%d", &op);
        switch( op ) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for ( i=1; i<=H->Size; i++ )
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue q = malloc(sizeof(*q));
    q->Elements = malloc(sizeof(ElementType) * (MaxElements+1));
    q->Capacity = MaxElements;
    q->Size = 0;
    return q;
}

void swap(PriorityQueue H, int a, int b) {
    int t = H->Elements[a];
    H->Elements[a] = H->Elements[b];
    H->Elements[b] = t;
}

void PercolateUp(int p, PriorityQueue H) {
    int pp;
    while (p > 1) {
        pp = p / 2;
        if (H->Elements[pp] > H->Elements[p]) {
            swap(H, pp, p);
            p = pp;
            continue;
        }
        break;
    }
}
void PercolateDown(int p, PriorityQueue H) {
    int left = p << 1;
    int right = (p << 1) + 1;
    int min = p;
    if (left <= H->Size && H->Elements[left] < H->Elements[p])
        min = left;
    if (right <= H->Size && H->Elements[right] < H->Elements[min])
        min = right;
    if (min != p) {
        swap(H, min, p);
        PercolateDown(min, H);
    }
}

