// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>

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

const int N = 1e5 + 7232;
int t, n;
int a[N], s[N], tot[N];

int main() {
    #ifdef LOCAL
        freopen(".in", "r", stdin);
        freopen(".out", "w", stdout);
    #endif
    scanf("%d", &t);
    while (t--) {
        memset(tot, 0, sizeof(tot));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            s[i] = a[i] - a[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            if (s[i] > 0) continue;
            tot[a[i - 1]] = i;
        }
        for (int i = 1; i <= n; i++)
            if (!tot[i])
                tot[i] = 1;
        for (int i = 1; i <= n; i++)
            printf("%d ", tot[i]);
        puts("");
    }
    return 0;
}
