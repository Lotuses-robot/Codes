#include <cstdio>

int pow(int x, int y) {
    int base = x, ans = 1;
    do {
        if (y & 1) ans *= base;
        base *= base;
    } while (y >>= 1);
    return ans;
}

int main() {
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d\n", pow(x, y));
}