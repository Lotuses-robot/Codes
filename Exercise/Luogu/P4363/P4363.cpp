// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>

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

const int maxn = 12;
int a[maxn][maxn],
    b[maxn][maxn];
int hi[maxn], base = 12;
int n, m;

int zip() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans *= base; ans += hi[i];
    }
    return ans;
}

void unzip(int sta) {
    for (int i = n; i >= 1; i--) {
        hi[i] = sta % base;
        sta /= base;
    }
}

std::map<int, int> mp;
const int inf = 1e18;
int dfs(int sta, int who) {
    if (mp.find(sta) != mp.end()) {
        return mp[sta];
    }
    unzip(sta);
    int ans = who ? inf : -inf;
    for (int i = 1; i <= n; i++) {
        if (hi[i - 1] > hi[i]) {
            hi[i]++;
            int stn = zip();
            if (who) ans = std::min(ans, dfs(stn, who ^ 1) - b[i][hi[i]]);
            else ans = std::max(ans, dfs(stn, who ^ 1) + a[i][hi[i]]);
            hi[i]--;
        }
    }
    return mp[sta] = ans;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m); hi[0] = m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(b[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) hi[i] = m;
    mp[zip()] = 0;
    writeln(dfs(0, 0));
    return 0;
}
