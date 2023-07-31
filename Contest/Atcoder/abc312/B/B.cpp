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

const int maxn = 300;
char ch[maxn][maxn];

bool check(int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (ch[x + i][y + j] != '#') return false;
        }
    }
    for (int i = 6; i < 9; i++) {
        for (int j = 6; j < 9; j++) {
            if (ch[x + i][y + j] != '#') return false;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (ch[x + 3][y + i] != '.') return false;
    }
    for (int i = 0; i < 4; i++) {
        if (ch[x + i][y + 3] != '.') return false;
    }
    for (int i = 5; i < 9; i++) {
        if (ch[x + 5][y + i] != '.') return false;
    }
    for (int i = 5; i < 9; i++) {
        if (ch[x + i][y + 5] != '.') return false;
    }
    return true;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch[i] + 1);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (check(i, j)) {
                writeln(i, j);
            }
        }
    }
    return 0;
}
