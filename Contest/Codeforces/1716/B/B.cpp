#include <cstdio>
#include <vector>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        static std::vector<int> v;
        v.clear();
        for (int i = 1; i <= n; i++) {
            v.push_back(i);
        }

        printf("%d\n", n);
        for (auto p : v) {
            printf("%d ", p);
        }
        puts("");
        for (int i = n - 1; i > 0; i--) {
            std::swap(v[i], v[i - 1]);
            for (auto p : v) {
                printf("%d ", p);
            }
            puts("");
        }
    }
    return 0;
}