// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 1e5 + 10;
int n, m;
int in[maxn], f[maxn];
std::vector<int> G[maxn];
std::queue<int> q;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        G[u].push_back(v);
        in[v]++;
    }
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        if (!in[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : G[u]) {
            in[v]--;
            f[v] = std::max(f[v], f[u] + 1);
            if (!in[v]) q.push(v);
        }
    }
    for (int i = 1; i <= n; i++) {
        writeln(f[i]);
    }
    return 0;
}