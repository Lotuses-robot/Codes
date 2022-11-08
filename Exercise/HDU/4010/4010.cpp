#include <cstdio>
#include <algorithm>

#define MAXN 1200000
#define max(a, b) ((a) > (b) ? (a) : (b))

// debug

// int a[MAXN];

struct LinkCutTree {
    #define lc(x) c[x][0]
    #define rc(x) c[x][1]
    int top, c[maxn][2], fa[maxn], st[maxn], rev[maxn], ADD[maxn], MAX[maxn], a[maxn];
    void init(int n) {
        for (int i = 0; i <= n + 114; i++) {
            c[i][0] = c[i][1] = 0;
            fa[i] = 0;
            rev[i] = 0;
            ADD[i] = 0;
            MAX[i] = 0;
            a[i] = 0;
        }
    }
    void update(int x) { MAX[x] = max(a[x], max(MAX[lc(x)], MAX[rc(x)])); }
    void add(int x, int d) {
        lct.MAX[x] += d;
        lct.ADD[x] += d;
        lct.a[x] += d;
    }
    void pushdown(int x) {
        if (rev[x]) {
            rev[lc(x)] ^= 1;
            rev[rc(x)] ^= 1;
            rev[x] ^= 1;
            std::swap(lc(x), rc(x));
        }
        if (ADD[x]) {
            if (lc(x)) {
                add(lc(x), ADD[x]);
            }
            if (rc(x)) {
                add(lc(x), ADD[x]);
            }
            ADD[x] = 0;
        }
    }
    #define isroot(x) (!fa[x] || (lc(fa[x]) != x && rc(fa[x]) != x))
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
        access(x);
        splay(x);
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

    bool cut(int x, int y) {
        if (x == y) return true;
        split(x, y);
        if (lc(y) != x || rc(x)) return true;
        lc(y) = fa[lc(y)] = 0;
        update(y);
        return false;
    }

    bool link(int x, int y) {
        makeroot(x);
        if (x == y || findroot(y) != x) return true;
        fa[x] = y;
        return false;
    }
}lct;

int linkl[maxn], linkr[maxn];

int main() {
    int n, m;
    while (scanf("%d", &n) != EOF) {
        lct.init(n);
        for (int i = 1; i < n; i++) {
            scanf("%d%d", &linkl[i], &linkr[i]);
        }
        for (int i = 1; i <= n; i++) scanf("%d", &lct.a[i]), lct.MAX[i] = lct.a[i];
        for (int i = 1; i < n; i++) {
            lct.link(linkl[i], linkr[i]);
        }
        
        scanf("%d", &m);
        while (m--) {
            int opt, x, y, w;
            scanf("%d", &opt);
            if (opt == 3) scanf("%d%d%d", &w, &x, &y);
            else scanf("%d%d", &x, &y);
            if (opt == 1) {
                if (lct.findroot(x) != lct.findroot(y) && x != y) {
                    lct.link(x, y);
                } else {
                    puts("-1");
                }
            }
            if (opt == 2) {
                if(lct.findroot(y) != lct.findroot(x) || x == y) {
                    puts("-1");
                    continue;
                }
                lct.makeroot(x);
                bool flag = lct.cut(y, lct.fa[y]);
                if (flag) {
                    puts("-1");
                }
            }
            if (opt == 3) {
                if (lct.findroot(x) != lct.findroot(y)) {
                    puts("-1");
                    continue;
                }
                lct.split(x, y);
            }
            if (opt == 4) {
                if (lct.findroot(x) != lct.findroot(y)) {
                    puts("-1");
                    continue;
                }
                lct.split(x, y);
                printf("%d\n", lct.MAX[y]);
            }
        }
        puts("");
    }
    return 0;
}