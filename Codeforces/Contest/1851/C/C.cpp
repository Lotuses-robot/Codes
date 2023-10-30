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
int c[maxn];

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
        for (int i = 1; i <= n; i++) {
            read(c[i]);
        }
        if (c[1] == c[n]) {
            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                if (c[i] == c[1]) {
                    cnt++;
                }
            }
            if (cnt >= k) {
                puts("YES");
            } else {
                puts("NO");
            }
            continue;
        }
        int ptl = -1, cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (c[i] == c[1]) {
                cnt++;
                if (cnt == k) {
                    ptl = i;
                }
            }
        }
        int ptr = -1; cnt = 0;
        for (int i = n; i >= 1; i--) {
            if (c[i] == c[n]) {
                cnt++;
                if (cnt == k) {
                    ptr = i;
                }
            }
        }
        if (ptl <= ptr && ptl != -1 && ptr != -1) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
