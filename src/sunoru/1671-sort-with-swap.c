/*
 * by スノル
 */
#include <stdio.h>

#define MAXN 100000

int count(int);
int a[MAXN];
int f[MAXN] = {0};

int main() {
    int n, i;
    int s;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    s = count(0) - 1;
    for (i = 1; i < n; i++)
        if (!f[i] && a[i] != i)
            s += count(i) + 1;
    printf("%d\n", s);

    return 0;
}

int count(int u) {
    int p = 0;

    while (!f[u]) {
        f[u] = 1;
        p++;
        u = a[u];
    }

    return p;
}
