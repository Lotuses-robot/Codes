#include <cstdio>

int main() {
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d", &n);
        if (n % 2) {
            int fst = -1;
            for(int i = 0; i < n; i++) {
                scanf("%d", &k);
                if (k == 0) {
                    if (fst == -1) fst = i;
                }
            }
            if (fst % 2 == 0) {
                puts("Joe");
            } else {
                puts("Mike");
            }
        } else {
            int Jmin = 1145141919, Mmin = 1145141919, Jid, Mid;
            for (int i = 0; i < n; i++) {
                scanf("%d", &k);
                if (i % 2 == 0 && Mmin > k) Mmin = k, Mid = i;
                if (i % 2 == 1 && Jmin > k) Jmin = k, Jid = i;
            }
            if (Jmin < Mmin) {
                puts("Mike");
            } else if (Mmin < Jmin) {
                puts("Joe");
            } else {
                if (Jid < Mid) puts("Mike");
                else puts("Joe");
            }
        }
    }
    return 0;
}