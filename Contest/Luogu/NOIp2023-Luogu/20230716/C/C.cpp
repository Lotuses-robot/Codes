// Copyright 2023 Lotuses
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

const int maxn = 300005;
int n;
int s[maxn], t[maxn], x[maxn], c[maxn];
int maxt = 1;
int ans = 0;

void dfs(int T, int w) {
    if (T > maxt) {
        ans = std::max(ans, w);
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (s[i] <= T && T <= t[i]) {
            dfs(T + x[i], w + c[i]);
        }
    }
    dfs(T + 1, w);
}

int maxw[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);

    bool subtask = 1;

    for (int i = 1; i <= n; i++) {
        read(s[i], t[i], x[i], c[i]);
        maxt = std::max(maxt, t[i]);
        subtask &= (x[i] == 1);
    }

    if (subtask) {
        for (int i = 1; i <= n; i++) {
            maxw[t[i]] = std::max(maxw[t[i]], c[i]);
        }
        int ans = 0;
        for (int i = 1; i <= maxt; i++) {
            ans += maxw[i];
        }
        writeln(ans);
        return 0;
    }

    dfs(1, 0);
    writeln(ans);
    return 0;
}
