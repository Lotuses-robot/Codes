// Copyright 2023 Lotuses
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <iostream>
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

const int maxn = 30, maxm = 1005;
int n, m;
struct Edge {
    int v; std::string s; int od;
};
std::vector<Edge> G[maxn];
std::string s[maxm];

int in[maxn], out[maxn], fa[maxn], cnt = 0;
bool vis[maxm];

bool cmp(std::string a, std::string b) {
    return a < b;
}

int find(int u) {
    if (fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}

std::string ans[maxm];
void dfs(int t, int u) {
    if (t == n) {
        for (int i = 0; i < n; i++) {
            if (i) putchar('.');
            std::cout << ans[i];
        }
        exit(0);
    }
    for (auto &e : G[u]) {
        if (!vis[e.od]) {
            vis[e.od] = true;
            ans[t] = e.s;
            dfs(t + 1, e.v);
            vis[e.od] = false;
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
    }
    std::sort(s + 1, s + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        int b = s[i][0] - 'a' + 1; int e = s[i][s[i].length() - 1] - 'a' + 1;
        in[e]++;
        out[b]++;
        if (!vis[b]) {
            vis[b] = true;
            cnt++;
            fa[b] = b;
        }
        if (!vis[e]) {
            vis[e] = true;
            cnt++;
            fa[e] = e;
        }

        if (b != e) {
            if (find(b) != find(e)) {
                cnt--;
                fa[find(e)] = find(b);
            }
        }
        G[b].push_back({e, s[i], i});
    }
    if (cnt != 1) {
        puts("***");
        return 0;
    }

    int be = 0, ed = 0;
    for (int i = 1; i <= 26; i++) {
        if (!vis[i]) {
            continue;
        }
        if (out[i] == in[i] + 1) {
            if (be) {
                puts("***");
                return 0;
            }
            be = i;
        } else if (out[i] + 1 == in[i]) {
            if (ed) {
                puts("***");
                return 0;
            }
            ed = i;
        } else if (in[i] != out[i]) {
            puts("***");
            return 0;
        }
    }
    if ((be && !ed) || (!be && ed)) {
        puts("***");
        return 0;
    }
    if (!be) {
        be = s[1][0] - 'a' + 1;
    }

    memset(vis, 0, sizeof(vis));

    dfs(0, be);
    return 0;
}
 