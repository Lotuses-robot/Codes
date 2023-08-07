// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

const int maxn = 1e6 + 6;
int a[maxn];
std::vector<std::pair<std::pair<int, int>, int> > q;

__gnu_pbds::tree<int, __gnu_pbds::null_type,
                 std::greater<int>, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update> trr;

int mp[maxn], ans[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, T;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    read(T);

    for (int i = 1; i <= T; i++) {
        int x, y;
        read(x, y);
        q.push_back({{y, x}, i});
    }

    std::sort(q.begin(), q.end());

    int p = 0;
    for (auto e : q) {
        for (p; p <= e.first.first; p++) {
            if (mp[a[p]] != 0) {
                trr.erase(mp[a[p]]);
            }
            mp[a[p]] = p;
            trr.insert(p);
        }
        // for (auto p : trr) {
        //     write(p); putchar(' ');
        // }
        // puts("");
        int od = trr.order_of_key(e.first.second);
        ans[e.second] = (od + (*trr.find_by_order(od) == e.first.second));
    }
    for (int i = 1; i <= T; i++) {
        writeln(ans[i]);
    }
    return 0;
}
