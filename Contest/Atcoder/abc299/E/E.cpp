#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

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

int n, m;
int k;
struct Edge {
    int u, v;
};
std::vector<Edge> edges[2003];
std::vector<std::pair<int, int> > v;

int needBlack[2003];
int needWhite[2003];
std::vector<int> needBlackv[2003];
std::vector<int> xv;
char color[2003];

void insert(int u, int v) {
    edges[u].push_back((Edge){u, v});
    edges[v].push_back((Edge){v, u});
}

int low, x;
std::queue<std::pair<int, int> > q;
bool vis[2003];
void bfs(int cur) {
    memset(vis, 0, sizeof(vis));
    q.push({cur, 0});
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int u = p.first, d = p.second;
        if (d < low) {
            needWhite[u] = 1;
        } else if (d == low) {
            needBlack[u] = 1;
            needBlackv[x].push_back(u);
            continue;
        }
        for (auto e : edges[u]) {
            int v = e.v;
            if (vis[v]) continue;
            vis[v] = true;
            q.push({v, d + 1});
        }
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) {
        color[i] = '0';
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        insert(u, v);
    }

    read(k);
    for (int i = 1; i <= k; i++) {
        read(x, low);
        bfs(x);
        xv.push_back(x);
    }

    for (int i = 1; i <= k; i++) {
        bool flag = false;
        for (int u : needBlackv[xv[i - 1]]) {
            if (needWhite[u]) continue;
            flag = true;
            color[u] = '1';
            break;
        }
        if (!flag) {
            puts("No");
            return 0;
        }
    }

    bool flag = false;
    for (int i = 1; i <= n; i++) {
        if (color[i] == '1') {
            flag = true;
            break;
        }
    }

    bool success = false;

    if (!flag) {
        for (int i = 1; i <= n; i++) {
            if (!needWhite[i]) {
                color[i] = '1';
                success = true;
                break;
            }
        }
        if (!success) {
            puts("No");
            return 0;
        }
    }

    puts("Yes");
    printf("%s\n", color + 1);
    return 0;
}
