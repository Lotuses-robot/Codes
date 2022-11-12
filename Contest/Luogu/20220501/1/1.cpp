#include <cstdio>
#include <cmath>

// int fabs(double fk) {
//     return fk + 1e-4;
// }

struct nd {
    int op, x, y;
};

int main() {
    static long long nm[10001];
    static nd p[10001];
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &nm[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &p[i].op, &p[i].x, &p[i].y);
    }

    for (int i = m - 1; i >= 0; i--) {
        if (p[i].x == p[i].y) {
            if (p[i].op == 1) {
                nm[p[i].x - 1] /= 2;
            } else {
                nm[p[i].x - 1] = fabs(sqrt(nm[p[i].x - 1]));
            }
        } else {
            if (p[i].op == 1) {
                nm[p[i].x - 1] -= nm[p[i].y - 1];
            } else {
                nm[p[i].x - 1] /= nm[p[i].y - 1];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", nm[i]);
    }
    return 0;
}