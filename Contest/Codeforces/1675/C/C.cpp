#include <cstdio>
#include <cstring>

#define doit(x, i) (i >= 0 && i < n ? x[i] : 1)

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        static char ch[2000005];
        static bool lst[2000005];
        static bool bef[2000005];
        scanf("%s", &ch);
        int n = strlen(ch), ans = 0;
        
        bef[0] = ch[0] != '0';
        for (int i = 1; i < n; i++) {
            bef[i] |= bef[i - 1];
            bef[i] |= (ch[i] != '0');
        }

        
        lst[n - 1] = ch[n - 1] != '1';
        for (int i = n - 2; i >= 0; i--) {
            lst[i] |= bef[i + 1];
            lst[i] |= (ch[i] != '1');
        }

        
        for (int i = 0; i < n; i++) {
            if (doit(bef, i - 1) && doit(lst, i + 1)) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}