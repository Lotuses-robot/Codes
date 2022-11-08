#include <cstdio>
#include <cmath>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y)) 

struct Point {
    int x, y;
};

double len(Point x, Point y) {
    return sqrt(1ll * (x.x - y.x) * (x.x - y.x) + 1ll * (x.y - y.y) * (x.y - y.y));
}

int main() {
    static int ak[1001];
    static Point a[1001];
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &ak[i]); ak[i]--;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    double maxn = -998244353;
    for (int i = 0; i < n; i++) {
        double minn = 998244353;
        for (int j = 0; j < k; j++) {
            minn = min(minn, len(a[ak[j]], a[i]));
        }
        maxn = max(maxn, minn);
    }
    printf("%.8lf\n", maxn);
    return 0;
}