// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; char ch, last; // NOLINT
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

struct Node {
    int x, y;
    bool operator < (Node b) const {
        if (x != b.x) return x > b.x;
        return y > b.y;
    }
};
std::vector<Node> nd;
int T, n;
struct Int {
    int x;
    bool operator < (Int b) const {
        return x < b.x;
    }
};
std::priority_queue<Int> q;

int calc() {
    while (!q.empty()) q.pop();
    std::sort(nd.begin(), nd.end());
    int tot = 0, x = -1, i;
    for (i = 0; i < n; i++) {
        x = nd[i].x; tot++;
        q.push({nd[i].y});
        i++;
        while (i < n && nd[i].x == x) {
            q.push({nd[i].y});
            i++; tot++;
        }
        if (tot >= n / 2) break;
        i--;
    }
    // i++;
    if (tot == n / 2) return 2;
    for (i; i < n; i++) {
        int y;
        while (tot > n / 2) {
            y = q.top().x; q.pop(); tot--;
            while (q.top().x == y) q.pop(), tot--;
        }
        if (tot == n / 2) return 3;
        for (i; i < n; i++) {
            x = nd[i].x;
            if (nd[i].y <= q.top().x) tot++, q.push({nd[i].y});
            i++;
            while (i < n && nd[i].x == x) {
                if (nd[i].y <= q.top().x) tot++, q.push({nd[i].y});
                i++;
            }
            if (tot >= n / 2) break;
            i--;
        }
        i--;
        if (tot == n / 2) return 3;
    }
    return 4;
}

int main() {
    #ifdef LOCAL
        freopen("2.in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    
    read(T);
    while (T--) {
        static int cnt = 0;
        cnt++;
        read(n);
        for (int i = 0; i < n; i++) {
            int x, y;
            read(x, y);
            // if (cnt == 11)
            // printf("%d %d\n", x, y);
            nd.push_back({x, y});
        }

        int ans1 = calc();

        for (int i = 0; i < n; i++) {
            std::swap(nd[i].x, nd[i].y);
        }

        int ans2 = calc();
        printf("%d\n", std::min(ans1, ans2));
        nd.clear();
    }
}
