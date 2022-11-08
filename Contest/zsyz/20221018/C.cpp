// Copyright 2022 Lotuses
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

struct Point {
    int x, y;
}p[20];

double ans[20][131072];
bool vis[20][131072];
int n;

double distence(int x, int y) {
    return sqrt((p[x].x - p[y].x) * (p[x].x - p[y].x) +
                (p[x].y - p[y].y) * (p[x].y - p[y].y));
}

double dfs(int pt, int status) {
    for (int i = 0; i < n; i++) {
        if (!((status >> i) & 1)) goto NotOK;
    }
    return 0;

    NotOK: if (vis[pt][status] && ans[pt][status]) {
        return ans[pt][status];
    }
    double minn = 1145141919;
    for (int i = 0; i < n; i++) {
        if ((status >> i) & 1 || pt == i) {
            continue;
        }
        minn = std::min(minn, dfs(i, status | (1 << i)) + distence(pt, i));
    }
    vis[pt][status] = true;
    return (ans[pt][status] = minn);
}

int main() {
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    read(n);
    for (int i = 0; i < n; i++) {
        read(p[i].x, p[i].y);
    }

    double minn = 1145141919;
    for (int i = 0; i < n; i++) {
        minn = std::min(dfs(i, 1 << i) + sqrt(p[i].x * p[i].x +
                                        p[i].y * p[i].y), minn);
    }

    printf("%.2lf\n", minn);
    return 0;
}
