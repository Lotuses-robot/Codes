// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template <typename T> void read(T &r) {
    r = 0;
    static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9')
        last = ch, ch = gc;
    while (ch >= '0' && ch <= '9')
        r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template <typename T, typename... Ts> void read(T &arg, Ts &...arg_left) {
    read(arg);
    read(arg_left...);
}

#define maxn 1145141
#define int long long

int zhi[maxn + 1000], low[maxn + 1000], pri[maxn + 1000], f[maxn + 1000];

#define mod 1000000007


int qpow(int x, int y) {
    int base = x, ans = 1;
    do {
        if (y & 1)
            ans *= base, ans %= mod;
        base *= base;
        base %= mod;
    } while (y >>= 1);
    return ans;
}

void calc(int y, int &x, int &k) {
    // int tot = 0;
    // while (y /= x) tot++;
    // return tot;
    int i;
    for (i = 2; i * i <= y; i++) {
        if (y % i == 0) {
            break;
        }
    }
    if (y % i != 0) {
        x = i;
        k = 1;
    } else {
        x = i;
        k = 0;
        while (y /= x) k++;
    }
}

int gcd(int a, int b){
    return b ? gcd(b, a % b) : a;
}

int k = 0;

bool vis[maxn + 1000];
int prix[maxn + 1000];

void sieve() {
    // int cnt = 0;
    // for (int i = 2; i <= maxn; ++i) {
    //     if (!vis[i]) {
    //         prix[cnt++] = i;
    //     }
    //     for (int j = 0; j < cnt; ++j) {
    //         if (1ll * i * prix[j] > maxn) break;
    //         vis[i * prix[j]] = 1;
    //         if (i % prix[j] == 0) {
    //             break;
    //         }
    //     }
    // }


    int tot = 0;
    zhi[1] = low[1] = 1;
    f[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        printf("%lld\n", i);
        if (!zhi[i])
            low[i] = pri[++tot] = i, f[i] = i;
        for (int j = 1; j <= tot && i * pri[j] <= maxn; j++) {
            zhi[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                low[i * pri[j]] = low[i] * pri[j];
                if (low[i] == i) {
                    int x, y;
                    calc(i * pri[j], x, y);
                    f[i * pri[j]] = qpow(x, 1);
                }
                else
                    f[i * pri[j]] = f[i / low[i]] * f[low[i] * pri[j]];
                break;
            }
            low[i * pri[j]] = pri[j];
            f[i * pri[j]] = f[i] * f[pri[j]];
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif

    int n, m;
    read(n, m, k);

    sieve();

    // for (int i = 1; i <= 100; i++) {
    //     printf("%lld %lld\n", i, f[i]);
    // }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans += f[i] * f[j] % mod;
            ans %= mod;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
