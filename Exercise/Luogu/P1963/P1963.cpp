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


const int maxn = 20001, maxm = 20001;
int match[maxn];
bool vis[maxn];
int n, right, e;
std::vector<int> G[maxn];

bool dfs(int u) {
    for (int i : G[u]) {
        if (!vis[i]) {
            vis[i] = 1;
            if (match[i] == 0 || dfs(match[i])) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}

int hagarian() {
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) ++ans;
    }
    return ans;
}

int ans[10001];

int main(){
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    // scanf("%d %d %d", &left, &right, &e);
    // for (int i = 1; i <= e; ++i) {
    //     int u, v;
    //     scanf("%d%d", &u, &v);
    //     G[u].push_back(v + left);
    //     G[v + left].push_back(u);
    // }
    read(n); right = n;
    for (int i = 0; i < n; i++) {
        int d;
        read(d);
        int p[4] = {i - d, d + i, d - n + i, n - d + i};
        std::sort(p, p + 4);
        for (int j = 0; j < 4; j++) {
            if (p[j] >= 0 && p[j] < n) {
                G[i].push_back(p[j] + n);
                G[p[j] + n].push_back(i);
                // writeln(i, p[j]);
            }
        }
    }
    int ans1 = hagarian();
    if (ans1 != n) {
        puts("No Answer");
        return 0;
    }
    for (int i = n; i < n * 2; i++) {
        // write(match[i]); putchar(' ');
        ans[match[i]] = i - n;
    }
    for (int i = 0; i < n; i++) {
        write(ans[i]); putchar(' ');
    }
    return 0;
}