#include <bits/stdc++.h>
#define int long long
using namespace std;
int p[1000001];
int bf[1000001];
int ans[1000001];
int id[1000001];
int idb[1000001];

void merge_sort(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i = l, j = mid + 1, len = 0;
    while (i <= mid && j <= r) {
        if (p[i] <= p[j])
            bf[len++] = p[i++];
        else
            ans[id[j]] += (mid - i + 1), idb[len] = id[j], bf[len++] = p[j++];
    }
    while (i <= mid)
        idb[len] = id[i], bf[len++] = p[i++];
    while (j <= r)
        idb[len] = id[j], bf[len++] = p[j++];

    for (int k = l; k <= r; k++)
        p[k] = bf[k - l], id[k] = idb[k - l];
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        id[i] = i;
    }
    merge_sort(1, n);
    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    return 0;
}