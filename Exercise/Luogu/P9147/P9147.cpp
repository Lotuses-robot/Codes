#include <bits/stdc++.h> // only for test
using namespace std;

inline int read() {
    int num = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            sign = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        num = (num << 3) + (num << 1) + (ch ^ 48), ch = getchar();
    return num * sign;
}

const int N = 1e6 + 7;
int dp[N], a[N], n, g[N];
signed main() {
    n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= n; i++) {
        if (a[i] > a[i - 1])
            dp[i] = dp[i - 1] + 1;
        else
            dp[i] = 1;
    }
    for (int i = n; i >= 1; i--) {
        if (a[i] < a[i + 1])
            g[i] = g[i + 1] + 1;
        else
            g[i] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] + 1 < a[i + 2]) {
            ans = max(ans, dp[i] + 1 + g[i + 2]);
        } else if (i == n)
            ans = max(ans, dp[i]);
        else
            ans = max(ans, max(dp[i - 1] + 1, g[i + 1] + 1));
    }
    ans = max(ans, g[2] + 1);
    cout << ans << endl;
    return 0;
}