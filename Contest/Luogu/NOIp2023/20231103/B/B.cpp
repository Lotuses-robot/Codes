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
#include <algorithm>
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

const int maxn = 5005;
int n;
int q[maxn][maxn];
int p[maxn];

bool chk(int x) {
    int pos = 1;
    for (int i = 1; i <= n; i++) {
        if (p[i] != x) {
            if (p[i] < x && p[i] != q[x][pos]) {
                return false;
            }
            if (p[i] > x && p[i] - 1 != q[x][pos]) {
                return false;
            }
            pos++;
        }
    }
    return true;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        if (!chk(i)) return false;
    }
    return true;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n - 1; j++) {
                read(q[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            p[i] = i;
        }
        while (true) {
            if (check()) {
                std::for_each(p + 1, p + n + 1, [](int x) {
                    write(x); putchar(' ');
                }); puts("");
                break;
            }
            std::next_permutation(p + 1, p + n + 1);
        }
    }
}