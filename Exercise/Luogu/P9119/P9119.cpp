// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

int n, k = -1;
struct Point { double x, y; };
// std::vector<Point> temp;
Point p[1003], c[3003];
int maper[3003], mp = 0;
double f[3003][3003][2];
struct pointer {
    int x, y, z;
}; pointer r[3003][3003][2];

#define pow2(x) ((x) * (x))

double dist(int i, int j) {
    return sqrt(pow2(c[i].x - c[j].x) + pow2(c[i].y - c[j].y));
}

void print(pointer x) {
    std::vector<int> ans; ans.clear();
    while (x.x != x.y) {
        if (x.z == 1) ans.push_back(x.y);
        if (x.z == 0) ans.push_back(x.x);
        x = r[x.x][x.y][x.z];
    }
    ans.push_back(x.x);
    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        printf("%d ", maper[ans[i]]);
    }
    puts("");
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
        if (k == -1 || p[i].y > p[k].y) {
            k = i;
        }
    }

    for (int q = k + 1; q <= n; q++) {
        // temp.push_back(p[q]);
        c[++mp] = p[q];
        maper[mp] = q;
    }
    for (int q = 1; q <= n; q++) {
        // temp.push_back(p[q]);
        c[++mp] = p[q];
        maper[mp] = q;
    }
    for (int q = 1; q <= k - 1; q++) {
        // temp.push_back(p[q]);
        c[++mp] = p[q];
        maper[mp] = q;
    }
    // for (int q = 1; q <= (int)temp.size() + 1; q++) {
    //     c[q] = temp[q];
    // }

    memset(f, 0x42, sizeof(f));
    f[n][n][1] = f[n][n][0] = 0;
    for (int l = 1; l < n; l++) {
        for (int i = 1; i <= 2 * n - l; i++) {
            int j = i + l;
            // f[i][j][1] = std::min(  f[i][j - 1][0] + dist(i, j),
            //                         f[i][j - 1][1] + dist(j - 1, j)  );
            if (f[i][j - 1][0] + dist(i, j) < f[i][j - 1][1] + dist(j - 1, j)) {
                f[i][j][1] = f[i][j - 1][0] + dist(i, j);
                r[i][j][1] = {i, j - 1, 0};
            } else {
                f[i][j][1] = f[i][j - 1][1] + dist(j - 1, j);
                r[i][j][1] = {i, j - 1, 1};
            }
            // f[i][j][0] = std::min(  f[i + 1][j][0] + dist(i, i + 1),
            //                         f[i + 1][j][1] + dist(j, i)  );
            if (f[i + 1][j][0] + dist(i, i + 1) < f[i + 1][j][1] + dist(j, i)) {
                f[i][j][0] = f[i + 1][j][0] + dist(i, i + 1);
                r[i][j][0] = {i + 1, j, 0};
            } else {
                f[i][j][0] = f[i + 1][j][1] + dist(j, i);
                r[i][j][0] = {i + 1, j, 1};
            }
        }
    }

    double ans = 1e18; pointer ansp;
    for (int i = 1; i <= n; i++) {
        // ans = std::min(ans, std::min(f[i][i + n - 1][0], f[i][i + n - 1][1]));
        if (ans > f[i][i + n - 1][0]) {
            ans = f[i][i + n - 1][0];
            ansp = {i, i + n - 1, 0};
        }
        if (ans > f[i][i + n - 1][1]) {
            ans = f[i][i + n - 1][1];
            ansp = {i, i + n - 1, 1};
        }
        // printf("%.2lf\n", std::min(f[i][i + n - 1][0], f[i][i + n - 1][1]));
    }
    // printf("%.2lf", ans);
    print(ansp);
    return 0;
}
