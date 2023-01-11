// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

#define maxn 114514
#define inf 0x3f3f3f3f

struct Flower {
    int n, m, s, t;
    struct Edge {
        int from, to, flow;
    };
    std::vector<int> G[maxn];
    std::vector<Edge> ed;
    
    void init(int n) {
        for (int i = 0; i <= n; i++) {
            G[i].clear();
        }
        ed.clear();
    }

    void insert(int from, int to, int cap) {
        ed.push_back({from, to, cap});
        ed.push_back({to, from, 0});
        G[from].push_back(ed.size() - 2);
        G[to].push_back(ed.size() - 1);
    }

    int dep[maxn];
    std::queue<int> q; 

    bool bfs() {
        while (!q.empty()) q.pop();
        memset(dep, 0, sizeof(dep));
        dep[s] = 1;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int nxt : G[u]) {
                if (!dep[ed[nxt].to] && ed[nxt].flow > 0) {
                    dep[ed[nxt].to] = dep[u] + 1;
                    q.push(ed[nxt].to);
                }
            }
        }
        return dep[t];
    }

    int cur[maxn];

    int dfs(int pt, int flow) {
        if (pt == t) {
            return flow;
        }
        for (int& i = cur[pt]; i < G[pt].size(); i++) {
            Edge& e = ed[G[pt][i]];
            if (dep[e.to] == dep[e.from] + 1 && e.flow > 0) {
                int fl = dfs(e.to, std::min(flow, e.flow));
                if (fl) {
                    e.flow -= fl;
                    ed[G[pt][i] ^ 1].flow += fl;
                    return fl;
                }
            }
        }
        return 0;
    }

    int MaxFlow() {
        int ans = 0;
        while (bfs()) {
            memset(cur, 0, sizeof(cur)); int subAns;
            while (subAns = dfs(s, inf)) ans += subAns;
        }
        return ans;
    }
    
}fl;

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(fl.n, fl.m, fl.s, fl.t);
    for (int i = 0; i < fl.m; i++) {
        int f, t, c;
        read(f, t, c);
        fl.insert(f, t, c);
    }
    printf("%lld\n", fl.MaxFlow());
    return 0;
}
