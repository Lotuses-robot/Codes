// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

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

#define mod 998244353

int n = 1000;
int a[3001][3001];
int b[3001][3001];
int c[3001][3001];

void times() {
    for (int i = 1; i <= n; i++) {
        if (i % 100 == 0) puts("fk");
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                c[i][j] += a[i][k] * b[k][j] % mod;
                c[i][j] %= mod;
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".in", "w", stdout);
    #endif
    
    srand(time(0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] = (rand() | rand() << 15) % mod;
            b[i][j] = (rand() | rand() << 15) % mod;
        }
    }
    times();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", a[i][j]);
        }
        puts("");
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", b[i][j]);
        }
        puts("");
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", c[i][j]);
        }
        puts("");
    }
    return 0;
}
