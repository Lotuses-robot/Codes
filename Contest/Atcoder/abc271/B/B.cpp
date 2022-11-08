#include <cstdio>
#include <vector>

std::vector<int> v[200005];

int main() {
    int n, q, l, x;
    scanf("%d%d", &n, &q);

    for (int i = 0; i < n; i++) {
        scanf("%d", &l);
        for (int j = 0; j < l; j++) {
            scanf("%d", &x);
            v[i].push_back(x);
        }
    }

    while (q--) {
        int s, t;
        scanf("%d%d", &s, &t);
        printf("%d\n", v[s - 1][t - 1]);
    }
    return 0;
}