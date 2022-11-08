#include <iostream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
int main()
{
    freopen("P4170.in", "r", stdin);
    freopen("P4170.out.std", "w", stdout);
    int n, i, j, k, l, t, dp[60][60];
    char s[60];
    scanf("%s", s);
    n = strlen(s);
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < 26; ++j)
        {
            dp[i][i] = 1;
        }
    }
    for (l = 1; l < n; ++l)
    {
        for (i = 0; i + l < n; ++i)
        {
            if (s[i] == s[i + l])
            {
                dp[i][i + l] = dp[i][i + l - 1];
            }
            else
            {
                dp[i][i + l] = dp[i][i] + dp[i + 1][i + l];
                for (k = i + 1; k < i + l; ++k)
                {
                    dp[i][i + l] = min(dp[i][i + l], dp[i][k] + dp[k + 1][i + l]);
                }
            }
        }
    }
    printf("%d", dp[0][n - 1]);
    return 0;
}