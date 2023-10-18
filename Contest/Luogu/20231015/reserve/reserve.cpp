// Copyright 2023 Lotuses
#define tsz signed
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

#define int long long

const int maxn = 5e5 + 10;
int a[maxn], yb[maxn], b[maxn], c[maxn], p[maxn];
int f[maxn][21];
int Logn[maxn];
int n, q;

void init() {
    Logn[1] = 0;
    Logn[2] = 1;
    for (int i = 3; i <= n; i++) {
        Logn[i] = Logn[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) f[i][0] = b[i];
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = std::max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}

int query(int x, int y) {
    int s = Logn[y - x + 1];
    // writeln(x, y, std::max(f[x][s], f[y - (1 << s) + 1][s]));
    return std::max(f[x][s], f[y - (1 << s) + 1][s]);
}

tsz main() {
    #ifdef LOCAL
        freopen("data/reserve7.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
    for (int i = 1; i <= n; i++) read(yb[i]), b[i] = yb[i], yb[i] += yb[i - 1], b[i] -= a[i], b[i] += b[i - 1];
    init();
    for (int i = 1; i <= n; i++) read(c[i]);
    read(q);
    while (q--) {
        int m, ans = 0, pans;
        read(m);
        for (int i = 1; i <= m; i++) {
            read(p[i]);
        }
        p[m + 1] = n + 1;
        ans = yb[n];
        for (int j = 1; j <= m; j++) {
            ans -= yb[p[j]] - yb[p[j] - 1];
        }
        pans = ans;
        p[0] = 0;
        for (int i = 1; i <= m + 1; i++) {
            if (p[i] - p[i - 1] > 1) {
                pans = std::min(pans, ans - (query(p[i - 1] + 1, p[i] - 1) - b[p[i - 1]]));
                ans -= (b[p[i] - 1] - b[p[i - 1]]);
            }
            if (i == m + 1) continue;
            ans += c[p[i]] + a[p[i]];
            pans = std::min(pans, ans);
        }
        writeln(pans);
    }
    return 0;
}