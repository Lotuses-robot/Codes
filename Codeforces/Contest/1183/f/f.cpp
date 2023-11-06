// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
#include <set>
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

int n;
std::set<int> s, s1;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, x, ans, mx, mx1, ans1;
    read(T);
    while (T--) {
        s.clear(); s1.clear();
        read(n);
        for (int i = 1; i <= n; i++) {
            read(x);
            s.insert(x);
        }
        // 1
        mx = ans = *s.rbegin();
        // 2
        for (int x : s) {
            if (mx % x) {
                ans = std::max(ans, mx + x);
            }
        }
        // 3
        if (mx % 2 == 0 && mx % 3 == 0 && mx % 5 == 0 &&
            s.find(mx / 2) != s.end() && s.find(mx / 3) != s.end() && s.find(mx / 5) != s.end()) {
            ans = std::max(ans, mx / 30 * 31);
        }
        for (int x : s) {
            if (mx % x) {
                s1.insert(x);
            }
        }
        if (s1.empty()) goto end;
        ans1 = mx1 = *s1.rbegin();
        for (int x : s1) {
            if (mx1 % x) {
                ans1 = std::max(ans1, x + mx1);
            }
        }
        ans = std::max(ans, mx + ans1);
        end: writeln(ans);
    }
    return 0;
}