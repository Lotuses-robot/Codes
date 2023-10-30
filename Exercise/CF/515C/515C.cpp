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

const int maxn = 100;
char ch[maxn];
int cnt[maxn];

void add(int i, int x = 1) {
    if (i >= 2) cnt[2] += x;
    if (i >= 3) cnt[3] += x;
    if (i >= 4) cnt[2] += 2 * x;
    if (i >= 5) cnt[5] += x;
    if (i >= 6) cnt[2] += x, cnt[3] += x;
    if (i >= 7) cnt[7] += x;
    if (i >= 8) cnt[2] += 3 * x;
    if (i >= 9) cnt[3] += 2 * x;
}

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    scanf("%s", ch + 1);
    for (int i = 1; i <= n; i++) {
        add(ch[i] - '0');
    }
    for (int i = 9; i >= 2; i--) {
        if (cnt[i] > 0) {
            for (int j = 1; j <= cnt[i]; j++) {
                putchar(i + '0');
            }
            add(i, -cnt[i]);
        }
    }
    puts("");
    return 0;
}