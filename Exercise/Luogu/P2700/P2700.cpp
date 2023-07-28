#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MAXN = 1e5 + 7;

int n, k;

struct Eg{
    int from, to, v;
    bool operator < (const Eg other) const {
        return v < other.v;
    }
}Edge[MAXN];

int F[MAXN], V[MAXN], ans;

int find(int x) {
    return (x == F[x] ? x : (F[x] = find(F[x])));
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (V[fx]) F[fy] = fx;
    else F[fx] = fy;
}

signed main () {
    cin >> n >> k;
    for (int i = 1; i <= n; i ++) F[i] = i;
    for (int i = 1, x; i <= k; i ++)
        cin >> x, V[x] ++;
    for (int i = 1, u, v, w; i < n; i ++) {
        cin >> u >> v >> w; Edge[i] = Eg{u, v, w};
    }
    sort(Edge + 1, Edge + n);
    for (int i = n - 1; i >= 1; i --) {
        int u = Edge[i].from, v = Edge[i].to;
        if (V[find(u)] && V[find(v)]) {ans += Edge[i].v; continue; }
        merge(u, v);
    }
    cout << ans << '\n';
    return 0;
}