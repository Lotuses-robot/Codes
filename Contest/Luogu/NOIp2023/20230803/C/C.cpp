// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>

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

#define int long long

const int maxn = 50004;
std::vector<unsigned int> st[maxn];
const int mod = 1e9 + 7;

inline unsigned next_integer(unsigned x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int n, q, j, cnt = 0;
    char ch[3];
    read(n, q);
    unsigned int sd, ans = 0, lastans = 0;
    read(sd);
    for (int i = 1; i <= q; i++) {
        scanf("%s%lld", ch, &j);
        if (ch[0] == '<') {
            st[j].push_back(sd = next_integer(sd));
        } else {
            // puts("/yiw");
            st[j].pop_back();
            if (cnt == 5e5) st[j].shrink_to_fit(), cnt = 0;
            cnt++;
        }
        if (st[j].size() != 0) {
            lastans = st[j][lastans % st[j].size()];
        }
        ans += 1ull * i * lastans % mod;
        ans %= mod;
    }
    writeln(ans);
    return 0;
}
