#include <cstdio>

int main() {
    int y;
    scanf("%d", &y);
    int yl = y % 4;
    if (yl == 0) {
        printf("%d\n", y + 2);
    } else if (yl == 1) {
        printf("%d\n", y + 1);
    } else if (yl == 2) {
        printf("%d\n", y);
    } else if (yl == 3) {
        printf("%d\n", y + 3);
    }
    return 0;
}