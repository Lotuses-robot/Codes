// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

#define abs(a) ((a) >= 0 ? (a) : -(a))

const int maxn = 1e5 + 5;
int n;
int q[3][maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(q[0][i], q[1][i], q[2][i]);
    }

    std::sort(q[0] + 1, q[0] + n + 1);
    std::sort(q[1] + 1, q[1] + n + 1);
    std::sort(q[2] + 1, q[2] + n + 1);

    int mid = (n + 1) / 2;

    int ans = 1e18 + 10;
    for (int i = 0; i < 3; i++) {
        // writeln(-1, i);
        int pans = 0;
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            // writeln(-2, q[j][mid]);
            for (int k = 1; k <= n; k++) {
                pans += abs(q[j][k] - q[j][mid]);
            }
        }
        int p = q[i][mid] - (n - 1) / 2;
        // writeln(-3, p);
        for (int k = 1; k <= n; k++) {
            pans += abs(q[i][k] - p);
            p++;
        }
        // writeln(-4, pans);
        ans = std::min(pans, ans);
    }
    writeln(ans);
    return 0;
}
