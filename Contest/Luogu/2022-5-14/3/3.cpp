#include <cstdio>
#include <vector>
#include <algorithm>

struct Edge {
    int from, to;

    bool operator == (Edge b) const {
        return from == b.from && to == b.to;
    }
};
std::vector<Edge> edges[4000006];
int n, m;

void insert(int from, int to) {
    edges[from].push_back({from, n + to});
    edges[n + to].push_back({n + to, from});
    // printf("debug0 %d %d\n", from, n + to);
    // printf("debug0 %d %d\n", n + to, from);
}

bool find(std::vector<Edge> fk, Edge x) {
    for (Edge f : fk) {
        if (f == x) {
            return true;
        }
    }
    return false;
}

void init() {
    for (int i = 0; i <= 2*n; i++) {
        edges[i].clear();
    }
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            insert(u, v);
        }
        bool flag = false;
        for (int i = 1; i <= n; i++) {
            for (Edge e : edges[i]) {
                Edge nxt = {e.from + n, e.to - n};
                bool p = find(edges[nxt.from], nxt);
                // printf("%d %d %d %d\n", p->from, nxt.from, p->to, nxt.to);
                if (e.from + n != e.to && p) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        if (flag) {
            puts("Merry");
        } else {
            puts("Renko");
        }
    }
    return 0;
}