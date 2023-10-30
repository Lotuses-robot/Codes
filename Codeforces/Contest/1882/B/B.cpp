// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

const int maxn = 100;
std::vector<int> v[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        for (int i = 1; i <= 50; i++) v[i].clear();
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            int k, x; read(k);
            for (int j = 1; j <= k; j++) {
                read(x);
                v[x].push_back(i);
            }
        }
        std::vector<int> m;
        for (int j = 1; j <= 50; j++) {
            if (!v[j].empty()) m.push_back(j);
        }
        int ans = 0;
        for (int i : m) {
            int cnt = 0;
            for (int j = 1; j <= 50; j++) {
                // bool flag = false;
                for (int y : v[j]) {
                    bool flag = false;
                    for (int x : v[i]) {
                        if (y == x) {
                            flag = true;
                            break;
                        }
                    }
                    if (!flag) { cnt++; break; }
                }
                // cnt += flag;
            }
            if (cnt == m.size()) continue;
            // puts("???");
            ans = std::max(ans, cnt);
        }
        // puts("-----");
        writeln(ans);
    }
    return 0;
}