#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NEW(x, size) if (!(x=malloc(sizeof(*(x))*size))) exit(error("Malloc failed."))

int
error(char *msg)
{
    if (msg) {
        printf("%s\n", msg);
        return 1;
    }
    printf("Unkown error.\n");
    return 2;
}

int n;
int *a, *d, *l;
int **map;

void
insert_edge(int a, int b)
{
    map[a][b] = 1;
    d[b]++;
}

void
init_graph()
{
    int i, j;
    int p;
    NEW(a, n);
    NEW(d, n);
    NEW(l, n);
    NEW(map, n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        NEW(map[i], n);
        memset(map[i], 0, n);
    }
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

void
swap(int *s, int x, int y)
{
    int t = s[x];
    s[x] = s[y];
    s[y] = t;
}

void
minheap(int *s, int i, int m)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    /* pay attention to the comparison is between the values of a[s[i]] but not s[i] itself. */
    if (left < m && a[s[left]] < a[s[smallest]])
        smallest = left;
    if (right < m && a[s[right]] < a[s[smallest]])
        smallest = right;
    if (smallest != i) {
        swap(s, i, smallest);
        minheap(s, smallest, m);
    }
}

void
make_minheap(int *s, int m)
{
    int i;
    for (i = (m-1) / 2; i >= 0; i--) {
        minheap(s, i, m);
    }
}

int
pop_min(int *s, int *m)
{
    swap(s, 0, --(*m));
    minheap(s, 0, *m);
    return s[*m];
}

void
insert(int *s, int x, int *m)
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

int
toposort()
{
    int *s;
    int m = 0;
    int i, j;
    int t;
    int ll = 0;

    NEW(s, n);
    for (i = 0; i < n; ++i) {
        if (a[i] < 0)
            continue;
        if (d[i] == 0) {
            s[m++] = i;
        }
    }
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
    free(s);

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
