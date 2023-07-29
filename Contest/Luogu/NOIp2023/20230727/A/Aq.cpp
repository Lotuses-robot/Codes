#include <bits/stdc++.h>
using namespace std;

inline unsigned long long Max(unsigned long long a, unsigned long long b) {
    return a > b ? a : b;
}
inline unsigned long long Min(unsigned long long a, unsigned long long b) {
    return a < b ? a : b;
}

int c, n, t;
int x[905], y[905], a[35][35];
unsigned long long ans, g[905], w[905], m, p;
priority_queue<pair<unsigned long long, int>> pq;

void dfs(int fx, int fy) {
    while (pq.size())
        pq.pop();
    unsigned long long res(0);
    for (int i(1); i <= c; i++) {
        int xx = abs(x[i] - fx) + abs(y[i] - fy);
        long long qwq = (1ll << xx);
        if (qwq > p)
            continue;
        if (!w[i]) {
            unsigned long long ww = Min(g[i], m);
            if (!ww)
                continue;
            pq.push(make_pair(ww, i));
            g[i] -= ww;
            ww = Min(g[i], m);
            if (ww)
                pq.push(make_pair(ww, i));
            continue;
        }
        unsigned long long ww = Min(Min((p - qwq) / w[i], g[i]), m);
        if (!ww)
            continue;
        pq.push(make_pair(ww, i));
        g[i] -= ww;
        ww = Min(Min((p - qwq) / w[i], g[i]), m);
        if (ww)
            pq.push(make_pair(ww, i));
    } // puts("qwq");
    for (int i(1); i <= t; i++) {
        if (pq.empty())
            break;
        res += pq.top().first;
        pq.pop();
    }
    ans = Max(ans, res);
    return;
}

int main() {
    // scanf("%d%d%llu%llu%d",&c,&n,&m,&p,&t);
    cin >> c >> n >> m >> p >> t;
    if (!m || !p || !c || !t)
        return puts("0"), 0;
    for (int i = 1; i <= c; ++i) {
        // scanf("%d%d%llu%llu",x+i,y+i,g+i,w+i);
        cin >> x[i] >> y[i] >> g[i] >> w[i];
        a[x[i]][y[i]] = 1;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (!a[i][j])
                dfs(i, j);
    cout << ans;
    return 0;
}