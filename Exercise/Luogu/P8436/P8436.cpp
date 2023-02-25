// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

#define maxn 1000006

int n, m, tot = 0;
std::vector<Edge> G[maxn];

void insert(int x, int y) {
    ++tot;
    G[x].push_back({x, y, tot});
    G[y].push_back({y, x, tot});
}

int tstamp;
int dfn[maxn], low[maxn], be[maxn];
int st[maxn];
int ans = 0, stlen = 0;
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
        ans++;
        int tmp = st[stlen--];
        static std::vector<int> qd; qd.clear();
        qd.push_back(tmp); be[tmp] = u;
        while (tmp != u) {
            tmp = st[stlen--];
            qd.push_back(tmp);
            be[tmp] = u;
        }
        v.push_back(qd);
    }
}

int main() {
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

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i, -1);
        while (stlen) stlen--;
    }

    printf("%d\n", ans);
    for (auto qd : v) {
        printf("%d ", qd.size());
        for (auto b : qd) {
            printf("%d ", b);
        }
        puts("");
    }
    return 0;
}
