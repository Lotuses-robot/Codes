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

const int maxn = 60, mod = 1e9 + 7;
struct Matrix {
    int mp[maxn][maxn];
    Matrix() { memset(mp, 0, sizeof(mp)); }
    Matrix operator * (Matrix b) const {
        Matrix r;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                for (int k = 0; k < maxn; k++) {
                    r.mp[i][j] += mp[i][k] * b.mp[k][j] % mod;
                    r.mp[i][j] %= mod;
                }
            }
        }
        return r;
    }
} a, bs;

int map[255];
template<typename T>
T pow(T it, T x, int y) {
    do {
        if (y & 1) it = it * x;
        x = x * x;
    } while (y >>= 1);
    return it;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    for (int i = 0; i < 26; i++) map['a' + i] = i + 1;
    for (int i = 0; i < 26; i++) map['A' + i] = i + 27;

    int n, m, k;
    read(n, m, k);
    for (int i = 1; i <= m; i++) a.mp[0][i] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            bs.mp[i][j] = 1;
        }
    }
    for (int i = 1; i <= k; i++) {
        static char ch[4];
        scanf("%s", ch);
        bs.mp[map[ch[0]]][map[ch[1]]] = 0;
    }
    a = pow(a, bs, n - 1);
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += a.mp[0][i]; ans %= mod;
    }
    writeln(ans);
    return 0;
}
