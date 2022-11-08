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

int a[1145];
int g[5];
int f[42][42][42][42];

int cj[4] = {-1, 0, 0, 0},
    ck[4] = {0, -1, 0, 0},
    cl[4] = {0, 0, -1, 0},
    cm[4] = {0, 0, 0, -1};

int main() {
    int n, m, t;
    read(n, m);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }
    for (int i = 0; i < m; i++) {
        read(t);
        g[t]++;
    }

    memset(f, -63, sizeof(f));
    f[0][0][0][0] = a[0];

    for (int i = 1; i < n; i++) {
        for (int j = g[1]; j >= 0; j--) {
            for (int k = g[2]; k >= 0; k--) {
                for (int l = g[3]; l >= 0; l--) {
                    for (int m = g[4]; m >= 0; m--) {
                        for (int ch = 0; ch < 4; ch++) {
                            int jj = j + cj[ch],
                                kk = k + ck[ch],
                                ll = l + cl[ch],
                                mm = m + cm[ch];

                            if (jj < 0 || kk < 0 || ll < 0 || mm < 0) continue;
                            f[j][k][l][m] = std::max(f[j][k][l][m],
                                                    f[jj][kk][ll][mm] + a[i]);
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", f[g[1]][g[2]][g[3]][g[4]]);
    return 0;
}
