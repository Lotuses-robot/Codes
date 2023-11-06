#include <cstdio>

int main()
{
    printf("%d\n", int((1u << 31) - 1) < (1u << 31));
    for (int i = 0; i < (1u << 31); i ++) {
        if (i % 100000000 == 0) printf("%d\n", i);
        // puts("Hello OIers!");
    }

    return 0;
}
