#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n == 1) {
            printf("%d\n", 2);
        } else if (n == 2) {
            printf("%d\n", 1);
        } else {
            int mod = n % 3, div = n / 3;
            if (mod == 1) {
                printf("%d\n", div + 1);
            } else if (mod == 2) {
                printf("%d\n", div + 1);
            } else {
                printf("%d\n", div);
            }
        }
    }
    return 0;
}