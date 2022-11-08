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

int a[114514];
int c[114514];
bool flag = false;
int n, m;

void dfs(int step, int sum) {
    if (step >= n) {
        if (sum == 0) {
            flag = true;
        }
        return;
    }
    c[step] = 1;
    dfs(step + 1, sum + a[step] * c[step]);
    if (flag) return;
    c[step] = -1;
    dfs(step + 1, sum + a[step] * c[step]);
    if (flag) return;
}

int main() {
    freopen("chaoticevil.in", "r", stdin);
    freopen("chaoticevil.out", "w", stdout);
    read(n, m);

    if (n > 20) goto fail;

    for (int i = 0; i < n; i++) {
        read(a[i]);
    }

    dfs(0, 0);

    if (flag) {
        puts("NP-Hard solved");
        for (int i = 0; i < n; i++) {
            printf("%d ", c[i]);
        }
    } else {
        fail: puts("Chaotic evil");
    }
    return 0;
}
