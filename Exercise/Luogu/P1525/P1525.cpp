#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

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
    int a, b, c;
    bool operator < (Node b) const {
        return c < b.c;
    }
};

std::priority_queue<Node> q;

#define maxn 1000006

int aFA = 1000001, bFA = 1000002;

int b[maxn];

struct union_find_set {
    #define min(x, y) (((x) < (y)) ? (x) : (y))
    int fa[maxn];
    void init(int n) {
        for (int i = 0; i <= min(maxn, n); i++) {
            fa[i] = i;
        }
        fa[aFA] = aFA; fa[bFA] = bFA;
    }
    int find(int x) {
        return fa[x] == x ? x : (fa[x] = find(fa[x]));
    }
    void uni(int x, int y) {
        fa[find(x)] = find(y);
    }
    int tot(int n) const {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += (i == fa[i]);
        }
        return ans;
    }
}ufs;

int solve() {
    while (!q.empty()) {
        Node top = q.top(); q.pop();
        if (ufs.find(top.a) == ufs.find(top.b)) {
            return top.c;
        } else {
            if (!b[top.a]) b[top.a] = top.b;
            else ufs.uni(b[top.a], top.b);
            if (!b[top.b]) b[top.b] = top.a;
            else ufs.uni(b[top.b], top.a);
        }
    }
    return 0;
}

int main() {
    int n, m;
    read(n, m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        read(a, b ,c);
        q.push({a, b, c});
    }
    ufs.init(n + 10);

    int ans = solve();
    printf("%d\n", ans);
    return 0;
}
