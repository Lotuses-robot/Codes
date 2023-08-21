// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
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

const int maxn = 100005;
char ch[maxn], len;
int f[20][20];

int dfs(int u, int lst, bool full, bool qd) {
    if (u == len + 1) return 1;
    if (!qd && !full && f[u][lst]) {
        return f[u][lst];
    }
    int p, ans = 0, maxx = (full ? ch[u] - '0' : 9);
    for (int i = 0; i <= maxx; i++) {
        if (std::abs(i - lst) < 2) continue;
        if (qd && i == 0) p = -666;
        else p = i;
        ans += dfs(u + 1, p, full && (i == maxx), p == -666);
    }
    if (!full && !qd) return f[u][lst] = ans;
    return ans;
}

int solve(int e) {
    sprintf(ch + 1, "%d", e);
    len = strlen(ch + 1);
    memset(f, 0, sizeof(f));
    // writeln(dfs(len, -1, true, true));
    return dfs(1, -666, 1, 1);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int a, b;
    read(a, b);
    writeln(solve(b) - solve(a - 1));
    return 0;
}
