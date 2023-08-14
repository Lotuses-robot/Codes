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

const int maxn = 2e5 + 10;
char ch[maxn];
std::vector<char> v[maxn];
int c[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m, x;
    read(n, m);
    scanf("%s", ch + 1);
    for (int i = 1; i <= n; i++) {
        read(x); c[i] = x;
        v[x].push_back(ch[i]);
    }
    for (int i = 1; i <= m; i++) {
        if (!v[i].empty()) {
            char ch = *v[i].rbegin();
            v[i].pop_back();
            v[i].insert(v[i].begin(), ch);
            std::reverse(v[i].begin(), v[i].end());
        }
    }
    for (int i = 1; i <= n; i++) {
        putchar(*v[c[i]].rbegin());
        v[c[i]].pop_back();
    }
    return 0;
}
