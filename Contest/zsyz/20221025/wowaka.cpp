// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <set>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

#define maxn 100005

#define siter std::set<int>::iterator

int n, fa[maxn], cnt;
std::queue<std::pair<int, int> > q;
std::set<int> G1[maxn], G2[maxn];

int find(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

void init(int n) {
    for (int i = 0; i <= n; i++) {
        G1[i].clear();
        G2[i].clear();
    }
    for (int i = 0; i <= n; i++)
        fa[i] = i;
}

int main() {
    freopen("wowaka.in", "r", stdin);
    freopen("wowaka.out", "w", stdout);
    int T;
    read(T);
    while (T--) {
        read(n);
        init(n);
        for (int i = 1; i < n; i++) {
            int u, v;
            read(u, v);
            G1[u].insert(v);
            G1[v].insert(u);
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G2[u].insert(v);
            G2[v].insert(u);
            if (G1[u].find(v) != G1[u].end())
                q.push(std::pair<int, int>(u, v));
        }
        while (!q.empty()) {
            int u = q.front().first, v = q.front().second;
            q.pop();
            u = find(u), v = find(v);
            if (u == v)
                continue;
            if (G1[u].size() + G2[u].size() > G1[v].size() + G2[v].size())
                std::swap(u, v);
            fa[u] = v;
            G1[u].erase(v);
            G1[v].erase(u);
            G2[u].erase(v);
            G2[v].erase(u);
            for (siter it = G1[u].begin(); it != G1[u].end(); it++) {
                int x = *it;
                G1[x].erase(u);
                G1[x].insert(v);
                G1[v].insert(x);
                if (G2[x].find(v) != G2[x].end())
                    q.push(std::pair<int, int>(x, v));
            }
            for (siter it = G2[u].begin(); it != G2[u].end(); it++) {
                int x = *it;
                G2[x].erase(u);
                G2[x].insert(v);
                G2[v].insert(x);
                if (G1[x].find(v) != G1[x].end())
                    q.push(std::pair<int, int>(x, v));
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n; i++)
            if (find(i) == i)
                cnt++;
        printf("%s\n", cnt == 1 ? "YES" : "NO");
    }
}
