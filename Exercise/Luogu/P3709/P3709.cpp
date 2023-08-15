// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

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

const int maxn = 2e5 + 10;
int a[maxn], BLOCK_SIZE;
struct Query {
    int l, r, id;
} q[maxn];

bool cmp(Query q1, Query q2) {
    int k1 = q1.l / BLOCK_SIZE, k2 = q2.l / BLOCK_SIZE;
    if (k1 != k2) return k1 < k2;
    return q1.r < q2.r;
}

int max = 0;
int mp[maxn];
int cnt[maxn];
void move(int p, int c) {
    cnt[mp[a[p]]]--;
    if (mp[a[p]] == max && cnt[mp[a[p]]] == 0) {
        max--;
    }
    mp[a[p]] += c;
    cnt[mp[a[p]]]++;
    max = std::max(max, mp[a[p]]);
}

int ans[maxn];

struct Node {
    int x, id;
    bool operator < (Node b) const {
        return x < b.x;
    }
} ax[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    BLOCK_SIZE = int(ceil(pow(n, 0.5)));

    for (int i = 1; i <= n; i++) read(a[i]), ax[i].x = a[i], ax[i].id = i;
    std::sort(ax + 1, ax + n + 1);
    int cnt = 1; a[ax[1].id] = cnt;
    for (int i = 2; i <= n; i++) {
        if (ax[i].x != ax[i - 1].x) {
            cnt++;
        }
        a[ax[i].id] = cnt;
    }
    for (int i = 1; i <= m; i++) {
        read(q[i].l, q[i].r); q[i].id = i;
    }

    std::sort(q + 1, q + m + 1, cmp);

    int l = 1, r = 0;
    move(++r, 1);
    for (int i = 1; i <= m; i++) {
        const Query &t = q[i];
        while (l > t.l) move(--l, 1);
        while (r < t.r) move(++r, 1);
        while (l < t.l) move(l++, -1);
        while (r > t.r) move(r--, -1);
        ans[t.id] = max;
    }
    for (int i = 1; i <= m; i++) {
        writeln(-ans[i]);
    }
    return 0;
}
