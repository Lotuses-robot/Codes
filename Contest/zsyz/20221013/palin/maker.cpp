// Copyright 2022 Lotuses
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

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

char np[1145][1145];

int main() {
    srand(time(NULL));
    freopen("palin.in", "w", stdout);

    int n = 10, m = 10;

    printf("%d %d\n", n, m);

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m; j++) {
            np[i][j] = rand() % 26 + 'a';
            np[n - i - 1][m - j - 1] = np[i][j];
        }
        puts(np[i]);
    }

    for (int i = n / 2; i < n; i++) {
        puts(np[i]);
    }
    return 0;
}
