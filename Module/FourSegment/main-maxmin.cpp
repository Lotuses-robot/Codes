#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize(2)

const int maxn = 1e3 + 13;
int n, m, x, y, L, T, q, a[maxn][maxn];

struct tree {
    int x1, y1, x2, y2;
    int MAX, MIN;
} tr[maxn * maxn * 4];

int son(int p, int x) { return p * 4 - 2 + x; }
void update1(int x) {
            max(tr[son(x, 0)].MAX, tr[son(x, 1)].MAX);
    tr[x].MIN = min(tr[son(x, 0)].MIN, tr[son(x, 1)].MIN);
    for (int i = 2; i < 4; ++i) {
        tr[x].MAX = max(tr[x].MAX, tr[son(x, i)].MAX);
        tr[x].MIN = min(tr[x].MIN, tr[son(x, i)].MIN);
    }
}
void update2(int x) {
    tr[x].MAX = max(tr[son(x, 0)].MAX, tr[son(x, 1)].MAX);
    tr[x].MIN = min(tr[son(x, 0)].MIN, tr[son(x, 1)].MIN);
}
void build(int X1, int Y1, int X2, int Y2, int index) {
    tr[index].x1 = X1, tr[index].x2 = X2;
    tr[index].y1 = Y1, tr[index].y2 = Y2;
    if (X1 == X2 && Y1 == Y2) {
        tr[index].MAX = a[X1][Y1];
        tr[index].MIN = a[X1][Y1];
        return;
    }
    int midx = (X1 + X2) >> 1;
    int midy = (Y1 + Y2) >> 1;
    if (X1 == X2) {
        build(X1, Y1, X2, midy, son(index, 0));
        build(X1, midy + 1, X2, Y2, son(index, 1));
        update2(index);
    } else if (Y1 == Y2) {
        build(X1, Y1, midx, Y2, son(index, 0));
        build(midx + 1, Y1, X2, Y2, son(index, 1));
        update2(index);
    } else {
        build(X1, Y1, midx, midy, son(index, 0));
        build(midx + 1, Y1, X2, midy, son(index, 1));
        build(X1, midy + 1, midx, Y2, son(index, 2));
        build(midx + 1, midy + 1, X2, Y2, son(index, 3));
        update1(index);
    }
}
int A, B;
void query(int X1, int Y1, int X2, int Y2, int x) {
    if (tr[x].x1 > X2 || tr[x].x2 < X1 || tr[x].y1 > Y2 || tr[x].y2 < Y1)
        return;
    if (tr[x].x1 >= X1 && tr[x].x2 <= X2 && tr[x].y1 >= Y1 && tr[x].y2 <= Y2) {
        A = max(A, tr[x].MAX);
        B = min(B, tr[x].MIN);
        return;
    }
    if (tr[x].x1 == tr[x].x2 || tr[x].y1 == tr[x].y2) {
        query(X1, Y1, X2, Y2, son(x, 0));
        query(X1, Y1, X2, Y2, son(x, 1));
    } else {
        query(X1, Y1, X2, Y2, son(x, 0));
        query(X1, Y1, X2, Y2, son(x, 1));
        query(X1, Y1, X2, Y2, son(x, 2));
        query(X1, Y1, X2, Y2, son(x, 3));
    }
}
void updata(int X1, int Y1, int X2, int Y2, int x, int val) {
    if (tr[x].x1 > X2 || tr[x].x2 < X1 || tr[x].y1 > Y2 || tr[x].y2 < Y1)
        return;
    if (tr[x].x1 >= X1 && tr[x].x2 <= X2 && tr[x].y1 >= Y1 && tr[x].y2 <= Y2) {
        tr[x].MAX = val;
        tr[x].MIN = val;
        return;
    }
    if (tr[x].x1 == tr[x].x2 || tr[x].y1 == tr[x].y2) {
        updata(X1, Y1, X2, Y2, son(x, 0), val);
        updata(X1, Y1, X2, Y2, son(x, 1), val);
        update2(x);
    } else {
        updata(X1, Y1, X2, Y2, son(x, 0), val);
        updata(X1, Y1, X2, Y2, son(x, 1), val);
        updata(X1, Y1, X2, Y2, son(x, 2), val);
        updata(X1, Y1, X2, Y2, son(x, 3), val);
        update1(x);
    }
}

int main() {
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                scanf("%d", &a[i][j]);
        build(1, 1, n, n, 1);
        scanf("%d", &q);
        printf("Case #%d:\n", i);
        int X1, X2, Y1, Y2;
        while (q--) {
            scanf("%d %d %d", &x, &y, &L);
            L = (L - 1) >> 1;
            X1 = max(1, x - L), Y1 = max(1, y - L);
            X2 = min(n, x + L), Y2 = min(n, y + L);
            A = 0, B = 1e9 + 19;
            query(X1, Y1, X2, Y2, 1);
            updata(x, y, x, y, 1, (A + B) >> 1);
            printf("%d\n", (A + B) >> 1);
        }
    }
    return 0;
}