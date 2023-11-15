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

std::map<int, int[2]> mp;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        mp.clear();
        int n, m, r, c, p = 0;
        read(n, m);
        for (int i = 1; i <= m; i++) {
            read(r, c);
            mp[c][r - 1] = true;
        }
        bool failed = false;
        int st[2] = {0, 0};
        for (auto x : mp) {
            if (p >= x.first) continue;
            int dis = x.first - p - 1;
            if (dis & 1) std::swap(st[0], st[1]);
            p = x.first - 1;
            if (st[0] || st[1]) {
                if (x.second[0] && x.second[1]) {
                    failed = true;
                    break;
                }
                if (x.second[0] && st[0] || x.second[1] && st[1]) {
                    st[0] = st[1] = 0;
                } else {
                    failed = true;
                    break;
                }
                p++;
            } else {
                if (x.second[0] && x.second[1]) {
                    p++;
                    continue;
                }
                if (!mp.count(x.first + 1)) {
                    p += 2;
                    if (x.second[0]) {
                        st[1] = 1;
                    } else {
                        st[0] = 1;
                    }
                } else {
                    if (mp[x.first + 1][0] && x.second[0] && !mp[x.first + 1][1] || mp[x.first + 1][1] && x.second[1] && !mp[x.first + 1][0]) {
                        p += 2;
                        st[0] = st[1] = 0;
                    } else {
                        failed = true;
                        break;
                    }
                }
            }
        }
        if (failed || st[0] || st[1]) puts("NO");
        else puts("YES");
    }
    return 0;
}