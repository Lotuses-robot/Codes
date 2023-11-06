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
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif
#define ins(a, b) (G[a].emplace_back(b))

#define int long long

const int maxn = 5e5 + 10, mod = 998244353;
int n;
char ch[maxn];
int k[maxn];

void init() {
    memset(k, 0, sizeof(int) * (n + 5));
    k[1] = 0;
    for (int i = 2; i <= n; i++) {
        int &p = k[i]; p = k[i - 1];
        while (p && ch[p + 1] != ch[i]) p = k[p];
        if (ch[p + 1] == ch[i]) p++;
    }
}

int f(int x) {
    int y = k[x];
    int ans = 0;
    while (y) {
        ans += std::__gcd(x, y);
        ans %= mod;
        y = k[y];
    }
    return ans;
}

tsz main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    
    int T;
    read(T);
    while (T--) {
        scanf("%s", ch + 1); n = strlen(ch + 1);
        init();
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            ans *= (f(i) + 1) % mod;
            ans %= mod;
        }
        writeln(ans);
    }
    return 0;
}