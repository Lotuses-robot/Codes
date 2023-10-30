#include <cstdio>
#include <cstring>
#include <cctype>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        static char ch[114514];
        scanf("%s", ch);
        int len = strlen(ch);
        for (int i = 0; i < len; i++) {
            ch[i] = toupper(ch[i]);
        }
        if (strcmp(ch, "YES") == 0) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}