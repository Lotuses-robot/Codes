// Copyright 2023 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>

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

const int maxn = 1e6 + 10;
int n, m;
std::vector<int> G[maxn], v[maxn];

// id -> arrnk arrnk -> id
int rnk[maxn], id[maxn], num[maxn];
void mcs() {
    int cur = 0;
    for (int i = 1; i <= n; i++) v[0].push_back(i);
    for (int cnt = n; cnt >= 1; cnt--) {
        int x, f = 0;
        while (!f) {
            for (int i = (int)v[cur].size() - 1; i >= 0; i--) {
                x = v[cur][i];
                if (rnk[x]) v[cur].pop_back();
                else { f = 1; break; }
            }
            if (!f) cur--;
            assert(cur >= 0);
        }
        rnk[x] = cnt;
        id[cnt] = x;
        for (int w : G[x]) {
            if (!rnk[w]) {
                v[++num[w]].push_back(w);
                cur = std::max(cur, num[w]);
            }
        }

    }
}

bool cnn[maxn];
bool check() {
    std::vector<int> sub;
    for (int i = 1; i <= n; i++) {
        int x = id[i];
        sub.clear();
        for (int w : G[x]) {
            if (rnk[w] > rnk[x]) sub.push_back(w), cnn[w] = 0;
            if (sub.size() > 1 && rnk[sub.front()] > rnk[sub.back()]) std::swap(sub.front(), sub.back());
        }
        if (sub.empty()) continue;
        for (int w : G[sub.front()]) {
            cnn[w] = 1;
        }
        for (int w : sub) {
            if (w == sub.front()) continue;
            if (!cnn[w]) return false;
        }
    }
    return true;
}

void init() {
    memset(rnk, 0, sizeof(rnk));
    memset(id, 0, sizeof(id));
    memset(num, 0, sizeof(num));
    for (int i = 1; i <= n; i++) {
        G[i].clear();
        v[i].clear();
    }
}

int main() {
    #ifdef LOCAL
        freopen("data.in", "r", stdin);
        freopen("data.out", "w", stdout);
    #endif
    
    while (read(n, m), (n != 0 || m != 0)) {
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            read(u, v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        mcs();
        if (check()) {
            puts("Perfect");
        } else {
            puts("Imperfect");
        }
    }
    return 0;
}
