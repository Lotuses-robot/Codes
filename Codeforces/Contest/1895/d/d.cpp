// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
// #include <map>
#include <set>
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

const int maxn = 2e5 + 10;
int a[maxn], n;
std::set<std::pair<int, int> > s;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i < n; i++) {
        read(a[i]); a[i] ^= a[i - 1];
    }
    for (int i = 0; i < n; i++) {
        std::bitset<30> prefix = 0;
        for (int x = 29; x >= 0; x--) {
            int ax = (a[i] >> x) & 1, nx = (n - 1 >> x) & 1;
            if (!nx) {
                int b = prefix.to_ulong() + ((ax ^ 1) << x);
                int e = prefix.to_ulong() + ((ax ^ 1) << x) + (1 << x) - 1;
                s.insert(std::make_pair(b, e));
            }
            prefix.set(x, ax ^ nx);
        }
    }
    int howend = -1, ret;
    for (auto p : s) {
        if (p.first > howend + 1) {
            ret = howend + 1;
            break;
        }
        howend = std::max(p.second, howend);
    }
    for (int i = 1; i <= n; i++) {
        write(a[i - 1] ^ ret); putchar(' ');
    }
    puts("");
    return 0;
}