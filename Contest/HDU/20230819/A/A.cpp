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

const int maxn = 100005;
struct Node {
    double a[7]; int cost;
    void rd(int rdd = true) {
        if (rdd) scanf("%lf%lf%lf%lf%lf%d", &a[1], &a[2], &a[3], &a[4], &a[5], &cost);
        else scanf("%lf%lf%lf%lf%lf", &a[1], &a[2], &a[3], &a[4], &a[5]);
    }
    bool check(Node b) const {
        for (int i = 1; i <= 5; i++) {
            if (a[i] < b.a[i]) return false;
        }
        return true;
    }
} it[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        for (int i = 1; i <= n; i++) {
            it[i].rd();
        }
        for (int i = 1; i <= m; i++) {
            Node c; c.rd(false);
            int minn = 0;
            for (int j = 1; j <= n; j++) {
                if (it[j].check(c)) {
                    if (minn == 0 || it[minn].cost > it[j].cost) {
                        minn = j;
                    }
                }
            }
            printf("%d\n", minn);
        }
    }
    return 0;
}
