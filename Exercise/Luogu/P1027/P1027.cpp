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
    double x, y; int id;
    bool operator != (Point b) const {
        return x != b.x && y != b.y;
    }
};

Point GetMid(Point a, Point b) {
    return {(a.x + b.x) / 2, (a.y + b.y) / 2};
}

Point GetCh(Point a, Point mid) {
    return {a.x + (mid.x - a.x) * 2, a.y + (mid.y - a.y) * 2};
}

Point Get(Point a, Point mid, Point b) {
    Point pmid = GetMid(a, b);
    return GetCh(mid, pmid);
}

#define M_PI		3.14159265358979323846
double get_angle(double x1, double y1, double x2, double y2, double x3, double y3) {
    double theta = atan2(x1 - x3, y1 - y3) - atan2(x2 - x3, y2 - y3);
	if (theta > M_PI)
		theta -= 2 * M_PI;
	if (theta < -M_PI)
		theta += 2 * M_PI;
 
	theta = abs(theta * 180.0 / M_PI);
	return theta;
}

double GetAngle(Point a, Point b, Point c) {
    return get_angle(a.x, a.y, b.x, b.y, c.x, c.y);
}

int cnt = -1;
std::map<int, int> mp1, mp2;
struct City {
    Point ap[4];
    void init(Point a, Point b, Point c) {
        ap[0] = a; ap[1] = b; ap[2] = c;
        if (fabs(GetAngle(a, b, c) - 90) <= 1e-4) {
            ap[3] = Get(a, c, b);
        }
        if (fabs(GetAngle(a, c, b) - 90) <= 1e-4) {
            ap[3] = Get(a, b, c);
        }
        if (fabs(GetAngle(b, c, a) - 90) <= 1e-4) {
            ap[3] = Get(b, a, c);
        }
        ap[0].id = ++cnt; ap[1].id = ++cnt; ap[2].id = ++cnt; ap[3].id = ++cnt;
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
    // printf("%d\n", s);
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x42, sizeof(dis));
    dis[s] = 0;
    q.push({s, 0});
    while (!q.empty()) {
        Node u = q.top(); q.pop();
        if (vis[u.id]) continue;
        vis[u.id] = true;
        for (Edge e : G[u.id]) {
            // printf("%d\n", e.to);
            int u = e.from, v = e.to;
            if (dis[u] + e.w < dis[v]) {
                dis[v] = dis[u] + e.w;
                q.push({v, dis[v]});
            }
        }
    }
}

int main() {
    // printf("%lf", GetAngle({2, 5}, {7, 4}, {5, 2}));

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
                scanf("%lf%lf", &a[j].x, &a[j].y);
            }
            c[i].init(a[0], a[1], a[2]);
            for (int j = 0; j < 4; j++) {
                // printf("(%lf, %lf)\n", c[i].ap[j].x, c[i].ap[j].y);
            }
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
                        // printf("%.0lf %.0lf %.0lf %.0lf %lf\n", c[i].ap[x].x, c[i].ap[x].y, c[j].ap[y].x, c[j].ap[y].y, w);
                    }
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int k = j + 1; k < 4; k++) {
                    int s = c[i].ap[j].id, t = c[i].ap[k].id;
                    double w = dist(c[i].ap[j], c[i].ap[k]) * tt[i];
                    G[s].push_back({s, t, w});
                    G[t].push_back({t, s, w});
                    // printf("! %.0lf %.0lf %.0lf %.0lf %lf\n", c[i].ap[j].x, c[i].ap[j].y, c[i].ap[k].x, c[i].ap[k].y, w);
                }
            }
        }

        // dij
        double ans = 1145141919;
        for (int i = 0; i < 4; i++) {
            dij(c[a].ap[i].id);
            for (int j = 0; j < 4; j++) {
                ans = std::min(ans, dis[c[b].ap[j].id]);
                // printf("%.0lf %.0lf %.0lf %.0lf %lf\n", c[a].ap[i].x, c[a].ap[i].y, c[b].ap[j].x, c[b].ap[j].y, dis[c[b].ap[j].id]);
            }
        }
        printf("%.1lf", ans);
    }
    return 0;
}
