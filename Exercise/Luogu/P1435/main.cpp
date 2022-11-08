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

char ch[1145];
int f[1145][1145];

int main() {
    int n;
    scanf("%s", ch + 1);
    n = strlen(ch + 1);

    memset(f, 63, sizeof(f));

    for (int l = 1; l <= n; l++) {
        for (int r = n; r >= l - 1; r--) {
            if (l == 1 && r == n) {
                f[l][r] = 0;
            } else {
                f[l][r] = std::min(f[l - 1][r], f[l][r + 1]) + 1;
                if (ch[l - 1] == ch[r + 1]) {
                    f[l][r] = std::min(f[l][r], f[l - 1][r + 1]);
                }
            }
        }
    }

    int ans = f[1][1];
    for (int i = 2; i <= n; i++) {
        ans = std::min(ans, f[i][i - 1]);
        ans = std::min(ans, f[i][i]);
    }
    printf("%d\n", ans);
    return 0;
}
