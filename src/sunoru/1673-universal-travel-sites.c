#include<stdio.h>
#include<string.h>
#define MAXN 1010
#define oo 200701281

char tstr[3];
int m, n;
int src, dest;
char dict[MAXN][3];
int map[MAXN][MAXN];
int head, tail;
int queue[MAXN];
int d[MAXN], e[MAXN];

int
find(char x[3])
{
    int i;
    for (i = 0; i < n; ++i) {
        if (x[0] == dict[i][0] &&
            x[1] == dict[i][1] &&
            x[2] == dict[i][2])
            return i;
    }
    dict[n][0] = x[0];
    dict[n][1] = x[1];
    dict[n][2] = x[2];
    return n++;
}

int
main()
{
    char ssrc[3], sdest[3];
    int a, b;
    int u, v;
    int i;
    int s = 0;
    scanf("%s%s%d", ssrc, sdest, &m);

    n = 0;
    for (i = 0; i < m; ++i) {
        scanf("%s", tstr);
        a = find(tstr);
        scanf("%s", tstr);
        b = find(tstr);
        scanf("%d", &map[a][b]);
    }
    src = find(ssrc);
    dest = find(sdest);
    
    while (src != dest) {
        head = 0;
        tail = 0;
        queue[tail++] = src;
        for (i = 0; i < n; ++i)
            d[i] = -1;
        for (i = 0; i < n; ++i)
            e[i] = 0;
        d[src] = -2;
        e[src] = oo;
        while (head != tail) {
            u = queue[head++];
            if (u == dest)
                break;
            for (v = 0; v < n; ++v)
                if (map[u][v] > 0 && d[v] == -1) {
                    d[v] = u;
                    if (map[u][v] < e[u])
                        e[v] = map[u][v];
                    else
                        e[v] = e[u];
                    queue[tail++] = v;
                }
        }
        if (e[dest] == 0)
            break;
        s += e[dest];
        u = dest;
        while (u != src) {
            v = d[u];
            map[v][u] -= e[dest];
            map[u][v] += e[dest];
            u = v;
        }
    }

    printf("%d\n", s);

    return 0;
}

