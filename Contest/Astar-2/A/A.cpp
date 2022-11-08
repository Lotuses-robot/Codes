#include <cstdio>

int main() {
    int n, t;
    long long sum = 0;
    scanf ("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf ("%d", &t);
        sum += t;
    }
    
    printf("%lld\n", sum);
    return 0;
}