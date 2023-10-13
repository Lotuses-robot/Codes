// Copyright 2023 Lotuses
#define tsz signed
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
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

const int maxn = 4e5 + 10;
int a[maxn];

struct Trie {
    struct Node {
        int id;
        int cnt;
        int ch[2];
    } nd[maxn << 4];
    int cnt;
    
    int b() {
        int id = ++cnt;
        nd[id].cnt = 0;
        nd[id].ch[0] = nd[id].ch[1] = -1;
        return id;
    }

    void init() {
        cnt = 0;
        b();
    }

    void add(int x, int id, int c = 2) {
        int p = 0;
        if (c == 2) c = 1, p = 1;
        int u = 1;
        nd[u].cnt += c;
        for (int i = 29; i >= 0; i--) {
            int mv = (x & (1 << i)) > 0;
            if (nd[u].ch[mv] < 0) {
                nd[u].ch[mv] = b();
            }
            u = nd[u].ch[mv];
            nd[u].cnt += c;
        }
        nd[u].id = id;
    }

    int query(int x) {
        int u = 1;
        for (int i = 29; i >= 0; i--) {
            int mv = (x & (1 << i)) > 0;
            if (nd[u].ch[mv] > 0 && nd[nd[u].ch[mv]].cnt > 0) {
                u = nd[u].ch[mv];
                if (mv) x ^= (1 << i);
            } else if (nd[u].ch[mv ^ 1] > 0 && nd[nd[u].ch[mv ^ 1]].cnt > 0) {
                u = nd[u].ch[mv ^ 1];
                if (!mv) x ^= (1 << i);
            } else {
                return -1;
            }
        }
        return nd[u].id;
    }
} t;

int fa[maxn];
int findfa(int u) {
    if (fa[u] == u) return u;
    return fa[u] = findfa(fa[u]);
}

std::vector<int> mem[maxn];
struct Node {
    int fa;
    bool operator < (const Node &b) const {
        return mem[fa].size() > mem[b.fa].size();
    }
};
std::priority_queue<Node> q;

struct Edge {
    int u, v;
    int calc() const {
        if (u == -1 || v == -1) return 1 << 30;
        return a[u] ^ a[v];
    }
    bool operator < (Edge b) const {
        return calc() < b.calc();
    }
};

tsz main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    t.init();
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    std::sort(a + 1, a + n + 1);
    n = std::unique(a + 1, a + 1 + n) - (a + 1);
    for (int i = 1; i <= n; i++) {
        t.add(a[i], i);
        mem[i].push_back(i);
        q.push({i});
        fa[i] = i;
    }

    long long ans = 0; Node p;
    int cnt = 0;
    while (q.size() > 1) {
        p = q.top(); q.pop();
        if (p.fa != findfa(mem[p.fa][0])) continue;
        for (int u : mem[p.fa]) {
            t.add(a[u], u, -1);
        }
        
        Edge e = { -1, -1 };
        for (int u : mem[p.fa]) {
            int v = t.query(a[u]);
            e = std::min(e, {u, v});
        }

        for (int u : mem[p.fa]) {
            t.add(a[u], u, 1);
        }
        // writeln(e.u, e.v, e.calc());
        // cnt++;
        // if (cnt % 10000 == 0 || cnt > 1.9e5) writeln(cnt);

        ans += e.calc();
        int fv = findfa(e.v), fu = findfa(e.u);
        for (int u : mem[fv]) {
            mem[fu].push_back(u);
        }
        mem[fv].clear();
        fa[fv] = fu;
        q.push({fu});
    }
    writeln(ans);
    return 0;
}