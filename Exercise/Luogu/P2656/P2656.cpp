// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
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

// #define __DEBUG
#ifdef __DEBUG
#define debug(arg, args...) { printf("db <%d> ", __LINE__); writeln(arg, ##args); }
#else
#define debug(arg, args...) {}
#endif

const int maxn = 400004;
int n, m;
struct Edge {
    int u, v, w, q;
    bool re;
};
std::vector<Edge> G[maxn];

int cnt;
int dfn[maxn], low[maxn];
bool vis[maxn], in_stack[maxn];
std::stack<int> st;
std::vector<std::vector<int> > pot;
int pc[maxn];

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    vis[u] = true; in_stack[u] = true;
    st.push(u);
    for (auto e : G[u]) {
        if (!vis[e.v]) {
            tarjan(e.v);
            low[u] = std::min(low[u], low[e.v]);
        } else if (in_stack[e.v]) {
            low[u] = std::min(low[u], dfn[e.v]);
        }
    }
    if (dfn[u] == low[u]) {
        std::vector<int> v; v.clear();
        while (st.top() != u) {
            v.push_back(st.top());
            in_stack[st.top()] = 0;
            pc[st.top()] = pot.size() + 1;
            st.pop();
        }
        v.push_back(u);
        in_stack[st.top()] = 0;
        pc[st.top()] = pot.size() + 1;
        st.pop();
        // std::reverse(v.begin(), v.end());
        pot.push_back(v);
    }
}

int f[maxn], in[maxn];
int cnt1[maxn];
// bool vis1[maxn];
// void dfs1(int u, int id) {
//     if (vis1[u]) return;
//     vis1[u] = true;
//     for (auto e : G[u]) {
//         if (pc[e.v] == id) {
//             in[id]--;
//             dfs1(e.v, id);
//             while (e.w > 0) {
//                 cnt1[id] += e.w;
//                 e.w = e.w * e.q;
//             }
//         }
//     }
// }

std::vector<Edge> G2[maxn];

void bfs2(int s) {
    f[s] = cnt1[s];
    // writeln(f[s]);
    std::queue<int> q;
    // q.push(s);
    for (int i = 1; i <= pot.size(); i++) {
        if (in[i] == 0) q.push(i);
    }
    while (!q.empty()) {
        int ft = q.front(); q.pop(); // ft is ok in default
        for (auto e : G2[ft]) {
            f[e.v] = std::max(f[e.v], f[ft] + e.w + cnt1[e.v]);
            in[e.v]--;
            if (in[e.v] == 0) q.push(e.v);
        }
    }
}


int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int s;
    memset(pc, -1, sizeof(pc));
    memset(f, -63, sizeof(f));
    read(n, m);
    for (int i = 1; i <= m; i++) {
        static int u, v, w; static double q;
        read(u, v, w); scanf("%lf", &q);
        G[u].push_back({u, v, w, int(q * 10 + 0.0001), false});
        // in[v]++;
    }
    read(s);

    for (int i = 1; i <= n; i++) if (!vis[i]) tarjan(i);
    // for (auto v : pot) {
    //     if (v.size() == 1) {
    //         pc[v[0]] = v[0];
    //         continue;
    //     }
    //     int id = ++n;
    //     pc[id] = id;
    //     for (int q : v) {
    //         pc[q] = id;
    //         in[id] += in[q];
    //     }
    //     dfs1(v[0], id);
    //     for (int q : v) {
    //         for (auto e : G[q]) {
    //             if (pc[e.v] == id) continue;
    //             e.u = id;
    //             G[id].push_back(e);
    //         }
    //     }
    // }
    for (int i = 1; i <= n; i++) {
        for (auto e : G[i]) {
            if (pc[e.u] != pc[e.v]) {
                G2[pc[e.u]].push_back({pc[e.u], pc[e.v], e.w, e.q, e.re});
                in[pc[e.v]]++;
            } else {
                while (e.w > 0) {
                    cnt1[pc[e.u]] += e.w;
                    e.w = e.w * e.q;
                    e.w /= 10;
                }
            }
        }
    }

    // writeln(pc[s], in[pc[s]]);
    bfs2(pc[s]);
    // writeln(pot.size());
    int ans = 0;
    for (int i = 1; i <= pot.size(); i++) {
        ans = std::max(ans, f[i]);
        // writeln(f[i]);
    }
    writeln(ans);
    return 0;
}
