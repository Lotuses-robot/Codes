// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define gc getchar()
template<typename T>
void read(T &r) { // NOLINT
    r = 0; static char ch, last; // NOLINT
    ch = gc, last = 'z';
    while (ch < '0' || ch > '9') last = ch, ch = gc;
    while (ch >= '0' && ch <= '9') r = (r << 1) + (r << 3) + (ch ^ 48), ch = gc;
    r = (last == '-') ? -r : r;
}

template<typename T, typename...Ts>
void read(T &arg, Ts&...arg_left) { // NOLINT
    read(arg);
    read(arg_left...);
}

char n[100];
int k;

std::vector<int> v[100];
int ch[100];
bool vis[100];
int ansbuf[100];

int dfs(int pt) {
    if (vis[pt]) return 0;
    vis[pt] = true;
    int ans = 1;
    for (int u : v[pt]) {
        ans += dfs(u);
    }
    return ans;
}

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif

    scanf("%s", n); read(k);
    for (int i = 0; i < k; i++) {
        int q, p; read(q, p);
        v[q].push_back(p);
    }

    for (int i = 0; i < 10; i++) {
        std::sort(v[i].begin(), v[i].end());
        std::unique(v[i].begin(), v[i].end());
    }

    for (int i = 0; i < 10; i++) {
        memset(vis, 0, sizeof(vis));
        ch[i] = dfs(i);
    }

    __int128 ans = 1;
    for (int i = 0, len = strlen(n); i < len; i++) {
        ans *= ch[n[i] - '0'];
    }
    
    int len = 0;
    do ansbuf[len++] = ans % 10; while (ans /= 10);
    for (int i = len - 1; i >= 0; i--) {
        printf("%d", ansbuf[i]);
    }
    puts("");
    return 0;
}
