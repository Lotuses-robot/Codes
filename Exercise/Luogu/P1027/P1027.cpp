// Copyright 2022 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

int tt[102];
struct Point {
    int x, y, id;
    bool operator != (Point b) const {
        return x != b.x && y != b.y;
    }
};
int cnt = 0;
std::map<int, int> mp1, mp2;
struct City {
    Point ap[4];
    void init(Point a, Point b, Point c) {
        mp1.clear(); mp2.clear();
        ap[0] = a; mp1[a.x]++; mp2[a.y]++;
        ap[1] = b; mp1[b.x]++; mp2[b.y]++;
        ap[2] = c; mp1[c.x]++; mp2[c.y]++;
        int x, y;
        for (auto p : mp1) {
            if (p.second == 1) {
                x = p.first;
            }
        }
        for (auto p : mp2) {
            if (p.second == 1) {
                y = p.second;
            }
        }
        ap[3] = {x, y};
        for (int i = 0; i < 4; i++) {
            ap[i].id = ++cnt;
        }
    }
} c[102];

// Graph
struct Edge {
    int from, to;
    double w;
};
std::vector<Edge> G[514514];

void init() {
    for (int i = 0; i < 500005; i++) {
        G[i].clear();
    }
}

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool vis[514514];
double dis[514514];
struct Node {
    int id; double dist;
    bool operator < (Node b) const {
        return dist > b.dist;
    }
};
std::priority_queue<Node> q;
void dij(int s) {
    printf("%d\n", s);
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x42, sizeof(dis));
    dis[s] = 0; vis[s] = true;
    q.push({s, 0});
    while (!q.empty()) {
        Node u = q.top(); q.pop();
        for (Edge e : G[u.id]) {
            printf("%d\n", e.to);
            if (vis[e.to]) continue;
            vis[e.to] = true;
            dis[e.to] = u.dist + e.w;
            q.push({e.to, dis[e.to]});
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);

    while (T--) {
        int n, t, a, b;
        read(n, t, a, b); a--; b--;
        for (int i = 0; i < n; i++) {
            Point a[3];
            for (int j = 0; j < 3; j++) {
                read(a[j].x, a[j].y);
            }
            c[i].init(a[0], a[1], a[2]);
            read(tt[i]);
        }

        for (int i = 0; i < n; i++) {
            for (int x = 0; x < 4; x++) {
                for (int j = i + 1; j < n; j++) {
                    for (int y = 0; y < 4; y++) {
                        double w = dist(c[i].ap[x], c[j].ap[y]) * t;
                        int s = c[i].ap[x].id, t = c[j].ap[y].id;
                        G[s].push_back({s, t, w});
                        G[t].push_back({t, s, w});
                        printf("1 %d %d\n", s, t);
                    }
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int k = j + 1; k < 4; k++) {
                    int s = c[i].ap[j].id, t = c[i].ap[k].id;
                    double w = dist(c[i].ap[i], c[i].ap[j]) * tt[i];
                    G[s].push_back({s, t, w});
                    G[t].push_back({t, s, w});
                    printf("2 %d %d\n", s, t);
                }
            }
        }

        // dij
        double ans = 1145141919;
        for (int i = 0; i < 4; i++) {
            dij(c[a].ap[i].id);
            for (int j = 0; j < 4; j++) {
                ans = std::min(ans, dis[c[b].ap[j].id]);
            }
        }
        printf("%.1lf", ans);
    }
    return 0;
}
