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

#define int long long

const int maxn = 1e5 + 10;
// std::map<int, int> mp, cnt;
int n, a[maxn], ans[maxn], b[maxn], id[maxn];
int lowbit(int x) { return x & (-x); }
struct ArT {
    int c[maxn];
    void add(int x, int y) {
        while (x <= n) {
            c[x] += y;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x > 0) {
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
} sum, ct;

tsz main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    
    int T, m;
    read(T);
    while (T--) {
        read(n, m);

        memset(sum.c, 0, sizeof(int) * (n + 5));
        memset(ct.c, 0, sizeof(int) * (n + 5));

        for (int i = 1; i <= n; i++) {
            read(a[i]);
            b[i] = i;
        }
        std::sort(b + 1, b + n + 1, [] (int x, int y) {
            if (a[x] == a[y]) return x < y;
            return a[x] < a[y];
        });
        int idx = 0;
        for (int i = 1; i <= n; i++) {
            if (a[b[i]] == a[b[i - 1]]) {
                idx++;
                b[i] = b[i - 1];
            } else {
                id[b[i]] = ++idx;
            }
        }
        for (int i = 1; i <= n; i++) {
            int pos = id[i]; id[i]++;
            int last = m - a[i];
            if (last < 0) {
                ans[i] = i;
            } else {
                int l = 0, r = n;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (sum.query(mid) <= last) {
                        l = mid;
                    } else {
                        r = mid - 1;
                    }
                }
                ans[i] = i - 1 - ct.query(l);
            }
            sum.add(pos, a[i]);
            ct.add(pos, 1);
        }
        for (int i = 1; i <= n; i++) {
            write(ans[i]); putchar(' ');
        }
        puts("");
    }
    return 0;
}