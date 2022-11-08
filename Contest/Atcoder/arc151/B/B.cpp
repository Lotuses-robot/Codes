// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

const int mod = 998244353;

int p[214514];

int quickPower(int a, int b) {
    int ans = 1, base = a;
    while (b > 0) {
        if (b & 1) {
            ans *= base;
            ans %= mod;
        }
        base *= base;
        ans %= mod;
        b >>= 1;
    }
    return ans;
}

#define maxn 214514

struct union_find_set {
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void uni(int x, int y) {
        fa[find(x)] = find(y);
    }
}ufs;

bool moreinf[maxn];

signed main() {
    int n, m;
    read(n, m);
    for (int i = 0; i < n; i++) {
        read(p[i]);
    }

    ufs.init(n);

    int s = 0, nowtt = n - 1;
    moreinf[0] = true;

    for (int i = 0; i < n; i++) {
        if (moreinf[i]) continue;
        int px = (m - 1) * m / 2;
        s += px * quickPower(m, nowtt - 1) % mod;
        s %= mod;

        printf("%d %d %d\n", px, m, nowtt - 1);
        nowtt--;

        if (p[i] > i) {
            nowtt--;
            moreinf[p[i]] = true;
        }
        // ufs.uni(i, p[i]);
    }
    printf("%lld\n", s);
    return 0;
}
