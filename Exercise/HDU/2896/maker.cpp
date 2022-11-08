#include <cstdio>
#include <cmath>

int main() {
    freopen("2896.in", "w", stdout);
    int n = 500;
    printf("%d\n", 500);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 200; j++) {
            putchar(rand() % 60 + '0');
        }
        puts("");
    }
    int m = 1000;
    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 10000; j++) {
            putchar(rand() % 60 + '0');
        }
        puts("");
    }
    return 0;
}