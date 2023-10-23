// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <vector>
// #include <map>
// #include <set>
// #include <queue>
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
#define ins(a, b) (G[a].push_back(b))

#define int long long
const int maxn = 1e6 + 10;
int n, ans = 0;
char ch[maxn];
int s[maxn];

tsz main() {
    #ifdef LOCAL
        freopen("data/sheng3.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    scanf("%s", ch + 1); n = strlen(ch + 1);
    for (int i = 1; i < n; i++) {
        if (ch[i] == ch[i + 1]) {
            ans++;
        }
    }
    ans *= n * (n + 1) / 2;
    for (int i = n - 1; i >= 1; i--) {
        s[i] = s[i + 1];
        if (ch[i] != ch[i + 1]) {
            s[i]++;
        } else {
            s[i]--;
        }
        ans += s[i];
    }
    s[1] = 0;
    for (int i = 2; i <= n; i++) {
        s[i] = s[i - 1];
        if (ch[i] != ch[i - 1]) {
            s[i]++;
        } else {
            s[i]--;
        }
        ans += s[i];
    }
    writeln(ans);
    return 0;
}