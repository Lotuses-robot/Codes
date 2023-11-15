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

const int maxn = 2e5 + 10;

int n, a[maxn], nn, k;
int f[maxn][20];
int Logn[maxn];
void pre() {
    Logn[1] = 0;
    for (int i = 2; i <= nn; i++)
        Logn[i] = Logn[i / 2] + 1;
}
void init() {
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= nn; i++)
        f[i][0] = a[i];
    int lognn = std::__lg(nn);
    for (int j = 1; j <= lognn; j++)
        for (int i = 1; i + (1 << j) - 1 <= nn; i++)
            f[i][j] = std::min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
}
int fun(int x, int sum = 0) {
    sum += x * k;
    for (int i = 1; i <= n; i++) {
        int l = i, r = i + x;
        int s = Logn[r - l + 1];
        sum += std::min(f[l][s], f[r - (1 << s) + 1][s]);
    }
    return sum;
}
tsz main() {
    freopen("collect.in", "r", stdin);
    freopen("collect.out", "w", stdout);
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        a[i + n] = a[i];
    }
    nn = n * 2;
    pre();
    init();
    int ans = 1e18;
    for (int i = 0; i < n; i++) {
        ans = std::min(fun(i), ans);
    }
    writeln(ans);
    return 0;
}