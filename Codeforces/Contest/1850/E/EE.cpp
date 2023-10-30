#include <iostream>
#include <cmath>

const int MAXN = 1000000;
int cnt[MAXN + 1];

void init() {
    for (int i = 1; i <= MAXN; ++i) {
        for (int j = i; j <= MAXN; j += i) {
            ++cnt[j];
        }
    }
}

int main() {
    init();

    int n;
    std::cin >> n;

    int maxCnt = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        int q;
        std::cin >> q;
        if (cnt[q] > maxCnt) {
            maxCnt = cnt[q];
            ans = q;
        }
    }

    std::cout << ans << std::endl;

    return 0;
}