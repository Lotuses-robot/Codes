// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

const int maxn = 2e5 + 5;
int a[maxn];
int f[maxn];

std::deque<std::pair<int, int> > q;

void push(int id) {
    while (!q.empty() && q.front().first <= f[id]) q.pop_front();
    q.push_back(std::make_pair(f[id], id));
}

int query(int id) {
    while (!q.empty() && q.front().second <= id) q.pop_front();
    if (q.empty()) return -1145141919;
    return q.front().first;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    memset(f, -63, sizeof(f));
    f[0] = 0;
    int n, l, r, ans = -1145141919;
    read(n, l, r);
    for (int i = 0; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        // for (int j = std::max(0, i - r); j <= i - l; j++) {
        //     f[i] = std::max(f[i], f[j] + a[i]);
        // }
        if (i - l >= 0) {
            push(i - l);
        }
        int fmax = query(std::max(0, i - r) - 1);
        f[i] = fmax + a[i];
        // writeln(i, f[i]);
        if (i > n - r) ans = std::max(ans, f[i]);
    }
    printf("%d\n", ans);
    return 0;
}
