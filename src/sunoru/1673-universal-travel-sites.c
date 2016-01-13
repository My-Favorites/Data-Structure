#include<stdio.h>
#include<string.h>

int
main(void)
{
    char a[5], b[5], tou[5], wei[5], ccc, c[1010][5];
    int n, i, j, h, m, k1, k2, l, tt, ww, head, tail, d[1010], x, y;
    long f[1010][1010], line[2000], max, money, e[1010];

    for (i = 1; i <= 4; i++)
        scanf("%c", &tou[i]);
    for (i = 1; i <= 4; i++)
        scanf("%c", &wei[i]);
    scanf("%d%c", &n, &ccc);

    m = 0;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= 4; j++)
            scanf("%c", &a[j]);
        k1 = 0;
        for (l = 1; l <= m; l++)
            if (c[l][1] == a[1] && c[l][2] == a[2] && c[l][3] == a[3]) {
                k1 = l;
                break;
            }
        if (k1 == 0) {
            m++;
            k1 = m;
            c[k1][1] = a[1];
            c[k1][2] = a[2];
            c[k1][3] = a[3];
        }
        for (j = 1; j <= 4; j++)
            scanf("%c", &b[j]);
        k2 = 0;
        for (l = 1; l <= m; l++)
            if (c[l][1] == b[1] && c[l][2] == b[2] && c[l][3] == b[3]) {
                k2 = l;
                break;
            }
        if (k2 == 0) {
            m++;
            k2 = m;
            c[k2][1] = b[1];
            c[k2][2] = b[2];
            c[k2][3] = b[3];
        }
        scanf("%d%c", &h, &ccc);
        f[k1][k2] = h;
    }
    for (l = 1; l <= m; l++)
        if (c[l][1] == tou[1] && c[l][2] == tou[2] && c[l][3] == tou[3]) {
            tt = l;
            break;
        }
    for (l = 1; l <= m; l++)
        if (c[l][1] == wei[1] && c[l][2] == wei[2] && c[l][3] == wei[3]) {
            ww = l;
            break;
        }

    money = 0;

    while (1) {
        if (tt == ww)
            break;
        head = 1;
        tail = 1;
        line[head] = tt;
        memset(d, 0, sizeof(d));
        memset(e, 0, sizeof(e));
        d[tt] = -1;
        e[tt] = 1000000;

        while (head <= tail) {
            x = line[head];
            if (x == ww)
                break;
            for (j = 1; j <= m; j++)
                if (f[x][j] > 0 && d[j] == 0) {
                    d[j] = x;
                    if (f[x][j] < e[x])
                        e[j] = f[x][j];
                    else
                        e[j] = e[x];
                    tail++;
                    line[tail] = j;
                }
            head++;
        }

        if (e[ww] == 0)
            break;
        money = money + e[ww];
        y = ww;
        while (y != tt) {
            x = d[y];
            f[x][y] = f[x][y] - e[ww];
            f[y][x] = f[y][x] + e[ww];
            y = x;
        }
    }

    printf("%ld\n", money);
    
    return 0;
}

