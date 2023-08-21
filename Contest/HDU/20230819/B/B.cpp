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

const int maxn = 1e4 + 10;
char ch[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, cnt1 = 0, cnt2 = 0;
        read(n);
        scanf("%s", ch);
        for (int i = 0; i < n; i++) {
            cnt1 += ch[i] == '1';
        }
        
        scanf("%s", ch);
        for (int i = 0; i < n; i++) {
            cnt2 += ch[i] == '1';
        }
        if (cnt1 + cnt2 > n) {
            int up = cnt1 + cnt2 - n;
            cnt1 -= up;
            cnt2 -= up;
        }
        for (int i = 1; i <= cnt1 + cnt2; i++) {
            putchar('1');
        }
        for (int i = cnt1 + cnt2 + 1; i <= n; i++) {
            putchar('0');
        }
        puts("");
    }
    return 0;
}
