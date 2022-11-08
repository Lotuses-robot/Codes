#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

const int M = 1 << 21;

int dp[2][M];
int map[22][22], n;
int status[M], ct;
int top;

void Init() {
    ct = 0;
    for (int i = 0; i < M; i++) {
        if (i & (i << 1))
            continue;
        status[ct++] = i;
    }
}

int getsum(int i, int x) {
    int sum = 0, t = n;
    while (x) {
        if (x & 1)
            sum += map[i][t];
        x = x >> 1;
        t--;
    }
    return sum;
}

void solve() {
    memset(dp, -1, sizeof(dp));
    for (int i = 0; status[i] < top; i++) {
        dp[0][i] = getsum(1, status[i]);
    }
    for (int i = 2; i <= n; i++)
        for (int j = 0; status[j] < top; j++) {
            for (int k = 0; status[k] < top; k++)
                if (dp[i & 1][k] != -1 && (!(status[k] & status[j])))
                    dp[(i + 1) & 1][j] =
                            max(dp[(i + 1) & 1][j], dp[i & 1][k] + getsum(i, status[j]));
        }
    int maxn = -9999;
    for (int i = 0; status[i] < top; i++)
        if (dp[(n + 1) & 1][i] > maxn)
            maxn = dp[(n + 1) & 1][i];
    printf("%d\n", maxn);
}

int main() {
    Init();
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                scanf("%d", &map[i][j]);
        top = 1 << n;
        solve();
    }
    return 0;
}