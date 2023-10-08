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

#define int long long

const int maxn = 1e6 + 10;
int n;
int a[maxn], b[maxn], f[maxn];
struct Int {
    int nxt, x;
    bool operator < (const Int b) const {
        return nxt > b.nxt;
    }
};
std::vector<Int> s;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".ans", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
        f[i] = 1;
    }

    int ans = f[1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (a[i] > a[j] * b[f[j]]) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
        ans = std::max(ans, f[i]);
    }
    writeln(ans);
    return 0;
}
