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

int calc(int x) {
    writeln(x);
    if (x < 0) return 1e9;
    int ans = 0;
    while (x) {
        if (x % 4 == 0) x /= 4, ans++;
        else if (x % 3 == 0) x /= 3, ans++;
        else break;
    }
    if (x) {
        ans = ans + std::min(calc(x - 1) + 1, std::min(calc(x - 3) + 3, calc(x - 2) + 2));
    }
    return ans;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int x;
        read(x);
        writeln(calc(x));
    }
    return 0;
}