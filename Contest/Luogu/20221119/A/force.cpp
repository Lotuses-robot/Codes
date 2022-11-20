// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

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

struct Node {
    int x, y;
    bool operator < (Node b) const {
        return y < b.y;
    }
};
std::vector<Node> v[500005];
int T, n;

int find(int x, int y) {
    int cnt = 0;
    for (Node e : v[x]) {
        if (e.y < y) cnt++;
        else break;
    }
    return cnt;
}

int dfs(int level, int y, int upp, int nowans, bool lastgo) {
    if (level > n) {
        if (upp != n / 2) return 1145141919;
        return nowans + lastgo + (y != n);
    }
    if (y == n) {
        return dfs(level + 1, y, upp + find(level, y), nowans + lastgo, false);
    }
    int ans = 1145141919; int qry = find(level, y);
    ans = std::min(ans, dfs(level + 1, y, upp + qry, nowans + lastgo, false));
    for (int cy = y + 1; cy <= n; cy++) {
        ans = std::min(ans, dfs(level + 1, cy, upp + qry, nowans + (level != 0) + lastgo, true));
        qry = find(level, cy + 1);
    }
    // for (int i = 0; i < level; i++) putchar(' ');
    // printf("%d %d %d\n", level, y, ans);
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    read(T);
    while (T--) {
        for (int i = 0; i <= n; i++) v[i].clear();
        read(n);
        for (int i = 0; i < n; i++) {
            static int x, y;
            read(x, y);
            v[x].push_back({x, y});
        }
        for (int i = 1; i <= n; i++) {
            std::sort(v[i].begin(), v[i].end());
        }
        n++;
        printf("%d\n", dfs(0, 0, 0, 0, false));
    }
}
