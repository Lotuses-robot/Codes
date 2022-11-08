// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    static char ch, last; r = 0; // NOLINT
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

// int C(int n, int m) {
//     int q = 1;
//     for (int i = 1; i <= n; i++) { q *= i; }
//     for (int i = 1; i <= m; i++) { q /= i; }
//     for (int i = 1; i <= n - m; i++) { q /= i; }
//     return q;
// }

// int solve(int n, int m, int k) {
//     int ans = 0;
//     for (int i = 0; i <= n; i++) {
//         for (int j = 0; j <= std::min(i, m); j++) {
//             int res = C(i, j);
//             if (res % k == 0) ans++;
//         }
//     }
//     return ans;
// }

int fc[3003][3003], k;
int fs[3003][3003];
const int maxn = 2000;

// C(n, m) = C(n - 1, m - 1) + C(n - 1, m)
void Cinit() {
    // memset(fc, -63, sizeof(fc));
    for (int i = 0; i <= maxn; i++) {
        fc[i][0] = 1;
        // fc[0][i] = 0;
    }
    for (int i = 1; i <= maxn; i++) {
        for (int j = 1; j <= i; j++) {
            fc[i][j] = fc[i - 1][j - 1] + fc[i - 1][j];
            fc[i][j] %= k;
        }
    }
}

void Sinit() {
    for (int i = 1; i <= maxn; i++) {
        for (int j = 1; j <= i; j++) {
            if (i == j) {
                fs[i][j] = fs[i][j - 1] + (fc[i][j] == 0);
            } else {
                fs[i][j] = fs[i - 1][j] + fs[i][j - 1]
                            - fs[i - 1][j - 1]
                            + (fc[i][j] == 0);
            }
            // printf("%d ", fs[i][j]);
        }
        // puts("");
    }
}

void init() {
    Cinit();
    Sinit();
}

int main() {
    int T;
    read(T, k);
    init();

    while (T--) {
        int n, m;
        read(n, m);
        m = std::min(m, n);
        printf("%d\n", fs[n][m]);
    }
    return 0;
}
