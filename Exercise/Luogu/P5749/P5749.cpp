// Copyright 2023 Lotuses
#define tsz signed
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
const int maxn = 3e5 + 10;
std::vector<int> vp[maxn];
int n, a[maxn], t[maxn << 2], ans = 0;
bool vis[maxn];

int lowbit(int x) { return x & (-x); }

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i))
        t[i] += y;
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += t[i];
    return res;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    read(n);
    n <<= 1;
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        vp[a[i] + n].push_back(i);
        add(i, 1);
    }
    for (int i = n; i >= 1; i--) {
        if (vis[i])
            continue;
        vis[i] = 1;
        vp[a[i] + n].pop_back();
        int res = vp[n - a[i]].back();
        vp[n - a[i]].pop_back();
        vis[res] = 1;
        ans =
            ans + (long long)(query(i - 1) - query(res)) + ((a[i] < 0) ? 1 : 0);
        add(res, -1);
    }
    writeln(ans);
    return 0;
}
