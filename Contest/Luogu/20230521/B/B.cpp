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

#define int long long

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (n > m) std::swap(n, m);
        if (m == 1) {
            writeln(0);
        } else {
            int hl = (m / 2 - 1) * 3 + (1 + m % 2) * 2;
            int ml = ((m - 1) / 2) * 4 + (m - 1) % 2 * 3;
            debug(hl, ml);
            if (n == 1) {
                writeln((m / 2 - 1) * 2 + (1 + m % 2) * 1);
            } else if (n == 2) {
                writeln(hl + ((m - 1) / 2) * 3 + ((m - 1) % 2) * 2);
            } else {
                if (m % 2) {
                    if (n % 2) {
                        writeln(hl * 2 + ((n - 2) / 2 + 1) * ml + (n - 2) / 2 * ((m / 2 - 1) * 4 + (1 + m % 2) * 3));
                    } else {
                        writeln(hl + (n / 2 - 1) * ((m / 2 - 1) * 4 + (1 + m % 2) * 3) + (n / 2 - 1) * ml + ((m - 1) / 2) * 3 + (m - 1) % 2 * 2);
                    }
                } else {
                    writeln(hl * 2 + ml * (n - 2));
                }
            }
        }
    }
    return 0;
}
