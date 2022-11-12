// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

struct Edge {
    int from, to;
};

std::vector<Edge> G[1145141];
bool vis[1145141];
int   id[1145141];
int  tot;

void dfs(int nowpt) {
    vis[nowpt] = true;
    id[nowpt] = ++tot;
    for (int i = 0; i < G[nowpt].size(); i++) {
        if (!vis[G[nowpt][i].to]) {
            dfs(G[nowpt][i].to);
        }
    }
}

int main() {
    int n;
    read(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        read(x, y);
        G[x].push_back({x, y});
        G[y].push_back({y, x});
    }

    dfs(1);

    for (int i = 1; i <= n; i++) {
        printf("%d ", id[i]);
    }
    return 0;
}
