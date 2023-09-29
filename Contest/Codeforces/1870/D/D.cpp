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

#define int long long

const int maxn = 2e5 + 10;
int c[maxn];
int n, k;
std::vector<std::pair<int, int> > vp;

void split(int l, int minus, int last) {
    int min = last / (c[l] - minus), minid = l;
    for (int i = l + 1; i <= n; i++) {
        if (last / (c[i] - minus) >= min) {
            min = last / (c[i] - minus);
            minid = i;
        }
    }
    debug(min, minid);
    int x = min, y = last - min * (c[minid] - minus);
    vp.push_back({minid, x});
    debug(l, last);
    if (y && minid < n) split(minid + 1, c[minid], y);
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; i++) {
            read(c[i]);
        }
        read(k);
        vp.clear();
        split(1, 0, k); int x = 1;
        for (auto e : vp) {
            for (x; x <= e.first; x++) {
                write(e.second), putchar(' ');
            }
        }
        for (x; x <= n; x++) {
            write(0); putchar(' ');
        }
        puts("");
    }
    return 0;
}
