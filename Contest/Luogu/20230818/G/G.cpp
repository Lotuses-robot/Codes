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

const int maxn = 2e5;
std::vector<int> G[maxn];
std::map<int, int> mp;
int cnt = 0;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        int n, a;
        mp.clear();
        for (int i = 0; i <= cnt; i++) G[i].clear();
        cnt = 0;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a);
            if (mp[a - i] == 0) {
                mp[a - i] = ++cnt;
            }
            G[mp[a - i]].push_back(a);
        }
        int ans = 0;
        for (int i = 1; i <= cnt; i++) {
            for (int j = (int)G[i].size() - 1; j >= 1; j -= 2) {
                if (G[i][j] + G[i][j - 1] < 0) break;
                // writeln(G[i][j], G[i][j - 1]);
                ans += G[i][j] + G[i][j - 1];
            }
        }
        writeln(ans);
    }
    return 0;
}
