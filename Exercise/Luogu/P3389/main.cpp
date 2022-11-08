// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

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

double mat[202][202];
double ans[202];

int main() {
    int n;
    read(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    for (int k = 0; k < n; k++) {
        bool flag = false;
        for (int j = k; j < n; j++) {
            if (mat[j][k] != 0) {
                std::swap(mat[k], mat[j]);
                flag = true;
                break;
            }
        }
        if (!flag) {
            puts("No Solution");
            return 0;
        }
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat[i][k]) <= 1e-6) {
                continue;
            }
            double t = mat[k][k] / mat[i][k];
            for (int j = k; j < n + 1; j++) {
                mat[i][j] = mat[i][j] * t - mat[k][j];
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        double left = 0;
        for (int j = i + 1; j < n; j++) {
            left += ans[j] * mat[i][j];
        }
        // left + mat[i][i] * ans[i] = mat[i][n];
        // printf("%d %d %.4lf\n", i, i, mat[i][i]);
        if (fabs(mat[i][i]) <= 1e-6) {
            puts("No Solution");
            return 0;
        }
        ans[i] = (mat[i][n] - left) / mat[i][i];
    }

    for (int i = 0; i < n; i++) {
        printf("%.2lf\n", ans[i]);
    }
    return 0;
}
