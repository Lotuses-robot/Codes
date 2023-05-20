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

#define int long long
const int maxn = 800005;
const int INT_MAX = 1e18;

int n, q, s;
struct segment {
    struct Int {
        int val, id;
        bool operator < (const Int b) const {
            return val < b.val;
        }
    };
    struct Node {
        int l, r, lc, rc;
        Int lazy, minn; bool del;
    };

    
    Node tn[maxn];
    int cnt;
    void init() {
        cnt = 0;
    }
    int build(int l, int r) {
        int id = ++cnt;
        tn[id].l = l; tn[id].r = r;
        tn[id].lazy = tn[id].minn = { INT_MAX, -1 };
        if (l == r) tn[id].lc = tn[id].rc = -1, tn[id].minn = { INT_MAX, l };
        else {
            int mid = (l + r) >> 1;
            tn[id].lc = build(l, mid);
            tn[id].rc = build(mid + 1, r);
            tn[id].minn = std::min(tn[tn[id].lc].minn, tn[tn[id].rc].minn);
        }
        return id;
    }
    void push_lazy(int cur) {
        if (tn[cur].del) return;
        if (tn[cur].lazy.val != INT_MAX) {
            int lc = tn[cur].lc, rc = tn[cur].rc;
            if (!tn[lc].del) {
                tn[lc].lazy = std::min(tn[lc].lazy, tn[cur].lazy);
                tn[lc].minn.val = std::min(tn[lc].minn.val, tn[cur].lazy.val);
            }
            if (!tn[rc].del) {
                tn[rc].lazy = std::min(tn[rc].lazy, tn[cur].lazy);
                tn[rc].minn.val = std::min(tn[rc].minn.val, tn[cur].lazy.val);
            }
            tn[cur].lazy.val = INT_MAX;
        }
    }
    void update(int cur, int l, int r, int val, bool d) {
        if (tn[cur].del) return;
        if (l == tn[cur].l && r == tn[cur].r) {
            if (d) tn[cur].del = true, tn[cur].minn = { INT_MAX + 100, -2 };
            else {
                tn[cur].minn.val = std::min(val, tn[cur].minn.val);
                tn[cur].lazy.val = std::min(val, tn[cur].lazy.val);
            }
        } else {
            push_lazy(cur);
            int mid = (tn[cur].l + tn[cur].r) >> 1;
            if (r <= mid) update(tn[cur].lc, l, r, val, d);
            else if (l >= mid + 1) update(tn[cur].rc, l, r, val, d);
            else {
                update(tn[cur].lc, l, mid, val, d);
                update(tn[cur].rc, mid + 1, r, val, d);
            }
            tn[cur].del = tn[tn[cur].lc].del & tn[tn[cur].rc].del;
            tn[cur].minn = tn[cur].del ? (Int){ INT_MAX + 100, -2 } : std::min(tn[tn[cur].lc].minn, tn[tn[cur].rc].minn);
        }
    }
    Int query(int cur) {
        return tn[cur].minn;
    }
};
segment sg;

struct seg2 {
    struct Node {
        int l, r, lc, rc;
        std::vector<std::pair<int, segment::Int> > v;
    };
    Node tn[maxn];
    bool vis[maxn * 4];

    int cnt, ed;
    void init() {
        cnt = ed = 0;
        memset(vis, 0, sizeof(vis));
    }

    int build(int l, int r) {
        int id = ++cnt;
        tn[id].l = l; tn[id].r = r;
        if (l == r) tn[id].lc = tn[id].rc = -1;
        else {
            int mid = (l + r) >> 1;
            tn[id].lc = build(l, mid);
            tn[id].rc = build(mid + 1, r);
        }
        return id;
    }

    void update(int cur, int l, int r, int val, int w) {
        debug(cur, l, tn[cur].l, r, tn[cur].r);
        if (l == tn[cur].l && r == tn[cur].r) {
            tn[cur].v.push_back({std::make_pair(val, segment::Int({w, ++ed}))});
        } else {
            int mid = (tn[cur].l + tn[cur].r) >> 1;
            if (r <= mid) update(tn[cur].lc, l, r, val, w);
            else if (l >= mid + 1) update(tn[cur].rc, l, r, val, w);
            else {
                update(tn[cur].lc, l, mid, val, w);
                update(tn[cur].rc, mid + 1, r, val, w);
            }
        }
    }

    void query(int cur, int p, int val) {
        for (auto q : tn[cur].v) {
            if (vis[q.second.id]) continue;
            sg.update(1, q.first, q.first, val + q.second.val, 0);
            vis[q.second.id] = true;
        }
        tn[cur].v.clear();
        if (tn[cur].l == p && tn[cur].r == p) return;
        int mid = (tn[cur].l + tn[cur].r) >> 1;
        if (p <= mid) query(tn[cur].lc, p, val);
        else query(tn[cur].rc, p, val);
    }
};
seg2 sg2;

struct Edge {
    int u, vl, vr, w;
};
std::vector<Edge> G[maxn];

void insert(int u, int vl, int vr, int w) {
    G[u].push_back({u, vl, vr, w});
}

int dep[maxn];
void dijkstra() {
    memset(dep, -1, sizeof(dep));
    sg.init();
    sg.build(1, n);
    sg.update(1, s, s, 0, 0);
    int cnt = 0;
    while (true) {
        segment::Int u = sg.query(1);
        debug(u.id, u.val);
        if (u.id < 0) break;
        dep[u.id] = u.val;
        cnt++;
        for (Edge e : G[u.id]) {
            debug(e.vl, e.vr, u.val + e.w);
            sg.update(1, e.vl, e.vr, u.val + e.w, 0);
        }
        // 1 -> 1, 1 -> n
        sg2.query(1, u.id, u.val);
        sg.update(1, u.id, u.id, INT_MAX, 1);
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif

    read(n, q, s);

    sg2.init();
    sg2.build(1, n);
    for (int i = 1; i <= q; i++) {
        static int op, a, b, c, d;
        read(op, a, b, c);
        debug(i, op);
        if (op == 1) {
            insert(a, b, b, c);
        } else if (op == 2) {
            read(d);
            insert(a, b, c, d);
        } else if (op == 3) {
            read(d);
            sg2.update(1, b, c, a, d);
        }
    }

    dijkstra();

    for (int i = 1; i <= n; i++) {
        write(dep[i] == INT_MAX ? -1 : dep[i]); putchar(' ');
    }

    return 0;

}