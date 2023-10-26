// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
// #include <queue>
#include <stack>
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

const int maxn = 2e6 + 10;
struct hsh {
    int val, mod, x;

    int pow(int y) const {
        int a = 1, bs = x;
        do {
            if (y & 1) a *= bs, a %= mod;
            bs *= bs; bs %= mod;
        } while (y >>= 1);
        return a;
    }

    void modify(int ch, int p, int mode) {
        val += mode * ch * pow(p - 1) % mod;
    }
} h1, h2;
std::stack<char> st;
char ch[maxn];
std::map<std::pair<int, int>, int> cnt;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    srand(time(0));
    h1 = { 0, 998244353, 131 };
    h2 = { 0, (int)1e9 + 7, 131 };

    int n, ans = 0;
    read(n);
    scanf("%s", ch + 1);

    cnt[{0, 0}]++;
    for (int i = 1; i <= n; i++) {
        if (st.empty() || st.top() != ch[i]) {
            st.push(ch[i]);
            h1.modify(ch[i], st.size(), 1);
            h2.modify(ch[i], st.size(), 1);
        } else {
            h1.modify(ch[i], st.size(), -1);
            h2.modify(ch[i], st.size(), -1);
            st.pop();
        }
        cnt[{h1.val, h2.val}]++;
    }
    for (auto p : cnt) {
        // writeln(p.first.first, p.first.second, p.second);
        ans += (p.second) * (p.second - 1) / 2;
    }
    writeln(ans);
    return 0;
}