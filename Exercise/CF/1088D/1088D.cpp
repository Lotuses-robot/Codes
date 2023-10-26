// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
// #include <list>
// #include <queue>
// #include <stack>
#include <bitset>
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

namespace iter {
    int x;
    int query(int a, int b) {
        printf("? %d %d\n", a, b);
        fflush(stdout);
        scanf("%d", &x);
        return x;
    }
    void ans(int a, int b) {
        printf("! %d %d\n", a, b);
        exit(0);
    }
}

std::bitset<30> a, b;
struct st {
    int s[4];
    st(): s({-2, -2, -2, -2}) {}
    st nxt(int x) const {
        st b;
        b.s[0] = s[x];
        return b;
    }
    std::set<int> equ() const {
        static std::map<int, std::set<int> > p;
        p.clear();
        for (int i = 0; i < 4; i++) {
            p[s[i]].insert(i);
        }
        for (auto px : p) {
            if (px.second.size() > 1) return px.second;
        }
    }
    std::pair<int, int> get() const {
        auto v = equ();
        for (int i = 0; i < 4; i++) {
            if (v.find(i) == v.end()) {
                switch (i) {
                    case 0:
                        if (s[i] == -1) { // a < b
                            return { 0, 1 };
                        } else  {
                            return { 1, 0 };
                        }
                    case 1:
                        if (s[i] == -1) {
                            return { 0, 0 };
                        } else {
                            return { 1, 1 };
                        }
                    case 2:
                        if (s[i] == -1) {
                            return { 1, 1 };
                        } else {
                            return { 0, 0 };
                        }
                    case 3:
                        if (s[i] == -1) {
                            return { 1, 0 };
                        } else {
                            return { 0, 1 };
                        }
                }
            }
        }
    }
} now;

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif

    for (int i = 29; i >= 0; i--) {
        if (now.s[0] == -2) {
            a.set(i, 0);
            b.set(i, 0);
            now.s[0] = iter::query(a.to_ulong(), b.to_ulong());
        }
        if (now.s[1] == -2) {
            a.set(i, 0);
            b.set(i, 1);
            now.s[1] = iter::query(a.to_ulong(), b.to_ulong());
        }
        if (now.s[2] == -2) {
            a.set(i, 1);
            b.set(i, 0);
            now.s[2] = iter::query(a.to_ulong(), b.to_ulong());
        }
        if (now.s[1] == now.s[2]) {
            now.s[3] = -now.s[0];
        } else {
            now.s[3] = now.s[0];
        }
        // writeln(now.s[0], now.s[1], now.s[2], now.s[3]);
        auto p = now.get();
        a.set(i, p.first);
        b.set(i, p.second);
        // writeln(666, p.first, p.second);
        if (i == 0) break;
        int sum = p.first * 2 + p.second;
        now = now.nxt(sum);
    }
    iter::ans(a.to_ulong(), b.to_ulong());
    return 0;
}