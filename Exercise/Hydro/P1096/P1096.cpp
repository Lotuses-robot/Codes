#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

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

const int maxn = 1e5 + 5;

int c[maxn][5];

struct Edge {
    int u, v;
};
std::vector<Edge> edges[maxn];
std::vector<int> ans;

void ins(int u, int v) {
    edges[u].push_back({u, v});
    edges[v].push_back({v, u});
}

int main(int argc, char *argv[]) {
    std::string s = argv[1];
    #ifdef LOCAL
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    #endif

    int n, m;
    read(n, m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        read(u, v);
        ins(u, v);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 4; j++) {
            c[i][j] = true;
        }
    }

    for (int i = 1; i <= n; i++) {
        int j;
        for (j = 1; j <= 4; j++) {
            if (c[i][j]) break;
        }
        ans.push_back(j);
        for (Edge e : edges[i]) {
            c[e.v][j] = false;
        }
    }

    for (int v : ans) {
        write(v);
    }
    puts("");
    return 0;
}
