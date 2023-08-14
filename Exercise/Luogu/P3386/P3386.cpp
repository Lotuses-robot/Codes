// Copyright 2023 Lotuses
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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif


const int maxn = 10001, maxm = 10001;
int match[maxn];
bool vis[maxn];
int left, right, e;
std::vector<int> G[maxn];

bool dfs(int u) {
    for (int i : G[u]) {
        if (!vis[i]) {
            vis[i] = 1;
            if (match[i] == 0 || dfs(match[i])) {
                match[i] = u;
                return true;
            }
        }
    }
    return false;
}

int hagarian() {
    int ans = 0;
    for (int i = 1; i <= left; ++i) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) ++ans;
    }
    return ans;
}

int main(){
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    scanf("%d %d %d", &left, &right, &e);
    for (int i = 1; i <= e; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v + left);
        G[v + left].push_back(u);
    }
    printf("%d", hagarian());
    return 0;
}