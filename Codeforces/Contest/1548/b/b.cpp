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

#define ull unsigned long long
#define int long long

const int maxn = 2e5 + 10;
int a[maxn], Lg[maxn];
int f[maxn][20], m;

inline int gcd(const int&a, const int&b) {
	return b ? gcd(b, a % b) : a;
}

void ent() {
    Lg[1] = 0;
    for (int i = 2; i <= maxn - 5; i++) Lg[i] = Lg[i >> 1] + 1;
}

void init() {
    for (int k = 1; k <= 18; k++) {
        for (int i = 1; i <= m - (1 << k) + 1; i++) {
            f[i][k] = std::__gcd(f[i][k - 1], f[i + (1 << k - 1)][k - 1]);
            // writeln(i, k, f[i][k - 1], f[i + (1 << k - 1)][k - 1], f[i][k]);
        }
    }
}

int query(int l, int r) {
    if (l == r) return f[l][0];
    int lg = Lg[r - l + 1];
    // writeln(-1, l, r, lg, f[l][lg], f[r - (1 << lg) + 1][lg]);
    return gcd(f[l][lg], f[r - (1 << lg) + 1][lg]);
}

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    ent();
    int T;
    read(T);
    while (T--) {
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        for (int i = 1; i < n; i++) {
            f[i][0] = std::abs(a[i + 1] - a[i]);
            // write(f[i][0]); putchar(' ');
        }
        // puts("");
        m = n - 1; init();

        int len = 1, j, ret, ans = 0;
        for (int i = 1; i <= m - len + 1; i++) {
            j = i + len - 1; ret = query(i, j);
            // writeln(i, j, ret);
            while (ret > 1 || ret == 0) {
                j++; len++;
                if (j > m) {
                    j--; len--;
                    break;
                }
                ret = query(i, j);
                // writeln(j, len);
                // writeln(i, j, len, ret);
            }
            if (ret == 1) len--;
            ans = std::max(ans, len);
            len = std::max(len, 1ll);
            // writeln(i, len, ret);
        }
        writeln(ans + 1);
    }
    return 0;
}