#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int N = 2e5 + 10;

struct Edge {
    int u, v;
};

int n, m;
vector<Edge> G[N];
bool st[N];
int mi[N];
bool vis[N];

bool check(int k) {
    memset(mi, 0, sizeof(mi));
    memset(vis, 0, sizeof(vis));
    while (true) {
        bool flag1 = false, flag2 = false;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) continue;
            if ((int)G[i].size() - mi[i] < k) {
                flag1 = true;
                vis[i] = true;
                for (auto e : G[i]) {
                    mi[e.v]++;
                }
            } else {
                flag2 = true;
            }
        }
        if (flag1) {
            continue;
        }
        return flag2;
    }
}

int main() {
    freopen(".in", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({u, v});
        G[v].push_back({v, u});
    }
    int l = 0, r = n - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;
    return 0;
}