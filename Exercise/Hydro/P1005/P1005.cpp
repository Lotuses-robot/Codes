// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int f[1001][1001];

int dfs(int x, int y) {
    if (x == 1) return 1;
    else if (y == 1) return x % 1234567;
    if (f[x][y]) return f[x][y];
    return (f[x][y] = (dfs(x - 1, y) + dfs(y - 1, x) + x) % 1234567);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    while (scanf("%d%d", &n, &m) == 2 && n && m) {
        printf("%d\n", dfs(n, m));
    }
    return 0;
}
