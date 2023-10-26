// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
#include <queue>
// #include <stack>
// #include <string>
// #include <algorithm>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define ins(a, b) (G[a].emplace_back(b))

#define int long long

const int maxn = 1e5 + 10;
struct Hash {
    struct Hsh {
        int val, x, mod;
        int qpow(int x, int y) const {
            int b = x, ans = 1;
            do {
                if (y & 1) ans *= b, ans %= mod;
                b *= b; b %= mod;
            } while (y >>= 1);
            return ans;
        }
        void modify(int a, int mode) {
            val = (val + mode * qpow(x, a) % mod + mod) % mod;
        }
        Hsh operator + (const Hsh &b) const {
            return { (val + b.val) % mod, x, mod };
        }
        Hsh operator - (const Hsh &b) const {
            return { (val - b.val + mod) % mod, x, mod };
        }
    } sh1, sh2;
    Hash() { sh1.mod = 1000000007; sh1.x = 100003; sh2.mod = 998244353; sh2.x = 100003; }
    Hash(Hsh a, Hsh b) { sh1 = a; sh2 = b; }

    void modify(int a, int mode) {
        sh1.modify(a, mode);
        sh2.modify(a, mode);
    }

    Hash operator + (const Hash &b) const {
        return { sh1 + b.sh1, sh2 + b.sh2 };
    }

    Hash operator - (const Hash &b) const {
        return { sh1 - b.sh1, sh2 - b.sh2 };
    }

    bool operator == (const Hash &b) const {
        return sh1.val == b.sh1.val && sh2.val == b.sh2.val;
    }
} hs, sum, base;

int ed[maxn], r[maxn << 2];
// std::vector<int> a[maxn];
std::vector<Hash> v[maxn];
std::vector<int> arr;
struct Node {
    int id, mv;
};
std::deque<Node> dq;
int nowlen;
int pre[maxn];
int n, m, T, x;

void mv(int i) {
    nowlen += v[i].size();
    sum = sum + v[i][0];
    dq.push_back({i, 0});
    while (nowlen > m) {
        // writeln(-1, nowlen, m);
        auto x = dq.front(); dq.pop_front();
        sum = sum - v[x.id][x.mv];
        nowlen -= (int)v[x.id].size() - x.mv;
        if (nowlen < m) {
            int pas = (int)v[x.id].size() - (m - nowlen);
            dq.push_front({x.id, pas});
            sum = sum + v[x.id][pas];
            nowlen = m;
        }
    }
    // writeln(sum.val);
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    read(n, m, T);
    for (int i = 1; i <= m; i++) {
        read(x);
        hs.modify(x, 1);
    }
    for (int i = 1; i <= n; i++) {
        int len; read(len);
        for (int j = 1; j <= len; j++) {
            read(x);
            v[i].emplace_back(base);
            v[i].back().modify(x, 1);
        }
        for (int j = len - 2; j >= 0; j--) {
            v[i][j] = v[i][j] + v[i][j + 1];
        }
    }
    
    int ml;
    read(ml);
    for (int i = 1; i <= ml; i++) {
        read(r[i]);
    }

    int ans = 0;
    for (int i = 1; i <= T && i <= ml; i++) {
        mv(r[i]);
        // writeln(sum.sh1.val);
        if (sum == hs && nowlen == m) {
            ans++;
        }
    }

    // writeln(ans);
    // puts("");

    if (T <= ml) {
        writeln(ans);
        return 0;
    }

    int tot = 0;
    T -= ml;
    for (int i = 1; i <= T && i <= ml; i++) {
        mv(r[i]); pre[i] = pre[i - 1];
        // writeln(sum.val);
        if (sum == hs) {
            pre[i]++; tot++;
        }
    }

    // writeln(tot);

    writeln(ans + T / ml * tot + pre[T % ml]);
    return 0;
}