// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
// #include <set>
// #include <list>
// #include <queue>
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

const int maxn = 1005;
std::map<int, int> mp;
int a[maxn], b[maxn];
std::vector<int> v;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        memset(b, 0, sizeof(b));
        mp.clear(); v.clear();
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            read(a[i]);
            mp[a[i]]++;
        }
        for (auto p : mp) {
            // writeln(p.first, p.second);
            if (p.second > 1) v.emplace_back(p.first);
        }
        if (v.size() < 2) {
            puts("-1");
        } else {
            int v0 = 1, v1 = 1;
            for (int i = 1; i <= n; i++) {
                if (a[i] == v[0]) {
                    b[i] = v0;
                    if (v0 == 1) v0 = 2;
                } else if (a[i] == v[1]) {
                    b[i] = v1;
                    if (v1 == 1) v1 = 3;
                }
            }
            for (int i = 1; i <= n; i++) {
                if (b[i] == 0) putchar('1'), putchar(' ');
                else write(b[i]), putchar(' ');
            }
            puts("");
        }
    }
    return 0;
}