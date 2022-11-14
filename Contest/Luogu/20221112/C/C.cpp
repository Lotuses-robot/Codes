// Copyright 2022 Lotuses
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>    

#define gc getchar()
template <typename T> void read(T &r) { // NOLINT
    r = 0;
    static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9')
        last = ch, ch = gc;
    while (ch >= '0' && ch <= '9')
        r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template <typename T, typename... Ts>
void read(T &arg, Ts &...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

int a[114514];
int backup[114514];

namespace pc {
    typedef long long LL;

    LL n, m, p = 998244353;

    LL quick_mod(LL a, LL b) {
            LL ans = 1;
            a %= p;
            while (b) {
                if (b & 1) {
                ans = ans * a % p;
                b--;
                }
                b >>= 1;
                a = a * a % p;
            }
            return ans;
    }

    LL C(LL n, LL m) {
            if (m > n)
                return 0;
            LL ans = 1;
            for (int i = 1; i <= m; i++) {
                LL a = (n + i - m) % p;
                LL b = i % p;
                ans = ans * (a * quick_mod(b, p - 2) % p) % p;
            }
            return ans;
    }

    LL Lucas(LL n, LL m) {
    if (m == 0)
            return 1;
    return C(n % p, m % p) * Lucas(n / p, m / p) % p;
    }
} // namespace pc

namespace dfs {
    int maxlevel;
    int split(int n,int m, int level) {
        if (level > maxlevel) return 0;
        if(n == 1 || m == 1) return 1;
        else if(n < m) return split(n,n, level + 1);
        else if(n == m) return split(n,n-1, level + 1) + 1;
        else return split(n,m-1, level + 1)+split(n-m,m, level + 1);
    }
}

int f[101][101][101];

int main() {
#ifdef LOCAL
    freopen(".in", "r", stdin);
    freopen(".out", "w", stdout);
#endif
    int n, ng = 0, po = 0, q;
    read(n);
    for (int i = 0; i < n; i++) {
        read(q);
        if (q == 1) po++;
        if (q == -1) ng++;
        a[i] = backup[i] = q;
    }
    if (ng == po) {
        printf("%d\n", ng + 1);
    } else if (ng > po) {
        printf("%lld\n", pc::Lucas(ng + 1, po));
    } else {
        // printf("%lld\n", pc::Lucas(po - 1, ng));
        int q = po - ng, ans = 0, t = ng + 1;

        // printf("%d %d\n", t, q);

        for (int j = 0; j <= q; j++) {
            if (j != 0) f[1][j][j - 1] = 1;
            
        }
        for (int i = 2; i <= t; i++) {
            for (int j = 0; j <= po; j++) {
                for (int k = 0; k <= std::min(j, q); k++) {
                    f[i][j] += f[i - 1][j - k];
                }
                printf("%d %d %d\n", i, j, f[i][j]);
            }
        }
        printf("%d\n", f[t][po]);
    }
    return 0;
}
