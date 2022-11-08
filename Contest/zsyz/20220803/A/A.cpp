#include <cstdio>
#include <cstring>

int main() {
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        static char ch[114514];
        scanf("%s", ch);
        int len = strlen(ch);
        for (int i = 0; i < len; i++) {
            if (ch[i] != '0') break;
            len--;
        }
        printf("%d\n", len);
    }
    return 0;
}