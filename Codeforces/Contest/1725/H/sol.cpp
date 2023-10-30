// 1725H 
#include <cstdio>

int a[114514];
int main() {
    int n, tot0 = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i] %= 3;
        tot0 += a[i] == 0;
    }

    if (tot0 <= n / 2) {
        puts("0");
        tot0 = n / 2 - tot0;
        for (int i = 0; i < n; i++) {
            if (!a[i]) {
                putchar('0');
            } else if (tot0) {
                putchar('0');
                tot0--;
            } else {
                putchar('1');
            }
        }
    } else {
        puts("2");
        tot0 = n / 2;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0 && tot0) {
                putchar('0');
                tot0--;
            } else {
                putchar('1');
            }
        }
    }
}