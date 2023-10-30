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

const int maxn = 1e5 + 10;
int to[maxn];
int vis[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, k;
        read(n, k);
        for (int i = 1; i <= n; i++) {
            read(to[i]);
        }
        memset(vis, 0, sizeof(int) * (n + 5));
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (k == 1 && to[i] != i) {
                flag = false;
                break;
            } else {
                if (vis[i]) continue;
                int cnt = 0, u = i;
                vis[u] = ++cnt;
                while (!vis[to[u]]) {
                    vis[to[u]] = ++cnt;
                    u = to[u];
                }
                if (vis[to[u]] != -1 && vis[u] - vis[to[u]] + 1 != k) {
                    flag = false;
                    break;
                }
                u = i; vis[u] = -1;
                while (~vis[to[u]]) {
                    vis[to[u]] = -1;
                    u = to[u];
                }
            }
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}