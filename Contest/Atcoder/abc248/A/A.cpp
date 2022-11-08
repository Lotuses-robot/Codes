#include <cstdio>

int main() {
    static bool vis[111];
    char ch;

    while ((ch = getchar()) != EOF) {vis[ch - '0'] = true;}

    for (int i = 0; i < 10; i++) {
        if (vis[i] == false) {
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}