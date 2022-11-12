#include <cstdio>
#include <cstring>

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        static int ans[5011];
        static bool des[5011];
        int n;
        scanf("%d", &n);
        memset(ans, 0, sizeof(ans));
        memset(des, 0, sizeof(des));
        ans[0] = -1e9;

        for (int i = 1; i <= n; i++) {
            printf("? 1 %d\n", i);
            fflush(stdout);
            
            int ret;
            scanf("%d", &ret);

            int q = i - 1;
            while (des[q] && q >= 1) q--;
            // printf("debug %d\n", q);
            if (ret > ans[q]) {
                ans[i] = ret;
            } else {
                int p = q;
                while ((des[p] || ret == ans[p]) && p >= 1) {
                    // printf("debug2 %d %d\n", p, des[p]);
                    if (des[p]) {
                        p--;
                        continue;
                    }
                    printf("? 2 %d\n", p);
                    fflush(stdout);

                    des[p] = true;
                    p--;

                    printf("? 1 %d\n", i);
                    fflush(stdout);

                    scanf("%d", &ret);
                }
                ans[i] = ret;
            }
        }

        printf("! ");
        for (int i = 1; i <= n; i++) {
            printf("%d ", ans[i]);
        }
        printf("\n");
        fflush(stdout);
    }
    return 0;
}