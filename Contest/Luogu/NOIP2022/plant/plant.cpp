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

int a[1003][1003],
    q[1003][1003],
    g[1003][1003],
    p[1003][1003];
int n, m, c, f;
int ansc, ansf;

void init() {
    // step: q
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = m; j >= 1; j--) {
            q[i][j] = sum++;
            if (a[i][j]) {
                sum = 0;
            }
        }
    }

    // step: g
    for (int j = 1; j <= m; j++) {
        int sum = 0; g[n][j] = g[n][j - 1] = 0;
        for (int i = n - 2; i >= 1; i--) {
            g[i][j] = sum; sum += q[i + 1][j];
            if (a[i][j]) {
                while (a[i - 1][j]) g[i - 1][j] = 0, i--;
                sum = 0;
            }
        }
    }


    // step: p
    for (int j = 1; j <= m; j++) {
        int sum = 0; p[n][j] = 0;
        for (int i = n - 1; i >= 1; i--) {
            p[i][j] = sum; sum += q[i + 1][j];
            if (a[i][j]) {
                sum = 0; p[i - 1][j] = 0;
                i--;
            }
        }
    }
}

void calc() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!a[i][j]) {
                ansc += q[i][j] * p[i][j];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!a[i][j]) {
                ansf += q[i][j] * g[i][j];
            }
        }
    }
}

char buf[1003];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, id;
    read(T, id);
    while (T--) {
        read(n, m, c, f);

        for (int i = 1; i <= n; i++) {
            scanf("%s", buf + 1);
            for (int j = 1; j <= m; j++) {
                a[i][j] = buf[j] == '1';
            }
        }

        init();
        calc();

        printf("%d %d\n", ansc * c, ansf * f);
    }
    return 0;
}
