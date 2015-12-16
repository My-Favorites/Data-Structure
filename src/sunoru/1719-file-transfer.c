#include <stdio.h>
#define MAXN 10010

int n;
int f[MAXN];
int t[MAXN];

int
input(char *x, int *a, int *b)
{
    scanf("%c", x);
    if (*x == 'S')
        return 0;
    scanf("%d%d", a, b);
    getchar();
    return 1;
}

int
find(int a)
{
    if (f[f[a]] != f[a])
        f[a] = find(f[a]);
    return f[a];
}

void
unite(int a, int b)
{
    f[find(b)] = find(a);
}

int
test(int a, int b)
{
    return find(a) == find(b);
}

int
main()
{
    int i;
    char x;
    int a, b;
    int s = 0;

    scanf("%d", &n);
    getchar();
    for (i = 0; i <= n; i++) {
        f[i] = i;
    }
    while (input(&x, &a, &b)) {
        switch (x) {
            case 'C': printf(test(a, b) ? "yes\n" : "no\n"); break;
            case 'I': unite(a, b);
        }
    }
    for (i = 1; i <= n; i++) {
        t[find(i)] = 1;
    }
    for (i = 1; i <= n; i++) {
        if (t[i]) {
            s++;
        }
    }
    if (s == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", s);

    return 0;
}
