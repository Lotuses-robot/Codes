#include <map>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using std::vector;

#define int long long

struct Edge {
    int from, to, w;
};

#define maxn 80004
vector<Edge> G[maxn];

void insert(int from, int to, int wei) {
    G[from].push_back({from, to, wei});
    G[to].push_back({to, from, wei});
}

#define max(a, b) ((a) > (b) ? (a) : (b))

int n, k;
bool vis[maxn];

int weight[maxn];
int size[maxn];
int centroId[2];
void GetCentro(int fa, int cur, int n) {
    size[cur] = 1;
    weight[cur] = 0;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        GetCentro(cur, e.to, n);
        size[cur] += size[e.to];
        weight[cur] = max(weight[cur], size[e.to]);
    }
    weight[cur] = max(n - size[cur], weight[cur]);
    if (weight[cur] <= n / 2) {
        centroId[centroId[0] != 0] = cur;
    }
}
int GetSize(int fa, int cur) {
    int ans = 1;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        ans += GetSize(cur, e.to);
    }
    return ans;
}
void GetCentro(int fa, int cur) {  // maintain
    // memset(weight, 0, sizeof(weight));
    // memset(size, 0, sizeof(size));
    memset(centroId, 0, sizeof(centroId));
    int sz = GetSize(fa, cur);
    GetCentro(fa, cur, sz);
}
std::map<int, int> dis;

// int Dist[maxn], distLen = 0;
void DfsDist(int fa, int dist, int cur) {
    // Dist[distLen++] = dist;
    dis[dist]++;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        DfsDist(cur, dist + e.w, e.to);
    }
}

int Calc(int cur, int initDist) {
    dis.clear();
    DfsDist(-1, initDist, cur);

    // std::sort(Dist, Dist + distLen);
    // int l = 0, r = distLen - 1, ans = 0;
    // while (true) {
    //     while (r >= 0 && Dist[l] + Dist[r] > k) --r;
    //     if (l > r) break;
    //     ans += r - l;
    //     l++;
    // }
    int ans = 0;
    for (auto p : dis) {
        // printf("%d %d %d\n", p.first, p.second, k - p.first);
        // ans += p.second * dis[k - p.first];
        if (k - p.first == p.first) {
            ans += p.second * (p.second - 1);
        } else {
            ans += p.second * dis[k - p.first];
        }
    }
    // printf("%d\n", ans);
    return ans / 2;
}

int Split(int cur) {
    int ans = 0; vis[cur] = true;
    ans += Calc(cur, 0);
    // printf("%d %d\n", ans, cur);
    for (auto e : G[cur]) {
        if (vis[e.to]) continue;
        ans -= Calc(e.to, e.w);
        GetCentro(e.from, e.to);
        ans += Split(centroId[0]);
    }
    return ans;
}

void init() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < maxn; i++) G[i].clear();
}

signed main() {
    while (~scanf("%lld", &n) && n) {
        scanf("%lld", &k);
        int root = 1;
        for (int i = 0; i < n - 1; i++) {
            int fm, to, w;
            scanf("%lld%lld", &fm, &to); w = 1;
            insert(fm, to, w);
            root = fm;
        }
        GetCentro(-1, root);
        root = centroId[0];
        int ans = Split(root);
        printf("%lld\n", ans);
    }
    return 0;
}