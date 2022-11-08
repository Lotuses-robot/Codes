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

#define mod 1000000007
char a[1001], b[201];
int n, m, t, f[2][201][201][2], s, ii, pre = 1;

int main() {
    read(n, m, t);
    scanf("%s%s", a + 1, b + 1);

    for (int i = 1; i <= n; i++) {
        std::swap(ii, pre);
        f[ii][1][1][0] = s;
        if (a[i] == b[1])
            f[ii][1][1][1] = 1, s++;
        for (int j = 2; j <= m; j++) {
            for (int k = 1; k <= t; k++) {
                f[ii][j][k][0] = (f[pre][j][k][0] + f[pre][j][k][1]) % mod;
                if (a[i] == b[j]) {
                    f[ii][j][k][1] = ((f[pre][j - 1][k - 1][1] + f[pre][j - 1][k][1]) % mod +
                                        f[pre][j - 1][k - 1][0]) % mod;
                }
            }
        }
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= t; k++)
                f[pre][j][k][1] = f[pre][j][k][0] = 0;
    }
    printf("%d", (f[ii][m][t][1] + f[ii][m][t][0]) % mod);
    return 0;
}
