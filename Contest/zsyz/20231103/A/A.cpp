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

#define ull unsigned long long

namespace MR {
    const __int128 __int128_1 = 1;
    ull qpow(ull x, ull y, ull p) {
        ull ans = 1;
        do {
            if (y & 1) ans = __int128_1 * ans * x % p;
            x = __int128_1 * x * x % p;
        } while (y >>= 1);
        return ans;
    }

    bool check(ull n, ull a, ull b, ull x) {
        // writeln(x);
        // writeln(x, a, n);
        ull v = qpow(x, a, n);
        // writeln(v);
        if (v == 1) return true;
        ull j = 1;
        while (j <= b) {
            if (v == n - 1) break;
            v = __int128_1 * v * v % n;
        // writeln(v);
            j++;
        }
        // writeln(j);
        if (j > b) return false;
        return true;
    }

    ull numx[] = { 0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };

    bool mr(ull n) {
        if (n <= 2 || n % 2 == 0) return n == 2;
        if (n > 37) {
            ull a = n - 1, b = 0;
            while (!(a & 1)) a >>= 1, b++;
            for (int i = 1; i <= 12; i++) {
                if (!check(n, a, b, numx[i])) {
                    return false;
                }
            }
            return true;
        } else {
            for (int i = 1; i <= 12; i++) {
                if (n == numx[i]) return true;
            }
            return false;
        }
    }
}

ull sqrt(ull x, ull y) {
    ull l = 1, r = (1ll << 32) - 1;
    while (l < r) {
        ull mid = (l + r) >> 1;
        if (MR::qpow(mid, y, -1) >= x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

const int mod = 998244353;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        ull n;
        read(n);
        if (MR::mr(n)) {
            writeln(n % mod);
            continue;
        }
        bool ok = false;
        for (int i = 2; i <= 10; i++) {
            int qt = sqrt(n, i);
            if (MR::qpow(qt, i, -1) == n) {
                ok = true;
                if (MR::mr(qt)) {
                    writeln(qt % mod);
                } else {
                    writeln(1);
                }
                break;
            }
        }
        if (ok) continue;
        ull qn = n;
        for (int i = 2; i <= 70; i++) {
            while (qn % i == 0) qn /= i;
            if (qn != n) {
                ok = true;
                if (qn == 1) {
                    writeln(i);
                } else {
                    writeln(1);
                }
                break;
            }
        }
        if (!ok) writeln(1);
    }
    return 0;
}