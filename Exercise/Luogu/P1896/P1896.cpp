// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1ll) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

#define maxn (1ll << 10)
#define int long long

int calc(int k) {
    int ans = 0;
    do ans += (k & 1ll); while (k >>= 1ll); // NOLINT
    return ans;
}

bool check(int k) {
    do {
        if ((k & 3) == 3) {
            return false;
        }
    } while (k >>= 1ll);
    return true;
}

bool check(int k, int j) {
    k <<= 1ll; j <<= 1ll; // NOLINT
    do {
        if ((k & 2) == 2) {
            if (j & 7) {
                return false;
            }
        }
        j >>= 1ll;
    } while (k >>= 1ll);
    return true;
}

int f[15][14514][100];

signed main() {
    // printf("%d %d %d\n", check(85), check(5), check(7));

    int n, K;
    read(n, K);

    for (int i = 0; i < (1ll << n); i++) {
        f[0][i][calc(i)] = check(i);
        // printf("%d %s\n", i, check(i) ? "Yes" : "No");
    }

    for (int i = 1ll; i < n; i++) {
        for (int j = 0; j < (1ll << n); j++) {
            int tot = calc(j);
            if (!check(j)) {
                continue;
            }
            for (int k = 0; k < (1ll << n); k++) {
                if ((j & k) || ((j << 1ll) & k) || (j & (k << 1ll))) continue;
                if (!check(k)) continue;
                for (int len = tot; len <= K; len++) {
                    f[i][j][len] += f[i - 1ll][k][len - tot];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < (1ll << n); i++) {
        ans += f[n - 1ll][i][K];
    }

    printf("%lld\n", ans);
    return 0;
}
