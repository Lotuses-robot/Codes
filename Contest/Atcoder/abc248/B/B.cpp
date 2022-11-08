#include <cstdio>
#include <cmath>

int main() {
    int a, b, k;
    scanf("%d%d%d", &a, &b, &k);

    double x = 1.0 * b / a;
    printf("%d", int(ceil(log(x) / log(k))));

    return 0;
}