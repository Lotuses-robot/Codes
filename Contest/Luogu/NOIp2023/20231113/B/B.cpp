// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].emplace_back(b))

std::vector<int> pm, nt;
bool vis[20000005];
void init() {
    vis[1] = true;
    for (int i = 2; i <= 20000000; i++) {
        if (!vis[i]) {
            pm.emplace_back(i);
            for (int j = i * 2; j <= 20000000; j += i) {
                vis[j] = true;
            }
        }
    }
    for (int i = 1; i < pm.size(); i++) {
        nt.emplace_back((pm[i] + 1) / 2);
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    init();
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        if (n == 1) {
            puts("2");
            continue;
        }
        if (n == 0) {
            puts("3");
            continue;
        }
        if (n == -1) {
            puts("4");
            continue;
        }
        if (n > 0) {
            if (!vis[n]) {
                puts("1");
                continue;
            }
            if (!vis[2 * n - 1] || !vis[2 * n + 1]) {
                puts("2");
                continue;
            }
        } else {
            if (!vis[(-n) + 1]) {
                writeln((-n) + 1 - n + 1);
                continue;
            }
            if (!vis[2 * ((-n) + 2) - 1]) {
                writeln((-n) + 2 - n + 1);
                continue;
            }
            n = (-n) + 1;
        }
        int x = *std::lower_bound(pm.begin(), pm.end(), n);
        int y = *std::lower_bound(nt.begin(), nt.end(), n + 1);
        // writeln(x, y);
        if (y <= x) {
            writeln(y * 2 - 1);
        } else {
            writeln(x * 2);
        }
    }
    return 0;
}