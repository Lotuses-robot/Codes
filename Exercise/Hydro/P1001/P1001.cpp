// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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
    int from, to; double cap;
};

std::vector<Edge> G[1000006];

void insert(int from, int to, int c) {
    double q = 1.0/(1 - c / 100.0);
    G[from].push_back({from, to, q});
    G[to].push_back({to, from, q});
}

double dis[1000006]; bool vis[1000006];

struct Node {
    int p; double d;
    bool operator > (Node b) const {
        return d > b.d;
    }
};

std::priority_queue<Node, std::vector<Node>, std::greater<Node> > q;

void dij(int s) {
    memset(dis, 0x7f, sizeof(dis));
    dis[s] = 1;
    q.push({s, 0});
    // int cnt = 0;
    while (!q.empty()) {
        int u = q.top().p; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        // cnt++;
        for (Edge e : G[u]) {
            if (dis[e.to] > dis[u] * e.cap) {
                dis[e.to] = dis[u] * e.cap;
                q.push({e.to, dis[e.to]});
            }
        }
        // if (cnt % 10000 == 0) printf("%d\n", cnt);
    }
}

int main() {   
    int n, m;
    read(n, m);
    for (int i = 0; i < m; i++) {
        int x, y, c;
        read(x, y, c);
        insert(x, y, c);
    }
    int a, b;
    read(a, b);
    dij(a);

    double ans = 100 * dis[b];
    printf("%.9lf\n", ans);
    return 0;
}
