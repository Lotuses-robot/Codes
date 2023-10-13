// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
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

const int maxn = 105;
int n;

namespace inter {
    void flush() {
        fflush(stdout);
    }

    void mv(int col) {
        printf("%d\n", col);
        fflush(stdout);
    }
    
    int c[maxn];
    void get() {
        int st;
        read(st);
        if (st) exit(0);
        for (int i = 2; i <= n; i++) {
            read(c[i]);
        }
    }
}

int p[maxn];
std::vector<int> G[maxn];
int col[maxn];
int id = 0;
struct Point {
    int fa, son, cnt;
    bool operator < (Point b) const {
        if (fa != b.fa) return fa < b.fa;
        if (son != b.son) return son < b.son;
        return cnt < b.cnt;
    }
};
std::map<Point, bool> mp;

void paint(int u) {
    int c = ++id;
    for (int v : G[u]) {
        col[v] = c;
        paint(v);
    }
}

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif

    read(n);
    for (int i = 2; i <= n; i++) {
        read(p[i]);
        G[p[i]].push_back(i);
    }
    paint(1);
    return 0;
}