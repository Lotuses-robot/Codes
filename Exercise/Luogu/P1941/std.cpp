// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define N 10005
using namespace std;
int n, m, k, x[N], y[N], low[N], high[N], f[N][2005];
bool flag[N];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &x[i], &y[i]);
    for (int i = 1; i <= n; i++) {
        high[i] = m;
        low[i] = 1;
    }
    for (int i = 1; i <= k; i++) {
        int xx, yy, zz;
        scanf("%d%d%d", &xx, &yy, &zz);
        flag[xx] = 1;
        low[xx] = yy + 1;
        high[xx] = zz - 1;
    }
    memset(f, 0x3f3f3f, sizeof(f));
    for (int i = 1; i <= m; i++)
        f[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = x[i] + 1; j <= x[i] + m; j++)
            f[i][j] = min(f[i - 1][j - x[i]] + 1, f[i][j - x[i]] + 1);
        for (int j = m + 1; j <= x[i] + m; j++)
            f[i][m] = min(f[i][m], f[i][j]);
        for (int j = 1; j <= m - y[i]; j++)
            f[i][j] = min(f[i][j], f[i - 1][j + y[i]]);
        for (int j = 1; j < low[i]; j++)
            f[i][j] = 0x3f3f3f;
        for (int j = high[i] + 1; j <= m; j++)
            f[i][j] = 0x3f3f3f;
    }
    int ans = 0x3f3f3f;
    for (int i = 1; i <= m; i++)
        ans = min(ans, f[n][i]);
    if (ans < 0x3f3f3f) {
        printf("1\n%d\n", ans);
        return 0;
    }
    int i, j;
    for (i = n; i >= 1; i--) {
        for (j = 1; j <= m; j++)
            if (f[i][j] < 0x3f3f3f)
                break;
        if (j <= m)
            break;
    }
    ans = 0;
    for (j = 1; j <= i; j++)
        if (flag[j])
            ans++;
    printf("0\n%d\n", ans);
    return 0;
}