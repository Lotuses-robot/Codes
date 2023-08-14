// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <ctime>

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

const int maxn = 2e7 + 5;
struct Edge {
    int u, v, next;
};
int head[maxn];
Edge G[maxn]; int cnt;

void ins(int u, int v) {
    cnt++;
    G[cnt] = {u, v, head[u]};
    head[u] = cnt;
}

void dfs(int u, int fa) {
    for (int s = head[u]; s != -1; s = G[s].next) {
        if (G[s].v != fa) dfs(G[s].v, u);
    }
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    
    int n, m, u, v;
    read(n, m);
    
    for (int i = 1; i <= n; i++) head[i] = -1;
    for (int i = 1; i <= m; i++) {
        read(u, v);
        ins(u, v);
        ins(v, u);
    }

    int bg = clock();
    dfs(1, 1);
    int ed = clock();
    
    writeln(ed - bg);
    return 0;
}
