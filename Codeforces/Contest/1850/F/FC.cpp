#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;
int n, q[maxn], sum[maxn], cnts[maxn], ans = -1;

void init() {
    memset(cnts, 0, sizeof(cnts));
    memset(sum, 0, sizeof(sum));
}

void init2() {
    sum[1] = cnts[1];
    ans = std::max(ans, sum[1]);
    for (int i = 2; i <= n; i++) {
        sum[i] += cnts[i] + cnts[1];
        if (!sum[i]) continue;
        for (int j = i + i; j <= n; j += i) {
            sum[j] += cnts[i];
        }
        ans = std::max(ans, sum[i]);
    }
}


int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &q[i]);
            if (q[i] > n) continue;
            cnts[q[i]]++;
        }
        ans = 0;
        init2();
        printf("%d\n", ans);
    }
    return 0;
}
