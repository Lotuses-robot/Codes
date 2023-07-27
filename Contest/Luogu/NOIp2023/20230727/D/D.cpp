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

std::vector<int> v;

bool check() {
    bool isf = false;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] < v[i - 1]) {
            if (isf) {
                return false;
            }
        } else if (v[i] > v[i - 1]) {
            if (!isf) {
                isf = true;
            }
        }
    }
    return true;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        v.push_back(i); v.push_back(i);
    }

    int ans = 0;
    std::vector<int> q = v;
    ans += check();
    next_permutation(v.begin(), v.end());
    while (q != v) {
        ans += check();
        next_permutation(v.begin(), v.end());
    }
    writeln(ans);
    return 0;
}
