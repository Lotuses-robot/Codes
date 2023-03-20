// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

#define int long long
#define mod 998244353
#define maxn 20000007

int qpow(int x, int y) {
    int base = x, ans = 1;
    do {
        if (y & 1) ans *= base, ans %= mod;
        base *= base; base %= mod;
    } while (y >>= 1);
    return ans;
}

int inv(int x) {
    return qpow(x, mod - 2);
}

bool xxs[maxn];
int invv[maxn];
std::vector<int> ss;
int n, k, frac = 1, ans = 0;

void init() {
    xxs[1] = 1;
    xxs[2] = 0;
    for (int i = 2; i <= maxn; i++) {
        if (!xxs[i]) {
            ss.push_back(i);
        }
        for (int j = 0; i * ss[j] <= maxn && j < (int)ss.size(); j++) {
            xxs[i * ss[j]] = 1;
            if (i % ss[j] == 0) {
                break;
            }
        }
    }

    for (int e : ss) {
        invv[e] = inv(qpow(e, k));
        // printf("%d %d\n", e, invv[e]);
    }

    invv[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        if (true) {
            // printf("%d\n", i);
            for (int j = 0; j < (int)ss.size() && ss[j] * i <= maxn; j++) {
                // printf("%d %d\n", ss[j] * i, invv[i] * invv[ss[j]]);
                invv[ss[j] * i] = invv[i] * invv[ss[j]];
                invv[ss[j] * i] %= mod;
                if (i % ss[j] == 0) {
                    break;
                }
            }
        }
        // printf("%d %d\n", i, invv[i]);
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, k);
    init();

    for (int i = 1; i <= n; i++) {
        frac *= i; frac %= mod;
        ans += frac * invv[i] % mod;
        ans %= mod;
    }
    printf("%lld\n", ans);
    return 0;
}
