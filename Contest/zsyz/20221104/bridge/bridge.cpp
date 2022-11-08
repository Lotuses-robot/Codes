// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define int long long

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
    int from, to, w;
    bool operator < (Edge b) const {
        return w < b.w;
    }
};

std::vector<Edge> G;

int f[200005];
int mxx[100005][2];

signed main() {
    int n, m, u, v, w;
    read(n, m);

    for (int i = 0; i < m; i++) {
        read(u, v, w);
        G.push_back({u, v, w});
        G.push_back({v, u, w});
    }
    std::sort(G.begin(), G.end());

    memset(mxx, -1, sizeof(mxx));
    int ans = 1;
    for (int i = 0; i < m * 2; i++) {
        f[i] = 1;
        // for (int j = 0; j < i; j++) {
            // if (G[i].w == G[j].w) break;
            // if (G[i].from == G[j].to && G[i].w != G[j].w) {
            //     f[i] = std::max(f[j] + 1, f[i]);
            // }
        // }

        if (mxx[G[i].from][0] != -1 && G[i].w != G[mxx[G[i].from][0]].w) {
            f[i] = std::max(f[i], f[mxx[G[i].from][0]] + 1);
        }
        if (mxx[G[i].from][1] != -1 && G[i].w != G[mxx[G[i].from][1]].w) {
            f[i] = std::max(f[i], f[mxx[G[i].from][1]] + 1);
        }

        int &id = mxx[G[i].to][0];
        if (id == -1) {
            id = i;
        } else {
            if (G[id].w == G[i].w) {
                if (f[i] > f[id]) {
                    id = i;
                }
            } else {
                if (mxx[G[i].to][1] == -1 || f[id] > f[mxx[G[i].to][1]]) {
                    mxx[G[i].to][1] = id;
                    id = i;
                } else {
                    id = i;
                }
            }
        }

        // printf("debug %d %d %d %d\n", i, f[i], G[i].from, G[i].to);
        ans = std::max(ans, f[i]);

    }
    printf("%lld\n", ans);
    return 0;
}
