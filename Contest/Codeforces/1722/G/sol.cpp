// 1722G

#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, txor = 0;
        scanf("%d", &n);
        
        for (int i = 1; i <= n - 3; i++) {
            printf("%d ", i);
            txor ^= i;
        }
        txor ^= (n - 2 + (1 << 29));
        txor ^= (n - 1 + (1 << 30));
        printf("%d %d %d\n", (n - 2 + (1 << 29)), (n - 1 + (1 << 30)), txor);
    }
    return 0;
}