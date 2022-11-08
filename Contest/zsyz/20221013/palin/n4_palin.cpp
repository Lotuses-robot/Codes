// Copyright 2022 Lotuses
#include <cstdio>
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

#define maxn 100

char chr[maxn][maxn];
int f[maxn][maxn][maxn][maxn];

int ch1x[2] = {0, -1},
    ch1y[2] = {-1, 0},
    ch2x[2] = {0, 1},
    ch2y[2] = {1, 0};

const int mod = 993244853;

int main() {
    int n, m;
    read(n, m);

    for (int i = 0; i < n; i++) {
        scanf("%s", chr[i]);
    }

    int ans = 0;
    if (chr[0][0] != chr[n - 1][m - 1]) {
        puts("0");
        return 0;
    }

    f[0][0][n - 1][m - 1] = 1;

    for (int mv = 1; mv < int((n + m - 1) / 2.0 + 0.5001); mv++) {
        for (int i = 0; i < n; i++) {
            int j = mv - i;
            if (j < 0 || j >= m) continue;
            int s = (m + n - 2) - mv;
            for (int k = 0; k < n; k++) {
                int l = s - k;
                if (l < 0 || l >= m || chr[i][j] != chr[k][l]) continue;
                if (i > k || j > l) continue;

                // f[i][j][k][l] = 0;

                for (int ch1 = 0; ch1 < 2; ch1++) {
                    for (int ch2 = 0; ch2 < 2; ch2++) {
                        int ii = i + ch1x[ch1],
                            jj = j + ch1y[ch1],
                            kk = k + ch2x[ch2],
                            ll = l + ch2y[ch2];

                        if (ii < 0 || jj < 0 || kk >= n || ll >= m) continue;

                        f[i][j][k][l] += f[ii][jj][kk][ll];
                        f[i][j][k][l] %= mod;
                    }
                }
                if ((n + m) % 2 == 1 && mv * 2 + 2 >= n + m - 2) {
                    ans += f[i][j][k][l];
                } else if ((n + m) % 2 == 0 && mv * 2 >= n + m - 2) {
                    ans += f[i][j][k][l];
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
