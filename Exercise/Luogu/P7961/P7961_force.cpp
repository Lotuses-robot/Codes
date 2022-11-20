// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <bitset>
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

#define mMax 1003
#define MOD 998244353
int n, m, k;
int v[mMax];

typedef std::bitset<mMax> bs;
#define ll long long
#define int long long

namespace force {
    ll dfs(int ct, bs st, ll val) {
        if (ct >= n && st.count() <= k) return val;
        else if (ct >= n) return 0;
        ll ans = 0;
        unsigned ll q = st.to_ullong();
        for (int i = 0; i <= m; i++) {
            ans += dfs(ct + 1, q + (1 << i), val * v[i]);
            ans %= MOD;00
        }
        return ans;
    }
}

signed main() {
    #ifdef LOCAL
        freopen("data/sequence2.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, k);
    for (int i = 0; i <= m; i++) {
        read(v[i]);
    }

    printf("%lld\n", force::dfs(0, 0, 1));
    return 0;
}
