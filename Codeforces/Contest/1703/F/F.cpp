#include <cstdio>
#include <vector>
#include <algorithm>

struct Node {
    int id, val;
    bool operator < (const Node b) const {
        return val < b.val;
    }
};

std::vector<Node> v;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        v.clear();
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            if (x < i) {
                v.push_back({i, x});
            }
        }

        long long ans = 0;
        std::sort(v.begin(), v.end());
        for (auto u : v) {
            auto it = std::upper_bound(v.begin(), v.end(), (Node){-114514, u.id});
            ans += v.end() - it;
        }
        printf("%lld\n", ans);
    }
    return 0;
}