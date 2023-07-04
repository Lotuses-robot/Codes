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

struct Trie {
    struct Node {
        int cntv, cnte;
        int s[2];
    };
    Node nd[500005];
    int cnt;
    void init() {
        cnt = 1;
    }
    void insert(std::vector<int> &v) {
        int cur = 1;
        for (int i = 0; i < v.size(); i++) {
            if (nd[cur].s[v[i]]) {
                cur = nd[cur].s[v[i]];
            } else {
                ++cnt;
                nd[cur].s[v[i]] = cnt;
                cur = cnt;
            }
            nd[cur].cntv++;
        }
        nd[cur].cnte++;
    }
    int query(std::vector<int> &v) {f
        for (int i = 0; i < v.size(); i++) {
            ans += nd[cur].cnte;
            if (nd[cur].s[v[i]]) {f
                cur = nd[cur].s[v[i]];ff
            } else {
                return ans;
            }
        }
        return ans + nd[cur].cntv;
    }
} tr;

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    tr.init();
    std::vector<int> t;
    int m, n, q, tt;
    read(m, n);
    for (int i = 1; i <= m; i++) {
        t.clear();
        read(q);
        for (int j = 1; j <= q; j++) {
            read(tt);
            t.push_back(tt);
        }
        tr.insert(t);
    }
    for (int i = 1; i <= n; i++) {
        t.clear();
        read(q);
        for (int j = 1; j <= q; j++) {
            read(tt);
            t.push_back(tt);
        }
        writeln(tr.query(t));
    }
    return 0;
}
