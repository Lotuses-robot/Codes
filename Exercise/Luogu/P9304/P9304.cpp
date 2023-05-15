#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>

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

#define maxn 100005

struct Edge {
    int u, v;
};
std::vector<Edge> G[maxn];
int dep[maxn];
std::vector<std::pair<int, int> > v;

void ins(int u, int v) {
    G[u].push_back({u, v});
    G[v].push_back({v, u});
}

void dfs(int u, int fa) {
    bool hvSon = false;
    dep[u] = dep[fa] + 1;
    for (Edge e : G[u]) {
        if (e.v != fa) {
            dfs(e.v, u);
            hvSon = true;
        }
    }
    if (!hvSon) {
        v.push_back({dep[u], u});
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        read(u, v);
        ins(u, v);
    }
    dfs(1, 1);
    std::sort(v.begin(), v.end(), std::greater<std::pair<int, int>>());
    int maxd = v.begin() -> first;
    for (int i = 1; i <= n; i++) {
        if (i - 1 <= maxd - 1) {
            printf("%d\n", i - 1);
        } else {
            printf("%d\n", 2 * (i - 1) - maxd + 1);
        }
    }
    return 0;
}
