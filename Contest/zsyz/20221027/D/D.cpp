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

int dist[100001];
int point[100001][30];

#define abs(x) ((x) < 0 ? -(x) : (x))

int dis(int x, int y) {
    int ans = 0;
    for (int i = 0; i < 30; i++) {
        ans += abs(point[x][i] - point[y][i]);
    }
    return ans;
}

int main() {
    freopen("D.in", "r", stdin);
    freopen("D.out", "w", stdout);
    int n, m;
    read(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            read(point[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[dis(i, j)]++;
        }
    }

    for (int i = 0; i <= 3 * m; i++) {
        printf("%d ", dist[i]);
    }
    puts("");
    return 0;
}
