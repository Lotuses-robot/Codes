// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <ctime>
#include <cstdlib>

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

int a[3001][3001];
int b[3001][3001];
int c[3001][3001];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    int T;
    read(T);
    while (T--) {
        int st = clock();
        int n;
        read(n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                read(a[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                read(b[i][j]);
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                read(c[i][j]);
            }
        }
        
        bool flag = false; int cnt = 0;
        while (clock() <= st + n) {
            for (int ct = 1000; ct <= n; ct++) {
                int x = rand() % n + 1, y = rand() % n + 1;
                int sum = 0;
                for (int k = 1; k <= n; k++) {
                    sum += a[x][k] * b[k][y] % mod;
                    sum %= mod;
                }
                if (sum != c[x][y]) { flag = true; break; }
            }cnt++;
            printf("%d\n", cnt);
        }

        if (flag) {
            puts("No");
        } else {
            puts("Yes");
        }
    }
    return 0;
}
