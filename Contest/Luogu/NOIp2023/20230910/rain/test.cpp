#include <iostream>
#include <cstdlib>
using namespace std;

int n;
int d[int(1e6 + 5)];

int find(int L, int R, int k) {
    int x = rand() % (R - L + 1) + L;
    swap(d[L], d[x]);
    int a = L + 1, b = R;
    while (a < b) {
        while (a < b && d[a] < d[L])
            ++a;
        while (a < b && d[b] >= d[L])
            --b;
        swap(d[a], d[b]);
    }
    if (d[a] < d[L])
        ++a;
    if (a - L == k)
        return d[L];
    if (a - L < k)
        return find(a, R, k - (a - L));
    return find(L + 1, a - 1, k);
}

int main() {
    freopen(".in", "r", stdin);
    int k;
    cin >> n;
    cin >> k;
    for (int i = 0; i < n; ++i)
        cin >> d[i];
    cout << find(0, n - 1, n);
    return 0;
}              

