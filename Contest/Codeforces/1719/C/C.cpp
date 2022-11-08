#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, q, a[100010], ans[100010], w[100010];

struct nd {
  int x, k, num;
} ska[100010];

bool cmp(nd a, nd b) { return a.k < b.k; }

signed main() {
  scanf("%lld", &t);

  while (t--) {
    memset(w, 0, sizeof(w));
    memset(ans, 0, sizeof(ans));
    scanf("%lld%lld", &n, &q);

    for (int i = 1; i <= n; i++) {

      scanf("%lld", &a[i]);
    }

    for (int i = 1; i <= q; i++) {

      scanf("%lld%lld", &ska[i].x, &ska[i].k);
      ska[i].num = i;
    }

    int tot = 1, now = 1;
    sort(ska + 1, ska + 1 + q, cmp);

    for (int i = 2; i <= n; i++) {

      if (a[i] > a[now]) {
        w[i]++;
        now = i;
      } else {
        w[now]++;
      }

      while (ska[tot].k == (i - 1) && tot <= q) {
        ans[ska[tot].num] = w[ska[tot].x];
        tot++;
      }
    }

    for (int i = tot; i <= q; i++) {

      if (ska[i].x != now) {
        ans[ska[i].num] = w[ska[i].x];
      } else {
        ans[ska[i].num] = w[now] + (ska[i].k - n + 1);
      }
    }

    for (int i = 1; i <= q; i++) {

      printf("%lld\n", ans[i]);
    }
  }

  return 0;
}