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

int a[100005];
std::vector<Edge> G[100005];
// from 0 ~ 2 ^ k
int fa[100005][30];
bool vis[100005];
int dep[100005];

int fat[100005];

// init fa
void dfs1(int pt, int f) {
    vis[pt] = true;
    fat[pt] = f;
    if (f == -1) {
        fa[pt][0] = -1;
        dep[pt] = 0;
    } else {
        dep[pt] = dep[f] + 1;
        while (a[pt] >= a[f]) {
            int ck = 0;
            while (fa[f][ck] != -1 && a[fa[f][ck]] <= a[f]) ck++;
            // printf("debug %d\n", ck);
            if (ck < 0) break;
            f = fa[f][ck];
            if (f == -1) break;
        }
        fa[pt][0] = f;
    }
    for (int i = 1; i <= 20; i++) {
        if (fa[pt][i - 1] == -1) {
            fa[pt][i] = -1;
        } else {
            fa[pt][i] = fa[fa[pt][i - 1]][i - 1];
        }
    }

    for (Edge e : G[pt]) {
        if (!vis[e.to]) dfs1(e.to, pt);
    }
}

int main() {
    // freopen("data/2.in", "r", stdin);
    // freopen("squirrel.out", "w", stdout);

    int n, q;
    read(n, q);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        int f, t;
        read(f, t);
        G[f].push_back({f, t});
        G[t].push_back({t, f});
    }

    dfs1(1, -1);

    // int pt = 549;
    // while (pt != 525) {
    //     printf("%d %d %d %d %d\n", pt, a[pt], fa[pt][0], fa[pt][1], fa[pt][2]);
    //     pt = fat[pt];
    // }
    // printf("%d %d %d %d %d\n", pt, a[pt], fa[pt][0], fa[pt][1], fa[pt][2]);


    while (q--) {
        int u, v, c;
        read(u, v, c);
        // first step
        // printf("%d: ", u);
        while (a[u] <= c) {
            int ck = 0; bool pd = 0;
            while (fa[u][ck] != -1 && a[fa[u][ck]] <= c && dep[fa[u][ck]] >= dep[v]) ck++;
            // printf("debug %d %d\n", ck, fa[u][ck]);
            if (dep[fa[u][ck]] < dep[v]) ck--, pd = 1;
            if (pd && ck < 0) {
                // printf("debug %d\n", fa[u][ck]);
                u = -1;
                break;
            }
            if (a[fa[u][ck]] > c) ck--;
            if (ck < 0) {
                u = fa[u][0];
                break;
            }
            u = fa[u][ck];
            // printf("heyeyeyy: %d %d\n", a[u], c);
            if (u == -1) break;
        }
        if (u == -1) {
            puts("0");
            continue;
        }
        // printf("%d ", u);
        // puts("First Step Finished");

        int ans = 1;
        while (u != v) {
            int ck = 0;
            while (fa[u][ck] != -1 && dep[fa[u][ck]] >= dep[v]) ck++;
            // printf("%d\n", fa[u][ck]);
            // printf("%d\n", ck);
            if (dep[fa[u][ck]] < dep[v]) ck--;
            if (fa[u][ck] == -1) ck--;
            if (ck < 0) break;
            u = fa[u][ck];
            ans += 1 << ck;
            // printf("debug %d %d %d\n", u, ans, ck);
        }
        printf("%d\n", ans);
    }
    return 0;
}
