某个人 X 直接给另一个人 Y 转账后，假如 Y 收到了 $t$ 元钱，手续费为 $z\%$，那么 X 花费了 $t/(1-z\%)$ 元钱。假如 X 和 Y 之间可以直接转账且手续费为 $z\%$ 的话，我们连接一条边并赋权值为 $1/(1-z\%)$。为了计算 A 最少需要花费多少钱，我们需要找到一条路，使得 B 到 A 走过的路的权值乘积最小。由于权值都是大于1的数（**总是越乘越大**），因此我们可以用 Dijkstra 算法。

至于权值乘积最小为什么也能用最短路算法，这可以用 Dijkstra 算法的原理来解释，这里不再叙述。

tip1：

为何可以使用最短路，由于大于 $1$ 的数乘积总是越来越大的，（即与加法的越来越大相同）。而 Dijkstra 利用了不断变大的贪心，进行了提前跟新，而乘法可以与其进行类比。

即使强硬的非要用数学证明，给每条边取 $\lg$，乘法就变成了加法，自然就可以使用最短路了。

tip2：

本题目的远古数据放过了 $O(n^2)$ 的 dp 做法，但是经过加强及构造卡 spfa，本题仅能用 Dijkstra $O(m\log m)$ 通过。

参考代码：

```cpp
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
    while (!q.empty()) {
        int u = q.top().p; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (Edge e : G[u]) {
            if (dis[e.to] > dis[u] * e.cap) {
                dis[e.to] = dis[u] * e.cap;
                q.push({e.to, dis[e.to]});
            }
        }
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

```