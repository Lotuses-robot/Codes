// Copyright 2023 Lotuses
#define tsz signed
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

const int maxn = 5005;
std::vector<int> G[maxn];
std::vector<double> s;
double c[maxn][maxn];
double f[maxn];

void init() {
    c[1][1] = 1;
    c[2][1] = 0.5; c[2][2] = 0;
    for (int i = 3; i <= 5000; i++) {
        c[i][1] = (double) 1 / i;
        for (int j = 2; j <= i; j++) {
            c[i][j] = c[i - 2][j - 2] * (j - 2) / i + c[i - 2][j - 1] * (i - j) / i;
        }
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    init();
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        for (int i = 1; i <= n; i++) G[i].clear();
        for (int i = 1; i <= m; i++) {
            int a, b;
            read(a, b);
            G[a].push_back(b);
        }
        f[n] = 1; f[1] = 0;
        for (int i = n - 1; i >= 1; i--) {
            f[i] = 0;
            if (G[i].empty()) continue;
            s.clear();
            for (int v : G[i]) {
                s.push_back(f[v]);
            }
            std::sort(s.begin(), s.end(), [](double a, double b) -> bool { return a > b; });
            // writeln(c.size(), s.size());
            // writeln(i);
            for (int j = 1; j <= G[i].size(); j++) {
                // printf("%.10lf %.10lf\n", c[G[i].size()][j], s[j - 1]);
                f[i] += c[G[i].size()][j] * s[j - 1];
            }
        }
        printf("%.10lf\n", f[1]);
    }
    return 0;
}