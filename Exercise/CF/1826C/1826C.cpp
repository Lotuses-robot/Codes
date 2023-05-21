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

const int maxn = 1e7 + 100;
bool vis[maxn]; int pri[maxn], vi[maxn], cnt = 0;
void init() {
    vis[1] = true;
    for (int i = 2; i <= 1e6; i++) {
        if (!vis[i]) pri[cnt++] = i;
        for (int j = 0; j < cnt; j++) {
            if (1ll * i * pri[j] > 1e6) break;
            vis[i * pri[j]] = true;
            vi[i * pri[j]] = pri[j];
            if (i % pri[j] == 0) break;
        }
    }
}

int check(int x) {
    return vi[x];
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    init();
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (n == 1 || m == 1) puts("YES");
        else if (n <= m) puts("NO");
        else {
            int min = check(n);
            debug(min);
            if (!min) puts("YES");
            else if (min <= m) puts("NO");
            else puts("YES");
        }
    }
    return 0;
}
