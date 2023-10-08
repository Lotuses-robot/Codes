// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 1e6 + 10;
int a[maxn], b[maxn], nxt[maxn];
int n;
struct Node {
    int x, y, val;
    bool operator < (Node b) const {
        return val > b.val;
    }
};
std::priority_queue<Node> q;

void merge() {
    while (!q.empty()) q.pop();
    for (int i = 1; i <= n; i++) {
        q.push({i, 1, a[i] + b[1]});
    }
    for (int i = 1; i <= n; i++) {
        Node tp = q.top(); q.pop();
        nxt[i] = tp.val;
        q.push({tp.x, tp.y + 1, a[tp.x] + b[tp.y + 1]});
    }
    for (int i = 1; i <= n; i++) {
        a[i] = nxt[i];
    }
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) {
            read(a[i]);
        }
        std::sort(a + 1, a + n + 1);
        for (int i = 2; i <= 2; i++) {
            for (int j = 1; j <= n; j++) {
                read(b[j]);
            }
            std::sort(b + 1, b + n + 1);
            merge();
        }
        for (int i = 1; i < n; i++) {
            write(a[i]); putchar(' ');
        }
        writeln(a[n]);
    }
    return 0;
}