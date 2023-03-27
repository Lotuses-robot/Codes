// Copyright 2023 Lotuses
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
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

int n, m, r, k;
struct Point {
    int x, y;
    void _read() {
        read(x, y);
    }
};
Point S;
int map[1003][1003];
int sub[1003][1003];
bool vis[1003][1003];
std::queue<Point> q;
const int cx[4] = { 1, 0, -1, 0 },
          cy[4] = { 0, 1, 0, -1 };

#define inMap(p) ((p.x >= 0) && (p.y >= 0) && (p.x <= n) && (p.y <= m))

#define pow2(x) ((x) * (x))
#define dist(q) (pow2((q).x - p.x) + pow2((q).y - p.y))

#define onSide(q) ((q).x == 0 || (q).x == n || (q).y == 0 || (q).y == m)
#define checkNO(nxt) (pow2(p.x - nxt.x) + pow2(p.y - nxt.y) < r)
#define checkOK(nxt) (pow2(p.x - nxt.x) + pow2(p.y - nxt.y) == r)

bool check(Point p) {
    // if (p.x == 185 && p.y == 100) {
    //     puts("fk");
    // }

    // just judge edge
    
    Point ru = {p.x + floor(sqrt(r)), p.y};
    Point ld = {p.x - floor(sqrt(r)), p.y};
    if (checkNO(ru) && (onSide(ru) || !inMap(ru))) return false;
    if (checkNO(ld) && (onSide(ld) || !inMap(ld))) return false;
    if (checkOK(ru) && !inMap(ru)) return false;
    if (checkOK(ld) && !inMap(ld)) return false;

    ru = {p.x, p.y + floor(sqrt(r))};
    ld = {p.x, p.y - floor(sqrt(r))};
    if (checkNO(ru) && (onSide(ru) || !inMap(ru))) return false;
    if (checkNO(ld) && (onSide(ld) || !inMap(ld))) return false;
    if (checkOK(ru) && !inMap(ru)) return false;
    if (checkOK(ld) && !inMap(ld)) return false;


    // real
    int sqt = sqrt(r);
    for (int i = -sqt; i * i <= r; i++) {
        if (i * i == r) {
            if (!inMap(((Point){p.x, p.y + sqt}))) {
                return false;
            }
            // puts("f");
        } else {
            int sqtt = sqrt(r - pow2(i)) + 0.0001;
            Point pl = p, pr = p;
            pl.x -= sqtt;
            pr.x += sqtt;
            pl.y += i;
            pr.y += i;
            if (dist(pl) == r) {
                pl.x++;
            } if (dist(pr) == r) {
                pr.x--;
            }
            if (!inMap(pl) || !inMap(pr)) {
                return false;
            }
            if (sub[pr.x][pr.y] - (pl.x == 0 ? 0 : sub[pl.x - 1][pl.y]) != 0) {
                return false;
            }
        }
    }
    return true;
}

int bfs() {
    int ans = 1;
    q.push(S); vis[S.x][S.y] = true;
    while (!q.empty()) {
        Point cur = q.front(); q.pop();
        for (int fac = 0; fac < 4; fac++) {
            Point ch = {cur.x + cx[fac], cur.y + cy[fac]};
            if (!vis[ch.x][ch.y] && inMap(ch) && check(ch) && !map[ch.x][ch.y]) {
                vis[ch.x][ch.y] = true;
                q.push(ch);
                ans++;
                // printf("%d %d\n", ch.x, ch.y);
            }
        }
    }

    // printf("check %d %d %d\n", 915, 619, vis[915][619]);
    // for (int i = 100; i <= 200; i++) {
    //     for (int j = 100; j <= 200; j++) {
    //         if (vis[i][j]) printf("%d %d\n", i, j);
    //     }
    // }

    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m, r);
    n++; m++; // atten.
    S._read();
    read(k);
    for (int i = 1; i <= k; i++) {
        Point tem;
        tem._read();
        map[tem.x][tem.y]++;
    }

    for (int j = 0; j <= n; j++) {
        sub[0][j] = map[0][j];
        for (int i = 1; i <= n; i++) {
            sub[i][j] = sub[i - 1][j] + map[i][j];
        }
    }

    // putchar(check({3, 3}) + '0');

    printf("%d\n", bfs());
    return 0;
}
