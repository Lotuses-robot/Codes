#include <cstdio>
using namespace std;
int n;
int a[100];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (i > 1 && a[i] < a[i - 1])
            ans = i;
        while (ans < n && a[i] >= a[ans + 1])
            ++ans;
        printf("%d\n", ans);
    }
    return 0;
}
