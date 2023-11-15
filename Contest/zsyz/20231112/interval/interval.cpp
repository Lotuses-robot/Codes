// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <list>
#include <queue>
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

const int Max = 2e5 + 10;

int n, a[Max], s[Max];
int tot, inf = 1e18, b[Max];

struct ST {
    int f1[Max << 1][20], f2[Max << 1][20], Lg[Max << 1];

    void init() {
        Lg[1] = 0;
        for (int i = 2; i <= Max - 5; i++)
            Lg[i] = Lg[i / 2] + 1;
        for (int i = 1; i <= n; i++)
            f1[i][0] = f2[i][0] = a[i];
        for (int k = 1; k <= 18; k++) {
            for (int i = 1; i <= n; i++) {
                f1[i][k] = std::max(f1[i][k - 1], f1[i + (1 << k - 1)][k - 1]);
                f2[i][k] = std::min(f2[i][k - 1], f2[i + (1 << k - 1)][k - 1]);
            }
        }
    }

    std::pair<int, int> query(int l, int r) {
        if (l == r)
            return {f1[l][0], f2[l][0]};
        int lg = Lg[r - l + 1];
        return { std::max(f1[l][lg], f1[r - (1 << lg) + 1][lg]),
                 std::min(f2[l][lg], f2[r - (1 << lg) + 1][lg]) };
    }

} st;

struct node {
    int l, r;
};

std::queue<node> q;

int solve1() {
    int ans = 0;
    q.push({1, n});
    while (!q.empty()) {
        node x = q.front();
        q.pop();
        int pos = b[st.query(x.l, x.r).first];
        ans += x.r - x.l;
        if (pos != x.l)
            q.push({x.l, pos - 1});
        if (pos != x.r)
            q.push({pos + 1, x.r});
    }
    q.push({1, n});
    while (!q.empty()) {
        node x = q.front();
        q.pop();
        int pos = b[st.query(x.l, x.r).second];
        ans += x.r - x.l;
        if (pos != x.l)
            q.push({x.l, pos - 1});
        if (pos != x.r)
            q.push({pos + 1, x.r});
    }
    return ans;
}

int solve(int i, int k) {
    int l = 1, r = tot, x = tot;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (k == 1) {
            if (st.query(b[s[mid]], b[i]).first > i)
                l = mid + 1;
            else {
                x = mid;
                r = mid - 1;
            }
        } else {
            if (st.query(b[s[mid]], b[i]).second < i)
                l = mid + 1;
            else {
                x = mid;
                r = mid - 1;
            }
        }
    }
    return x;
}

int solve2() {
    int ans = 0;
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (tot && s[tot] < a[i])
            ans += tot - solve(a[i], 1) + 1;
        while (tot && s[tot] > a[i])
            tot--;
        s[++tot] = a[i];
    }
    tot = 0;
    for (int i = 1; i <= n; i++) {
        if (tot && s[tot] > a[i])
            ans += tot - solve(a[i], 2) + 1;
        while (tot && s[tot] < a[i])
            tot--;
        s[++tot] = a[i];
    }
    return ans;
}

tsz main() {
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[a[i]] = i;
    }
    st.init();
    printf("%lld\n", n * (n - 1) / 2 - solve1() + solve2());
    return 0;
}