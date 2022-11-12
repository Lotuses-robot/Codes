#include <cstdio>

const int mod = 9;
int f[1000006];
int sum[1000006];

void init() {
    f[1] = 1; sum[1] = 1;
    f[2] = 1; sum[2] = 2;
    for (int i = 3; i <= 1000000; i++) {
        f[i] = f[i - 1] + f[i - 2]; f[i] %= mod;
        sum[i] = sum[i - 1] + f[i]; sum[i] %= mod;
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", sum[n]);
    }
    return 0;
}