// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <unordered_map>

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

const int mod = 1e9 + 7,
          maxn = 5e3 + 10;

int n;
int f[maxn][maxn];
int ans[maxn << 2], fac[maxn << 2];

void init() {
    fac[0] = 1;
    for (int i = 1; i <= n * 4; i++) fac[i] = fac[i - 1] * i % mod;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        f[1][i] = i;
        (sum += f[1][i]) %= mod;
    }
    ans[1] = sum * fac[1] % mod * fac[n - 1] % mod;
    // writeln(ans[1]);
}

void dp() {
    for (int i = 2; i <= n; i++) {
        int cal = f[i - 1][n - i + 2], sum = 0;
        for (int j = n - i + 1; j >= 1; j--) {
            f[i][j] = cal * j % mod; (sum += f[i][j]) %= mod;
            (cal += f[i - 1][j]) %= mod;
        }
        ans[i] = sum * fac[i] % mod * fac[n - i] % mod;
        // writeln(ans[i]);
    }
}

char ch[maxn << 4]; int _n;
int lf[maxn << 4], rf[maxn << 4];

std::unordered_map<int, int> build(int l, int r) {
    std::unordered_map<int, int> mp, lc; lc[0] = 1;
    for (int i = l; i <= r; i++) {
        if (ch[i] == '(') {
            auto x = build(i + 1, rf[i] - 1); const auto ls = lc; lc.clear();
            // for (auto q : x) {
            //     writeln(q.first, q.second);
            //     writeln(-1);
            // }
            for (auto p : ls) {
                for (auto q : x) {
                    (lc[p.first + q.first] += p.second * q.second % mod) %= mod;
                }
            }
            i = rf[i];
        }
        if (ch[i] == 'x') {
            const auto ls = lc; lc.clear();
            for (auto p : ls) {
                lc[p.first + 1] = p.second;
            }
        }
        if (ch[i] == '+') {
            for (auto p : lc) {
                (mp[p.first] += p.second) %= mod;
            }
            lc.clear(); lc[0] = 1;
        }
    }
    for (auto p : lc) {
        (mp[p.first] += p.second) %= mod;
    }
    return mp;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%s", ch); _n = strlen(ch);
    std::stack<int> stt;
    memset(lf, -1, sizeof(lf)); memset(rf, -1, sizeof(rf));
    for (int i = 0; i < _n; i++) {
        if (ch[i] == 'x') n++;
        if (ch[i] == '(') stt.push(i);
        if (ch[i] == ')') lf[i] = stt.top(), rf[stt.top()] = i, stt.pop();
    }
    init(); dp();
    auto list = build(0, _n);
    int sum = 0;
    for (auto p : list) {
        (sum += ans[p.first] * p.second % mod) %= mod;
    }
    writeln(sum);
    // int sum = 0, cntx = 0;
    // for (int i = 0; i < _n; i++) {
    //     if (ch[i] == 'x') {
    //         cntx++;
    //     } else if (ch[i] == '+') {
    //         (sum += ans[cntx]) %= mod;
    //         cntx = 0;
    //     }
    // }
    // if (cntx) (sum += ans[cntx]) %= mod;
    // printf("%lld\n", sum);
    return 0;
}
