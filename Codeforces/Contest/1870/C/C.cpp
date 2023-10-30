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

const int maxn = 1e5 + 10;
int a[maxn], l[maxn], r[maxn], cnt[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, k;
        read(n, k);
        for (int i = 0; i <= k + 1; i++) {
            l[i] = 1e9; r[i] = -1e9; cnt[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            read(a[i]);
            r[a[i]] = i;
            cnt[a[i]] = 1;
        }
        for (int i = n; i >= 1; i--) {
            l[a[i]] = i;
        }
        for (int i = k; i >= 1; i--) {
            l[i] = std::min(l[i], l[i + 1]);
            r[i] = std::max(r[i], r[i + 1]);
        }
        for (int i = 1; i <= k; i++) {
            if (!cnt[i]) {
                write(0); putchar(' ');
            } else {
                write((r[i] - l[i] + 1) * 2); putchar(' ');
            }
        }
        puts("");
    }
    return 0;
}
