// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
#include <list>
// #include <queue>
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

const int maxn = 1e6 + 10;
std::list<int> q[maxn];
int a, x;
char ch[maxn];

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        scanf("%s", ch);
        read(a);
        if (ch[0] == 'p') {
            if (ch[1] == 'u') {
                read(x);
                if (ch[5] == 'b') {
                    q[a].emplace_back(x);
                } else {
                    q[a].emplace_front(x);
                }
            } else {
                if (!q[a].empty()) {
                    if (ch[4] == 'b') {
                        q[a].pop_back();
                    } else {
                        q[a].pop_front();
                    }
                }
            }
        } else if (ch[0] == 's') {
            writeln(q[a].size());
        } else if (ch[0] == 'b') {
            if (!q[a].empty()) {
                writeln(q[a].back());
            }
        } else if (ch[0] == 'f') {
            if (!q[a].empty()) {
                writeln(q[a].front());
            }
        }
    }
}