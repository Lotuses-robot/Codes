// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
#include <queue>
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

#define ll long long

const int maxn = 1e5 + 10, upb = 2e7 + 1;
int n, cnt[upb + 10], a[maxn];
ll f[upb + 10];
// std::set<int> q;
// std::queue<int> q;

#define max(a, b) ((a) > (b) ? (a) : (b))

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        cnt[a[i]]++;
    }
    for (int i = 1; i <= upb; i++) {
        for (int j = i * 2; j <= upb; j += i) {
            cnt[i] += cnt[j];
        }
    }

    ll ans = 0;
    for (int i = upb; i >= 1; i--) {
        f[i] = 1ll * cnt[i] * i;
        for (int j = i * 2; j <= upb; j += i) {
            f[i] = max(f[i], f[j] + (cnt[i] - cnt[j]) * 1ll * i);
        }
        if (cnt[i] == n) {
            ans = max(ans, f[i]);
        }
    }
    writeln(ans);
    return 0;
}