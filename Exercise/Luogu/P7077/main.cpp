// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define int long long

// Fast Read
#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}
// End Fast Read

// Var Define
int n, m, q;
int ysum;
int data[100005];
int T[100005];
std::pair<int, int> T1[1000005];
int T2[1000005];
int cnt[1000005];
bool vis[1000005];
struct Edge {
    int from, to;
};
std::vector<Edge> G1[100005];
std::vector<Edge> G2[100005];
const int mod = 998244353;
// End Var Define

// Function Define
int dfs1(int pt) {
    // printf("duuugeg %lld %lld\n", pt, T[pt]);
    if (T[pt] == 2) { return T2[pt]; }
    if (T[pt] == 1) { return T2[pt] = 1; }
    if (T2[pt] || vis[pt]) { return T2[pt]; }
    int ans = 1;
    for (Edge e : G1[pt]) {
        ans *= dfs1(e.to);
        ans %= mod;
    }
    // printf("debuuugg %lld %lld\n", pt, ans);
    vis[pt] = true;
    return T2[pt] = ans;
}

int deg[100005];

void bfs2() {
    std::queue<int> q;
    for (int i = 0; i <= m; i++) {
        deg[i] = G2[i].size();
        if (!deg[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop(); // NOLINT
        // printf("init %lld %lld\n", u, cnt[u]);
        int nowmul = 1;
        for (int i = G1[u].size() - 1; i >= 0; i--) {
            Edge e = G1[u][i];
            cnt[e.to] = (cnt[e.to] + cnt[u] * nowmul) % mod;
            nowmul = nowmul * T2[e.to] % mod;
            deg[e.to]--;
            // printf("dev %lld %lld %lld\n", e.to, cnt[e.to], nowmul);
            if (!deg[e.to]) q.push(e.to);
        }
    }
}
// End Function Define

signed main() {
    // freopen("call/call10.in", "r", stdin);
    // freopen("call.out", "w", stdout);
    read(n);
    for (int i = 0; i < n; i++) {
        read(data[i]);
    }
    read(m);
    for (int i = 1; i <= m; i++) {
        read(T[i]);
        if (T[i] == 1) {
            read(T1[i].first, T1[i].second);
            T1[i].first--;
        } else if (T[i] == 2) {
            read(T2[i]);
        } else {
            static int c, g;
            read(c);
            for (int j = 0; j < c; j++) {
                read(g);
                G1[i].push_back({i, g});
                G2[g].push_back({g, i});
            }
        }
    }

    read(q);
    for (int i = 0; i < q; i++) {
        static int f;
        read(f);
        G1[0].push_back({0, f});
        G2[f].push_back({f, 0});
    }
    T[0] = 3;
    cnt[0] = 1;

    dfs1(0);
    bfs2();

    for (int i = 0; i < n; i++) data[i] = data[i] * T2[0] % mod;
    // printf("debug %lld\n", T2[0]);
    for (int i = 0; i <= m; i++) {
        if (T[i] == 1) {
            // printf("debug %lld %lld %lld\n", T1[i].first, T1[i].second, cnt[i]);
            data[T1[i].first] = data[T1[i].first] + T1[i].second * cnt[i];
            data[T1[i].first] %= mod;
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%lld ", data[i]);
    }
    puts("");
    return 0;
}
