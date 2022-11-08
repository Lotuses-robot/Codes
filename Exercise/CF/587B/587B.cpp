// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

#define int long long

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

int a[200005];
int n, k, x;
int dfs(int u, int lst, int s) {
    if (u == n) {
        return s;
    }
    int ans = -1;
    for (int i = -1; i < lst; i++) {
        ans = std::max(ans, dfs(u + 1, lst - (i + 1), s | a[u]));
        a[u] *= x;
    }
    for (int i = -1; i < lst; i++) {
        a[u] /= x;
    }
    return ans;
}

signed main() {
    read(n, k, x);
    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    printf("%lld\n", dfs(0, k, 0));
    return 0;
}
