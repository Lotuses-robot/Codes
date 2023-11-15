// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
// #include <queue>
// #include <stack>
// #include <string>
#include <algorithm>
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

#define int unsigned long long

const int mod = 1e9 + 7;
int cnt[128];
int powx[128][128];

int log(int x, int y, bool up = false) {
    int cnt = 0;
    while (y >= x) y /= x, cnt++;
    if (up && y > 0) {
        cnt++;
    }
    return cnt;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    for (int i = 2; i <= 63; i++) {
        powx[i][0] = 1; cnt[i] = 1;
        for (int &j = cnt[i]; 1.0 * powx[i][j - 1] * i <= 1e18; j++) {
            powx[i][j] = powx[i][j - 1] * i;
        }
        powx[i][cnt[i]] = powx[i][cnt[i] - 1] * i;
        cnt[i]++;
    }

    int T;
    read(T);
    while (T--) {
        int l, r, ans = 0, id;
        read(l, r); id = log(2, l);
        for (int a = l, b; a <= r; a++, id++) {
            b = std::min(r, powx[2][id + 1] - 1);
            int idx = log(id, a);
            for (int _l = a, _r; _l <= b; _l++, idx++) {
                _r = std::min(b, powx[id][idx + 1] - 1);
                ans += (_r - _l + 1) % mod * idx % mod;
                ans %= mod;
                _l = _r;
            }
            a = b;
        }
        writeln(ans);
    }
    return 0;
}