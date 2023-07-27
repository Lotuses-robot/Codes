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

#define int long long

const int mod = 998244353;
const int sz = 2;
struct mat {
    int a[sz][sz];
    inline mat() { memset(a, 0, sizeof a); }
    inline mat operator-(const mat &T) const {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                res.a[i][j] = (a[i][j] - T.a[i][j]) % mod;
        return res;
    }
    inline mat operator+(const mat &T) const {
        mat res;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                res.a[i][j] = (a[i][j] + T.a[i][j]) % mod;
        return res;
    }
    inline mat operator*(const mat &T) const {
        mat res;
        int r;
        for (int i = 0; i < sz; ++i)
            for (int k = 0; k < sz; ++k) {
                r = a[i][k];
                for (int j = 0; j < sz; ++j)
                    res.a[i][j] += T.a[k][j] * r % mod, res.a[i][j] %= mod;
            }
        return res;
    }
    inline mat operator^(int x) const {
        mat res, bas;
        for (int i = 0; i < sz; ++i)
            res.a[i][i] = 1;
        for (int i = 0; i < sz; ++i)
            for (int j = 0; j < sz; ++j)
                bas.a[i][j] = a[i][j] % mod;
        while (x) {
            if (x & 1)
                res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }
};

const int maxn = 2550;
int f[maxn][maxn][2];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    mat q, a, base, ans;

    base.a[0][0] = 2; base.a[0][1] = 1;
    q.a[0][0] = 1; q.a[0][1] = 1;
    q.a[1][0] = 1; q.a[1][1] = 0;

    bool flag = false;

    int T;
    read(T);
    while (T--) {
        int n, m;
        read(n, m);
        if (m == 1) {
            if (n < 2) {
                writeln(1);
                continue;
            }
            a = base;
            ans = a * (q ^ (n - 2));
            writeln((ans.a[0][0] + ans.a[0][1] - 1) % mod);
        } else {
            if (!flag) {
                f[1][0][0] = f[1][1][1] = 1;
                for (int i = 2; i <= 2501; i++) {
                    for (int j = 0; j <= 2501; j++) {
                        if (j > 0) f[i][j][1] = f[i - 1][j - 1][0];
                        f[i][j][0] = f[i - 1][j][1] + f[i - 1][j][0];
                        f[i][j][0] %= mod;
                    }
                }
                flag = true;
            }
            int ans = 0;
            for (int j = m; j <= n; j++) {
                ans += (f[n][j][0] + f[n][j][1]) % mod;
                ans %= mod;
            }
            writeln(ans);
        }
    }
    return 0;
}
