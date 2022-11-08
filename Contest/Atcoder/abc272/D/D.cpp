#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define gc getchar()
template<typename T>
void read(T &r) {
    r = 0; static char ch, last;
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) {
    read(arg);
    read(arg_left...);
}

double sqrt(double a) {
    double t = 1;
    for (int i = 1; i <= 10; i++) {
        t = (t + a / t) / 2;
    }
    return t;
}

int gx[4] = {1, 1, -1, -1},
    gy[4] = {-1, 1, -1, 1},
    gox = -1, goy = -1;

bool vis[1145][1145];

int ans[1145][1145];

struct Node {
    int x, y;
};

std::queue<Node> q;

void bfs() {
    ans[1][1] = 0;
    vis[1][1] = false;
    q.push({1, 1});
    
    while (!q.empty()) {
        Node nd = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int px = gx[i] * gox, py = gy[i] * goy;
            Node p = {nd.x + px, nd.y + py};
            if (p.x < 0 || p.y < 0 || !vis[p.x][p.y]) goto st;
            vis[p.x][p.y] = false;
            ans[p.x][p.y] = ans[nd.x][nd.y] + 1;
            q.push(p);


            st:;

            std::swap(px, py);
            p = {nd.x + px, nd.y + py};
            if (p.x < 0 || p.y < 0 || !vis[p.x][p.y]) continue;
            vis[p.x][p.y] = false;
            ans[p.x][p.y] = ans[nd.x][nd.y] + 1;
            q.push(p);
        }
    }
}

int main() {
    int n, m;
    read(n, m);

    for (int i = 0; i <= m; i++) {
        int l = sqrt(i) + 0.00001;
        int r = sqrt(m - i) + 0.00001;
        if (l * l == i && r * r == m - i) {
            gox = l;
            goy = r;
            break;
        }
    }
    // printf("%d %d\n", gox, goy);

    if (gox == -1 || goy == -1) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) printf("0 ");
                else printf("%d ", -1);
            }
            puts("");
        }
        return 0;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            vis[i][j] = true;
        }
    }
    bfs();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", ans[i][j]);
        }
        puts("");
    }
    return 0;
}
