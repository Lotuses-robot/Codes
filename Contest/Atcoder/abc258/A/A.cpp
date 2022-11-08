#include <cstdio>

int main() {
    int k;
    scanf("%d", &k);
    int p1 = k / 60, p2 = k % 60;
    printf("%02d:%02d\n", (21 + p1) % 24, p2);
}