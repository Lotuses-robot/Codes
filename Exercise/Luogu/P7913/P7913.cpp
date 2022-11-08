#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

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

struct Node {
    int prev, nxt;
    bool operator < (Node b) const {
        return prev < b.prev;
    }
};

int m[2];
Node mm[2][114514];
int st[2][114514];
int ans[2][114514];

std::priority_queue<std::pair<int, bool>, std::vector<std::pair<int, bool> >, std::greater<std::pair<int, bool> > > q;
void init(int id) {
    for (int i = 0; i < m[id]; i++) {
        read(mm[id][i].prev, mm[id][i].nxt);
        q.push(std::make_pair(mm[id][i].prev, true));
        q.push(std::make_pair(mm[id][i].nxt, false));
    }
    // std::sort(mm[id], mm[id] + m[id]);

    int nowi = 0, nowPlane = 0;
    while (!q.empty()) {
        auto t = q.top(); q.pop();
        printf("debug %d %d\n", t.first, t.second);

        if (!t.second) {
            nowPlane--;
        } else {
            st[id][nowi++] = ++nowPlane;
        }
    }

    for (int i = 0; i < m[id]; i++) {
        printf("%d ", st[id][i]);
        ans[id][st[id][i]]++;
    }
    puts("");

    for (int i = 1; i < 100005; i++) {
        ans[id][i] += ans[id][i - 1];
    }
}

int main() {
    int n;
    read(n, m[0], m[1]);
    
    init(0);
    init(1);

    for (int i = 0; i <= n; i++) {
        printf("%d ", ans[0][i]);
    }
    puts("");

    int maxn = -1145141919;
    for (int i = 0; i <= n; i++) {
        int j = n - i;
        maxn = std::max(maxn, ans[0][i] + ans[1][j]);
    }

    printf("%d\n", maxn);
    return 0;
}
