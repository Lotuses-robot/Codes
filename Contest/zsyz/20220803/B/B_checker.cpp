#include <cstdio>
#include <vector>

int minn = 1145141919;
std::vector<int> ans;
int p;
const int levelLimit = 20;

void dfs(int id, int kth, std::vector<int> v, int level) {
    if (level >= levelLimit) return;
    if (id == p) {
        if (kth < minn) {
            ans = v;
            minn = kth;
        }
    }
    auto v1 = v; v1.push_back(id + kth);
    dfs(id + kth, kth + 1, v1, level + 1);
    
    auto v2 = v; v2.push_back(id - 1);
    dfs(id - 1, kth + 1, v2, level + 1);
}

int main() {
    while (true) {
        scanf("%d", &p);
        minn = 1145141919;
        dfs(0, 1, std::vector<int>(), 0);
        printf("tot: %d\n", minn - 1);
        for (auto x : ans) {
            printf("%d ", x);
        }
        puts("");
    }
    return 0;
}