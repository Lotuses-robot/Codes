// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

int cs[1000006];

struct Trie {
    struct Node {
        int lc, rc;
        int vis;
    };

    Node nd[1 << 25];
    int cnt = 0;

    int init(int h) {
        if (h >= 23) {
            return -1;
        }
        int id = ++cnt;
        nd[id].vis = 0;
        nd[id].lc = init(h + 1);
        nd[id].rc = init(h + 1);
        return id;
    }

    int num[30];
    
    void invert(int x) {
        int i = 21;
        while (i >= 0) {
            num[i] = x & 1;
            i--; x >>= 1;
        }
    }

    void insert() {
        int pt = 1, i = 0;
        while (i < 22) {
            if (num[i] == 0) {
                pt = nd[pt].lc;
            } else {
                pt = nd[pt].rc;
            }
            nd[pt].vis++; i++;
        }
    }

    int query() {
        int pt = 1, i = 0, p = 1, ans = 0;
        while (i < 22) {
            if (num[i] == 0) {
                if (nd[nd[p].rc].vis) {
                    p = nd[p].rc;
                    ans++;
                } else {
                    p = nd[p].lc;
                }
                pt = nd[pt].lc;
            } else {
                if (nd[nd[p].lc].vis) {
                    p = nd[p].lc;
                    ans++;
                } else {
                    p = nd[p].rc;
                }
                pt = nd[pt].rc;
            }
            ans <<= 1; i++;
        }
        return ans >> 1;
    }
} tr;

int main() {
    #ifdef LOCAL
        freopen("data/2.in", "r", stdin);
        freopen("data/2.out", "w", stdout);
    #endif
    
    int n, c;
    tr.init(0);
    read(n);
    for (int i = 1; i <= n; i++) {
        read(c);
        cs[i] = cs[i - 1] ^ c;
        tr.invert(cs[i]);
        tr.insert();
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        tr.invert(cs[i]);
        ans = std::max(tr.query(), ans);
    }
    writeln(ans);
    return 0;
}
