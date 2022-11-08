#include <cstdio>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
    int n;
    static int a[201],b[201];
    static int f[201][201];

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i == 0 ? 2*n - 1 : i - 1] = a[i];
    }

    for (int i = n; i < n * 2; i++) {
        a[i] = a[i - n];
        b[i - 1] = a[i];
    }
    
    b[2*n - 1] = a[0];

    // for (int i = 0; i < n * 2; i++) {
    //     printf("%d %d\n", a[i], b[i]);
    // }

    // get MAX ans
    for (int len = 0; len < n; len++) {
        for (int i = 0, j = i + len; j < 2*n; i++,j++) {
            if (i == j) {
                f[i][j] = 0;
            } else {
                f[i][j] = -998244353;
                for (int k = i; k < j; k++) {
                    f[i][j] = max(f[i][j], f[i][k] + f[k+1][j] + a[i] * b[k] * b[j]);
                }
            }
        }
    }
    int maxx = -998244353;
    for (int i = 0; i < n; i++) {
        maxx = max(maxx, f[i][i+n-1]);
    }
    printf("%d\n", maxx);
    return 0;
}