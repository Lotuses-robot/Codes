#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
int a[N];
int f[N];
int n, k;
 
void solve()
{
    cin >> n >> k;
    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        f[i] = 0;
        cin >> a[i];
        if (a[i] == i && k != 1)
            flag = 1;
        if (k == 1 && a[i] != i)
            flag = 1;
    }
    if (flag == 1)
    {
        cout << "NO" << "\n";
        return;
    }
    else if (k == 1)
    {
        cout << "YES" << "\n";
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (f[i] == 0)
        {
            int ind = i;
            while (f[ind] == 0)
            {
                f[ind] = i;
                ind = a[ind];
            }
            if (f[ind] == i)
            {
                int tmp = a[ind], cnt = 1;
                while (tmp != ind)
                {
                    cnt++;
                    tmp = a[tmp];
                }
                if (cnt != k)
                {
                    cout << "NO" << "\n";
                    return;
                }
            }
        }
    }
    cout << "YES" << "\n";
    return;
}
 
int main()
{
    freopen(".in", "r", stdin);
    freopen(".ans", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}