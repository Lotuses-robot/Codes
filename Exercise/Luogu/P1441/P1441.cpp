// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

const int maxn = 205;
int n, m;
int a[maxn]; bool del[maxn];
std::vector<int> delv;
int ans = 0;
std::vector<int> upp;
bool vis[20005];

void upd() {
    upp.clear(); memset(vis, 0, sizeof(vis));
    upp.push_back(0);
    for (int i = 1; i <= n; i++) {
        if (!del[i]) {
            auto npp = upp;
            for (int u : npp) {
                if (!vis[u + a[i]]) {
                    upp.push_back(u + a[i]);
                    vis[u + a[i]] = true;
                }
            }
        }
    }
    ans = std::max(ans, (int)upp.size() - 1);
}

void dfs(int k) {
    if (k == m + 1) {
        upd();
    }
    for (int i = (k == 1 ? 1 : delv[k - 2] + 1); i <= n; i++) {
        del[i] = true;
        delv.push_back(i);
        dfs(k + 1);
        delv.pop_back();
        del[i] = false;
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    dfs(1);
    writeln(ans);
    return 0;
}
