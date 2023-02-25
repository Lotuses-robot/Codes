// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

struct Edge {
    int from, to, id;
};

#define maxn 2000006

int n, m, tot = 0;
std::vector<Edge> G[maxn];

void insert(int x, int y) {
    ++tot;
    G[x].push_back({x, y, tot});
    G[y].push_back({y, x, tot});
}

int tstamp;
int dfn[maxn], low[maxn], be[maxn], bel[maxn];
int st[maxn];
int stlen = 0;
std::vector<std::vector<int> > v;
void tarjan(int u, int id) {
    dfn[u] = low[u] = ++tstamp;
    st[++stlen] = u;
    for (Edge e : G[u]) {
        if (!dfn[e.to]) {
            tarjan(e.to, e.id);
            low[u] = std::min(low[u], low[e.to]);
        } else if (e.id != id) {
            low[u] = std::min(low[u], dfn[e.to]);
        }
    }
    if (low[u] == dfn[u]) {
        int tmp = st[stlen--];
        static std::vector<int> qd; qd.clear();
        qd.push_back(tmp); be[tmp] = v.size(); bel[tmp] = u;
        while (tmp != u) {
            tmp = st[stlen--];
            qd.push_back(tmp);
            be[tmp] = v.size();
            bel[tmp] = u;
        }
        v.push_back(qd);
    }
}

// -- after tarjan

std::vector<Edge> Gra[maxn];
int siz[maxn];
int linked[maxn];

void remake(int u) {
    if (be[u] == -1) {
        Gra[u] = G[u];
        dfn[u] = 1;
    } else {
        int top = bel[u], id = be[u];
        linked[top] = top;
        siz[top] = v[id].size();
        for (int c : v[id]) {
            for (Edge e : G[c]) {
                int nxt = bel[e.to];
                if (nxt == -1) nxt = e.to;
                if (linked[nxt] == top) continue;
                linked[nxt] = top;
                Gra[top].push_back({top, nxt});
            }
            dfn[c] = 1;
        }
    }
}

const int mod = 1000000007;
int pow2[maxn + 100];
void init() {
    pow2[0] = 1;
    for (int i = 1; i <= maxn + 10; i++) {
        pow2[i] = pow2[i - 1] << 1;
        pow2[i] %= mod;
    }
}

int f[maxn][2], ans = 0, total[maxn];
void dp(int u, int fa) {
    int g1 = pow2[siz[u]] - 1, g0 = 1; bool leaf = 0;
    for (Edge e : Gra[u]) {
        if (e.to != fa) {
            dp(e.to, u);
            leaf = true;
        }
    }
    if (!leaf) {
        f[u][1] = g1, f[u][0] = g0;
        total[u] = 0;
    } else {
        f[u][0] = f[u][1] = 1; total[u] = 0;
        int rem = 1;
        for (Edge e : Gra[u]) {
            if (e.to != fa) {
                total[u] += total[e.to] + 1;
                // 0.
                f[u][0] *= f[e.to][0]; f[u][0] %= mod;
                f[u][0] *= 2; f[u][0] %= mod;

                // 1.
                f[u][1] *= (f[e.to][1] + 2 * f[e.to][0]) % mod; f[u][1] %= mod;
                rem *= 2 * f[e.to][0] % mod; rem %= mod;
            }
        }
        f[u][1] = (g1 * f[u][1] + (f[u][1] - rem) + mod) % mod;
        // ans += f[u][1]; ans %= mod;
    }
    ans += f[u][1] * pow2[m - total[u] - (u == 1 ? 0 : 1)] % mod; ans %= mod;
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 0; i < m; i++) {
        int x, y;
        read(x, y);
        insert(x, y);
    }

    memset(be, -1, sizeof(be));
    memset(bel, -1, sizeof(bel));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i, -1);
        while (stlen) stlen--;
    }
    
    // remake graph
    memset(dfn, 0, sizeof(dfn));
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) { remake(i); }
    }
    // --main--
    init();

    // 1 must in the top[]
    // so just dp

    dp(1, -1);
    // printf("%lld\n", ans * pow2[m - (gb >> 1)] % mod);
    // printf("%lld\n", f[1][1]);
    printf("%lld\n", ans);
    return 0;
}
