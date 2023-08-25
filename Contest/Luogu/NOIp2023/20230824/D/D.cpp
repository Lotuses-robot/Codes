// Copyright 2023 Lotuses
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

#define int long long
const int maxn = 10;
std::vector<int> bg[maxn][maxn];
int n, m, s;

int dfs(int u, int last, int b) {
    if (u == n + 1) {
        return 1;
    }
    int ans = 0;
    for (int i = 1; i <= s; i++) {
        int clast = last, cb = b;
        if (i != clast || clast == -1) {
            cb = u;
            clast = i;
        }
        bool flag = false;
        for (int p : bg[u][clast]) {
            if (p >= cb) {
                flag = true;
                break;
            }
        }
        if (flag) continue;
        ans += dfs(u + 1, clast, cb);
    }
    return ans;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, s);
    for (int i = 1; i <= m; i++) {
        int l, r, x;
        read(l, r, x);
        bg[r][x].push_back(l);
    }
    writeln(dfs(1, -1, -1));
    return 0;
}
