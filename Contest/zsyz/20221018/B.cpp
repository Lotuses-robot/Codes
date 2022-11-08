// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define ll long long // NOLINT

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

// const mod = 100000008;

struct Map {
    int a[2][2];
    Map() { memset(a, 0, sizeof(a)); }
    Map operator * (const Map b) const {
        Map ans;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    ans.a[i][j] += a[i][k] * b.a[k][j];
                    ans.a[i][j] %= 100000000;
                }
            }
        }
        return ans;
    }
    Map operator ^ (ll y) const {
        Map x = *this, base = *this;
        y--;
        do {
            if (y & 1) {
                x = x * base;
            }
            base = base * base;
            y >>= 1;
        } while (y);
        return x;
    }
};

Map bs;
Map real;

ll solve(ll power) {
    if (power == 0) return 1;
    bs.a[0][0] = 0; bs.a[0][1] = 1; // NOLINT
    bs.a[1][0] = 1; bs.a[1][1] = 1; // NOLINT

    real.a[0][0] = 1;
    real.a[0][1] = 1;

    real = real * (bs ^ power);
    return real.a[0][0];
}

ll gcd(ll a, ll b) {
    while (a ^= b ^= a ^= b %= a);
    return b;
}

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    ll n, m;
    read(n, m);

    ll gd = gcd(n, m);
    // printf("%lld\n", gd);
    printf("%lld\n", solve(gd - 1));
    return 0;
}
