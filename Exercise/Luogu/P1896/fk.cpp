#include <cstdio>
#define ll long long
#define lowbit(x) ((x) & (-x))

ll a, b, c;

int main() {
    scanf("%lld%lld%lld", &a, &b, &c);
    if (a % 2 == 1 && c % 2 == 0) {
        puts("1");
        return 0;
    } else {
        if ((a % 2 == 1 && c % 2 == 1 && b % 2 == 1) ||
                (a % 2 == 0 && c % 2 == 1 && b % 2 == 0)) {
            c -= lowbit(c);
            printf("%lld", lowbit(c));
            return 0;
        }
        printf("%lld", lowbit(c));
        return 0;
    }
    return 0;
}