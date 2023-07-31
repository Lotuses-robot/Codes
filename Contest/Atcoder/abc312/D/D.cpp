#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5005, mod = 998244353;

int n, f[N][N];

int main()
{
    string s;
    cin >> s;
    n = s.size();

    f[0][0] = 1;
    for (int i = 1; i <= n; i ++ )
        for (int j = 0; j <= i; j ++ )
            if (s[i - 1] == '(')
                f[i][j] = j ? f[i - 1][j - 1] : 0;
            else if (s[i - 1] == ')')
                f[i][j] = f[i - 1][j + 1];
            else {
                if (j >= 1) f[i][j] += (f[i - 1][j - 1]);
                f[i][j] += f[i - 1][j + 1];
                f[i][j] %= mod;
            }

    cout << f[n][0] << endl;

    return 0;
}