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

#define int long long

const int maxn = 1e6 + 10;
int a[maxn], b[maxn];
struct Node {
    int x, y;
}; std::vector<Node> v, nv;
int sum[maxn];

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, up = 0;
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]), up = std::max(up, a[i]);
    for (int i = 1; i <= n; i++) {
        read(b[i]); up = std::max(up, b[i]);
        if (a[i] < b[i]) {
            v.push_back({a[i], b[i]});
        }
    }
    if (v.empty()) {
        writeln(up);
        return 0;
    }
    Node nd = *v.begin();
    for (Node e : v) {
        if (e.x <= nd.y) {
            nd.y = std::max(nd.y, e.y);
        } else {
            nv.push_back(nd);
            nd = e;
        }
    }
    nv.push_back(nd);
    for (int i = 0; i < nv.size(); i++) {
        sum[i + 1] = sum[i] + 2 * (nv[i].y - nv[i].x);
    }
    int ans = up + sum[nv.size()];
    for (int i = 0; i < nv.size(); i++) {
        ans = std::min(ans, up + sum[i] + (up - nv[i].x));
    }
    writeln(ans);
    return 0;
}
