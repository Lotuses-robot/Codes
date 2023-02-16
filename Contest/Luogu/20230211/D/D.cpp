#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int n, m;
int x[N], a[N];
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(make_pair(a[i], x[i]));
    }
    sort(vec.begin(), vec.end());
    int now = vec[n - 1].second;
    for (int i = n - 2; i >= 0; i--)
    {
        if (now >= vec[i].second)
        {
            now = vec[i].second;
        }
        else
        {
            now = (now + vec[i].second) / 2;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << now << " ";
        now = vec[i].second;
    }
    return 0;
}
