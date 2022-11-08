#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define min(x, y) ((x) < (y) ? (x) : (y))

struct uniSet {
    int fa[1000006];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    int fnd(int x) { 
        return fa[x] = (fa[x] != x ? fnd(fa[x]) : x);
    }

    void uni(int x, int y) {
        int fx = fnd(x), fy = fnd(y);
        if (fx != fy) {
            fa[fx] = fy;
        }
    }

    bool qry(int x, int y) {
        return fnd(x) == fnd(y);
    }
}us;

struct Edge {
    int from, to, id;
};

std::vector<Edge> edges[1000006];
bool fire[1000006];
bool vis[2000006];
int dis[1000006];
int len = 0;
std::queue<int> fq;

void insert(int from, int to) {
    len++;
    edges[from].push_back({from, to, len});
    edges[to].push_back({to, from, len});
}

int bfs() {
    int tot = 0, ans = 998244353;
    while (!fq.empty()) {
        tot++;
        int node = fq.front(); fq.pop();
        for (Edge e : edges[node]) {
            if (!vis[e.id]) {
                dis[e.to] = min(dis[e.to], dis[e.from] + 1);
                if (us.qry(e.to, e.from)) {
                    // printf("debug %d %d\n", e.from, e.to);
                    // if (fire[e.to]) node.second--;
                    ans = min(ans, dis[e.to]);
                } else {
                    us.uni(e.to, e.from);
                }
                if (!fire[e.to]) {
                    fire[e.to] = true;
                    fq.push(e.to);
                }
                vis[e.id] = true;
            }
        }
    }
    return ans == 998244353? -1 : ans;
}

#define gc getchar()
char ch, last = 'z';
template<typename T>
void read(T &r) {
    ch = gc, last = 'z'; r = 0;
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    if (last == '-') r = -r;
}

int main() {
    memset(dis, 63, sizeof(dis));
    int n, m, k;
    // scanf("%d%d%d", &n, &m, &k);
    read(n), read(m), read(k);
    us.init(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        // scanf("%d%d", &x, &y);
        read(x), read(y);
        insert(x, y);
    }
    for (int i = 0; i < k; i++) {
        int x;
        // scanf("%d", &x);
        read(x);
        fire[x] = true;
        dis[x] = 0;
        fq.push(x);
    }
    int ans = bfs();
    if (ans != -1) {
        // if (ans % 10 == 3 || ans % 10 == 2) {
        //     ans--;
        // }
        printf("%d\n", ans);
    } else {
        puts("Poor D!");
    }
    return 0;
}