#include <cstdio>

#define min(intA, intB) ((intA) < (intB) ? (intA) : (intB))

int main() {
    int n;
    static int a[501],f[501][501];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // dp
    for (int len = 0; len <= n; len++) {
        for (int i = 0, j = i + len; j < n; i++, j++) {
            if (i == j) {
                f[i][j] = 1;
            } else if (i + 1 == j) {
                f[i][j] = 1 + (a[i] != a[j]);
            } else {
                f[i][j] = 998244353;
                if (a[i] == a[j]) f[i][j] = f[i + 1][j - 1];

                for (int k = i; k < j; k++) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k+1][j]);
                }
            }
        }
    }

    printf("%d\n", f[0][n-1]);
    return 0;
}