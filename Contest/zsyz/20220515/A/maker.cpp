#include <cstdio>
#include <cmath>
#include <ctime>

int main() {
    freopen("mk.txt", "w", stdout);
    srand(time(NULL));
    printf("1\n5 %d\n", rand()%100);
    for (int i = 1; i <= 5; i++) {printf("%d ", 1ll * rand()%100);}
    freopen("CON", "w", stdout);
    system("A");
    system("7");
}