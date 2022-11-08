#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 2e9 + 10, N = 2e5 + 10;
int lo[30001], le;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        le = 0;
        string s1, s2;
        int n, x, y;
        cin >> n >> x >> y >> s1 >> s2;
        s1 = " " + s1;
        s2 = " " + s2;
        for (int i = 1; i <= n; i++)
            if (s1[i] != s2[i])
                lo[++le] = i;
        if (le % 2)
            cout << "-1\n";
        else if (le == 2 && lo[1] + 1 == lo[2])
            cout << min(x, 2 * y) << "\n";
        else {
            long long ans = le / 2;
            ans *= y;
            cout << ans << "\n";
        }
    }
    return 0;
}