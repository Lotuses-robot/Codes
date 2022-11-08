#include <cstdio>

#define MOD (int)(1e9 + 7)

bool end[114514];
int f[114514];

int dfs(int cur) {
    if (cur == 0) return 1;
    if (end[cur]) return 0;
    if (f[cur]) return f[cur];
    return f[cur] = (dfs(cur - 1) + dfs(cur - 2)) % MOD;
}

int main() {
    freopen("stairs.in", "r", stdin);
    freopen("stairs.out", "w", stdout);

    int n, m, k;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &k);
        end[k] = true;
    }

    printf("%d\n", dfs(n));
    return 0;
}