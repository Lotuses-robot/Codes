#include <cstdio>

#define maxn 114514

struct union_find_set {
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void uni(int x, int y) {
        fa[find(x)] = find(y);
    }
    int tot(int n) const {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += (i == fa[i]);
        }
        return ans;
    }
}ufs;

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF && n) {
        ufs.init(n);
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            ufs.uni(x, y);
        }
        printf("%d\n", ufs.tot(n) - 1);
    }
    return 0;
}