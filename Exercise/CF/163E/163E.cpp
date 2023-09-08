// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

const int maxn = 1e6 + 10;
struct Tree {
    int c[maxn], n;
    void init() {
        n = maxn - 5;
    }
    int lowbit(int x) {
        return x & (-x);
    }
    void add(int x, int y) {
        while (x <= n) {
            c[x] += y;
            x += lowbit(x);
        }
    }
    int query(int x) {
        int ans = 0;
        while (x >= 1) {
            ans += c[x];
            x -= lowbit(x);
        }
        return ans;
    }
    void add(int l, int r, int x) {
        // writeln(l, r, x);
        add(l, x);
        add(r + 1, -x);
    }
} tr;

int l[maxn], r[maxn];
struct AC {
    struct Node {
        int nxt[26], fail, sum, bgn, edn;
        std::vector<int> failson;
        std::vector<int> p;
    } nd[maxn];
    int cnt, idx;
    void init() {
        cnt = idx = 0;
    }
    void ins(char *ch, int id) {
        int u = 0;
        for (int i = 0, len = strlen(ch); i < len; i++) {
            int &v = nd[u].nxt[ch[i] - 'a'];
            if (!v) {
                v = ++cnt;
            }
            u = v;
        }
        nd[u].sum++;
        nd[u].p.push_back(id);
    }
    void build() {
        std::queue<int> q;
        for (int i = 0; i < 26; i++) {
            int v = nd[0].nxt[i];
            if (v) q.push(v), nd[0].failson.push_back(v);
        }

        while (!q.empty()) {
            int u = q.front(); q.pop(); auto &e = nd[u];
            for (int i = 0; i < 26; i++) {
                int &v = nd[u].nxt[i];
                if (v) {
                    nd[v].fail = nd[e.fail].nxt[i];
                    nd[nd[v].fail].failson.push_back(v);
                    q.push(v);
                } else {
                    e.nxt[i] = nd[e.fail].nxt[i];
                }
            }
        }
    }
    void dfs(int u) {
        auto &e = nd[u];
        e.bgn = ++idx;
        for (int v : e.failson) {
            dfs(v);
        }
        e.edn = idx;
        tr.add(e.bgn, e.edn, e.sum);
        for (int q : e.p) {
            l[q] = e.bgn;
            r[q] = e.edn;
        }
    }
    int query(char *ch) {
        int ans = 0, u = 0;
        for (int i = 0, len = strlen(ch); i < len; i++) {
            u = nd[u].nxt[ch[i] - 'a'];
            ans += tr.query(nd[u].bgn);
        }
        return ans;
    }
} ac;

bool st[maxn];
char ch[maxn];
int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n, k;
    read(n, k);
    tr.init();
    ac.init();
    for (int i = 1; i <= k; i++) {
        scanf("%s", ch);
        ac.ins(ch, i);
    }
    ac.build();
    ac.dfs(0);
    for (int i = 1; i <= n; i++) {
        scanf("%s", ch);
        if (ch[0] == '?') {
            writeln(ac.query(ch + 1));
        } else if (ch[0] == '-') {
            int x; sscanf(ch + 1, "%d", &x);
            if (!st[x]) {
                st[x] = 1;
                tr.add(l[x], r[x], -1);
            }
        } else if (ch[0] == '+') {
            int x; sscanf(ch + 1, "%d", &x);
            if (st[x]) {
                st[x] = 0;
                tr.add(l[x], r[x], 1);
            }
        }
    }
    return 0;
}
