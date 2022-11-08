#include <cstdio>

struct uniSet {
    int fa[1000006];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    int fnd(int x) { 
        return fa[x] = (fa[x] != x ? fnd(fa[x]) : x);
    }

    void uni(int x, int y) {
        int fx = fnd(x), fy = fnd(y);
        if (fx != fy) {
            fa[fx] = fy;
        }
    }

    bool qry(int x, int y) {
        return fnd(x) == fnd(y);
    }
}us;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    us.init(n);

    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            us.uni(x, y);
        } else {
            puts(us.qry(x, y) ? "Y" : "N");
        }
    }
}