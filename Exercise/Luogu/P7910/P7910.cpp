// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

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
#define debug(arg, args...) { printf("d <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 8005;
int a[maxn];
struct Int {
    int fst, snd;
    bool operator < (const Int &b) const {
        if (fst != b.fst) return fst < b.fst;
        return snd < b.snd;
    }
};
__gnu_pbds::tree<Int, __gnu_pbds::null_type, std::less<Int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, q;
    read(n, q);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        tr.insert({a[i], i});
    }

    while (q--) {
        int ch, x;
        read(ch, x);
        if (ch == 1) {
            int y;
            read(y);
            tr.erase({a[x], x});
            a[x] = y;
            tr.insert({a[x], x});
        } else {
            writeln(tr.order_of_key({a[x], x}) + 1);
        }
    }
    return 0;
}
