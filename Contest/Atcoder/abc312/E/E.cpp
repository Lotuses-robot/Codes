// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

struct pr {
    int a, b1, b2, c1, c2;
    bool operator < (pr b) const {
        if (a != b.a) return a < b.a;
        if (b1 != b.b1) return b1 < b.b1;
        if (b2 != b.b2) return b2 < b.b2;
        if (c1 != b.c1) return c1 < b.c1;
        return c2 < b.c2;
    }
};
std::map<pr, int> mp[6];

struct Point {
    int c[3];
};

#define nt(x) ((x) % 3)

std::vector<Point> sva;
std::vector<Point> svb;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        Point a, b;
        read(a.c[0], a.c[1], a.c[2], b.c[0], b.c[1], b.c[2]);
        sva.push_back(a);
        svb.push_back(b);
        for (int j = 0; j < 3; j++) {
            writeln(a.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]);
            mp[j * 2][{a.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]}]++;
            writeln(b.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]);
            mp[j * 2 + 1][{b.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]}]++;
        }
    }


    for (int i = 0; i < n; i++) {
        auto a = sva[i], b = svb[i];
        int ans = 0;
        for (int j = 0; j < 3; j++) {
            ans += mp[j * 2 + 1][{a.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]}];
            ans += mp[j * 2][{b.c[j], a.c[nt(j + 1)], a.c[nt(j + 2)], b.c[nt(j + 1)], b.c[nt(j + 2)]}];
        }
        writeln(ans);
    }
    return 0;
}
