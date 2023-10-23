// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
#include <queue>
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
#define ins(a, b) (G[a].push_back(b))
#define fl(x) ((x) - d + 1)

#define int long long

const int maxn = 2e6 + 10;
int w[maxn], s[maxn];
struct Node {
    int val, id;
}; std::deque<Node> q;

void push(int val, int id) {
    while (!q.empty() && q.back().val < val) q.pop_back();
    q.push_back({val, id});
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, p, d;
    read(n, p, d);
    for (int i = 1; i <= n; i++) {
        read(w[i]);
        s[i] = s[i - 1] + w[i];
    }

    int ans = d;
    int l = 1, r = 1 + d - 1, ps = s[r] - s[l - 1]; push(ps, l);
    while (l <= n - d + 1) {
        while (r < n && ps + w[r + 1] - std::max(q.front().val, s[r + 1] - s[fl(r + 1) - 1]) <= p) {
            r++;
            push(s[r] - s[fl(r) - 1], fl(r));
            ps += w[r];
            ans = std::max(ans, r - l + 1);
        }

        ps -= w[l];
        l++;
        while (!q.empty() && q.front().id < l) q.pop_front();
    }
    writeln(ans);
    return 0;
}