#include <cstdio>
#include <cstring>
#include <vector>

int main() {
    int T, t, sum = 0;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &t);
        sum += t;
    }
    printf("%d\n", sum);
    return 0;
}