// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
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

#define int long long

const int maxn = 1000;
int c[maxn];
int f[40005];
std::vector<int> tp;
int vis[40005];
std::queue<int> q;

void init(int x, int y, int r) {
    memset(vis, 0, sizeof(vis));
    tp.clear();
    vis[0] = true; tp.push_back(0);
    vis[x] = true; tp.push_back(x);
    vis[y] = true; tp.push_back(y);
    q.push(x); q.push(y);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        if (t + x <= r + 20000 && !vis[t + x]) {
            vis[t + x] = true;
            tp.push_back(t + x);
            q.push(t + x);
        }
        if (t + y <= r + 20000 && !vis[t + y]) {
            vis[t + y] = true;
            tp.push_back(t + y);
            q.push(t + y);
        }
    }
    std::sort(tp.begin(), tp.end());
    // for (int e : tp) {
    //     writeln(e);
    // }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, x, y, r;
        read(n, x, y, r);
        init(x, y, r);
        for (int i = 1; i <= n; i++) {
            read(c[i]);
        }

        memset(f, -63, sizeof(f));
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int v = r + 20000; v >= 0; v--) {
                for (int j : tp) {
                    if (v - j < 0 || c[i] < j) break;
                    f[v] = std::max(f[v], f[v - j] + (c[i] - j) * (c[i] - j));
                    // writeln(j);
                }
                // write(f[v]); putchar(' ');
            }
            // puts("");
        }
        // std::sort(c + 1, c + n + 1);
        int ans = -1;
        for (int i = r; i <= r + 20000; i++) {
            // writeln(f[i]);
            ans = std::max(f[i], ans);
        }
        writeln(ans);
    }
    return 0;
}
