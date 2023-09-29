#include <bits/stdc++.h>

using namespace std;

unordered_map<int, unordered_map<int, bool> > um;
int main() {
    freopen(".in", "w", stdout);
    cout << 100000 << ' ' << 500000 << '\n';
    int idx = 0;
    for (int i = 2; i <= 100000; i++) cout << 1 << ' ' << i << '\n', um[1][i] = um[i][1] = true, idx++;
    for (int i = idx + 1; i <= 500000; i++) {
        int u = rand() % 100000 + 1, v = rand() % 100000 + 1;
        while (u == v || um[u][v]) u = rand() % 100000 + 1, v = rand() % 100000 + 1;
        um[u][v] = um[v][u] = true;
        cout << u << ' ' << v << '\n';
    }
    return 0;
}
