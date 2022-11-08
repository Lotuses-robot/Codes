#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define MAXN 805
int xL, xR, yL, yR, val;
int maxv, minv;
int Max[MAXN << 2][MAXN << 2], Min[MAXN << 2][MAXN << 2];
int N, mat[MAXN][MAXN];

void PushUp(int xrt, int rt) {
    Max[xrt][rt] = max(Max[xrt][rt << 1], Max[xrt][rt << 1 | 1]);
    Min[xrt][rt] = min(Min[xrt][rt << 1], Min[xrt][rt << 1 | 1]);
}

void BuildY(int xrt, int x, int l, int r, int rt) {
    int m;
    if (l == r) {
        if (x != -1)
            Max[xrt][rt] = Min[xrt][rt] = mat[x][l];
        else {
            Max[xrt][rt] = max(Max[xrt << 1][rt], Max[xrt << 1 | 1][rt]);
            Min[xrt][rt] = min(Min[xrt << 1][rt], Min[xrt << 1 | 1][rt]);
        }
        return;
    }
    m = (l + r) >> 1;
    BuildY(xrt, x, lson);
    BuildY(xrt, x, rson);
    PushUp(xrt, rt);
}

void BuildX(int l, int r, int rt) {
    int m;
    if (l == r) {
        BuildY(rt, l, 1, N, 1);
        return;
    }
    m = (l + r) >> 1;
    BuildX(lson);
    BuildX(rson);
    BuildY(rt, -1, 1, N, 1);
}

void UpdateY(int xrt, int x, int l, int r, int rt) {
    int m;
    if (l == r) {
        if (x != -1)
            Max[xrt][rt] = Min[xrt][rt] = val;
        else {
            Max[xrt][rt] = max(Max[xrt << 1][rt], Max[xrt << 1 | 1][rt]);
            Min[xrt][rt] = min(Min[xrt << 1][rt], Min[xrt << 1 | 1][rt]);
        }
        return;
    }
    m = (l + r) >> 1;
    if (yL <= m)
        UpdateY(xrt, x, lson);
    else
        UpdateY(xrt, x, rson);
    PushUp(xrt, rt);
}

void UpdateX(int l, int r, int rt) {
    int m;
    if (l == r) {
        UpdateY(rt, l, 1, N, 1);
        return;
    }
    m = (l + r) >> 1;
    if (xL <= m)
        UpdateX(lson);
    else
        UpdateX(rson);
    UpdateY(rt, -1, 1, N, 1);
}

void QueryY(int xrt, int l, int r, int rt) {
    int m;
    if (yL <= l && yR >= r) {
        minv = min(minv, Min[xrt][rt]);
        maxv = max(maxv, Max[xrt][rt]);
        return;
    }
    m = (l + r) >> 1;
    if (yL <= m)
        QueryY(xrt, lson);
    if (yR > m)
        QueryY(xrt, rson);
}

void QueryX(int l, int r, int rt) {
    int m;
    if (xL <= l && xR >= r) {
        QueryY(rt, 1, N, 1);
        return;
    }
    m = (l + r) >> 1;
    if (xL <= m)
        QueryX(lson);
    if (xR > m)
        QueryX(rson);
}

int main() {
    // freopen("in.txt","r",stdin);
    int i, j, q, cas, T, x, y, l;
    char op[5];
    scanf("%d", &T);
    for (cas = 1; cas <= T; cas++) {
        scanf("%d", &N);
        for (i = 1; i <= N; i++)
            for (j = 1; j <= N; j++)
                scanf("%d", &mat[i][j]);
        BuildX(1, N, 1);
        scanf("%d", &q);
        printf("Case #%d:\n", cas);
        while (q--) {
            scanf("%d%d%d", &x, &y, &l);
            l = (l + 1) / 2;
            xL = max(1, x - l + 1), xR = min(N, x + l - 1);
            yL = max(1, y - l + 1), yR = min(N, y + l - 1);
            minv = 1 << 30, maxv = -(1 << 30);
            QueryX(1, N, 1);
            val = (maxv + minv) / 2;
            xL = x, yL = y;
            printf("%d\n", val);
            UpdateX(1, N, 1);
        }
    }
    return 0;
}