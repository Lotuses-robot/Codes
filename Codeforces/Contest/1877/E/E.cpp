// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <queue>
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

const int maxn = 1e6 + 10;
int n, in[maxn], col[maxn], to[maxn];
std::queue<int> q;
std::vector<int> ans;

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        read(to[i]);
        // if (to[i] == i) {
        //     puts("-1");
        //     return 0;
        // }
        in[to[i]]++;
    }
    memset(col, -1, sizeof(col));
    for (int i = 1; i <= n; i++) {
        if (!in[i]) q.push(i), col[i] = 0;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        // writeln(u);
        if (!col[u]) col[to[u]] = 1;
        in[to[u]]--;
        // writeln(to[u], in[to[u]]);
        if (in[to[u]] <= 0) {
            if (!(~col[to[u]])) col[to[u]] = 0;
            q.push(to[u]);
        }
    }
    // if (to[1] == 126990) return 0;
    int rt = -1;
    for (int i = 1; i <= n; i++) {
        // writeln(i, in[i], col[i]);
        if (in[i] > 0) {
            // pt = i;
            rt = -1;
            int u = i;
            while (to[u] != i) {
                if (~col[u]) {
                    rt = u;
                }
                u = to[u];
            }
            if (~col[u]) {
                rt = u;
            }
            if (!(~rt)) {
                col[i] = 0;
                rt = i;
            }

            u = rt;
            in[u]--;
            // writeln(u, to[u]);
            while (to[u] != rt) {
                if (!col[u]) {
                    col[to[u]] = 1;
                } else if (!(~col[to[u]])) {
                    col[to[u]] = 0;
                }
                in[to[u]]--;
                u = to[u];
            }
            if (!col[u] && !col[to[u]]) {
                puts("-1");
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!col[i]) {
            ans.push_back(to[i]);
        }
    }
    writeln(ans.size());
    for (int e : ans) {
        write(e); putchar(' ');
    }
    puts("");
    return 0;
}