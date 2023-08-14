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

const int maxn = 101;
std::vector<int> a[maxn];
std::vector<int> ans;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        int c, aa;
        read(c);
        for (int j = 1; j <= c; j++) {
            read(aa);
            a[i].push_back(aa);
        }
    }
    
    int x;
    read(x);
    for (int i = 1; i <= n; i++) {
        bool flag = false;
        for (int j : a[i]) {
            if (j == x) { flag = true; break; }
        }
        if (flag) {
            if (ans.empty() || a[ans[0]].size() == a[i].size()) {
                ans.push_back(i);
            } else if (a[ans[0]].size() > a[i].size()) {
                ans.clear();
                ans.push_back(i);
            }
        }
    }

    std::sort(ans.begin(), ans.end());
    writeln(ans.size());
    for (int i : ans) {
        write(i); putchar(' ');
    }
    return 0;
}
