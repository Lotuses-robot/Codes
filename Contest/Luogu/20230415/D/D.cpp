#include <cstdio>
#include <cstring>
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

#define maxn 200040
#define maxm 400040

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
        nd[st.top()] = sz;
        in_stack[st.top()] = false;
        st.pop();
    }
}

int allstatus;
int status[maxn];
bool full0, mem[maxn];

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
        return status[u] = -1;
    }
}

void init2() {
    full0 = true;
    for (int i = 1; i <= n + 10; i++) {
        rebuild[i].clear();
        rever[i].clear();
    }
    for (int i = 1; i <= sz + 100; i++) {
        ssc[i].clear();
    }
    tm = 0; sz = 0;
    for (int i = 1; i <= n + 10; i++) {
        edges[i].clear();
    }
    memset(low, 0, sizeof(int) * (n + 10));
    memset(dfn, 0, sizeof(int) * (n + 10));
    memset(nd, 0, sizeof(int) * (n + 10));
    memset(status, 0, sizeof(int) * (n + 10));
    memset(mem, 0, sizeof(bool) * (n + 10));
    allstatus = 0;
}

int in[maxn];
std::vector<int> L;
std::queue<int> S;

bool toposort() {
    L.clear();
    for (int i = 1; i <= sz; i++)
        if ((in[i] = rever[i].size()) == 0) S.push(i);
    while (!S.empty()) {
        int u = S.front();
        S.pop();
        if (!mem[u]) L.push_back(u), mem[u] = true;
        for (auto v : rebuild[u]) {
            if (--in[v.v] == 0) {
                S.push(v.v);
            }
        }
    }
    memset(mem, 0, sizeof(bool) * (n + 10));
    if (L.size() == sz) {
        return true;
    } else {
        return false;
    }
}

bool search(int u) {
    mem[u] = true;
    for (Edge e : rebuild[u]) {
        if (dd(e.v) == 0) {
            return false;
        }
        bool res = search(e.v);
        if (!res) return false;
            // return true;
    }
    return true;
}

int main() {
    #ifdef LOCAL
        freopen("hack/5.in", "r", stdin);
        freopen("hack/5.out", "w", stdout);
    #endif
    
    int T;
    read(T);
    while (T--) {
        read(n, m);
        init2();
        for (int i = 1; i <= n; i++) {
            read(color[i]);
            full0 &= (color[i] == 0);
        }
        for (int i = 1; i <= m; i++) {
            static int u, v;
            read(u, v);
            edges[u].push_back({u, v});
        }

        if (full0) {
            putchar('B');
            continue;
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

        if (sz == 2 && (dd(1) == 1 && dd(2) == 0 && rebuild[2].size() == 0 && rebuild[1].size() != 0 || 
                        dd(2) == 1 && dd(1) == 0 && rebuild[1].size() == 0 && rebuild[2].size() != 0)) { // 1 -> 0 
            putchar('B');
            continue;
        }

        if (sz == 2 && rebuild[1].size() == 0 && rebuild[2].size() == 0 && dd(1) == 1 && dd(2) == 1) {
            putchar('B');
            continue;
        }

        bool res = toposort();
        if (!res) {
            puts("fuck you bitch");
            return 0;
        }

        bool flag = false, ans = true;
        for (int u : L) {
            if (dd(u) == -1) {
                ans = false;
                break;
            }
            if (dd(u) == 1 && !mem[u]) {
                if (!flag) {
                    if (!search(u)) {
                        ans = false;
                        break;
                    } else {
                        flag = true;
                    }
                } else {
                    ans = false;
                    break;
                }
            }
        }

        if (ans) {
            putchar('A');
        } else {
            putchar('N');
        }

        // if (rand() % 10 > 3) {
        //     putchar('N');
        // } else {
        //     putchar('A');
        // }

    }
    return 0;
}