// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

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

std::map<std::pair<int, int>, int> mp;

const int maxn = 3e5 * 5;
int fa[maxn], id, up[maxn], h[maxn];
bool isc[maxn];

int findfa(int u) {
    if (fa[u] == u) return u;
    else return fa[u] = findfa(fa[u]);
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, m;
    read(n, m);
    for (id = 1; id <= n; id++) {
        fa[id] = id;
    }
    
    bool is2 = false;
    for (int i = 1; i <= m; i++) {
        int ch;
        read(ch);
        if (ch == 1) {
            int x, y;
            read(x, y);
            if (x > y) std::swap(x, y);
            if (findfa(x) == findfa(y)) {
                int newpt = id++;
                up[newpt] = fa[newpt] = newpt;
                up[findfa(x)] = newpt;
                fa[findfa(x)] = newpt;
                mp[std::make_pair(x, y)]++;
            } else {
                int newpt = id++;
                up[newpt] = fa[newpt] = newpt;
                up[findfa(x)] = newpt; up[findfa(y)] = newpt;
                fa[findfa(x)] = newpt; fa[findfa(y)] = newpt;
                mp[std::make_pair(x, y)]++;
            }
        } else if (ch == 2) {
            int x;
            read(x);
            int newpt = id++;
            up[newpt] = fa[newpt] = newpt;
            up[findfa(x)] = newpt;
            fa[findfa(x)] = newpt;
            isc[newpt] = true;
            is2 = true;
        } else {
            int x, y, yx, yy;
            read(x, y);
            if (x > y) std::swap(x, y);
            yx = x; yy = y;
            if (!is2) {
                writeln(mp[std::make_pair(yx, yy)]);
                continue;
            }
            if (findfa(x) != findfa(y)) {
                writeln(0);
            } else {
                int rt = findfa(x), ans = 0;
                while (x != y) {
                    if (x > y || y <= n) std::swap(x, y);
                    x = up[x];
                }
                
                while (x != rt) {
                    ans += isc[x];
                    x = up[x];
                }
                ans += isc[x];
                writeln(ans + mp[std::make_pair(yx, yy)]);
            }
        }
    }
    return 0;
}
