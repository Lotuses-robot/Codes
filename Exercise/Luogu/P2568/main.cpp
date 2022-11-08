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
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

#define int long long
#define MAXN 11451419

int N, prime[MAXN], vis[MAXN], phi[MAXN], tot;
void GetPhi(int N) {
    vis[1] = phi[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!vis[i]) prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * prime[j] <= N; j++) {
            vis[i * prime[j]] = 1;
            if (!(i % prime[j])) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            phi[i * prime[j]] = phi[i] * phi[prime[j]];
        }
    }
    for (int i = 1; i <= N; i++) {
        phi[i] += phi[i - 1];
    }
}

signed main() {
    int n, ans = 0;
    read(n);
    GetPhi(n + 57);
    for (int i = 1; ; i++) {
        if (prime[i] > n) break;
        ans += phi[n / prime[i]] * 2 - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
