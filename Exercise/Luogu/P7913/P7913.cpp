// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

#define int long long

const int maxn = 2e6 + 10;
int n, m[2];
struct Line {
    int l, r;
    bool operator < (const Line b) const {
        return l < b.l;
    }
} pl[2][maxn];
struct Int {
    int x;
    bool operator < (const Int b) const {
        return x > b.x;
    }
};
std::priority_queue<Int> q;
std::map<int, int> mp;
struct Event {
    int id, st;
} ev[2][maxn];
int level[2][maxn];
int ans[2][maxn];

void input(int id) {
    int idx = 0;
    while (!q.empty()) q.pop();
    mp.clear();
    for (int i = 1; i <= m[id]; i++) {
        read(pl[id][i].l, pl[id][i].r);
        q.push({pl[id][i].l});
        q.push({pl[id][i].r});
    }
    while (!q.empty()) {
        mp[q.top().x] = ++idx; q.pop();
    }
    for (int i = 1; i <= m[id]; i++) {
        pl[id][i].l = mp[pl[id][i].l];
        pl[id][i].r = mp[pl[id][i].r];
        ev[id][pl[id][i].l] = {i, 1};
        ev[id][pl[id][i].r] = {i, 0};
    }
    std::sort(pl[id] + 1, pl[id] + m[id] + 1);
}

void init(int id) {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= m[id]; i++) {
        q.push({i});
    }
    for (int i = 1; i <= 2 * m[id]; i++) {
        if (ev[id][i].st) {
            level[id][ev[id][i].id] = q.top().x;
            ans[id][q.top().x]++;
            q.pop();
        } else {
            q.push({level[id][ev[id][i].id]});
        }
    }
    for (int i = 1; i <= std::max(m[id], n); i++) {
        ans[id][i] += ans[id][i - 1];
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m[0], m[1]);
    input(0); input(1);
    init(0); init(1);
    int x = 0;
    for (int i = 0; i <= n; i++) {
        x = std::max(x, ans[0][i] + ans[1][n - i]);
    }
    writeln(x);
    return 0;
}
