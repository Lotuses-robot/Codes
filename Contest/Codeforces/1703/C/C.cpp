#include <cstdio>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        static int lst[114514];
        for (int i = 0; i < n; i++) {
            scanf("%d", &lst[i]);
        }

        for (int i = 0; i < n; i++) {
            int len = 0;
            static char ch[114514];
            scanf("%d%s", &len, ch);
            for (int j = 0; j < len; j++) {
                if (ch[j] == 'U') {
                    lst[i]--;
                    if (lst[i] < 0) lst[i] += 10;
                } else {
                    lst[i]++;
                    if (lst[i] > 9) lst[i] -= 10;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            printf("%d ", lst[i]);
        }
        puts("");
    }
    return 0;
}