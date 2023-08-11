// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
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

#define int long long

const int maxn = 2e5 + 5;
int n, m;
int a[maxn];
std::vector<int> G[maxn];

// tarjan
int dfn[maxn], low[maxn], cnt = 0, scnt = 0, id[maxn];
int in[maxn];
std::vector<int> ssc[maxn];
std::stack<int> st;
void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    st.push(u); in[u] = true;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (in[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scnt++;
        while (st.top() != u) {
            ssc[scnt].push_back(st.top());
            id[st.top()] = scnt;
            in[st.top()] = false;
            st.pop();
        }
        ssc[scnt].push_back(st.top());
        id[st.top()] = scnt;
        in[st.top()] = false;
        st.pop();
    }
}

int s[maxn], mx[maxn];
std::vector<int> Gn[maxn];
bool vis[maxn];
int f[maxn], ffmax[maxn];
std::queue<int> q;

int ans = -1, max = -1;

void dp() {
    memset(f, -63, sizeof(f));
    memset(ffmax, -63, sizeof(ffmax));
    for (int i = 1; i <= scnt; i++) {
        if (!in[i]) {
            q.push(i), f[i] = s[i], ffmax[i] = mx[i];
            if (ans < f[i]) {
                ans = f[i];
                max = ffmax[i];
            } else if (ans == f[i]) {
                max = std::max(max, ffmax[i]);
            }
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : Gn[u]) {
            if (f[v] < f[u] + s[v]) {
                f[v] = f[u] + s[v];
                ffmax[v] = std::max(ffmax[u], mx[v]);
            } else if (f[v] == f[u] + s[v]) {
                ffmax[v] = std::max(ffmax[v], std::max(ffmax[u], mx[v]));
            }

            if (ans < f[v]) {
                ans = f[v];
                max = ffmax[v];
            } else if (ans == f[v]) {
                max = std::max(max, ffmax[v]);
            }

            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
}

signed main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= m; i++) {
        static int x, y;
        read(x, y);
        G[x].push_back(y);
    }

    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);

    memset(in, 0, sizeof(in));

    for (int i = 1; i <= scnt; i++) {
        for (int e : ssc[i]) {
            s[i] += a[e];
            mx[i] = std::max(mx[i], a[e]);
            for (int v : G[e]) {
                if (!vis[id[v]] && id[v] != i) {
                    vis[id[v]] = true;
                    Gn[i].push_back(id[v]);
                }
            }
        }
        // writeln(666, i, s[i], mx[i]);
        for (int v : Gn[i]) {
            // writeln(i, v);
            vis[v] = false;
            in[v]++;
        }
    }

    dp();

    writeln(ans, max);
    return 0;
}
