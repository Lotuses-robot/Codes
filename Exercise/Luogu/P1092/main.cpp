// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <cstdlib>
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

char a[30], b[30], c[30];
int t[300], vis[30], p[30], u[30], y;
int n;

bool check() {
    for (int i = n; i >= 1; i--) {
        if (t[a[i]] == -1 || t[b[i]] == -1 || t[c[i]] == -1)
            continue;
        if ((t[a[i]] + t[b[i]]) % n != t[c[i]]) {
            if ((t[a[i]] + t[b[i]] + 1) % n != t[c[i]])
                return 0;
        }
    }
    return 1;
}
void tr() {
    int jw = 0;
    for (int i = n; i >= 1; i--) {
        int s = t[a[i]] + t[b[i]] + jw;
        if (t[c[i]] != s % n)
            return;
        jw = s / n;
    }
    printf("%d", t['A']);
    for (int i = 'A' + 1; i <= 'A' + n - 1; i++)
        printf(" %d", t[i]);
    exit(0);
}
void dfs(int now) {
    if (now > n) {
        tr();
        return;
    }
    for (int i = n - 1; i >= 0; i--) {
        if (vis[i])
            continue;
        t[p[now] + 'A' - 1] = i;
        if (check()) {
            vis[i] = 1;
            dfs(now + 1);
            vis[i] = 0;
        }
    }
    t[p[now] + 'A' - 1] = -1;
}
int main() {
    memset(t, -1, sizeof(t));
    read(n);
    scanf("%s%s%s", a + 1, b + 1, c + 1);
    for (int i = n; i >= 1; i--) {
        if (!u[a[i] - 'A' + 1])
            p[++y] = a[i] - 'A' + 1, u[a[i] - 'A' + 1] = 1;
        if (!u[b[i] - 'A' + 1])
            p[++y] = b[i] - 'A' + 1, u[b[i] - 'A' + 1] = 1;
        if (!u[c[i] - 'A' + 1])
            p[++y] = c[i] - 'A' + 1, u[c[i] - 'A' + 1] = 1;
    }
    dfs(1);
    return 0;
}
