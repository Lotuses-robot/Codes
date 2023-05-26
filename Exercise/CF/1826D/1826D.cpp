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

const int maxn = 200005;

int a[maxn], ls[maxn], rs[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }

        memset(ls, -1, sizeof(int) * (n + 10));
        int s = 0;
        for (int i = 2; i <= n; i++) {
            s = std::max(s - 1, a[i - 1] - 1);
            ls[i] = s;
        }

        memset(rs, -1, sizeof(int) * (n + 10));
        s = 0;
        for (int i = n - 1; i >= 1; i--) {
            s = std::max(s - 1, a[i + 1] - 1);
            rs[i] = s;
        }

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = std::max(ans, ls[i] + a[i] + rs[i]);
        }
        writeln(ans);
    }
}
