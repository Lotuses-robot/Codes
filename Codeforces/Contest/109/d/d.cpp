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

const int maxn = 1e5 + 10;
int n;
int a[maxn], sid[maxn];

bool check(int x) {
    do {
        if (x % 10 != 4 && x % 10 != 7) return false;
    } while (x /= 10);
    return true;
}

std::vector<std::pair<int, int> > v;

tsz main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    int pos = -1;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]); sid[i] = i;
        if (check(a[i])) pos = i;
    }
    bool flag = true;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i + 1]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        puts("0");
        return 0;
    }
    if (pos == -1) {
        puts("-1");
        return 0;
    }
    std::sort(sid + 1, sid + n + 1, [] (int x, int y) {
        return a[x] < a[y];
    });

    for (int i = 1; i <= n; i++) {
        a[sid[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] == i) continue;
        if (pos != i) {
            v.push_back({pos, i});
            std::swap(sid[a[pos]], sid[a[i]]);
            std::swap(a[pos], a[i]);
            pos = i;
            // puts("i");
        }
        int nxt = sid[i];
        if (nxt == pos) {
            continue;
        }
        v.push_back({nxt, pos});
        std::swap(sid[a[nxt]], sid[a[pos]]);
        std::swap(a[nxt], a[pos]);
        pos = nxt;
    }
    // writeln(a[pos]);
    while (pos < a[pos]) {
        v.push_back({pos, pos + 1});
        std::swap(sid[a[pos + 1]], sid[a[pos]]);
        std::swap(a[pos], a[pos + 1]);
        pos++;
    }

    while (pos > a[pos]) {
        puts("?");
        v.push_back({pos, pos - 1});
        std::swap(sid[a[pos - 1]], sid[a[pos]]);
        std::swap(a[pos], a[pos - 1]);
        pos--;
    }

    writeln(v.size());
    for (auto p : v) {
        writeln(p.first, p.second);
    }
    return 0;
}