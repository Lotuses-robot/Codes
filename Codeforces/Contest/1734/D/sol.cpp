// 1734D 
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long

using std::make_pair;

std::vector<std::pair<int, int> > v;

int a[200005];
int suba[200005];

int n, k;

bool check() {
    // memset(suba, 0, sizeof(suba));
    // suba[k] = a[k];
    // for (int i = k + 1; i < n; i++) {
    //     suba[i] = suba[i - 1] + a[i];
    // }

    v.clear();
    int r, kcost = 0, qearn = 0;
    for (r = k; r < n; r++) {
        qearn += a[r];
        kcost = std::min(qearn, kcost);
        if (qearn > 0) {
            v.push_back(make_pair(kcost, qearn));
            kcost = qearn = 0;
        }
    }

    if (qearn != 0) {
        v.push_back(make_pair(kcost, qearn));
    }

    int now = k - 1, sum = a[k - 1], vi = 0;
    for (now = k - 2; now >= 0 && sum >= 0; now--) {
        while (sum + a[now] < 0 && vi < v.size()) {
            if (v[vi].first + sum >= 0) {
                sum += v[vi].second;
                vi++;
            } else {
                sum += a[now];
                break;
            }
        }
        sum += a[now];
    }
    if (sum < 0) return false;
    else return true;
}

signed main() {
    int T;
    scanf("%lld", &T);

    while (T--) {
        scanf("%lld%lld", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &a[i]);
        }
        if (check()) {
            puts("YES");
            continue;
        }
        k = n - k + 1;
        std::reverse(a, a + n);

        if (check()) {
            puts("YES");
            continue;
        }
        puts("NO");
    }
    return 0;
}