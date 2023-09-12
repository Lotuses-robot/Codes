// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
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

struct Node {
    int x, id;
    bool operator > (Node b) const {
        if (x != b.x) return x > b.x;
        return id > b.id;
    }
};

__gnu_pbds::tree<Node, __gnu_pbds::null_type, std::greater<Node>, __gnu_pbds::rb_tree_tag, 
                __gnu_pbds::tree_order_statistics_node_update> tr;

int tt[1000];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, w, cnt = 0;
    read(n, w);
    for (int i = 1; i <= n; i++) {
        int xx; read(xx);
        tr.insert({xx, ++tt[xx]}); cnt++;
        int rp = std::max(1, cnt * w / 100);
        write(tr.find_by_order(rp - 1) -> x); putchar(' ');
    }
    return 0;
}
