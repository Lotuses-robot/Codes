#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>

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

#define maxn 200005
#define maxm 400005

struct Edge {
    int u, v;
};
std::vector<Edge> edges[maxn];
std::vector<Edge> rebuild[maxn];
std::vector<Edge> rever[maxn];
int n, m;
int color[maxn];

int dfn[maxn], low[maxn], tm = 0;
int nd[maxn], sz = 0;
std::vector<int> ssc[maxn];
bool in_stack[maxn];
std::stack<int> st;
void tarjan(int u) {
    dfn[u] = low[u] = ++tm;
    st.push(u); in_stack[u] = true;
    for (Edge e : edges[u]) {
        if (!dfn[e.v]) {
            tarjan(e.v);
            low[u] = std::min(low[e.v], low[u]);
        } else if (in_stack[e.v]) {
            low[u] = std::min(dfn[e.v], low[u]); 
        }
    }
    if (low[u] == dfn[u]) {
        ++sz;
        while (st.top() != u) {
            ssc[sz].push_back(st.top());
            nd[st.top()] = sz;
            in_stack[st.top()] = false;
            st.pop();
        }
        ssc[sz].push_back(st.top());
        in_stack[st.top()] = false;
        nd[st.top()] = sz;
        st.pop();
    }
}

int allstatus;

int status[maxn];
int dd(int u) {
    if (status[u]) return status[u];
    int sum = 0;
    for (int i : ssc[u]) {
        sum += color[i];
    }
    if (sum == ssc[u].size()) {
        return status[u] = 1;
    } else if (sum == 0) {
        return status[u] = 0;
    } else {
        return status[u] = 2;
    }
}

std::vector<int> vis;
bool f[maxn];
bool full0;

bool dfs1(int u, int fa) {
    full0 &= (!(bool)dd(u));
    vis.push_back(u);
    if (dd(u) == 3) { allstatus = -1; return false; }
    // if (dd(u) == 2 && f[fa] == 1) return false;
    if (dd(u) != 0 && f[fa] == 0) { allstatus = -1; return false; }
    f[u] = f[fa] && dd(u);

    for (Edge e : rever[u]) {
        if (e.v != fa) {
            bool ref = dfs1(e.v, u);
            if (!ref) return false;
        }
    }
    return true;
}

void init() {
    for (int i = 1; i <= n + 100; i++) {
        rever[i].clear();
    }
    memset(low, 0, sizeof(int) * (n + 10));
    memset(dfn, 0, sizeof(int) * (n + 10));
    memset(nd, 0, sizeof(int) * (n + 10));
    memset(status, 0, sizeof(int) * (n + 10));
    memset(f, 0, sizeof(bool) * (n + 10));
    allstatus = 0;
}

void init2() {
    for (int i = 1; i <= n + 10; i++) {
        edges[i].clear();
        rebuild[i].clear();
    }
    for (int i = 1; i <= sz + 100; i++) {
        ssc[i].clear();
    }
    tm = 0; sz = 0;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n, m);
        init2();
        for (int i = 1; i <= n; i++) {
            read(color[i]);
        }
        for (int i = 1; i <= m; i++) {
            static int u, v;
            read(u, v);
            edges[u].push_back({u, v});
        }

        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) tarjan(i);
        }
        
        for (int i = 1; i <= sz; i++) {
            for (int u : ssc[i]) {
                for (Edge e : edges[u]) {
                    if (nd[e.v] != i) rebuild[i].push_back({i, nd[e.v]}),
                                      rever[nd[e.v]].push_back({nd[e.v], i});
                }
            }
        }

        init();

        bool down = 0; int need = 0, b_maybe_can_win = 0; full0 = true;
        for (int i = 1; i <= sz; i++) {
            if (rebuild[i].size() == 0) {
                vis.clear();
                f[i] = dd(i);
                need += f[i];
                dfs1(i, i);
                if (vis.size() == 2 && dd(vis[0]) == 0 && dd(vis[1]) == 1) {
                    b_maybe_can_win++;
                    // allstatus = 0;
                }
                // if (allstatus == 1) {
                //     if (down) {
                //         allstatus = -1;
                //         break;
                //     } else {
                //         down = true;
                //         allstatus = 0;
                //     }
                // }
                if (allstatus < 0) {
                    break;
                }
            }
        }

        if (sz == 2) {
            if (rebuild[1].size() == 0 && rebuild[1].size() == 0 && f[1] == 1 && f[2] == 1) {
                putchar('B');
                continue;
            }
        }

        if (allstatus == -1) {
            putchar('N');
            continue;
        }

        if (full0 || b_maybe_can_win == 1 && sz == 1) {
            putchar('B');
            continue;
        }

        if (need == 1) {
            putchar('A');
            continue;
        }

        putchar('N');
    }
    return 0;
}
