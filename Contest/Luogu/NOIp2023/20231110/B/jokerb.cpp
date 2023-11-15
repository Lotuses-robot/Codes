// Copyright 2023 Lotuses
#define tsz signed
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

#define int long long
const double eps = 1e-8;
int rq, rx;

int f(int Q) {
    int ans = 0; rx = floor(sqrt(Q + rq * rq) + eps) - 1;
    // writeln(rx);
    for (int x = floor(sqrt(Q) - eps); ; x++) {
        int ql = ceil(sqrt(x * x - Q) - eps), qr = floor(sqrt((x + 1) * (x + 1) - Q - 1) + eps);
        if (x * x - Q < 0) ql = 0;
        if (x % 1000000 == 0) {
            writeln(x);
            writeln(ql, qr);
        }
        ans += (std::min(qr, rx) - ql + 1) * x;
        if (qr >= rx) break;
    }
    return ans;
}

int g(int P) {
    int ans = 0; int px = (P - 1) / 2; int x;
    for (x = ceil(sqrt(P) - eps); ; x++) {
        int ql = ceil(sqrt((x - 1) * (x - 1) + 1 - P) - eps), qr = floor(sqrt(x * x - P) + eps);
        if ((x - 1) * (x - 1) + 1 - P < 0) ql = 0;
        // writeln(ql, qr, x);
        // if (x % 1000000 == 0) writeln(x);
        ans += (std::min(qr, px) - ql + 1) * (x - 1);
        if (qr >= px) {
            if (qr == px) x++;
            break;
        }
    }
    x--;
    // x++;
    // writeln(x, rx, px);
    ans += (x + x + (rx - px) - 1) * (rx - px) / 2;
    return ans;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int P, Q, ans;
        read(P, Q);
        rq = (Q - 1) / 2;
        ans = f(Q);
        writeln(ans - g(P));
    }
    return 0;
}