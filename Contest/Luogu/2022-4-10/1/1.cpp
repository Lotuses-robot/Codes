#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        static int p[100005];
        static int ped[100005];
        memset(ped,-63,sizeof(ped));
        int n, last;
        scanf("%d", &n);
        last = n;

        for (int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
        }

        for (int i = n - 1; i >= 0; i--) {
            if (p[i] == -1) {
                ped[i] = last;
            } else {
                last = i;
            }
        }

        int now = 0;
        for (int i = 0; i < n; i++) {
            if(p[i] != -1) {
                printf("%d ", p[i] - now);
                now = p[i];
            } else {
                int last = ped[i];
                int need = p[last] - now;
                int each = need / (last - i + 1);
                each = max(each, 1);
                int lastone = need - each * (last - i);
                lastone = max(lastone, 1);
                //printf("\n%d %d %d %d\n", last, need, each, lastone);

                for (int j = i; j <= min(last, n - 1); j++) {
                   if (j != last - 1) printf("%d ", each);
                   else printf("%d ", lastone);
                }

                i = last;
                now = p[last];
            }
        }
        puts("");
    }
    return 0;
}