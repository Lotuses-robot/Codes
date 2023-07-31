// Copyright 2023 Lotuses
// sell X >= buy X
// seller >= ai
// 从小到大
// buyer <= bi
// 从大到小
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

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

const int maxn = 400005;
int a[maxn], b[maxn];
struct nd {
    int x, y;
    bool operator < (nd b) const {
        if (x != b.x) return x < b.x;
        else return y < b.y;
    }
};
std::vector<nd> v;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, m;
    read(n, m);
    
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        v.push_back({a[i], 1});
    }
    for (int i = 1; i <= m; i++) {
        read(b[i]);
        v.push_back({b[i] + 1, 2});
    }

    std::sort(v.begin(), v.end());

    int x = 0, y = m;

    int i;
    for (i = 0; i < v.size(); i++) {
        int nxt = i;
        while (v[nxt].x == v[i].x) {
            // writeln(v[nxt].x, v[nxt].y);
            if (v[nxt].y == 1) {
                x++;
            } else {
                y--;
            }
            nxt++;
        }
        nxt--;
        // writeln(x, y);
        if (x >= y) break;
        i = nxt;
    }

    writeln(v[i].x);

    return 0;
}
