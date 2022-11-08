#include <cstdio>

#define maxn 114514

struct union_find_set {
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    int tot[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
            tot[i] = 1;
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
    ufs.init();
    int p;
    scanf("%d", &p);
    while (p--) {
        char ch[14];
        scanf("%s", ch);
        if (ch[0] == 'M') {
            int x, y;
            scanf("%d%d", &x, &y);
            ufs.uni(x, y);
        } else if (ch[0] == 'C') {
            int x;
            scanf("%d", &x);

        }
    }
}