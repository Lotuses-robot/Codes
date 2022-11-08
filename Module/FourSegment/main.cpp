#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

typedef long long LL;
using namespace std;

const int maxn = 1025;

LL sum[maxn * 4][maxn * 4];
int n;

void subBuild(int rt, int l, int r, int x) {
    sum[x][rt] = 0;
    if (l != r) {
        int m = (l + r) >> 1;
        subBuild(rt << 1, l, m, x);
        subBuild(rt << 1 | 1, m + 1, r, x);
    }
}

void build(int rt, int l, int r) {
    subBuild(1, 1, n, rt);
    if (l != r) {
        int m = (l + r) >> 1;
        build(rt << 1, l, m);
        build(rt << 1 | 1, m + 1, r);
    }
}

void subUpdate(int rt, int l, int r, int x, int Y, int num) {
    if (l == r && r == Y) {
        sum[x][rt] += num;
    } else {
        int m = (l + r) >> 1;
        if (Y <= m) subUpdate(rt << 1, l, m, x, Y, num);
        if (Y > m) subUpdate(rt << 1 | 1, m + 1, r, x, Y, num);
        sum[x][rt] = sum[x][rt << 1] + sum[x][rt << 1 | 1];
    }
}

void update(int rt, int l, int r, int X, int Y, int num) {
    subUpdate(1, 1, n, rt, Y, num);
    if (l != r) {
        int m = (l + r) >> 1;
        if (X <= m) update(rt << 1, l, m, X, Y, num);
        if (X > m) update(rt << 1 | 1, m + 1, r, X, Y, num);
    }
}

LL subQuery(int rt, int l, int r, int x, int Y1, int Y2) {
    if (Y1 <= l && r <= Y2) {
        return sum[x][rt];
    } else {
        int m = (l + r) >> 1;
        LL tmp = 0;
        if (Y1 <= m) tmp += subQuery(rt << 1, l, m, x, Y1, Y2);
        if (Y2 > m) tmp += subQuery(rt << 1 | 1, m + 1, r, x, Y1, Y2);
        return tmp;
    }
}

LL query(int rt, int l, int r, int X1, int Y1, int X2, int Y2) {
    if (X1 <= l && r <= X2) {
        return subQuery(1, 1, n, rt, Y1, Y2);
    } else {
        int m = (l + r) >> 1;
        LL tmp = 0;
        if (X1 <= m) tmp += query(rt << 1, l, m, X1, Y1, X2, Y2);
        if (X2 > m) tmp += query(rt << 1 | 1, m + 1, r, X1, Y1, X2, Y2);
        return tmp;
    }
}

int main() {
    int op, X1, Y1, X2, Y2, num;
    while (scanf("%d", &op) != EOF) {
        if (op == 0) {
            scanf("%d", &n);
            build(1, 1, n);
        } else if (op == 1) {
            scanf("%d%d%d", &X1, &Y1, &num);
            X1++, Y1++;
            update(1, 1, n, X1, Y1, num);
        } else if (op == 2) {
            scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
            X1++, Y1++, X2++, Y2++;
            printf("%LLd\n", query(1, 1, n, X1, Y1, X2, Y2));
        } else if (op == 3) {
            break;
        }
    }
    return 0;
}
