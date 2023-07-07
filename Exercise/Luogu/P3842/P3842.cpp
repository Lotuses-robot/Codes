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

#define abs(a) ((a) < 0 ? -(a) : (a))

int L[20004], R[20004];
int f[20004][2];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(L[i], R[i]);
    }

    f[1][0] = R[1] - 1 + R[1] - L[1];
    f[1][1] = R[1] - 1;

    for (int i = 2; i <= n; i++) {
        f[i][0] = std::min(f[i - 1][0] + abs(L[i - 1] - R[i]) + R[i] - L[i],
                           f[i - 1][1] + abs(R[i - 1] - R[i]) + R[i] - L[i]);
        f[i][1] = std::min(f[i - 1][0] + abs(L[i - 1] - L[i]) + R[i] - L[i],
                           f[i - 1][1] + abs(R[i - 1] - L[i]) + R[i] - L[i]);
    }

    printf("%d\n", std::min(f[n][0] + (n - L[n]), f[n][1] + (n - R[n])) + n - 1);
    return 0;
}
