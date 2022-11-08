#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using std::map;

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
bool flag[maxn];
int weight[maxn];
int size[maxn];
int centroId[2];
void GetCentroid(int fa, int cur, int n) {
    size[cur] = 1;
    weight[cur] = 0;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        GetCentroid(cur, e.to, n);
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
void GetCentroid(int fa, int cur) {  // maintain
    memset(weight, 0, sizeof(weight));
    memset(size, 0, sizeof(size));
    memset(centroId, 0, sizeof(centroId));
    int sz = GetSize(fa, cur);
    GetCentroid(fa, cur, sz);
}

int Dist[maxn], distLen = 0;
void DfsDist(int fa, int dist, int cur) {
    Dist[distLen++] = dist;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        DfsDist(cur, dist + e.w, e.to);
    }
}

vector<int> queris;
map<int, int> mp;

int Calc(int cur, int initDist) {
    distLen = 0;
    DfsDist(-1, initDist, cur);
    for (int i = 0; i < queris.size(); i++) {
        if (flag[i]) continue;
        for (int k = 0; k < distLen; k++) {
            if (mp.count(queris[i] - Dist[k])) {
                flag[i] = true;
                break;
            }
        }
    }
    for (int k = 0; k < distLen; k++) {
        mp[Dist[k]] = 1;
    }
    return 0;
}

int Split(int cur) {
    mp.clear(); mp[0] = 1;
    int ans = 0; vis[cur] = true;
    for (auto e : G[cur]) {
        if (vis[e.to]) continue;
        Calc(e.to, e.w);
    }
    for (auto e : G[cur]) {
        if (vis[e.to]) continue;
        GetCentroid(e.from, e.to);
        Split(centroId[0]);
    }
    return ans;
}

void init() {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < maxn; i++) G[i].clear();
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        int root;
        for (int i = 0; i < n; i++) {
            int q;
            while (~scanf("%d", &q) && q) {
                int w; q--;
                scanf("%d", &w);
                insert(i, q, w);
            }
        }
        queris.clear();
        memset(flag, 0, sizeof(flag));
        while (scanf("%d", &k) && k) {
            queris.push_back(k);
        }
        Split(0);

        for (int i = 0; i < queris.size(); i++) {
            if (flag[i]) {
                puts("AYE");
            } else {
                puts("NAY");
            }
        }
        puts(".");
    }
    return 0;
}