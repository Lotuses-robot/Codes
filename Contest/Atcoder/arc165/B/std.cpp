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
int a[maxn];
int b[maxn];
int n, k;
std::vector<int> v, ac;

int main() {
    #ifdef LOCAL
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]); b[i] = a[i];
    }
    for (int i = 1; i <= n - k + 1; i++) {
        std::sort(b + i, b + i + k);
        v.clear();
        for (int j = 1; j <= n; j++) {
            v.push_back(b[j]);
        }
        if (ac.empty()) ac = v;
        else ac = std::max(ac, v);
        
        // for (int i : v) {
        //     write(i); putchar(' ');
        // }
        // puts("");

        // for (int i : ac) {
        //     write(i); putchar(' ');
        // }
        // puts("");
        for (int j = 1; j <= n; j++) {
            b[j] = a[j];
        }
    }
    for (int i : ac) {
        write(i); putchar(' ');
    }
    puts("");
    return 0;
}
