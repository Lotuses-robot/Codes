// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <iostream>

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

const int maxn = 2005;
int n, m, s, t;
struct Edge {
    int from, to;
    long long cap, flow;
};
std::vector<Edge> edges;
std::vector<int> G[maxn];
bool vis[maxn];
int cur[maxn];
long long w[maxn];

void init() {
    edges.clear();
    for (int i = 0; i < 1001; i++)
        G[i].clear();
}

void ins(int from, int to, long long w) {
    // writeln(from, to, w);
    edges.push_back((Edge){from, to, w, 0});
    edges.push_back((Edge){to, from, 0, 0});
    int t = edges.size();
    G[from].push_back(t - 2);
    G[to].push_back(t - 1);
}

bool BFS() {
    memset(vis, 0, sizeof(vis));
    memset(w, 0, sizeof(w));
    std::queue<int> q;
    vis[s] = 1;
    q.push(s);
    w[s] = 0;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        for (int i = 0; i < G[p].size(); i++) {
            Edge &e = edges[G[p][i]];
            if (!vis[e.to] && e.cap > e.flow) {
                vis[e.to] = true;
                w[e.to] = w[p] + 1;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}

long long DFS(int p, long long a) {
    if (a == 0 || p == t)
        return a;
    long long f, flow = 0;
    for (int &i = cur[p]; i < G[p].size(); i++) {
        Edge &e = edges[G[p][i]];
        if (w[e.to] == w[p] + 1 && (f = DFS(e.to, std::min(a, e.cap - e.flow))) > 0) {
            e.flow += f;
            flow += f;
            a -= f;
            edges[G[p][i] ^ 1].flow -= f;
            if (a == 0)
                break;
        }
    }
    return flow;
}

long long maxflow() {
    long long flow = 0;
    while (BFS()) {
        memset(cur, 0, sizeof(cur));
        flow += DFS(s, maxn * maxn);
    }
    return flow;
}

int p[maxn], c[maxn];
char ch[maxn];
bool v2[maxn];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int m1, n1, ss = 0;
    read(m1, n1);
    n = m1 + n1 + 2;

    for (int i = 1; i <= m1; i++) {
        read(p[i]); ss += p[i];
        memset(ch, 0, sizeof(ch));
        std::cin.getline(ch, maxn); int ulen = 0, tool;
        while (sscanf(ch + ulen, "%d", &tool) == 1) {
            ins(i, tool + m1, maxn * maxn);
            if (!tool) 
                ulen++;
            else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }

    s = n - 1; t = n;
    for (int i = 1; i <= m1; i++) {
        ins(s, i, p[i]);
    }
    for (int i = m1 + 1; i <= m1 + n1; i++) {
        read(c[i - m1]);
        ins(i, t, c[i - m1]);
    }
    int maxf = maxflow();
    for (int i = 1; i <= m1; i++) {
        if (w[i] > 0) write(i), putchar(' ');
    }
    puts("");
    for (int i = 1; i <= n1; i++) {
        if (w[i + m1] > 0) write(i), putchar(' ');
    }
    puts("");
    writeln(ss - maxf);
    return 0;
}