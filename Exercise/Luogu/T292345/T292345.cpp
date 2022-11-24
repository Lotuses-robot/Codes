// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

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

int a[114514];
struct Node {
    int a1, a2;
    bool operator < (Node b) const {
        return a1 > b.a1;
    }
};
std::vector<Node> v;
std::queue<Node> q;
int T[100010];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    int n, k;
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    
    while (k--) {
        int p;
        read(p);
        for (int i = 1; i < p; i++) {
            v.push_back({a[i], 1});
        }
        for (int i = p, od = 1; i <= n; i++, od++) {
            v.push_back({a[i], od});
        }
        std::sort(v.begin(), v.end());
        v.insert(v.begin(), {0, 0});
        for (int i = 1; i <= n; i++) {
            q.push(v[i]);
        }

        memset(T, -63, sizeof(T));
        int ans1 = 0, ans2 = 0;
        for (int i = 1; i <= n; i++) {
            int nowAns = T[i]; T[i] = 0;
            if (nowAns >= 0) {
                goto tot;
            }
            while (!q.empty()) {
                Node nd = q.front(); q.pop();
                if (nd.a1 <= nowAns) break;
                if (nd.a2 > i) {
                    T[nd.a2] = nd.a1;
                } else {
                    nowAns = nd.a1;
                    break;
                }
            }
            tot:if (i & 1) ans1 += nowAns;
            else ans2 += nowAns;
        }

        printf("%d\n", ans1);
        while (!q.empty()) q.pop();
        v.clear();
    }
    return 0;
}
