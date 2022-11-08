#include <cstdio>
#include <algorithm>

#define MAXN 114514

int a[maxn];

struct LinkCutTree {
    #define lc(x) c[x][0]
    #define rc(x) c[x][1]
    int top, c[maxn][2], fa[maxn], v[maxn], st[maxn], rev[maxn];
    void update(int x) { v[x] = v[lc(x)] ^ v[rc(x)] ^ a[x]; }
    void pushdown(int x) {
        if (rev[x]) {
            rev[lc(x)] ^= 1;
            rev[rc(x)] ^= 1;
            rev[x] ^= 1;
            std::swap(lc(x), rc(x));
        }
    }
    #define isroot(x) (lc(fa[x]) != x && rc(fa[x]) != x)
    void rotate(int x) {
        int y = fa[x], z = fa[y], k;
        k = x == lc(y); // left or right
        if (!isroot(y)) c[z][rc(z) == y] = x;
        fa[x] = z; fa[y] = x; fa[c[x][k]] = y; // hack here!
        c[y][!k] = c[x][k]; c[x][k] = y;
        update(y); update(x);
    }

    void splay(int x) {
        st[top = 1] = x;
        for (int i = x; !isroot(i); i = fa[i]) st[++top] = fa[i];
        while (top) pushdown(st[top--]);
        while (!isroot(x)) {
            int y = fa[x], z = fa[y];
            if (!isroot(y)) (lc(y) == x) ^ (lc(z) == y) ? rotate(x) : rotate(y);
            rotate(x);
        }
    }

    void access(int x) {
        for (int y = 0; x; x = fa[y = x]) {
            splay(x);
            rc(x) = y;
            update(x);
            // printf("%d %d\n", x, v[x]);
        }
    }

    void makeroot(int x) {
        access(x);
        // printf("%d %d %d\n", lc(2), rc(2), fa[x]);
        splay(x); rev[x] ^= 1;
    }

    int findroot(int x) {
        access(x); splay(x);
        while (lc(x)) x = lc(x);
        return x;
    }

    void split(int x, int y) {
        // printf("%d %d %d\n", lc(x), rc(x), fa[x]);
        makeroot(x);
        // printf("%d %d %d\n", lc(x), rc(x), fa[y]);
        access(y);
        splay(y);
    }

    void cut(int x, int y) {
        split(x, y);
        if (lc(y) != x || rc(x)) return;
        lc(y) = fa[lc(y)] = 0;
        update(y);
    }

    void link(int x, int y) {
        makeroot(x);
        fa[x] = y;
    }
}lct;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), lct.v[i] = a[i];
    while (m--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 0) {
            lct.split(x, y);
            printf("%d\n", lct.v[y]);
        }
        if (opt == 1) {
            if (lct.findroot(x) != lct.findroot(y)) {
                lct.link(x, y);
            }
        }
        if (opt == 2) {
            if (lct.findroot(x) == lct.findroot(y)) {
                lct.cut(x, y);
            }
        }
        if (opt == 3) {
            lct.splay(x); a[x] = y;
        }
    }
    return 0;
}