#include <cstdio>

#define maxn 2000000
#define max(a, b) ((a) < (b) ? (b) : (a))

bool nss[maxn + 10];
int ans[maxn + 10];
int rans[maxn + 10];

void init() {
    ans[1] = 1;
    nss[1] = true;
    for (int i = 2; i <= maxn; i++) {
        if (!nss[i]) {
            ans[i] = i;
            for (int j = 2 * i; j <= maxn; j += i) {
                // init ss
                nss[j] = true;
                // init ans
                ans[j] = ans[i] + ans[j / i];
            }

        }
    }

    rans[1] = 1;
    for (int i = 2; i <= maxn; i++) {
        rans[i] = max(rans[i - 1], ans[i]);
    }
}

int main() {
    init();
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        
        printf("%d\n", rans[n]);
    }
    // printf("%d\n", rans[114514]);
    return 0;
}