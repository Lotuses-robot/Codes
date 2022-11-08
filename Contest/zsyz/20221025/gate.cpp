// Copyright 2022 Lotuses

// 1. 无论如何，首都的传送门都只能指向自身
// prove:
// 对于每一个点 x 都要保证 (d_a[1] + 1) | (k - d_x)
// 特别的，对于点 1，要保证 (d_a[1] + 1) | k
// 如果不指向自身，指向 a[1] => q(d_a[1] + 1) = k
// 对于 x = a[1] 的特殊情况，带入 k 得到了这样
// (d_a[1] + 1) | (q(d_a[1] + 1) - d_a[1])
// 后面的第一坨东西必然整除，
// 后面整一坨式子 >= 1
// 单独考虑 (d_a[1] + 1) | -d_a[1]
// 前面乘 p
// 也就是 p(d_a[1] + 1) = q(d_a[1] + 1) - d_a[1]
// (p - q)(d_a[1] + 1) - d_a[1] = 0
// (p - q - 1)d_a[1] + p - q = 0
// 其中由于整除 q > p （等于时不成立）
// 所以 p - q - 1 < -1, p - q < 0, 而 d_a[1] > 0
// 这一坨东西仅当 p = q 时成立
// 但是只有 d_a[1] = 0 时 p = q 才能让
// (d_a[1] + 1) | (q(d_a[1] + 1) - d_a[1]) 这一坨都成立
// 所以 p != q 时必然不成立
// 而刚好当 p = q 且 d_a[1] = 0 时成立
// 证毕

#include <cstdio>
#include <cstring>
#include <hash_map>
#include <queue>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

std::map<int, int> f[500005];
int n, k;
int fa[500005];
struct Edge {
    int from, to;
};
std::vector<Edge> G[500005];
int cnt[500005];

#define inff 114514191

int dfs(int pt, int lev) {
    if (lev == 0) {
        int ans = 0;
        for (Edge e : G[pt]) {
            ans += dfs(e.to, lev + 1);
        }
        return ans;
    }

    // printf("%d %d %d\n", pt, lev, ++cnt[pt]);

    if (f[pt][lev] != 0) {
        // puts("YES");
        return f[pt][lev];
    }

    int ans = 1;
    for (Edge e : G[pt]) {
        ans += dfs(e.to, 2);
    }
    if (lev <= k) {
        int ans2 = 0;
        for (Edge e : G[pt]) {
            ans2 += dfs(e.to, lev + 1);
        }
        // if (ans2 >= ans) {
        //     printf("debug %d\n", pt);
        // }
        ans = std::min(ans, ans2);
    }
    f[pt][lev] = ans;
    return ans;
}

int main() {
    // freopen("gate/32.in", "r", stdin);
    // freopen("gate.out", "w", stdout);
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(fa[i]);
        if (i != 1) {
            G[fa[i]].push_back({fa[i], i});
        }
        // printf("%d %d\n", i, n);
    }


    int ans = dfs(1, 0);
    printf("%d\n", ans + (fa[1] != 1));
    return 0;
}
