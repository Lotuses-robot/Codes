// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <ctime>
#include <cstdlib>
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

const int maxn = 5e5 + 10;
int n;
struct Node {
    int x, y, z;
} p[maxn][2];

#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))

int tm, ans = 0;

void upd() {
    static int maxx, maxy, maxz; maxx = maxy = maxz = 0;
    static int minx, miny, minz; minx = miny = minz = 1e9 + 1;
    for (register int i = 1; i <= n; i++) {
        static int x;
        x = rand() & 1;
        minx = min(minx, p[i][x].x);
        maxx = max(maxx, p[i][x].x);
        miny = min(miny, p[i][x].y);
        maxy = max(maxy, p[i][x].y);
        minz = min(minz, p[i][x].z);
        maxz = max(maxz, p[i][x].z);
    }
    ans = min(ans, max(max(maxx - minx, maxy - miny), maxz - minz));
}

tsz main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    
    srand(time(NULL));

    register int T, bg, now;
    read(T); tm = 2900 / T - 10;
    while (T--) {
        read(n);
        for (int i = 1; i <= n; i++) {
            read(p[i][0].x, p[i][0].y, p[i][0].z);
            read(p[i][1].x, p[i][1].y, p[i][1].z);
        }
        bg = clock(); now = clock(); ans = 2e9;
        while (now - bg <= tm) {
            for (int i = 1; i <= 5; i++) {
                upd();
            }
            now = clock();
        }
        writeln(ans);
    }
    return 0;
}