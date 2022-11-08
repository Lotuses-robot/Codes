#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
// #pragma comment(linker,"/STACK:102400000,102400000")
#pragma GCC optimize(2)

#define int long long

using std::vector;
using std::queue;

struct Edge {
    int from, to;
};

#define MOD 1000003
#define maxn 100005
vector<Edge> G[maxn];
int val[maxn];
int inv[maxn];
queue<int> q_for_G;

void insert(int from, int to) {
    G[from].push_back({from, to});
    G[to].push_back({to, from});
    // q_for_G.push(from);
    // q_for_G.push(to);
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
    // memset(weight, 0, sizeof(weight));
    // memset(size, 0, sizeof(size));
    memset(centroId, 0, sizeof(centroId));
    int sz = GetSize(fa, cur);
    GetCentroid(fa, cur, sz);
}

int Dist[maxn], distLen = 0;
int invDist[maxn];
int point[maxn];
void DfsDist(int fa, int dist, int invdist, int cur) {
    Dist[distLen] = dist;
    invDist[distLen] = invdist;
    point[distLen] = cur;
    distLen++;
    for (auto e : G[cur]) {
        if (e.to == fa || vis[e.to]) continue;
        DfsDist(cur, dist * val[e.to] % MOD, invdist * inv[e.to] % MOD, e.to);
    }
}

vector<std::pair<int, int> > Ans;
// map<int, int> mp;
queue<int> q;

int mp[MOD + 6];

#define min(a, b) ((a) < (b) ? (a) : (b))

int Calc(int cur, int fa) {
    distLen = 0;    
    DfsDist(-1, val[cur], inv[cur], cur);
    for (int kk = 0; kk < distLen; kk++) {
            // if (mp.count(queris[i] - Dist[k])) {
        // printf("debug %d %d %d %d %d\n", cur, k, inv[cur], invDist[kk], );
        if (mp[k * inv[fa] % MOD * invDist[kk] % MOD]) { // need change
            // if (k * val[cur] % MOD * invDist[kk] % MOD != 1) {
            if (mp[k * inv[fa] % MOD * invDist[kk] % MOD] == -1) {
                Ans.push_back(std::make_pair(0, point[kk]));
            } else {
                Ans.push_back(std::make_pair(mp[k * inv[fa] % MOD * invDist[kk] % MOD], point[kk]));
            }
            // }
        }
    }
    for (int kk = 0; kk < distLen; kk++) {
        mp[Dist[kk]] = min(mp[Dist[kk]], point[kk]);
        if (!mp[Dist[kk]]) {
            mp[Dist[kk]] = point[kk];
            q.push(Dist[kk]);
        }
    }
    return 0;
}

void Split(int cur) {
    while (!q.empty()) {
        mp[q.front()] = 0;
        q.pop();
    }
    q.push(1);
    mp[1] = cur == 0 ? -1 : cur;
    vis[cur] = true;
    for (auto e : G[cur]) {
        if (vis[e.to]) continue;
        Calc(e.to, cur);
    }
    for (auto e : G[cur]) {
        if (vis[e.to]) continue;
        GetCentroid(e.from, e.to);
        Split(centroId[0]);
    }
}

void init() {
    Ans.clear();
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < maxn; i++) G[i].clear();
    // while (!q_for_G.empty()) {
    //     G[q_for_G.front()].clear();
    //     q_for_G.pop();
    // }
}

int PowMod(int a, int qq, int mod) {
    int ret = 1;
    while(qq) {
        if(qq & 1) ret = ret * a % mod;
        a = a * a % mod;
        qq >>= 1;
    }
    return ret;
}

int FermatInv(int a) {
    return PowMod(a, MOD - 2, MOD);
}

signed main() {
    // freopen("4812.in", "r", stdin);
    // freopen("4812.out", "w", stdout);
    // 1. input
    while (~scanf("%lld%lld", &n, &k) && n) { // k maybe is 0
        init();
        for (int i = 0; i < n; i++) {
            scanf("%lld", &val[i]);
            inv[i] = FermatInv(val[i]);
        }
        for (int i = 0; i < n - 1; i++) {
            static int x, y;
            scanf("%lld%lld", &x, &y);
            insert(x - 1, y - 1); // from 0 start
        }
        Split(0);
        if (Ans.size() == 0) {
            puts("No solution");
            continue;
        }
        for (auto &u : Ans) {
            if (u.first > u.second) {
                std::swap(u.first, u.second);
            }
            u.first++;
            u.second++;
        }
        std::sort(Ans.begin(), Ans.end());
        printf("%lld %lld\n", Ans[0].first, Ans[0].second);
    }
    return 0;
}