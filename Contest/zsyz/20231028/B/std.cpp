#include <cstdio>
#include <cmath>
#include <algorithm>
#define double long double 
using namespace std;
struct point {
    double x, y;
} a[10005], b[10005];
struct segment {
    point st, ed;
    segment(point st, point ed) {
        if (st.x > ed.x)
            swap(st, ed);
        if (st.x == ed.x && st.y > ed.y)
            swap(st, ed);
        this -> st = st;
        this -> ed = ed;
    }
};
inline double dist(const point& a, const point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
inline double distance(segment a, point b) {
    point inter;
    if (a.st.x == a.ed.x) {
        inter.x = a.st.x;
        inter.y = b.y;
    } else if (a.st.y == a.ed.y) {
        inter.x = b.x;
        inter.y = a.st.y;
    } else {
        double k1 = (a.ed.y - a.st.y) / (a.ed.x - a.st.x);
        double b1 = a.st.y - k1 * a.st.x;
        double k2 = -1 / k1;
        double b2 = b.y - k2 * b.x;
        inter.x = (b2 - b1) / (k1 - k2);
        inter.y = k1 * inter.x + b1;
    }
    if (a.st.x <= inter.x && inter.x <= a.ed.x && (a.st.y <= inter.y && inter.y <= a.ed.y || a.st.y >= inter.y && inter.y >= a.ed.y))
        return dist(inter, b);
    else
        return min(dist(a.st, b), dist(a.ed, b));
}
double ans[10005];
int main() {
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        scanf("%Lf%Lf", &a[i].x, &a[i].y);
    for (int i = 1; i <= n; i++) {
        scanf("%Lf%Lf", &b[i].x, &b[i].y);
        ans[i] = 1e18;
    }
    for (int i = 1; i < m; i++) {
        if (a[i].x == a[i + 1].x && a[i].y == a[i + 1].y)
            continue;
        segment t(a[i], a[i + 1]);
        for (int j = 1; j <= n; j++)
            ans[j] = min(ans[j], distance(t, b[j]));
    }
    for (int i = 1; i <= n; i++)
        printf("%.4Lf\n", ans[i]);
    return 0;
}