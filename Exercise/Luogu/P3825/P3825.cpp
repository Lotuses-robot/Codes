// Copyright 2023 Lotuses
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <stack>
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

const int maxn = int(5e4 + 5) << 2, maxm = 1e5 + 5;
int n, m, d;
char ch[maxn];
int conv(int id, char c) {
    switch(ch[id]) {
        case 'a':
            return id + (c == 'C') * n;
        case 'b':
            return id + (c == 'C') * n;
        case 'c':
            return id + (c == 'B') * n;
    }
    return -1;
}
struct rule {
    int i, hi, j, hj;
} r[maxm];

std::vector<int> G[maxn];

int inv(int x) {
    if (x > n) return x - n;
    else return x + n;
}

void ins(int u, int v) {
    // std::swap(u,v);
    G[u].push_back(v);
}

int dfn[maxn], low[maxn], id[maxn], cnt, scnt;
std::vector<int> ssc[maxn];
bool inss[maxn];
std::stack<int> st;
void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    st.push(u); inss[u] = true;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (inss[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scnt++;
        while (st.top() != u) {
            id[st.top()] = scnt;
            inss[st.top()] = false;
            // ssc[scnt].push_back(st.top());
            st.pop();
        }
        id[st.top()] = scnt;
        inss[st.top()] = false;
        // ssc[scnt].push_back(st.top());
        st.pop();
    }
}

void init() {
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(id, 0, sizeof(id));
    memset(inss, 0, sizeof(inss));
    // for (int i = 1; i <= scnt; i++) {
    //     ssc[i].clear();
    // }
    cnt = scnt = 0;
    while (!st.empty()) st.pop();
    for (int i = 0; i <= 2 * n; i++) {
        G[i].clear();
    }
}

void work() {
    init();
    // puts("666");
    for (int i = 1; i <= m; i++) {
        if (ch[r[i].i] == tolower(r[i].hi)) continue;
        int cvi = conv(r[i].i, r[i].hi), cvj = conv(r[i].j, r[i].hj);
        // writeln(666, cvi, cvj, i, r[i].i, r[i].j);
        if (ch[r[i].j] == tolower(r[i].hj)) {
            ins(cvi, inv(cvi));
            // writeln(1, cvi, inv(cvi));
        } else {
            ins(cvi, cvj);
            ins(inv(cvj), inv(cvi));
            // writeln(2, cvi, cvj);
            // writeln(2, inv(cvj), inv(cvi));
        }
    }
    for (int i = 1; i <= 2 * n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++) {
        if (id[i] == id[i + n]) {
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        switch(ch[i]) {
            case 'a':
                if (id[i] < id[i + n]) {
                    putchar('B');
                } else {
                    putchar('C');
                }
                break;
            case 'b':
                if (id[i] < id[i + n]) {
                    putchar('A');
                } else {
                    putchar('C');
                }
                break;
            case 'c':
                if (id[i] < id[i + n]) {
                    putchar('A');
                } else {
                    putchar('B');
                }
        }
    }
    exit(0);
}

void dfs(int u) {
    if (u == n + 1) {
        work();
        return;
    }
    if (ch[u] == 'x') {
        writeln(u, 1);
        ch[u] = 'a';
        dfs(u + 1);
        writeln(u, 2);
        ch[u] = 'b';
        dfs(u + 1);
    } else {
        dfs(u + 1);
    }
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    char ch1[3], ch2[3];
    read(n, d);
    scanf("%s", ch + 1);
    read(m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %s %d %s", &r[i].i, ch1, &r[i].j, ch2);
        r[i].hi = ch1[0];
        r[i].hj = ch2[0];
    }

    dfs(1);
    puts("-1");
    return 0;
}
