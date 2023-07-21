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

const int maxn = 10005;
int x[maxn], y[maxn];
std::vector<std::pair<int, int> > tube[maxn];
int f[1005], g[1005];
std::vector<int> v;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, k;
    read(n, m, k);
    for (int i = 1; i <= n; i++) {
        read(x[i], y[i]);
    }
    for (int i = 1; i <= k; i++) {
        static int p, l, r; // l <= r
        read(p, l, r);
        tube[p].push_back(std::make_pair(l, r));
        v.push_back(p);
    }

    memset(f, 63, sizeof(f));
    memset(g, 63, sizeof(g));
    for (int i = 1; i <= m; i++) {
        g[i] = 0;
    }

    int back = 0; bool flg = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[j] = g[j];
        }
        memset(g, 63, sizeof(g));
        for (int j = 1; j <= m; j++) {
            if (j - x[i] >= 1) {
                g[j] = std::min(g[j], g[j - x[i]] + 1);
                g[j] = std::min(g[j], f[j - x[i]] + 1);
                if (j == m) {
                    for (int k = j - x[i] + 1; k < m; k++) {
                        g[j] = std::min(g[j], g[k] + 1);
                        g[j] = std::min(g[j], f[k] + 1);
                    }
                }
            }
            if (j + y[i] <= m) g[j] = std::min(g[j], f[j + y[i]]);
        }
        for (auto tub : tube[i]) {
            for (int j = 1; j <= tub.first; j++) {
                g[j] = g[0];
            }
            for (int j = tub.second; j <= m; j++) {
                g[j] = g[0];
            }
        }
        bool flag = false;
        for (int j = 1; j <= m; j++) {
            if (g[j] != g[0]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            flg = true;
            break;
        }
        back += tube[i].size();
    }

    if (flg) {
        puts("0");
        writeln(back);
    } else {
        int minn = 998244353;
        for (int j = 1; j <= m; j++) {
            minn = std::min(g[j], minn);
        }
        puts("1");
        writeln(minn);
    }
    return 0;
}
