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
#define debuqg(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].emplace_back(b))

typedef long long ll;

const int maxn = 2e5 + 10;
int a[maxn], b[maxn];

tsz main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        read(b[i]);
    }
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + m + 1);
    int al = 1, ar = n, bl = 1, br = m; ll ans = 0;
    while (ar >= 1 && br >= 1 && a[ar] > 0 && b[br] > 0) {
        ans += 1ll * a[ar] * b[br];
        ar--; br--;
    }
    while (al <= ar && bl <= br && a[al] < 0 && b[bl] < 0) {
        ans += 1ll * a[al] * b[bl];
        al++; bl++;
    }
    if (al <= ar) {
        std::sort(a + al, a + ar + 1, [] (int a, int b) { return std::abs(a) < std::abs(b); });
        std::sort(b + bl, b + br + 1, [] (int a, int b) { return std::abs(a) < std::abs(b); });
        for (int i = al; i <= ar; i++) {
            ans += 1ll * a[i] * b[br--];
        }
    }
    writeln(ans);
    return 0;
}