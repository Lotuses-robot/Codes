// Copyright 2023 Lotuses
#define tsz signed
#define _USE_MATH_DEFINES 
#include <cmath>
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

int n; 
double a[100];

double calc(double x) {
    double sum = 0;
    for(int i = 0; i <= n; i++) sum = sum * x + a[i];
    return sum; 
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    double l, r;
    read(n); scanf("%lf%lf", &l, &r);
    for (int i = 0; i <= n; i++) scanf("%lf", &a[i]);

    while (fabs(r - l) > 1e-7) {
        double len = (r - l) / M_E;
        double lm = calc(l + len), rm = calc(r - len);
        // printf("%.6lf %.6lf\n", lm, rm);
        if (lm < rm) {
            l = l + len;
        } else {
            r = r - len;
        }
        // printf("%.6lf %.6lf\n", l, r);
    }
    printf("%.6lf\n", l);
    return 0;
}