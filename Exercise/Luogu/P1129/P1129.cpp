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

const int maxn = 200 + 10 << 2;
int n, x;
std::vector<int> G[maxn];
void init() {
    for (int i = 1; i <= n; i++) G[i].clear();
}
void ins(int u, int v) {
    G[u].push_back(v);
}
bool vis[maxn];
int mat[maxn];
bool dfs(int u) {
    for (int v : G[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (mat[v] == 0 || dfs(mat[v])) {
                mat[v] = u;
                return true;
            }
        }
    }
    return false;
}
int calc() {
    memset(mat, 0, sizeof(mat));
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) cnt++;
    }
    return cnt;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n);
        init();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                read(x);
                if (x) {
                    ins(i, j + n);
                    ins(j + n, i);
                }
            }
        }
        if (calc() == n) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
}