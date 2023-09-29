// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
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
#define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 20;
const double eps = 1e-7;
struct Point {
    double x, y;
} p[maxn];
struct func {
    double a, b;
    void get(Point p1, Point p2) {
        a = (p1.y * p2.x - p2.y * p1.x) / (p1.x * p2.x * (p1.x - p2.x));
        b = (p1.x * p1.x * p2.y - p2.x * p2.x * p1.y) / (p1.x * p2.x * (p1.x - p2.x));
    }
    bool on(Point p) const {
        double y = a * p.x * p.x + b * p.x;
        if (fabs(p.y - y) <= eps) return true;
        else return false;
    }
};
std::vector<std::pair<int, func> > ch;

int dis[1 << maxn + 2], endst;
std::queue<int> q;
void bfs() {
    while (!q.empty()) q.pop();
    memset(dis, 63, sizeof(dis));
    dis[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        for (auto nxt : ch) {
            int nt = t | nxt.first;
            if (dis[nt] <= dis[t] + 1) continue; dis[nt] = dis[t] + 1;
            q.push(nt);
            // writeln(nt, dis[nt]);
            if (nt == endst) return;
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
        int n, m;
        read(n, m);
        for (int i = 1; i <= n; i++) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        endst = (1 << n + 1) - 2;
        ch.clear();
        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                func f; int st = 0;
                if (fabs(p[i].x - p[j].x) <= eps || fabs(p[i].y / p[i].x - p[j].y / p[j].x) <= eps) continue;
                f.get(p[i], p[j]);
                if (f.a < eps) {
                    // printf("%d %d %lf %lf\n", i, j, f.a, f.b);
                    for (int k = 1; k <= n; k++) {
                        if (f.on(p[k])) {
                            st |= 1 << k;
                            // debug(k);
                        }
                    }
                    ch.push_back({st, f});
                }
            }
            ch.push_back({1 << i, {0, p[i].y / p[i].x}});
        }
        ch.push_back({1 << n, {0, p[n].y / p[n].x}});
        bfs();
        writeln(dis[endst]);
    }
    return 0;
}
