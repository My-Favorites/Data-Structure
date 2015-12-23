#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* macro MAXN denotes to the max value of n */
#define MAXN 1010

/* n is the size of the hash table. */
int n;
/* a[] denotes to the cells in the hash table.
 * d[] contains the in-degree values of the nodes.
 * l[] is the result list.
 * s[] is an array for implementing a heap.
 */
int a[MAXN], d[MAXN], l[MAXN], s[MAXN];
/* map[][] is an 2d array that contains the relation between the nodes. 
 * There is an edge from i to j if map[i][j] = 1.
 */
int map[MAXN][MAXN];

/* 
 * Insert an edge from node a to b and increase the in-degree of b.
 */
void
insert_edge(int a, int b)
{
    map[a][b] = 1;
    d[b]++;
}

/*
 * Initialize the graph.
 */
void
init_graph()
{
    int i, j;
    int p;

    /* Initialize a[]. */
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        memset(map[i], 0, n);
    }
    /* If a[i] is not in the position it should be in, then all the nodes
     * between the right position and i (excludes i) have an edge to node i.
     */
    for (i = 0; i < n; ++i) {
        if (a[i] == -1)
            continue;
        p = a[i] % n;
        if (p <= i) {
            for (j = p; j < i; j++) {
                insert_edge(j, i);
            }
        } else {
            for (j = p; j < n; j++) {
                insert_edge(j, i);
            }
            for (j = 0; j < i; j++) {
                insert_edge(j, i);
            }
        }
    }
}

/*
 * Exchange two elements of s[] that have subscripts x and y.
 */
void
swap(int s[], int x, int y)
{
    int t = s[x];
    s[x] = s[y];
    s[y] = t;
}

/*
 * Min-heapify the subheap of s[m] whose root is node i
 */
void
minheap(int s[], int i, int m)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    /* Pay attention to the comparison is between the values of a[s[i]] but not s[i] itself. */
    if (left < m && a[s[left]] < a[s[smallest]])
        smallest = left;
    if (right < m && a[s[right]] < a[s[smallest]])
        smallest = right;
    if (smallest != i) {
        swap(s, i, smallest);
        minheap(s, smallest, m);
    }
}

/*
 * Make a min-heap in s[] whose size is m.
 */
void
make_minheap(int s[], int m)
{
    int i;
    for (i = (m-1) / 2; i >= 0; i--) {
        minheap(s, i, m);
    }
}

/*
 * Pop the minimum in the min-heap s[m].
 */
int
pop_min(int s[], int *m)
{
    swap(s, 0, --(*m));
    minheap(s, 0, *m);
    return s[*m];
}

/*
 * Insert a node with data x into the min-heap s[m].
 */
void
insert(int s[], int x, int *m)
{
    int t = (*m)++;
    int p = (t-1) / 2;
    s[t] = x;
    while (p >= 0 && a[s[p]] > a[s[t]]) {
        swap(s, p, t);
        t = p;
        p = (t-1) / 2;
    }
}

/*
 * Do the topological sorting for the graph using Kahn's algorithm.
 */
int
toposort()
{
    /* m denotes the current length of min-heap s[] */
    int m = 0;
    /* ll is the length of results l[] */
    int ll = 0;
    int i, j;
    int t;
 
    /* s[] stores the nodes that have no incoming edge. */   
    for (i = 0; i < n; ++i) {
        if (a[i] < 0)
            continue;
        if (d[i] == 0) {
            s[m++] = i;
        }
    }
    /* Make s[] a min-heap to implement a monotone priority queue. */
    make_minheap(s, m);
    while (m > 0) {
        t = pop_min(s, &m);
        l[ll++] = t;
        for (i = 0; i < n; ++i) {
            if (map[t][i]) {
                map[t][i] = 0;
                if (--(d[i]) == 0) {
                    insert(s, i, &m);
                }
            }
        }
    }

    return ll;
}

int
main()
{
    int i, ll;

    scanf("%d", &n);
    init_graph();
    ll = toposort();
    if (ll > 0)
        printf("%d", a[l[0]]);
    for (i = 1; i < ll; ++i) {
        printf(" %d", a[l[i]]);
    }
    printf("\n");

    return 0;
}
