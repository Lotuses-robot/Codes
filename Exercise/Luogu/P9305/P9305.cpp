#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

template<typename T>
void read(T &r) { r = 0; static char ch, last; ch = getchar(), last = 'z'; while (ch < '0' || ch > '9') last = ch, ch = getchar(); while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = getchar(); r = (last == '-') ? -r : r; }
template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { read(arg); read(arg_left...); }

template<typename T>
void write(T x) { if (x < 0) putchar('-'), x = -x; int len = 0; static char ch[100]; while (x) ch[++len] = x % 10 + '0', x /= 10; if (!len) ch[++len] = '0'; while (len) putchar(ch[len--]); }
template<typename T, typename...Ts>
void write(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); }
template<typename T>
void writeln(T x) { write(x); putchar('\n'); }
template<typename T, typename...Ts>
void writeln(T arg, Ts...arg_left) { write(arg); putchar(' '); write(arg_left...); putchar('\n'); }

const int maxn = 300005;
struct Edge {
    int u, v, m;
};
std::vector<Edge> G[maxn];
const int root = 1;
int lv[maxn], cnt = 0;
int cap[maxn][2];
int sub[maxn];
int sum[maxn][2];

void clear(int n) {
    for (int i = 1; i <= n + 3; i++) {
        G[i].clear();
    }
    memset(lv, 0, sizeof(int) * (n + 3));
    memset(cap, 0, sizeof(int) * (n + 3) * 2);
    memset(sub, 0, sizeof(int) * (n + 3) * 2);
    memset(sum, 0, sizeof(int) * (n + 3) * 2);
}

int sumInit(int u) {
    for (Edge e : G[u]) {
        sub[u] += e.m;
        sub[u] += sumInit(e.v);
    }
    return sub[u];
}

void init(int u, int l, int r) {
    sum[u][0] = l; sum[u][1] = r;
    if (G[u].empty()) {
        lv[++cnt] = u;
        cap[u][0] = cap[u][1] = -1;
        return;
    }
    int lc = 0, rc = sub[u] - (sub[G[u][0].v] + G[u][0].m);
    cap[u][0] = cnt + 1;
    for (int i = 0; i < G[u].size(); i++) {
        // printf("%d %d %d %d\n", l, lc, r, rc);
        init(G[u][i].v, l + lc, r + rc);
        if (i != G[u].size() - 1) {
            lc += sub[G[u][i].v] + G[u][i].m;
            rc -= sub[G[u][i + 1].v] + G[u][i + 1].m;
        }
    }
    cap[u][1] = cnt;
}

int calc(int leave, int rt) {
    return (sum[leave][0] - sum[rt][0]) - (sum[leave][1] - sum[rt][1]);
}

int query(int u) {
    if (cap[u][0] == -1) return 0;
    int l = cap[u][0], r = cap[u][1];
    while (r - l > 4) {
        int mid = (l + r) >> 1; int res = calc(lv[mid], u);
        if (res < 0) l = mid;
        else if (res > 0) r = mid;
        else {
            return 0;
        }
    }
    int lmin, rmin, last = 998244353;
    for (int i = l; i <= r; i++) {
        int res = calc(lv[i], u);
        if (res == 0) {
            return 0;
        }
        if (res > 0) {
            lmin = last;
            rmin = res;
            break;
        }
        last = res;
    }
    return std::min(abs(lmin), abs(rmin));
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T, k;
    read(T, k);

    while (T--) {
        int n;
        read(n);
        clear(n);
        for (int i = 1; i <= n; i++) {
            static int t;
            read(t);
            while (t--) {
                static int v, m;
                read(v, m);
                G[i].push_back({i, v, m});
            }
        }

        sumInit(1);
        init(1, 0, 0);

        if (k == 1) {
            writeln(query(1));
        } else {
            for (int i = 1; i <= n; i++) {
                write(query(i)); putchar(' ');
            }
            puts("");
        }
    }
    return 0;
}
